/***************************************************************************
                          xqpdebug.cpp  -  Interface to QP
                             -------------------
    begin                : April 2004
    copyright            : (C) 2002 by Peter Robinson
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

// $Id: xqpdebug.cc,v 1.4 2004/05/27 00:04:01 qp Exp $

#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include <qdialog.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qapplication.h>
#include <qpopupmenu.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qvbox.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qlistbox.h>

#include "xqpdebug.h"
#include "interact.h"
#include <qcolor.h>
#include <qfontdialog.h>
#include <qlayout.h>
#include <qbuttongroup.h>


using namespace std;

// Dialog box for configuration
ConfigDialog::ConfigDialog(Xqpdebug *parent, QFont xqpf, QColor xqpc)
  : QDialog(parent, "Configuration", TRUE)
{
  QPushButton *ok, *cancel, *font, *colour;
  ok = new QPushButton("OK", this);
  cancel = new QPushButton("Cancel", this);
  font = new QPushButton("Choose Font", this);
  colour = new QPushButton("Choose Colour", this);
  f = xqpf;
  c = xqpc;
  p = parent;
  
  QLabel *label = new QLabel(this);
  label->setText("Sample");
  label->setGeometry(10,50,60,30);
  
  ok->setGeometry(20,200,120,40);
  cancel->setGeometry(190,200,120,40);
  font->setGeometry(10,10,150,40);
  colour->setGeometry(170,10,150,40);
  browser = new QTextBrowser(this);
  browser->setGeometry(10,80,310,100);
  browser->setText("AaBb :- \n| ?-");
  browser->setFont(f);
  browser->setPaper(QBrush(c));
  
  connect(ok, SIGNAL(clicked()), SLOT(accept()));
  connect(cancel, SIGNAL(clicked()), SLOT(reject()));
  connect(font, SIGNAL(clicked()), SLOT(choose_font()));
  connect(colour, SIGNAL(clicked()), SLOT(choose_colour()));
}

void ConfigDialog::choose_font()
{
   bool ok;
    QFont pick =  QFontDialog::getFont(&ok, f,this);
   if (ok)
     {
       browser->setFont(pick);
       f = pick;
     }

}

void ConfigDialog::choose_colour()
{
  QColor pick = QColorDialog::getColor(c, this);
  if (pick.isValid())
    {
      browser->setPaper(QBrush(pick));
      c = pick;
    }
}

void ConfigDialog::accept()
{
  p->setConfigs(f, c);
  QDialog::accept();
}


Xqpdebug::Xqpdebug(char* threadname, char* processname, 
		   char* machineid, char* portstr)
  : QWidget()
{
  int port;
  sscanf(portstr, "%d", &port);
  char gui_name[1024];
  sprintf(gui_name, "%s_%s_debug_gui", threadname, processname);
  if (machineid[0] == '\0') machineid = NULL;
  icm_env = new ICMEnvironment(gui_name, port, machineid);
  to_addr = string(":");
  to_addr.append(processname);
  string addr = threadname;
  addr.append(":");
  addr.append(processname);
  handle = string(":");
  handle.append(gui_name);
  while (icm_env->msgAvail())
    {     
      string msg;
      string from;
      string replyto;
      bool compressed = false;
      icm_env->getMsg(compressed, msg, from, replyto);
    }
  sn = new QSocketNotifier(icm_env->getCommFD(), QSocketNotifier::Read, this);
  connect(sn, SIGNAL(activated(int)), this, SLOT(process_msg(int)));
  
  config = new QPConfig(this);

  QString caption = QString(threadname);
  caption.append(" ");
  caption.append(processname);
  caption.append(" GUI");
  setCaption(caption);
  move(config->getX(), config->getY());
  resize(config->getWidth(), config->getHeight());
  QVBoxLayout* v = new QVBoxLayout(this,5,5,"vvv");
  qpint = new Interact(this);
  qpint->setFont(config->qpFont());
  qpint->setPaper(QBrush(config->qpColor()));
  qpint->setReadOnly(false);  
  v->addWidget(qpint);
  QHBoxLayout* h = new QHBoxLayout(v,3,"hhh");
  QPushButton* creap = new QPushButton("Creap", this);
  QPushButton* skip = new QPushButton("Skip", this);
  QPushButton* leap = new QPushButton("Leap", this);
  QPushButton* exitd = new QPushButton("Exit Debugger", this);
  QPushButton* config = new QPushButton("Configure", this);
  QPushButton* about = new QPushButton("About", this);
  connect(creap, SIGNAL(clicked()), SLOT(process_creap()));
  connect(skip, SIGNAL(clicked()), SLOT(process_skip()));
  connect(leap, SIGNAL(clicked()), SLOT(process_leap()));
  connect(exitd, SIGNAL(clicked()), SLOT(process_exitd()));
  connect(config, SIGNAL(clicked()), SLOT(configure_int()));
  connect(about, SIGNAL(clicked()), SLOT(process_about()));
  h->addWidget(creap);
  h->addWidget(skip);
  h->addWidget(leap);
  h->addWidget(exitd);
  h->addWidget(config);
  h->addWidget(about);
  show();

  qpint->setFocus();

  icm_env->sendMsg(false, "ready_to_go", addr, handle);

}


void Xqpdebug::process_qp_cmd(QString cmd)
{
   qpint->setColor(Qt::blue);
   qpint->insert_at_end(cmd);
   qpint->setColor(Qt::black);
   send_cmd_to_qp(cmd);
}

void Xqpdebug::send_cmd_to_qp(QString cmd)
{
  //  cmd.append("\n");
  string msg = string(cmd.ascii());
  icm_env->sendMsg(false, msg, to_addr, handle);
}

void Xqpdebug::process_creap()
{
  process_qp_cmd("\n");
}

void Xqpdebug::process_skip()
{
  process_qp_cmd("s\n");
}

void Xqpdebug::process_leap()
{
  process_qp_cmd("l\n");
}

void Xqpdebug::process_exitd()
{
  process_qp_cmd("n\n");
}

void Xqpdebug::process_about()
{
  QMessageBox::about(this, "xqpdebug",
             "A QT interface to the QP debugger.\n\nPeter Robinson pjr@itee.uq.edu.au");
}
  
void Xqpdebug::closeEvent(QCloseEvent *e)
{
  process_qp_cmd("n\n");
  QWidget::closeEvent(e);
}


void
Xqpdebug::process_msg(int)
{
  while (icm_env->msgAvail())
    {
      string msg;
      string from;
      string replyto;
      bool compressed = false;
      icm_env->getMsg(compressed, msg, from, replyto);
      if (!compressed)
	{
	  QString inq = QString(msg);
	  if (inq == QString("$exit_gui"))
	    {
	      emit close();
	      return;
	    }
	  qpint->setColor(Qt::black);
	  qpint->insert_at_end(inq);
	}
    }
}


void Xqpdebug::process_CTRL_D()
{
  icm_env->sendMsg(false, "", to_addr, handle);
     //close();
}

void Xqpdebug::setConfigs(QFont f, QColor c)
{
  config->setQPFont(f);
  qpint->setFont(config->qpFont());
  config->setQPColor(c);
  qpint->setPaper(QBrush(config->qpColor()));
}
void Xqpdebug::configure_int()
{
  ConfigDialog* cd;
  QColor cc = config->qpColor();
  cd = new ConfigDialog(this, config->qpFont(), cc);
  if (cd->exec())
    {   
      
    }
  delete cd;
}


Xqpdebug::~Xqpdebug()
{
  delete icm_env;
  delete qpint;
  delete config;
}


