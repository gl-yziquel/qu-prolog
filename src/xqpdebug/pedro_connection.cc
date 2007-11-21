
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "pedro_connection.h"


// No DNS lookup - so use ifcofig to get IP
void getIPfromifconfig(char* ip)
{
  struct ifreq *ifr, ifr_tmp;
  struct ifconf ifc;
  char buf[1024];
  int s, i;
  struct sockaddr_in *sin;

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s == -1) {
    fprintf(stderr, "Can't open socket for ifconfig\n");
    exit(1);
  }

  ifc.ifc_len = sizeof(buf);
  ifc.ifc_buf = buf;
  ioctl(s, SIOCGIFCONF, &ifc);

  for (i = 0; i < ifc.ifc_len; ) {
    ifr = (struct ifreq *) &ifc.ifc_buf[i];
    sin = (struct sockaddr_in *) &ifr->ifr_addr;
    i += sizeof(struct ifreq);
    /* skip nulls */
    if (sin->sin_addr.s_addr == 0)
      continue;
    /* skip non AF_INET's */
    if (ifr->ifr_addr.sa_family != AF_INET)
      continue;

#ifdef SIOCGIFFLAGS
    memset(&ifr_tmp, 0, sizeof(ifr_tmp));
    strncpy(ifr_tmp.ifr_name, ifr->ifr_name, sizeof(ifr_tmp.ifr_name) - 1);
    if (ioctl(s, SIOCGIFFLAGS, (caddr_t) &ifr_tmp) < 0)
#endif
      ifr_tmp = *ifr;
    
    /* skip DOWN and loopback interfaces */
    if (((ifr_tmp.ifr_flags & IFF_UP) == 0) ||
          (ifr_tmp.ifr_flags & IFF_LOOPBACK))
      continue;

    close(s);
    strcpy(ip, inet_ntoa(sin->sin_addr));
    return;
  }
  close(s);
  return;
}


bool needsQuotes(string& str)
{
  if (str == "") return true;
  if ((str == "[]") || (str == ";")) return false;

  string::size_type pos = str.find_first_of("abcdefghijklmnopqrstuvwxyz");

  if (pos == 0) {
    pos = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789");
    return (pos != string::npos);
  }
  return (str.find_first_not_of("#$&*+-./:<=>?@^~\\") != string::npos);
}

void addQuotes(string& str)
{
  if (needsQuotes(str)) {
    str.append("'");
    str.insert(0, "'");
  }
}

PedroConnection::PedroConnection(string me, string other, 
				 int port, u_long ip) :
  my_address(me), other_address(other)
{
  addQuotes(my_address);
  addQuotes(other_address);
  ack_fd = (int)(::socket(AF_INET, SOCK_STREAM, 0));
  
  struct sockaddr_in add;
  memset((char *)&add, 0, sizeof(add));
  add.sin_family = AF_INET;
  add.sin_port = port;
  add.sin_addr.s_addr = ip;
  const int ret = connect(ack_fd, (struct sockaddr *)&add, sizeof(add));

  if (ret != 0) {
    if (errno == EINPROGRESS) {
      fd_set fds;
      
      FD_ZERO(&fds);
      FD_SET(ack_fd, &fds);
      select(ack_fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
    }
    else {
      cerr << "Failed to connect" << endl;
      exit(1);
    }
  }

  // now connected

  // set up for a connection from server
  const int sock = (int)(::socket(AF_INET, SOCK_STREAM, 0));
  struct sockaddr_in client;

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = ((u_long)INADDR_ANY);
  client.sin_port = htons(0);

  if (bind(sock, (struct sockaddr *) &client, sizeof(client)) != 0)
    { 
      close(sock);
      cerr << "Can't bind socket" << endl;
      exit(1);
    }

  /* get the port for this socket */
  struct sockaddr_in addr;
  socklen_t length = sizeof(struct sockaddr_in);

  if (getsockname(sock,(struct sockaddr *)&addr,&length) < 0)
    {
      fprintf(stderr, "Error: getsockname\n");
      exit(1);
    }
  int cport = ntohs(addr.sin_port);

  char hostname[1000];
  gethostname(hostname, 1000);

  hostent *hp = gethostbyname(hostname);
  if (hp == NULL)
    {
      // if we can't get host by name then try to use ifconfig
      strcpy(hostname, "127.0.0.1");
      getIPfromifconfig(hostname);
      host = hostname;
    }
  // if we can get the host then try to see if
  // we can get host by address from hp
  else {
      struct in_addr in;
      struct in_addr in_copy;
      in.s_addr = *(int*)(hp->h_addr);
      in_copy.s_addr = *(int*)(hp->h_addr);
      hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
      if (hp == NULL) 
        {
          // we can't look up name given address so just use dotted IP
          host = inet_ntoa(in_copy);
        } 
      else 
        {
          host = hp->h_name;
        }
  }
  addQuotes(host);
  /* get ready for server connection */
  if (listen(sock, 1) == -1) {
    fprintf(stderr, "Can't listen\n");
    exit(1);
  }

 /* send port to server so server can connect */
  ostringstream strm;
  strm << cport << "\n";
  string st = strm.str();
  int len = st.length();
  write(ack_fd, st.c_str(), len);

  struct sockaddr_in saddr;
  socklen_t slength = sizeof(struct sockaddr_in);
  data_fd = (int)(accept(sock, (struct sockaddr *) &saddr, &slength));
  /* server is now connected - this socket is used for data */
  if (data_fd < 0)
    {
      close(ack_fd);
      close(sock);
      cerr << "Can't accept" << endl;
      exit(1);
    }
  close(sock);

  strm.str("");
  strm << "register(" << my_address << ")\n";
  if (!send(strm.str())) {
    cerr << "Can't register" << endl;
    exit(1);
  }
}

bool 
PedroConnection::send(string s)
{
  size_t len = s.length();
  
  size_t num_written = write(data_fd, s.c_str(), len);
  
  while (num_written != len)
    {
      s.erase(0, num_written);
      fd_set fds;
      FD_ZERO(&fds);
      FD_SET(data_fd, &fds);
      select(data_fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
      assert(s.length() == (len - num_written));
      len = s.length();
      num_written = write(data_fd, s.c_str(), len);
    }
  return (get_ack() != 0);
}

int 
PedroConnection::get_ack()
{
  char buff[32];
  int size;
  int offset = 0;
  while (1) {
    size = recv(ack_fd, buff + offset, 30 - offset, 0);
    offset += size;
    if (offset > 25) {
      cerr << "Can't get ack" << endl;
      exit(1);
    }
    if (buff[offset-1] == '\n') {
      buff[offset] = '\0';
      break;
    }
  }
  return atoi(buff);
}

void addEscapes(string& str)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      switch ((int)c)
	{
	case 7:  // \a
	  tmp.push_back('\\');
	  tmp.push_back('a');
	  break;
	case 8:  // \b
	  tmp.push_back('\\');
	  tmp.push_back('b');
	  break;
	case 9:  // \t
	  tmp.push_back('\\');
	  tmp.push_back('t');
	  break;
	case 10:  // \n
	  tmp.push_back('\\');
	  tmp.push_back('n');
	  break;
	case 11:  // \v
	  tmp.push_back('\\');
	  tmp.push_back('v');
	  break;
	case 12:  // \f
	  tmp.push_back('\\');
	  tmp.push_back('f');
	  break;
	case 13:  // \r
	  tmp.push_back('\\');
	  tmp.push_back('r');
	  break;
	case 92:  
	  tmp.push_back('\\');
	  tmp.push_back('\\');
	  break;
	default:
	  if (c == '"')
	    {
	      tmp.push_back('\\');
	      tmp.push_back(c);
	    }
	  else
	      tmp.push_back(c);
	  break;
	}
    }
  str = tmp;
}

bool 
PedroConnection::send_p2p(string s)
{
  addEscapes(s);
  ostringstream strm;
  strm << "p2pmsg('':"
       << other_address
       << "@"
       << host
       << ", "
       << "'':"
       << my_address
       << "@"
       << host
       << ", \""
       << s
       << "\")\n";
  return send(strm.str());
}

bool 
PedroConnection::msgAvail()
{
      fd_set fds;
      timeval tv = { 0, 0 };
      FD_ZERO(&fds);
      FD_SET(data_fd, &fds);
      int ret = select(data_fd + 1, &fds, (fd_set *) NULL,  
			(fd_set *) NULL, &tv);
      if (ret == 1) {
	char buff[1101];
	ssize_t size = read(data_fd, buff, 1100);
	buff[size] = '\0';
	in.append(buff);
	return true;
      }
      return false;
}


void removeEscapes(string& str)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      if (c == '\\') {
	iter++;
	assert(iter != str.end());
	c = *iter;
	switch ((int)c)
	  {
	  case 'a': 
	    tmp.push_back('\a');
	    break;
	  case 'b':  
	    tmp.push_back('\b');
	    break;
	  case 't':  
	    tmp.push_back('\t');
	    break;
	  case 'n':  
	    tmp.push_back('\n');
	    break;
	  case 'v': 
	    tmp.push_back('\v');
	    break;
	  case 'f':  
	    tmp.push_back('\f');
	    tmp.push_back('f');
	    break;
	  case 'r': 
	    tmp.push_back('\r');
	    break;
	  case '\\':  
	    tmp.push_back('\\');
	    break;
	  default:
	    if (c == '"')
	      {
		tmp.push_back(c);
	      }
	    else
	      {
		assert(false);
	      }
	    break;
	  }
      }
      else {
	tmp.push_back(c);
      }
    }
  str = tmp;
}

bool
PedroConnection::getMsg(string& msg)
{
  size_t pos = in.find('\n');
  if (pos != string::npos)
    {
      string m = in.substr(0, pos + 1);
      in.erase(0, pos+1);
      size_t loc_quote1 = m.find('"');
      size_t loc_quote2 = m.find_last_of('"');
      msg =  m.substr(loc_quote1+1, loc_quote2 - loc_quote1 - 1);
      removeEscapes(msg);
      return true;
    }
  return false;
}
