/***************************************************************************
                          interact.cc  -  QP interaction widget
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

// $Id: interact.cc,v 1.3 2004/05/25 04:31:33 qp Exp $

#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "interact.h"
#include "term.h"
#include "xqpqueries.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qfile.h>

using namespace std;

Interact::Interact( QWidget *box )
  : QTextEdit(box)
{
  parent = box;
  setTextFormat(Qt::PlainText);
  setFont( QFont( "Lucidatypewriter", 12, QFont::Normal ) );
  para = 0;
  indent = 0;
  connect(this, SIGNAL(returnPressed()), this, SLOT(processReturn()));
  connect(this, SIGNAL(send_cmd(QString)), box, SLOT(send_cmd_to_qp(QString)));
  in_history = false;
  //setPaper(QBrush(yellow));
}

void Interact::insert_at_end(QString s)
{
  para = paragraphs()-1;
  indent = paragraphLength(para);
  setCursorPosition(para, indent);
  insert(s);
  para = paragraphs()-1;
  indent = paragraphLength(para);
  setCursorPosition(para, indent);
  setColor(Qt::blue);
  int n = s.find(QRegExp("'| \\?- $"));
  in_query = (n != -1);
}

void Interact::processF5(QString s)
{
  int p = paragraphs()-1;
  int i = paragraphLength(para);
  setCursorPosition(p, i);
  insert(s);
}

void Interact::processReturn()
{
  int p = paragraphs()-1;
  int i = paragraphLength(p);
  setSelection(para, indent, p, i);
  in_history = false;
  QString cmd = selectedText();
  setSelection(p, i, p, i);
  if (!in_query || end_of_term(cmd, 0))
    {
      para = p;
      indent = i;
      send_cmd(cmd);
      cmd.truncate(cmd.length()-1);
      if (in_query) addHistoryItem(new QString(cmd));
      in_query = false;
    }
}


Interact::~Interact()
{
}

void Interact::contentsMouseReleaseEvent(QMouseEvent* e)
{
  int p,i;
  getCursorPosition(&p,&i);
  if ((p < para) || ((p == para) && (i < indent)))
    {
      if (e->button() != Qt::MidButton)
	QTextEdit::contentsMouseReleaseEvent(e);
      setCursorPosition(currpara,currindent);
      readonly = true;
    }
  else
    {
      QTextEdit::contentsMouseReleaseEvent(e);
      readonly = false;
    }
}

void Interact::contentsMousePressEvent(QMouseEvent* e)
{
  getCursorPosition(&currpara, &currindent);
  if (e->button() == Qt::MidButton)
    {
      QMouseEvent lbe(QEvent::MouseButtonPress, e->pos(), 
		      Qt::LeftButton, Qt::LeftButton);
      QTextEdit::contentsMousePressEvent(&lbe);
      QTextEdit::contentsMouseReleaseEvent(&lbe);
    }
  QTextEdit::contentsMousePressEvent(e);
}

void Interact::cut()
{
  if (readonly) QTextEdit::copy();
  else QTextEdit::cut();
}

void Interact::paste()
{
  if (!readonly) QTextEdit::paste();
}

void Interact::keyPressEvent(QKeyEvent *k)
{
  int key_pressed = k->key();
  if (key_pressed == Qt::Key_Control)
    {
      QTextEdit::keyPressEvent(k);
      return;
    }
  if (k->state() == ControlButton)
    {
      in_history = false;
      if (key_pressed == 'D')
        {
          emit ctrl_D_sig();
          return;
        } 
      if (key_pressed == 'C')
	{
	  QTextEdit::keyPressEvent(k);
	  return;
	}
    }
  if (readonly)
    {
      in_history = false;
      int p = paragraphs()-1;
      int i = paragraphLength(p);

      setSelection(p,i,p,i);
    }
  if ((key_pressed == Qt::Key_Backspace)
      || (key_pressed == Qt::Key_Left))
    {
      in_history = false;
      int p,i;
      getCursorPosition(&p,&i);
      if ((p < para) || ((p == para) && (i <= indent)))
	{
	  return;
	}
    }
  if (key_pressed == Qt::Key_Up)
    {
      QString* item;
      if (!in_history)
	{
	  item = firstHistoryItem();
	}
      else
	{
	  item = nextHistoryItem();
	}
      in_history = true;
      if (item != NULL)
	{
	  int p = paragraphs()-1;
	  int i = paragraphLength(p);
	  
	  setSelection(para,indent,p,i);
	  insert(*item);
	}
      return;
    }
   if (key_pressed == Qt::Key_Down)
    {
       QString* item = previousHistoryItem();
       if ( item != NULL)
         {
	   int p = paragraphs()-1;
	   int i = paragraphLength(p);
	   
	   setSelection(para,indent,p,i);
	   insert(*item);
          }
       else
	 {
	   int p = paragraphs()-1;
	   int i = paragraphLength(p);

	   setSelection(para,indent,p,i);
	   insert("");
	 }
       return;
    }
  if (key_pressed == Qt::Key_Home)
    {
      in_history = false;
      if (k->state() == ControlButton)
	{
	  setCursorPosition(para,indent);
	  return;
	}
      else
	{
	  int p,i;
	  getCursorPosition(&p,&i);
	  if (p >= para)
	    {
	      setCursorPosition(p, 0);
	    }
	  return;
	}
    }
  if (key_pressed == Qt::Key_PageUp)
    {
      in_history = false;
      setCursorPosition(para,indent);
      return;
    }

  in_history = false;
  QTextEdit::keyPressEvent(k);
}

void Interact::addHistoryItem(QString* s)
{
  history.prepend(s);
}

QString* Interact::firstHistoryItem(void)
{
    return history.first();
}

QString* Interact::nextHistoryItem(void)
{
    if (history.current() == NULL) history.first();
    return history.next();
}

QString* Interact::previousHistoryItem(void)
{
    if (history.current() == NULL) history.last();
    return history.prev();
}

void Interact::openQueryFile()
{
  QString fileName = QFileDialog::getOpenFileName(QString::null, "*", this);
  if (fileName != QString::null)
    {
      QFile f(fileName);
      if (f.open(IO_ReadOnly))
	{
	  QTextStream t(&f);
	  XQPQueries* xqp_queries = new XQPQueries(parent, fileName, t.read());
	  xqp_queries->setFont(font());
	  connect(xqp_queries, SIGNAL(process_text(QString)), this, SLOT(processF5(QString)));
	  connect(xqp_queries, SIGNAL(process_return()), this, SLOT(processReturn()));
	  f.close();
	}
    }
}

void Interact::saveHistory()
{  
  QString fileName = QFileDialog::getSaveFileName(QString::null, "*", this);
  if (fileName != QString::null)
    {
      QFile f(fileName);
      if (f.open(IO_WriteOnly))
	{
	  QString* item = firstHistoryItem();
	  while (item != NULL)
	    {
	      f.writeBlock(*item, item->length());
	      f.writeBlock("\n", 1);
	      item = nextHistoryItem();
	    }
	  f.close();
	}
    }
}

void Interact::saveSession()
{
  QString fileName = QFileDialog::getSaveFileName(QString::null, "*", this);
  if (fileName != QString::null)
    {
      QFile f(fileName);
      if (f.open(IO_WriteOnly))
	{
	  QString s = text();
	  f.writeBlock(s, s.length());
	  f.close();
	}
    }
}
