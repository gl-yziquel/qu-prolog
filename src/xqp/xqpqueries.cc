/***************************************************************************
                          xqpqueries.cc  -  QP queries widget
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

// $Id: xqpqueries.cc,v 1.1 2004/05/09 23:51:11 qp Exp $

#include "xqpqueries.h"
#include "term.h"

XQPQueries::XQPQueries(QWidget *p, QString& name, QString text)
  : QMainWindow(p, name)
{
  queries = new QTextEdit(this);
  setCentralWidget(queries);
  parent = p;
  resize(400,300);
  //  queries->setReadOnly(true);
  queries->setText(text);
  name.prepend("Queries File: ");
  setCaption(name);
  show();
  queries->setCursorPosition(0,0);
  queries->setFocus();
  
}

XQPQueries::~XQPQueries()
{
  delete queries;
}

void XQPQueries::keyPressEvent(QKeyEvent * k)
{
  if (k->key() == Qt::Key_F5 || k->key() == Qt::Key_F9)
    {
      QString text = "";
      while (true)
	{
	  int p,i;
	  queries->getCursorPosition(&p, &i);
	  i =  queries->paragraphLength(p);
	  queries->setSelection(p, 0, p, i);
	  QString line = queries->selectedText();
	  queries->setSelection(p+1,0,p+1,0);
	  text.append(line);
	  text.append("\n");
	  if (end_of_term(text, 0))
	    break;
	}
      if (k->key() == Qt::Key_F5)
	{
	  process_text(text);
	  process_return();
	}
      else
	{
	  text.truncate(text.length() - 1);
	  process_text(text);
	}
    }
  else if (k->key() == Qt::Key_F6)
    {
      process_text("\n");
      process_return();
    }
  else if (k->key() == Qt::Key_F7)
    {
      process_text(";\n");
      process_return();
    }
  else if (k->key() == Qt::Key_F8)
    {
      process_text(",\n");
      process_return();
    }
  else
    {
      QMainWindow::keyPressEvent(k);
    }
}
