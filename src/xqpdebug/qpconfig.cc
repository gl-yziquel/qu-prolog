/***************************************************************************
                          qpconfig.cc  -  configuration
                             -------------------
    begin                : April 2004
    copyright            : (C) 2004 by Peter Robinson
    email                : pjr@itee.uq.edu.au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// $Id: qpconfig.cc,v 1.2 2004/05/26 03:05:32 qp Exp $

#include "qpconfig.h"
#include <iostream>
#include "xqpdebug.h"

using namespace std;

QPConfig::QPConfig(Xqpdebug* xe) 
  : QSettings(),
    parent(xe),
    default_font("Lucidatypewriter", 12, QFont::Normal),
    default_color(QColor("white"))
{

   QString sf =  default_font.toString();
   QString fontstring = readEntry("/Xqpdebug/font", sf);
   font.fromString(fontstring);
   QString def_cname = default_color.name();
   QString cname = readEntry("/Xqpdebug/color", def_cname);
   color = QColor(cname);
   x = readNumEntry("/Xqpdebug/x", 0);
   y = readNumEntry("/Xqpdebug/y", 0);
   width = readNumEntry("/Xqpdebug/width", 300);
   height = readNumEntry("/Xqpdebug/height", 300);
}

QPConfig::~QPConfig()
{
   writeEntry("/Xqpdebug/font", font.toString());
   writeEntry("/Xqpdebug/color", color.name());
   writeEntry("/Xqpdebug/x",parent-> x());
   writeEntry("/Xqpdebug/y", parent->y());
   writeEntry("/Xqpdebug/width", parent->width());
   writeEntry("/Xqpdebug/height", parent->height());
}

void QPConfig::setQPFont(const QFont& f)
{
      font = f;
}

void QPConfig::setQPColor(const QColor& c)
{
      color = c;
}
