
#ifndef WRITE_SUPPORT_H
#define WRITE_SUPPORT_H

#include <string>

#include "objects.h"

using namespace std;

void addEscapes(string& str, char quote);
void removeEscapes(string& str, char quote);
bool SafeAtom(const char *s);
void writeAtom(ostream& strm, Object* a);

#endif
