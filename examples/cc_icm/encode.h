// encode.h - Term encoding and decoding.
//

#ifndef ENCODE_H
#define ENCODE_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//
// Map the atoms into unique entries.
//
class	EncodeMap
{
private:
  //
  // The array index cannot be larger than 1 byte because the encoder
  // sends 1 byte.
  // Therefore we consider a vector of tables with the max length of the
  // vector being 256.

  static const int TABLE_MAX	= 256;
  
  vector<string**>	vector_of_tables;
  int top_table_entry;
  int top_vector_entry;
  
public:
  
  static const int NOT_FOUND	=             -1;
  static const u_char ENCODE_REFERENCE =        0;
  static const u_char ENCODE_VARIABLE =         1; 
  static const u_char ENCODE_OB_REFERENCE =     2;
  static const u_char ENCODE_OB_VARIABLE =      3;
  static const u_char ENCODE_LIST =             4;
  static const u_char ENCODE_STRUCTURE =        5; 
  static const u_char ENCODE_QUANTIFIER =       6;
  static const u_char ENCODE_ATOM_REF =         7;
  static const u_char ENCODE_ATOM =             8;
  static const u_char ENCODE_INTEGER =          9;
  static const u_char ENCODE_SUBSTITUTION =     10;
  static const u_char ENCODE_SUBSTITUTION_END = 11;
  static const u_char ENCODE_NAME =             12;
  static const u_char ENCODE_REF_OFFSET =       13;

  //
  // Add.
  //
  void add(string* c)
  {
    if (top_table_entry < TABLE_MAX)
      {
        vector_of_tables[top_vector_entry-1][top_table_entry++] = c;
      }
    else
      {
	if (top_vector_entry == TABLE_MAX)
	  {
	    cerr << "Not enough space to encode term" << endl;
            exit(1);
          }
	vector_of_tables.push_back(new string* [TABLE_MAX]);
        top_table_entry = 0;
	vector_of_tables[top_vector_entry++][top_table_entry++] = c;
      }
  }
  
  //
  // Look-up.
  //
  string* lookUp(u_char i, u_char j) { return(vector_of_tables[i][j]); }

  int	lookUp(string* c)
  {
    int i;
    int j;
    
    for (i = 0; i < top_table_entry; i++)
      {
	if (vector_of_tables[top_vector_entry-1][i] == c)
	  {
	    return(TABLE_MAX*(top_vector_entry-1) + i);
	  }
      }
    for (j = 0; j < top_vector_entry-1; j++)
      {
	for (i = 0; i < TABLE_MAX; i++)
	  {
	    if (vector_of_tables[j][i] == c)
	      {
		return(TABLE_MAX*j + i);
	      }
	  }
      }
    return(NOT_FOUND);
  }
  
  
  EncodeMap(void)
    {
      vector_of_tables.push_back(new string* [TABLE_MAX]);
      top_table_entry = 0;
      top_vector_entry = 1;
    }
  ~EncodeMap(void)
    {
      for (int i = 0; i < top_vector_entry; i++)
	{
	  if (vector_of_tables[i] != NULL)
	    {
	      for (int j = 0; j < top_table_entry; j++)
		{
		  if (vector_of_tables[i][j] != NULL)
		    {
		      delete vector_of_tables[i][j];
		      vector_of_tables[i][j] = NULL;
		    }
		}
	      delete [] vector_of_tables[i];
	      vector_of_tables[i] = NULL;
	    }
	}
      top_table_entry = 0;
    }
};

//
// Auxiliary class bundles up some useful things.
//
class EncodeBase
{
protected:
  EncodeMap *map;

public:
  EncodeBase(void)
    : map(new EncodeMap())
    {
    }
  ~EncodeBase(void)
    {
      delete map;
    }
};

class EncodeWrite : public EncodeBase {

private:
  ostringstream stream;
public:
  //
  // Write a character.
  //
  bool encodeWriteChar(const u_char);
  
  //
  // Encode write a number
  //
  bool encodeWriteNumber(const int);
    
  //
  // Encode the string and write the result to the stream.
  //
  bool encodeWriteString(string str);
  
  const string getString() { return stream.str(); }

  EncodeWrite()
    {
    }

};

class EncodeRead : public EncodeBase {
private:
  int index;
  string input;

    
public:

  EncodeRead(string& in);
  ~EncodeRead(void)
    {
    }

  //
  // Get next type.
  //
  u_char encodeReadChar();
  
  //
  // Read from a stream and decode back to a string.
  //
  string* encodeReadString();

  string* encodeReadRef();
  //
  // Read a number.
  //
  int encodeReadNumber();

 
};

#endif	// ENCODE_H
