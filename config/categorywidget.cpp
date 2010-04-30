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

#include "categorywidget.h"
#include <QStringListModel>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QModelIndex>
#include <QDebug>
#include <KPushButton>
#include <KInputDialog>

#include "../settings.h"

CategoryWidget::CategoryWidget(QWidget *parent)
  : QWidget(parent)
{
  setupUi();
  catOpList = new QStringList();
  catIdList = new QList<int>();
  model->setStringList(*Settings::self()->categories());
  qDebug() << "CategoryWidget: Created.";
}

CategoryWidget::~CategoryWidget()
{
  delete catOpList;
  delete catIdList;
}

const QStringList* CategoryWidget::getCatOpList()
{
  return catOpList;
}

const QList<int>* CategoryWidget::getCatIdList()
{
  return catIdList;
}

void CategoryWidget::save()
{
  Settings::self()->setCategories( new QStringList(model->stringList()) );
  Settings::self()->emitConfigChanged();
  qDebug() << "CategoryWidget: saved: " << model->stringList();
}

void CategoryWidget::restore()
{
  model->setStringList(*Settings::self()->categories());
  catOpList->clear();
  catIdList->clear();
}

void CategoryWidget::add()
{
  bool ok=false;
  QString name = KInputDialog::getText( "New category", "Enter the name for the new category:", "", &ok );
  if( !ok || name == "" ){
    return; // cancel pressed
  }
  // not needed, as there is no change to the Todos
  //catOpList->push_back("ADD");
  //catIdList->push_back(model->rowCount());
  model->insertRow( model->rowCount(), QModelIndex() );
  model->setData( model->index( model->rowCount()-1, 0, QModelIndex() ), name );
}

void CategoryWidget::rename()
{
  bool ok=false;
  QString name = KInputDialog::getText( "Rename category", "Enter the new name for the category:", "", &ok );
  if( !ok || name == "" ){
    return; // cancel pressed
  }
  // not needed, as there is no change to the Todos
  //catOpList->push_back("RENAME");
  //catIdList->push_back(view->currentIndex().row());
  model->setData( model->index( view->currentIndex().row(), 0, QModelIndex() ), name );  
}

void CategoryWidget::remove()
{
  if( view->currentIndex().row() == 0 ){
    return;
  }
  catOpList->push_back("REMOVE");
  catIdList->push_back(view->currentIndex().row() );
  model->removeRow( view->currentIndex().row(), QModelIndex() );
}

void CategoryWidget::setupUi()
{
  model = new QStringListModel(this);
  view = new QListView();
  view->setModel(model);
  addBtn = new KPushButton(KIcon("list-add"),"Add");
  renameBtn = new KPushButton(KIcon("edit-rename"),"Rename");
  removeBtn = new KPushButton(KIcon("list-remove"),"Remove");
  
  buttonLayout = new QVBoxLayout();
  buttonLayout->addWidget(addBtn);
  buttonLayout->addWidget(renameBtn);
  buttonLayout->addWidget(removeBtn);
  buttonLayout->addStretch();
  
  mainLayout = new QHBoxLayout();
  mainLayout->addWidget(view);
  mainLayout->addLayout(buttonLayout);
  setLayout(mainLayout);
  
  connect( addBtn, SIGNAL(clicked()), this, SLOT(add()) );
  connect( renameBtn, SIGNAL(clicked()), this, SLOT(rename()) );
  connect( removeBtn, SIGNAL(clicked()), this, SLOT(remove()) );
}


