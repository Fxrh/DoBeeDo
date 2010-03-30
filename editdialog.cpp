/**************************************************************************
 *                                                                        *
 * Copyright (C) 2010 Felix Rohrbach <fxrh@gmx.de>                        *
 *                                                                        *
 * This program is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU General Public License            *
 * as published by the Free Software Foundation; either version 3         *
 * of the License, or (at your option) any later version.                 *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                        *
 **************************************************************************/ 

#include "editdialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <KPushButton>
#include <KDatePicker>

#include "todoobject.h"

EditDialog::EditDialog(QWidget *parent)
  : KDialog(parent)
{
  todo = 0;
  setButtons(KDialog::Ok | KDialog::Cancel);
  setupUi();
}

void EditDialog::editTodo(TodoObject *object)
{
  todo = object;
  nameEdit->setText( todo->getName() );
  datePicker->setDate( todo->getDate() );
}

void EditDialog::accept()
{
  if( nameEdit->text() == "" ){
    
  }
  todo->setName( nameEdit->text() );
  todo->setDate( datePicker->date() );
  KDialog::accept();
}

void EditDialog::setupUi()
{
  nameLabel = new QLabel("Name");
  nameEdit = new QLineEdit;
  dateLabel = new QLabel("Date");
  datePicker = new KDatePicker();
//  acceptBtn = new KPushButton(KIcon("dialog-ok-apply"),"Ok");
//  cancelBtn = new KPushButton(KIcon("dialog-cancel"),"Cancel");
  
  nameLayout = new QVBoxLayout();
  nameLayout->addWidget(nameLabel);
  nameLayout->addWidget(nameEdit);
  nameLayout->addStretch();
  
  dateLayout = new QVBoxLayout();
  dateLayout->addWidget(dateLabel);
  dateLayout->addWidget(datePicker);
  dateLayout->addStretch();
  
  mainLayout = new QHBoxLayout;
  mainLayout->addLayout(nameLayout);
  mainLayout->addLayout(dateLayout);
  
  this->mainWidget()->setLayout(mainLayout);
  
//  optionsLayout = new QHBoxLayout;
//  optionsLayout->addLayout(nameLayout);
//  optionsLayout->addLayout(dateLayout);
//  
//  bottomLayout = new QHBoxLayout();
//  bottomLayout->addStretch();
//  bottomLayout->addWidget(acceptBtn);
//  bottomLayout->addWidget(cancelBtn);
//  
//  mainLayout = new QVBoxLayout;
//  mainLayout->addLayout(optionsLayout);
//  mainLayout->addLayout(bottomLayout);
  
//  setLayout(mainLayout);
  
//  connect( acceptBtn, SIGNAL(clicked()), this, SLOT(accept()) );
//  connect( cancelBtn, SIGNAL(clicked()), this, SLOT(reject()) );
}
