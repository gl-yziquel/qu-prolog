// encode.cc - Term encoding and decoding.


#ifndef ENCODE_CC
#define ENCODE_CC

#include <iostream>
#include <string.h>

#include "encode.h"

  
//
// Write a character.
//
bool
EncodeWrite::encodeWriteChar(u_char c)
{
  return stream.good() && stream.put(c) && stream.good();
}

//
// Encode the string and write the result to the stream.
//
bool
EncodeWrite::encodeWriteString(string str)
{
  u_char length = str.size();
  bool result = encodeWriteChar(length);

  for (u_int i = 0; i < length; i++)
    {
      result &= encodeWriteChar(str[i]);
    }
  return(result);
}


//
// Encode write a number
//
bool
EncodeWrite::encodeWriteNumber(const int val)
{
  return(encodeWriteChar((val & 0xff000000) >> 24) &&
	 encodeWriteChar((val & 0x00ff0000) >> 16) &&
	 encodeWriteChar((val & 0x0000ff00) >> 8) &&
	 encodeWriteChar((val & 0x000000ff)));
}


EncodeRead::EncodeRead(string& in)
    : index(0), input(in)
  {
  }

//
// Read a character.
//
u_char
EncodeRead::encodeReadChar()
{
  return ((u_char)(input[index++]));
}

//
// Read a number.
//
int
EncodeRead::encodeReadNumber()
{
  u_char c;
  c = encodeReadChar();
  int num = c;
  c = encodeReadChar();
  num = (num << 8) | c;
  c = encodeReadChar();
  num = (num << 8) | c;
  c = encodeReadChar();
  num = (num << 8) | c;
  return num;
}
//
// Read from input and decode back to a string.
//
string*
EncodeRead::encodeReadString()
{
  u_char len;
  len = encodeReadChar();
  string* str = new string;
  str->insert(0, input, index, len);
  map->add(str);
  index += len;
  return (str);
}

string*
EncodeRead:: encodeReadRef()
{
  return (map->lookUp(0,encodeReadChar()));
}


#endif	// ENCODE_CC







