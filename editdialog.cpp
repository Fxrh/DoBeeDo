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
#include <QComboBox>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
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
  priorityBox->setCurrentIndex( todo->getPriority()-1 );
  descriptionEdit->setPlainText( todo->getDescription() );
  datePicker->setDate( todo->getDate() );
  if( object->getDate().isNull() ){
    dateBox->setChecked(false);
  } else {
    dateBox->setChecked(true);
  }
}

void EditDialog::accept()
{
  if( nameEdit->text() == "" ){
    
  }
  todo->setName( nameEdit->text() );
  todo->setPriority( priorityBox->currentIndex()+1 );
  todo->setDescription( descriptionEdit->toPlainText() );
  if( dateBox->isChecked() ){
    todo->setDate( datePicker->date() );
  } else {
    todo->setDate( QDate() );
  }
  KDialog::accept();
}

void EditDialog::setupUi()
{
  nameLabel = new QLabel("Name: ");
  nameEdit = new QLineEdit;
  priorityLabel = new QLabel("Priority: ");
  priorityBox = new QComboBox();
  priorityBox->addItem("1");
  priorityBox->addItem("2");
  priorityBox->addItem("3");
  priorityBox->addItem("-");
  descriptionLabel = new QLabel("Description: ");
  descriptionEdit = new QPlainTextEdit();
  dateBox = new QCheckBox("select Date");
  dateBox->setChecked(true);
  //dateLabel = new QLabel("Date");
  datePicker = new KDatePicker();
  
  nameLayout = new QGridLayout();
  nameLayout->addWidget(nameLabel,0,0);
  nameLayout->addWidget(nameEdit,0,1);
  nameLayout->addWidget(priorityLabel,1,0);
  nameLayout->addWidget(priorityBox,1,1);
  nameLayout->addWidget(descriptionLabel,2,0,1,2);
  nameLayout->addWidget(descriptionEdit,3,0,1,2);
  
  dateLayout = new QVBoxLayout();
  dateLayout->addWidget(dateBox);
  dateLayout->addWidget(datePicker);
  dateLayout->addStretch();
  
  mainLayout = new QHBoxLayout;
  mainLayout->addLayout(nameLayout);
  mainLayout->addLayout(dateLayout);
  
  this->mainWidget()->setLayout(mainLayout);
  
  connect( dateBox, SIGNAL(toggled(bool)), datePicker, SLOT(setEnabled(bool)) );
  
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
