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

// $Id: interact.cc,v 1.2 2004/05/16 04:27:55 qp Exp $

#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "interact.h"
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
}

void Interact::processReturn()
{
  int p = paragraphs()-1;
  int i = paragraphLength(p);
  setSelection(para, indent, p, i);
  QString cmd = selectedText();
  setSelection(p, i, p, i);
  para = p;
  indent = i;
  send_cmd(cmd);
  cmd.truncate(cmd.length()-1);
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
      int p = paragraphs()-1;
      int i = paragraphLength(p);

      setSelection(p,i,p,i);
    }
  if ((key_pressed == Qt::Key_Backspace)
      || (key_pressed == Qt::Key_Left))
    {
      int p,i;
      getCursorPosition(&p,&i);
      if ((p < para) || ((p == para) && (i <= indent)))
	{
	  return;
	}
    }
  if (key_pressed == Qt::Key_Up)
    {
      int p,i;
      getCursorPosition(&p,&i);
      if (p <= para)
	{
	  return;
	}
    }
  if (key_pressed == Qt::Key_Home)
    {
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
      setCursorPosition(para,indent);
      return;
    }

  QTextEdit::keyPressEvent(k);
}

