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

#include "mainwindow.h"
#include "model/treemodel.h"
#include "model/filtermodel.h"
#include "model/tododelegate.h"
#include "todoobject.h"
#include "settings.h"
#include "editdialog.h"

#include <klineedit.h>
#include <KPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QComboBox>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow( QWidget* parent )
    : QWidget(parent)
{
  setupGui();
  show();
  
  model->resetAllTodo( Settings::self()->getTodoList() );
  view->expandAll();
  connect( model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(expandSections(QModelIndex,QModelIndex)) );
}

MainWindow::~MainWindow()
{
  Settings::self()->setTodoList( model->getAllTodo() );
  Settings::destroy();
}

void MainWindow::newTodo()
{
  QString name = doEdit->text();
  if( name == "" ){
    return;
  }
  QDate date;
  switch( timeBox->currentIndex() ){
  case 0:
    date = QDate::currentDate();
    break;
  case 1:
    date = QDate::currentDate().addDays(1);
    break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
    date = QDate::currentDate().addDays( timeBox->currentIndex()-1 - QDate::currentDate().dayOfWeek() );
    if( QDate::currentDate().daysTo(date) < 1 ){
      date = date.addDays(7);
    }
    break;
  default:
    break;
  }
  TodoObject object( name, date );
  model->addTodo(object);
  doEdit->setText("");
}

void MainWindow::showContextMenu(QPoint point)
{
  if( !view->indexAt(point).isValid() ){
    return;
  }
  QList<QAction*> actionList;
  actionList.push_back(editAct);
  actionList.push_back(doneAct);
  QMenu::exec(actionList, view->mapToGlobal(point));
}

void MainWindow::removeTodo()
{
  model->removeTodo( filterModel->mapToSource(view->currentIndex()) );
}

void MainWindow::editTodo()
{
  QModelIndex index = filterModel->mapToSource(view->currentIndex());
  TodoObject object = model->getTodo(index);
  EditDialog dialog;
  dialog.editTodo(&object);
  if( dialog.exec() == QDialog::Accepted ){
    model->updateTodo(object, index);
  }
}

void MainWindow::showCat(int comboIndex)
{
  filterModel->setCategoryFilter( comboIndex-1 );
}

void MainWindow::expandSections(const QModelIndex &index, const QModelIndex &)
{
  view->expand( filterModel->mapFromSource(index) );
}

void MainWindow::setupGui()
{
  model = new TreeModel(this);
  model->addSection("Overdue", -1 );
  model->addSection("Today", 0);
  model->addSection("Tomorrow", 1 );
  model->addSection("Next week", 7);
  model->addSection("Next Month", 31);
  model->addSection("Future", -2);
  filterModel = new FilterModel(this);
  filterModel->setSourceModel(model);
  view = new QTreeView(this);
  delegate = new TodoDelegate(view, this);
  view->setModel(filterModel);
  view->setHeaderHidden(true);
  view->setIconSize(QSize(0,0));
  view->setAnimated(true);
  view->setStyleSheet("QTreeView::branch{border-image: none; image: none;border-left: 0px;}");
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //view->setTabKeyNavigation(true);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
  view->setRootIsDecorated(false);
  view->setSortingEnabled(false);
  view->setAllColumnsShowFocus(true);
  view->setExpandsOnDoubleClick(true);
  view->header()->setStretchLastSection(false);
  view->header()->setResizeMode(0,QHeaderView::Stretch);
  view->setItemDelegate(delegate);
  view->setContextMenuPolicy(Qt::CustomContextMenu);
  
  doEdit = new KLineEdit(this);
  doEdit->setClickMessage("new task...");
  view->setFocusProxy(doEdit);
//  doAddBtn = new KPushButton(KIcon("list-add"),"",this);
  doAddBtn = new QToolButton();
  doAddBtn->setIcon(KIcon("list-add"));
  doAddBtn->setIconSize(QSize(35,35));
  timeBox = new QComboBox(this);
  timeBox->addItem("Today");
  timeBox->addItem("Tomorrow");
  timeBox->addItem("Next Monday");
  timeBox->addItem("Next Tuesday");
  timeBox->addItem("Next Wednesday");
  timeBox->addItem("Next Thursday");
  timeBox->addItem("Next Friday");
  timeBox->addItem("Next Saturday");
  timeBox->addItem("Next Sunday");
  timeBox->addItem("Future");
  timeBox->setFocusProxy(doEdit);
  addLayout = new QGridLayout;
  addLayout->addWidget(doEdit, 0,0);
  addLayout->addWidget(timeBox, 1,0);
  addLayout->addWidget(doAddBtn, 0,1,2,2);
  
  categoryBox = new QComboBox();
  categoryBox->addItem("All");
  for( int i=0; i<Settings::self()->categories()->count(); i++ ){
    categoryBox->addItem(Settings::self()->categories()->at(i));
  }
  selectLayout = new QHBoxLayout();
  selectLayout->addWidget(categoryBox);
  selectLayout->addStretch();
  
  doneBtn = new KPushButton(KIcon("checkbox"),"Done");
  editBtn = new KPushButton(KIcon("document-edit"),"Edit");
  configBtn = new KPushButton(KIcon("configure"), "Configure");
  bottomLayout = new QHBoxLayout;
  bottomLayout->addStretch();
  bottomLayout->addWidget(editBtn);
  bottomLayout->addWidget(doneBtn);
  bottomLayout->addWidget(configBtn);
  
  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(addLayout);
  mainLayout->addWidget(view);
  mainLayout->addLayout(selectLayout);
  mainLayout->addLayout(bottomLayout);
  setLayout(mainLayout);
  setWindowTitle("DoBeeDo");
  
  doneAct = new QAction("Done", this);
  editAct = new QAction("Edit", this);
  
  connect( view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)) );
  connect( doEdit, SIGNAL(returnPressed()), doAddBtn, SLOT(animateClick()) );
  connect( doAddBtn, SIGNAL(clicked()), this, SLOT(newTodo()) );
  connect( doneAct, SIGNAL(triggered()), this, SLOT(removeTodo()) );
  connect( doneBtn, SIGNAL(clicked()), this, SLOT(removeTodo()) );
  connect( editAct, SIGNAL(triggered()), this, SLOT(editTodo()) );
  connect( editBtn, SIGNAL(clicked()), this, SLOT(editTodo()) );
  connect( categoryBox, SIGNAL(currentIndexChanged(int)), this, SLOT(showCat(int)) );
}
