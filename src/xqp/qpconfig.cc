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

// $Id: qpconfig.cc,v 1.1 2004/05/09 23:51:08 qp Exp $

#include "qpconfig.h"
#include <iostream>
#include "xqp.h"

using namespace std;

QPConfig::QPConfig(Xqp* xe) 
  : QSettings(),
    parent(xe),
    default_font("Lucidatypewriter", 12, QFont::Normal),
    default_color(QColor("white"))
{

   QString sf =  default_font.toString();
   QString fontstring = readEntry("/Xqp/font", sf);
   font.fromString(fontstring);
   QString def_cname = default_color.name();
   QString cname = readEntry("/Xqp/color", def_cname);
   color = QColor(cname);
   x = readNumEntry("/Xqp/x", 0);
   y = readNumEntry("/Xqp/y", 0);
   width = readNumEntry("/Xqp/width", 800);
   height = readNumEntry("/Xqp/height", 800);
}

QPConfig::~QPConfig()
{
   writeEntry("/Xqp/font", font.toString());
   writeEntry("/Xqp/color", color.name());
   writeEntry("/Xqp/x",parent-> x());
   writeEntry("/Xqp/y", parent->y());
   writeEntry("/Xqp/width", parent->width());
   writeEntry("/Xqp/height", parent->height());
}

void QPConfig::setQPFont(const QFont& f)
{
      font = f;
}

void QPConfig::setQPColor(const QColor& c)
{
      color = c;
}
