//
// A simple program that uses ICM communication and
// Qu-Prolog term encoding/decoding.
//
// To use start this process
// ./ccicm
// and in another window start qp as follows
// qp -Afoo
// In the qp interpreter send messages to ccicm as follows
// "hello" +>> '':ccicm.
// which sends hello as a normal string - then
// M <<- A.
// should recieve the echoed message from ccicm.
// [f(a),b,4] ->> '':ccicm.
// sends the encoded term to ccicm and
// M <<- A.
// should receive the term [f(a,b), 3]
//
// NOTE : The encode/decode classes do not process other 
// Qu-Prolog terms such as variables, object variables,
// substitution terms or quantified terms.
//

#include <sys/select.h>

#include "encode.h"
#include "icm_env.h"

//
// Parse and display the compressed term stored in the EncodeRead object
//
void show_compressed_term(EncodeRead& er)
{
  // Switch on the type of the term
  switch (er.encodeReadChar())
    {
    case EncodeMap::ENCODE_LIST :
      {
	// A list is a pair of terms - the head of the list
	// and the tail of the list
	cout << "List Head: "<< endl;
	show_compressed_term(er);
	cout << "List Tail: " << endl;
	show_compressed_term(er);
	return;
	break;
      }
    case EncodeMap::ENCODE_STRUCTURE :
      {
	// An encoded structure is
	// the arity (as an integer)
	// the functor
	// the arguments
	int arity =  er.encodeReadNumber();
	cout << "Structure - Functor :" << endl;
	show_compressed_term(er);
	cout << "Structure - Arity : " << arity << endl;
	for (int i = 1; i <= arity; i++)
	  {
	    cout << "Arg " << i << " :" << endl;
	    show_compressed_term(er);
	  }
	return;
	break;
      }
    case EncodeMap::ENCODE_ATOM_REF :
      {
	// An atom reference - an offset into a map table
	// containing the string representation of an
	// atom that occurred before in the term.
	cout << "Atom: " << *(er.encodeReadRef()) << endl;
	return;
	break;
      }
    case EncodeMap::ENCODE_ATOM :
      {
	// An atom is a string
	cout << "Atom: "<< *(er.encodeReadString()) << endl;
	return;
	break;
      }
    case EncodeMap::ENCODE_INTEGER :
      {
	// An integer
	cout << "Integer: "<< er.encodeReadNumber() << endl;
	return;
	break;
      }
      default:
	cout << "Can't decode" << endl;
	exit(0);
	break;
      }
}

int main(int argc, char *argv[])
{
  // Connect to ICM naming this process ccicm
  // and using the default ICM server port and IP address
  ICMEnvironment* icm_env = new ICMEnvironment("ccicm", 0, NULL);
  // Set the handle (i.e. address of this process -
  // Handles are usually threadname:processname but for non-QP
  // processes the thread name is null
  string my_handle = ":ccicm";
  
  //
  // Process messages until "quit" recieved
  //
  while (true)
    {
      // Use select to block until message arrives
      fd_set icmfd;
      FD_ZERO(&icmfd);
      FD_SET(icm_env->getCommFD(), &icmfd);
      select(icm_env->getCommFD()+1, &icmfd, NULL, NULL, NULL);
      while (icm_env->msgAvail())
	{
	  // process messages  
	  bool compressed;
	  string msg;
	  string sender;
	  string reply_to;
	  // Get a message
	  icm_env->getMsg(compressed, msg, sender, reply_to);
	  cout << "Message from: " << sender << endl;
	  if (compressed)
	    {
	      // The message is compressed - so set up a decoder object
	      // and display the term
	      EncodeRead er(msg);
	      show_compressed_term(er);
	      // Construct the compressed representation of the
	      // term [f(a,b), 3] and send that to sender
	      EncodeWrite ew;
	      ew.encodeWriteChar(EncodeMap::ENCODE_LIST);
	      ew.encodeWriteChar(EncodeMap::ENCODE_STRUCTURE);
	      ew.encodeWriteNumber(2);
	      ew.encodeWriteChar(EncodeMap::ENCODE_ATOM);
	      ew.encodeWriteString("f");
	      ew.encodeWriteChar(EncodeMap::ENCODE_ATOM);
	      ew.encodeWriteString("a");
	      ew.encodeWriteChar(EncodeMap::ENCODE_ATOM);
	      ew.encodeWriteString("b");
	      ew.encodeWriteChar(EncodeMap::ENCODE_LIST);
	      ew.encodeWriteChar(EncodeMap::ENCODE_INTEGER);
	      ew.encodeWriteNumber(3);
	      ew.encodeWriteChar(EncodeMap::ENCODE_ATOM);
	      ew.encodeWriteString("[]");
	      icm_env->sendMsg(true, ew.getString(), sender, my_handle);
	    }
	  else
	    {
	      // The message is a normal string
	      cout << msg << endl;
	      // Echo the message by sending back a normal string 
	      // (uncompressed) to sender
	      string reply = "echo ";
	      reply.append(msg);
	      icm_env->sendMsg(false, reply, sender, my_handle);
	      // Exit if quit message recieved
	      if (msg == string("quit"))
		{
		  // delete will deregister the process with ICM
		  // and break the connection
		  delete icm_env;
		  exit(0);
		}
	    }
	}
    }
}
  
  
