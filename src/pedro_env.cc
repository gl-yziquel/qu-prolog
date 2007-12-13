
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#include "QuProlog.h"
#include "thread_table.h"
#include "scheduler.h"
#include "io_qp.h"
#include "thread_qp.h"

#include "pedro_env.h"
#include "pedro_token.h"
#include "write_support.h"
#include "objects.h"
#include "tcp_qp.h"

// Required global variables from QP
extern AtomTable* atoms;
extern ThreadTable *thread_table;
extern Scheduler *scheduler;

static const char* p2pmsg_string = "p2pmsg(";
static const char* stream_string = "''";

static const int p2pmsg_string_len = strlen(p2pmsg_string);

// Global variables for Pedro interface.
// static PedroMessageChannel* pedro_channel_ptr = NULL;


Object* parse_basic(Thread* th, AtomTable& atoms, VarMap& vmap, 
		    ObjectsStack& stk, bool remember);
Object* parse_prec50(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec200(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec400(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec500(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec700(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec1000(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember);
Object* parse_prec1050(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember);
Object* parse_prec1100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember);



static int curr_token_type = ERROR_TOKEN;
static Object* curr_token = NULL;

void next_token(Thread* th, AtomTable& atoms, VarMap& vmap, bool remember)
{
  curr_token_type = scanner(th, &atoms, &vmap, &curr_token, remember);
}



int parseargs(Thread* th, AtomTable& atoms, VarMap& vmap, 
	      ObjectsStack& stk, bool remember)
{
  int num = 0;
  Object* t = parse_prec700(th, atoms, vmap, stk, remember);
  assert(t != NULL);
  stk.push(t);
  num++;
  while (curr_token_type == COMMA_TOKEN) {
    next_token(th, atoms, vmap, remember);
    t = parse_prec700(th, atoms, vmap, stk, remember);
    assert(t != NULL);
    stk.push(t);
    num++;
  }
  return num;
}

Object* parse_basic(Thread* th, AtomTable& atoms, VarMap& vmap, 
		    ObjectsStack& stk, bool remember)
{
  switch (curr_token_type) {
  case ERROR_TOKEN:
  case NEWLINE_TOKEN:
  case CBRA_TOKEN:
  case CSBRA_TOKEN:
  case COMMA_TOKEN:
    assert(false);
    return NULL;
    break;
  case OBRA_TOKEN:
    {
      next_token(th, atoms, vmap, remember);
      Object* t = parse_prec1100(th, atoms, vmap, stk, remember);
      assert(curr_token_type == CBRA_TOKEN);
      next_token(th, atoms, vmap, remember);
      return t;
      break;
    }
  case OSBRA_TOKEN:
    {
      next_token(th, atoms, vmap, remember);
      if (curr_token_type == CSBRA_TOKEN)
	{
	  next_token(th, atoms, vmap, remember);
	  return AtomTable::nil;
	}
      Object* t = parse_prec700(th, atoms, vmap, stk, remember);
      assert(t != NULL);
      Cons* lst = th->TheHeap().newCons();
      lst->setHead(t);
      Cons* lst_tmp = lst;
      while (curr_token_type == COMMA_TOKEN) 
	{
	  next_token(th, atoms, vmap, remember);
	  t = parse_prec700(th, atoms, vmap, stk, remember);
	  assert(t != NULL);
	  Cons* tmp = th->TheHeap().newCons();
	  tmp->setHead(t);
	  lst_tmp->setTail(tmp);
	  lst_tmp = tmp;
	}
      lst_tmp->setTail(AtomTable::nil);
      assert(curr_token_type == CSBRA_TOKEN); 
      next_token(th, atoms, vmap, remember);
      return lst;
    }
    break;
  case TERM_TOKEN:
    {
      Object* t = curr_token;
      next_token(th, atoms, vmap, remember);
      if (t->isAtom() && (curr_token_type == OBRA_TOKEN))
	{
	  next_token(th, atoms, vmap, remember);
	  int arity = parseargs(th, atoms, vmap, stk, remember);
	  assert((arity != 0) && (curr_token_type == CBRA_TOKEN));
	  next_token(th, atoms, vmap, remember);
	  Structure* compound = th->TheHeap().newStructure(arity);
	  compound->setFunctor(t);
	  for (int i = arity; i > 0; i--)
	    {
	      compound->setArgument(i, stk.pop());
	    }
	  return compound;
	}
      else
	{
	  return t;
	}
      break;
    }
  default:
    assert(false);
    return curr_token;
    break;
  }
}

Object* parse_prec50(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_basic(th, atoms, vmap, stk, remember);
  if (curr_token == AtomTable::colon) {
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_basic(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(AtomTable::colon);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec50(th, atoms, vmap, stk, remember);
  if (curr_token == AtomTable::at) {
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec50(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(AtomTable::at);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec200(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  assert((curr_token_type != ERROR_TOKEN) 
	 && (curr_token_type != NEWLINE_TOKEN));

  if (curr_token == AtomTable::minus) {
    next_token(th, atoms, vmap, remember);
    Object* arg = parse_prec100(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(1);
    sterm->setFunctor(AtomTable::minus);
    sterm->setArgument(1, arg);
    return sterm;
  }
  Object* t1 = parse_prec100(th, atoms, vmap, stk, remember);
  if (curr_token == AtomTable::power) {
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec100(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(AtomTable::power);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec400(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec200(th, atoms, vmap, stk, remember);
  while ((curr_token == AtomTable::multiply) ||
         (curr_token == AtomTable::divide) ||
         (curr_token == AtomTable::intdivide) ||
         (curr_token == AtomTable::mod) ||
         (curr_token == AtomTable::shiftl) ||
         (curr_token == AtomTable::shiftr)) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec200(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    t1 = sterm;
  }
  return t1;
}

Object* parse_prec500(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec400(th, atoms, vmap, stk, remember);
  while ((curr_token == AtomTable::plus) ||
         (curr_token == AtomTable::minus) ||
         (curr_token == AtomTable::bitwiseand) ||
         (curr_token == AtomTable::bitwiseor)) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec400(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    t1 = sterm;
  }
  return t1;
}

Object* parse_prec700(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec500(th, atoms, vmap, stk, remember);
  if ((curr_token == AtomTable::equal) || (curr_token == AtomTable::is) ||
      (curr_token == AtomTable::lt) || (curr_token == AtomTable::gt) ||
      (curr_token == AtomTable::le) || (curr_token == AtomTable::ge)) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec500(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec1000(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember)
{  
  Object* t1 = parse_prec700(th, atoms, vmap, stk, remember);
  if (curr_token_type == COMMA_TOKEN) {
    Object* op = AtomTable::comma;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec1000(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec1050(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec1000(th, atoms, vmap, stk, remember);
  if (curr_token == AtomTable::arrow) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec1050(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec1100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec1050(th, atoms, vmap, stk, remember);
  if (curr_token == AtomTable::semi) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec1100(th, atoms, vmap, stk, remember);
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;

}

Object* parsePedroTerm(Thread* th, AtomTable& atoms,
		       VarMap& vmap, ObjectsStack& stk, bool remember)
{
  next_token(th, atoms, vmap, remember);
  Object* t = parse_prec1100(th, atoms, vmap, stk, remember);
  assert(curr_token_type == NEWLINE_TOKEN);
  return t;
}

void write_term(Object* term, int prec, ostringstream& strm);

void write_list_tail(Object* tail, ostringstream& strm)
{
  if (tail->isCons())
    {
      strm << ", ";
      Cons* lst = OBJECT_CAST(Cons*, tail);
      write_term(lst->getHead(), 999, strm);
      write_list_tail(lst->getTail()->variableDereference(), strm);
    }
  else if (tail == AtomTable::nil)
    {
      strm << ']';
    }
  else
    {
      strm << '|';
      write_term(tail, 999, strm);
      strm << ']';
    }
}

void get_pre_prec(Object* functor, int& argprec)
{
  if (functor == AtomTable::minus)
    {
      argprec = 200;
    }
}

void write_prefix(Object* functor, Object* arg, int prec, 
		  int argprec, ostringstream& strm)
{
  if (argprec < prec)
    {
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(arg, argprec, strm);
    }
  else
    {
      strm << '(';
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(arg, argprec, strm);
      strm << ')';
    }
}

void get_infix_prec(Object* functor, int& funprec, int& lprec, int & rprec)
{
  if (functor == AtomTable::power)
    {
      funprec = 200;
      lprec = 199;
      rprec = 199;
    }
  else if ((functor == AtomTable::multiply) ||
	   (functor == AtomTable::divide) || 
	   (functor == AtomTable::intdivide) || 
	   (functor == AtomTable::mod) || 
	   (functor == AtomTable::shiftl) || 
	   (functor == AtomTable::shiftr))
    {
      funprec = 400;
      lprec = 400;
      rprec = 399;
    }
  else if ((functor == AtomTable::plus) ||
	   (functor == AtomTable::minus) || 
	   (functor == AtomTable::bitwiseand) || 
	   (functor == AtomTable::bitwiseor))
    {
      funprec = 500;
      lprec = 500;
      rprec = 499;
    }
  else if ((functor == AtomTable::equal) ||
	   (functor == AtomTable::is) || 
	   (functor == AtomTable::lt) || 
	   (functor == AtomTable::gt) || 
	   (functor == AtomTable::le) || 
	   (functor == AtomTable::ge))
    {
      funprec = 700;
      lprec = 699;
      rprec = 699;
    }
  else if (functor == AtomTable::comma)
    {
      funprec = 1000;
      lprec = 999;
      rprec = 1000;
    }
  else if (functor == AtomTable::arrow)
    {
      funprec = 1050;
      lprec = 1049;
      rprec = 1050;
    }
  else if (functor == AtomTable::semi)
    {
      funprec = 1100;
      lprec = 1099;
      rprec = 1100;
    }
  else if (functor == AtomTable::colon)
    {
      funprec = 50;
      lprec = 49;
      rprec = 49;
    }
  else if (functor == AtomTable::at)
    {
      funprec = 200;
      lprec = 199;
      rprec = 199;
    }
}

void write_infix(Object* functor, Object* larg, Object* rarg, int prec, 
		 int funprec, int leftprec, int rightprec, ostringstream& strm)
{
  if (funprec <= prec)
    {
      write_term(larg, leftprec, strm);
      strm << ' ';
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(rarg, rightprec, strm);
    }
  else
    {
      strm << '(';
      write_term(larg, leftprec, strm);
      strm << ' ';
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(rarg, rightprec, strm);
      strm << ')';
    }
}

void write_infix_comma(Object* larg, Object* rarg, int prec, 
		       ostringstream& strm)
{
  if (1000 <= prec)
    {
      write_term(larg, 999, strm);
      strm << " , ";
      write_term(rarg, 1000, strm);
    }
  else
    {
      strm << '(';
      write_term(larg, 999, strm);
      strm << " , ";
      write_term(rarg, 1000, strm);
      strm << ')';
    }
}

void write_structure(Structure* str, int arity, ostringstream& strm)
{
  write_term(str->getFunctor(), 999, strm);
  strm << '(';
  for (int i = 1; i <arity; i++)
    {
      write_term(str->getArgument(i), 999, strm);
      strm << ", ";
    }
  write_term(str->getArgument(arity), 999, strm);
  strm << ')';
}

void write_term(Object* term, int prec, ostringstream& strm)
{
  term = term->variableDereference();
  
  switch (term->tTag())
    {
    case Object::tShort:
    case Object::tLong:
      strm << term->getInteger();
      break;
    case Object::tDouble:
      {
	double d = term->getDouble();
	char buff[20];
	sprintf(buff, "%g", d);
	if (strpbrk(buff, ".e") == NULL) {
	  strcat(buff, ".0");
	}
	strm << buff; 
	break;
      }
    case Object::tAtom:
      {
	writeAtom(strm, term);
	break;
      }
    case Object::tString:
      {
	const char *s = OBJECT_CAST(StringObject*, term)->getChars();
	string thechars(s);
	addEscapes(thechars, '"');
	strm << '"';
	strm << thechars;
	strm << '"';
	break;
      }
    case Object::tVar:
      {
	Variable* var = OBJECT_CAST(Variable*, term);

	if (var->hasExtraInfo() && var->getName() != NULL) {
	  strm << var->getName()->getName();
	}
	else {
	  strm << '_' << (uint)var;
	}
	break;
      }
    case Object::tCons:
      {
	strm << '[';
	Cons* lst = OBJECT_CAST(Cons*, term);
	write_term(lst->getHead(), 999, strm);
	write_list_tail(lst->getTail()->variableDereference(), strm);
	break;
      }
    case Object::tStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	int arity = str->getArity();
	if (arity > 2)
	  {
	    write_structure(str, arity, strm);
	  } 
	else if (arity == 1)
	  {
	    int argprec = -1;
	    Object* functor = str->getFunctor()->variableDereference();
	    get_pre_prec(functor, argprec);
	    if (argprec < 0)
	      {
		write_structure(str, 1, strm);
	      }
	    else
	      {
		Object* arg = str->getArgument(1)->variableDereference();
		write_prefix(functor, arg, prec, argprec, strm);
	      }
	  }
	else
 	  {
	    Object* functor = str->getFunctor()->variableDereference();
	    if (functor == AtomTable::comma)
	      {
		Object* larg = str->getArgument(1)->variableDereference();
		Object* rarg = str->getArgument(2)->variableDereference();
		write_infix_comma(larg, rarg, prec, strm);
	      }
	    else
	      {
		int funprec = -1;
		int leftprec = -1;
		int rightprec = -1;
		get_infix_prec(functor, funprec, leftprec, rightprec);
		if (funprec < 0)
		  {
		    write_structure(str, 2, strm);
		  }
		else
		  {
		    Object* larg = str->getArgument(1)->variableDereference();
		    Object* rarg = str->getArgument(2)->variableDereference();
		    write_infix(functor, larg, rarg, prec, funprec, leftprec, rightprec, strm);
		  }
	      }
	  }
	break;
      }
    default:
      assert(false);
    }

}

void 
PedroMessage::constructMessage(Object*& sender, Object*& msgterm,
			       Thread& thread, AtomTable& atoms,
			       bool rn)
{
  char buff[1026];
  strcpy(buff, msg.c_str());
  int size = msg.length();
  buff[size+1] = '\0';
  ObjectsStack stk(1024);
  VarMap varMap;
  
  set_buffstate(buff, size+2);
  Object* term = parsePedroTerm(&thread, atoms, varMap, stk, rn); 
  delete_buffstate();



  if (term == NULL) {
    sender = AtomTable::semi;
    msgterm = AtomTable::semi;
    return;
  }
  if (!term->isStructure()) {
    sender = atoms.add("pedro");
    msgterm = term;
    return;
  }
  Structure* sterm = OBJECT_CAST(Structure*, term);
  if (sterm->getFunctor() == atoms.add("p2pmsg")) {
    int arity = sterm->getArity();
    assert(arity == 2);
    sender = sterm->getArgument(1);
    msgterm = sterm->getArgument(2);
  }
  else {
    sender = atoms.add("pedro");
    msgterm = term;
  }
}

void
PedroMessageChannel::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
  if (fd == -1) return;

  if (fd > max_fd) max_fd = fd;
  FD_SET(fd, rfds);
}

void
PedroMessageChannel::readMessages()
{
  size_t pos = in.find('\n');
  while (pos != string::npos)
    {
      string m = in.substr(0, pos + 1);
      in.erase(0, pos+1);
      size_t sppos = m.find(' ');
      assert(sppos != string::npos);
      int id = atoi(m.c_str());
      m.erase(0, sppos+1);
      pushMessage(id, m);
      pos = in.find('\n');
    }
}

bool 
PedroMessageChannel::ShuffleMessages(void)
{
  if (fd == -1) return false;

  bool new_msg = false;
  timeval tv = { 0, 0 };
  fd_set fds;

  while (true)
    {
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      int result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      if (!result || !FD_ISSET(fd, &fds)) return new_msg;
      char buff[1101];
      ssize_t size = read(fd, buff, 1100);
      buff[size] = '\0';
      in.append(buff);
      new_msg = true;
      readMessages();
    }
  return new_msg;
}

int
PedroMessageChannel::get_ack()
{
  char buff[32];
  int size;
  int offset = 0;
  while (1) {
    size = recv(ack_fd, buff + offset, 30 - offset, 0);
    offset += size;
    if (offset > 25) {
      fprintf(stderr, "Can't get ack\n");
      exit(1);
    }
    if (buff[offset-1] == '\n') {
      buff[offset] = '\0';
      break;
    }
  }
  return atoi(buff);
}

int
PedroMessageChannel::subscribe(Object* t)
{

  send(t);
  int id = get_ack();
  if (id != 0) attach_subscription(id, t);
  return id;
}

void
PedroMessageChannel::attach_subscription(int id, Object* t)
{
  t = t->variableDereference();
  assert(t->isStructure());
  Structure* st = OBJECT_CAST(Structure*, t);
  int tid = st->getArgument(3)->variableDereference()->getInteger();
  list<int>& tid_list = thread_subs[tid];
  tid_list.push_back(id);
}


void
PedroMessageChannel::pushMessage(int id, string m)
{
  ThreadTable& thread_table = getThreadTable();
  ThreadTableLoc tid = id;

  string::size_type loc = m.find(p2pmsg_string, 0);
  if (loc == 0) {
    // p2p msg found - get the thread name
    loc =  m.find('@', p2pmsg_string_len);
    string::size_type loc_colon =  m.find(':', p2pmsg_string_len);
    if (loc_colon < loc) {
      // has thread name
      // so strip off trailing spaces
      int i = loc_colon-1;
      while (m.at(i) == ' ') i--;
      // and leading spaces
      int j = p2pmsg_string_len;
      while (m.at(j) == ' ') j++;
      string thread_name = m.substr(j, i-j+1);
      // if the thread name is '' then this is message stream
      // message
      if (thread_name == stream_string) {
	string::size_type loc_comma1 =  m.find(',', loc);
	assert(loc_comma1 != string::npos);
	string::size_type loc_comma2 =  m.find(',', loc_comma1 + 1);
	assert(loc_comma2 != string::npos);
	string from_addr;
	// copy the address part removing spaces
	for (string::size_type i = loc_comma1+1; i < loc_comma2; i++) {
	  if (m.at(i) != ' ') from_addr.push_back(m.at(i));
	}
	// Now get the string part - the message argument should be a string
	// starting and ending with "
	string::size_type loc_quote1 =  m.find('"', loc_comma2);
	assert(loc_quote1 != string::npos);
	string::size_type loc_quote2 =  m.find_last_of('"');
	assert(loc_quote2 != string::npos);
	assert(loc_quote1 < loc_quote2);
	string message =  m.substr(loc_quote1+1, loc_quote2 - loc_quote1 - 1);
	removeEscapes(message, '"');
	iom.updateStreamMessages(from_addr, message);

	return;
      }

      tid = thread_table.LookupName(thread_name.c_str());
      if (tid == (ThreadTableLoc) -1)
	return;
    }
    // So this is a p2p message that is not being used as a message stream
    // erase the to address for this string because the recipient knows
    // who they are
    string::size_type loc_comma =  m.find(',', p2pmsg_string_len);
    assert(loc_comma != string::npos);
    m.erase(p2pmsg_string_len, loc_comma - p2pmsg_string_len + 1);
  }
  if (!thread_table.IsValid(tid)) return;

  Thread* thread = thread_table.LookupID(tid);
  if (thread != NULL) {
    thread->MessageQueue().push_back(new PedroMessage(m));
  }
}

bool
PedroMessageChannel::unsubscribe(int tid, Object* t)
{
  t = t->variableDereference();
  assert(t->isStructure());
  Structure* st = OBJECT_CAST(Structure*, t);
  int id = st->getArgument(1)->variableDereference()->getInteger();

  list<int>::iterator iter;
  list<int>& entry = thread_subs[tid];
  iter = find(entry.begin(), entry.end(), id);
  if (iter == entry.end()) return false;
  send(t);
  int ack = get_ack();
  if (ack == id) {
    entry.erase(iter);
    return true;
  }
  return false;
}

bool
PedroMessageChannel::notify(Object* t)
{
  send(t);
  return (get_ack() != 0);
}

void
PedroMessageChannel::send(Object* t)
{
  ostringstream strm;
  write_term(t, 1200, strm);
  strm << '\n';
  send(strm.str());
}

string pedro_write(Object* t)
{
  ostringstream strm;
  write_term(t, 1200, strm);
  return strm.str();
}

void
PedroMessageChannel::send(string s)
{
  size_t len = s.length();
  
  size_t num_written = write(fd, s.c_str(), len);
  
  while (num_written != len)
    {
      s.erase(0, num_written);
      fd_set fds;
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
      assert(s.length() == (len - num_written));
      len = s.length();
      num_written = write(fd, s.c_str(), len);
    }
      
}

void 
PedroMessageChannel::delete_subscriptions(int tid)
{
  list<int>::iterator iter;
  list<int>& entry = thread_subs[tid];
  while (entry.size() > 0)
  {
    int id = entry.front();
    ostringstream strm;
    strm << "unsubscribe(" << id << ")\n";
    string s = strm.str();
    send(s);
    entry.pop_front();
  } 
}


void 
PedroMessageChannel::connect(int f, int s)
{
  ack_fd = f; 
  socket = s;

  /* Set up client for server connections */
  const int sock = (int)(::socket(AF_INET, SOCK_STREAM, 0));
  if (sock < 0)
    {
      fprintf(stderr, "Can't open socket\n");
      exit(1);
    }
  struct sockaddr_in client;

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = ((u_long)INADDR_ANY);
  client.sin_port = htons(0);

  if (bind(sock, (struct sockaddr *) &client, sizeof(client)) != 0)
    { 
      close(sock);
      fprintf(stderr, "Can't bind socket\n");
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
  int port = ntohs(addr.sin_port);


  char hostname[1000];
  gethostname(hostname, 1000);
  hostent *hp = gethostbyname(hostname);
  if (hp == NULL)
    {
      // if we can't get host by name then try to use ifconfig
      strcpy(hostname, "127.0.0.1");
      getIPfromifconfig(hostname);
      host = atoms->add(hostname);
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
          host = atoms->add(inet_ntoa(in_copy));
        } 
      else 
        {
          host = atoms->add(hp->h_name);
        }
  }



  /* get ready for server connection */
  if (listen(sock, 1) == -1) {
    fprintf(stderr, "Can't listen\n");
    exit(1);
  }

 /* send port to server so server can connect */
  ostringstream strm;
  strm << port << "\n";
  string st = strm.str();
  int len = st.length();
  write(ack_fd, st.c_str(), len);


  struct sockaddr_in saddr;
  socklen_t slength = sizeof(struct sockaddr_in);
  fd = (int)(accept(sock, (struct sockaddr *) &saddr, &slength));
  /* server is now connected - this socket is used for data */
  if (fd < 0)
    {
      close(ack_fd);
      close(sock);
      fprintf(stderr, "Can't accept\n");
      exit(1);
    }
  close(sock);

}

/* disconnect */
void 
PedroMessageChannel::disconnect()
{
  close(ack_fd);
  fd = -1; 
  socket = -1;
}


bool
PedroMessageChannel::pedro_register(Object* regname)
{
  ostringstream strm;
  strm << "register(" << OBJECT_CAST(Atom*, regname)->getName() << ")\n";
  string s = strm.str();
  send(s);

  if (get_ack() == 0) return false;
  name = regname;
  return true;
}

bool
PedroMessageChannel::pedro_deregister(Object* regname)
{
  ostringstream strm;
  strm << "deregister(" << OBJECT_CAST(Atom*, regname)->getName() << ")\n";
  string s = strm.str();
  send(s);

  if (get_ack() == 0) return false;
  name = NULL;
  return true;
}
