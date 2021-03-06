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
#include "systray.h"
#include "config/configdialog.h"

#include <klineedit.h>
#include <KPushButton>
#include <KAction>
#include <KActionCollection>
#include <KStandardAction>
#include <KApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <KComboBox>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QCloseEvent>
#include <QTimerEvent>
#include <QDebug>
#include <klocalizedstring.h>

MainWindow::MainWindow( SysTray* _systray, QWidget* parent )
  : KXmlGuiWindow(parent, Qt::Window ),
  systray(_systray)
{
  move( Settings::self()->getPosition() );
  resize( Settings::self()->getSize() );
  
  Settings::self();
  configDialog = 0;
  setupGui();
  if( !Settings::self()->getStartInTray() && !Settings::self()->getAlwaysStartInTray() ){
    show();
  }
  
  curDate = new QDate(QDate::currentDate());
  dateCheckTimer = startTimer(60*1000);
  
  model->resetAllTodo( Settings::self()->getTodoList() );
  view->expandAll();
  todosChanged();
  connect( model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(expandSections(QModelIndex,QModelIndex)) );
  connect( model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(todosChanged()) );
  connect( Settings::self(), SIGNAL(sigConfigChanged()), this, SLOT(configChanged()) );
}

MainWindow::~MainWindow()
{
  Settings::self()->setPosition( this->pos() );
  Settings::self()->setSize( this->size() );
  Settings::self()->setStartInTray(isHidden());
  Settings::self()->setTodoList( model->getAllTodo() );
  Settings::destroy();
  qDebug() << "MainWindow: destroyed";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  event->ignore();
  this->hide();
}

void MainWindow::newTodo()
{
  QString name = doEdit->text();
  if( name.isEmpty() ){
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
  object.setCategory( addSelectCatBox->currentIndex() );
  QModelIndex index = model->addTodo(object);
  view->setCurrentIndex( filterModel->mapFromSource(index) );
  doEdit->setText("");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
  if( event->timerId() == dateCheckTimer ){
    if( *curDate != QDate::currentDate() ){
      qDebug() << "dawn of a new day...";
      model->resetAllTodo( model->getAllTodo() );
      todosChanged();
      *curDate = QDate::currentDate();
    }
  }
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
  if( index.parent() == QModelIndex() ){
    return; //hey, it's named editTodo, not editSection!
  }
  TodoObject object = model->getTodo(index);
  EditDialog dialog;
  dialog.editTodo(&object);
  if( dialog.exec() == QDialog::Accepted ){
    QModelIndex newIndex = model->updateTodo(object, index);
    view->setCurrentIndex( filterModel->mapFromSource(newIndex) );
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

void MainWindow::showConfigDialog()
{
  if( configDialog == 0 ){
    configDialog = new ConfigDialog(this);
  }
  configDialog->clear();
  configDialog->exec();
  
  //Now, make all needed changes on the Todo category ids
  const QStringList* opList = configDialog->getCatOpList();
  const QList<int>* idList = configDialog->getCatIdList();
  if( opList->isEmpty() ){
    return;
  }
  QList<TodoObject>* todoList = model->getAllTodo();
  for( int i=0; i<opList->count(); i++){
    if( opList->at(i) == "REMOVE" ){
//      foreach( TodoObject object, *todoList ){
//        if( object.getCategory() == idList->at(i) ){
//          object.setCategory(0);
//        }
//        if( object.getCategory() > idList->at(i) ){
//          object.setCategory( object.getCategory()-1 );
//        }
//      }
      QList<TodoObject>::iterator iter;
      for( iter = todoList->begin(); iter != todoList->end(); ++iter){
        if( iter->getCategory() == idList->at(i) ){
          qDebug() << iter->getName() << ": Set " << iter->getCategory() << " to 0.";
          iter->setCategory(0);
        }
        if( iter->getCategory() > idList->at(i) ){
          qDebug() << iter->getName() << ": Set " << iter->getCategory() << " to " << iter->getCategory()-1 << ".";
          iter->setCategory( iter->getCategory()-1 );
        }
      }
    }
  }
  model->resetAllTodo(todoList);
  //model->resetAllTodo((new QList<TodoObject>()));
}

void MainWindow::configChanged()
{
  categoryBox->clear();
  addSelectCatBox->clear();
  categoryBox->addItem(i18nc("category, show all items", "All"));
  for( int i=0; i<Settings::self()->categories()->count(); i++ ){
    categoryBox->addItem(Settings::self()->categories()->at(i));
    addSelectCatBox->addItem(Settings::self()->categories()->at(i));
  } 
  categoryBox->setCurrentIndex(0);
  addSelectCatBox->setCurrentIndex(0);
  view->repaint();
}

void MainWindow::todosChanged()
{
  int array[6];
  for( int i=0; i<=5; i++ ){
    array[i] = model->rowCountActive( model->index(i, 0, QModelIndex()) );
    //array[i] = model->rowCount( model->index(i,0,QModelIndex()) );
  }
  systray->updateStatusInformation( array[0], array[1], array[2], array[3], array[4], array[5] );
}

void MainWindow::setupGui()
{
  model = new TreeModel(this);
  model->addSection(i18n("Overdue"), -1 );
  model->addSection(i18n("Today"), 0);
  model->addSection(i18n("Tomorrow"), 1 );
  model->addSection(i18n("Next week"), 7);
  model->addSection(i18n("Next month"), 31);
  model->addSection(i18n("Future"), -2);
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
  view->setEditTriggers(QAbstractItemView::AllEditTriggers);
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
  doEdit->setClickMessage(i18n("new task..."));
  view->setFocusProxy(doEdit);
//  doAddBtn = new KPushButton(KIcon("list-add"),"",this);
  doAddBtn = new QToolButton();
  doAddBtn->setIcon(KIcon("list-add"));
  doAddBtn->setIconSize(QSize(35,35));
  timeBox = new KComboBox(this);
  timeBox->addItem(i18n("Today"));
  timeBox->addItem(i18n("Tomorrow"));
  timeBox->addItem(i18n("Next Monday"));
  timeBox->addItem(i18n("Next Tuesday"));
  timeBox->addItem(i18n("Next Wednesday"));
  timeBox->addItem(i18n("Next Thursday"));
  timeBox->addItem(i18n("Next Friday"));
  timeBox->addItem(i18n("Next Saturday"));
  timeBox->addItem(i18n("Next Sunday"));
  timeBox->addItem(i18n("Future"));
  timeBox->setFocusProxy(doEdit);
  addSelectCatBox = new KComboBox(this);
  for( int i=0; i<Settings::self()->categories()->count(); i++ ){
    addSelectCatBox->addItem(Settings::self()->categories()->at(i));
  } 
  addSelectCatBox->setCurrentIndex(0);
  addSelectCatBox->setFocusProxy(doEdit);
  addLayout = new QGridLayout;
  addLayout->addWidget(doEdit, 0,0,1,2);
  addLayout->addWidget(timeBox, 1,0);
  addLayout->addWidget(addSelectCatBox, 1, 1);
  addLayout->addWidget(doAddBtn, 0,2,2,1);
  
  categoryBox = new KComboBox();
  categoryBox->addItem(i18nc("category, show all items", "All"));
  for( int i=0; i<Settings::self()->categories()->count(); i++ ){
    categoryBox->addItem(Settings::self()->categories()->at(i));
  }  
  doneBtn = new KPushButton(KIcon("edit-delete"),i18n("Remove"));
  editBtn = new KPushButton(KIcon("document-edit"),i18n("Edit"));
  bottomLayout = new QHBoxLayout;
  bottomLayout->addWidget(categoryBox);
  bottomLayout->addStretch();
  bottomLayout->addWidget(editBtn);
  bottomLayout->addWidget(doneBtn);
  
  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(addLayout);
  mainLayout->addWidget(view);
  mainLayout->addLayout(bottomLayout);
  
  mainWidget = new QWidget(this);
  mainWidget->setLayout(mainLayout);
  setCentralWidget(mainWidget);
  setWindowTitle("DoBeeDo");
  
  doneAct = new KAction(KIcon("edit-delete"),i18n("Remove"), this);
  editAct = new KAction(KIcon("document-edit"),i18n("Edit"), this);
  configAct = new KAction(KIcon("configure"),i18n("Configure DoBeeDo"),this);
  actionCollection()->addAction("done", doneAct);
  actionCollection()->addAction("edit", editAct);
  actionCollection()->addAction("configDobeedo", configAct);
  KStandardAction::quit( kapp, SLOT(quit()), actionCollection() );
  
  KXmlGuiWindow::setupGUI(Default, "dobeedoui.rc");
  
  connect( view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)) );
  connect( view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editTodo()) );
  connect( doEdit, SIGNAL(returnPressed()), doAddBtn, SLOT(animateClick()) );
  connect( doAddBtn, SIGNAL(clicked()), this, SLOT(newTodo()) );
  connect( doneAct, SIGNAL(triggered()), this, SLOT(removeTodo()) );
  connect( doneBtn, SIGNAL(clicked()), this, SLOT(removeTodo()) );
  connect( editAct, SIGNAL(triggered()), this, SLOT(editTodo()) );
  connect( editBtn, SIGNAL(clicked()), this, SLOT(editTodo()) );
  connect( categoryBox, SIGNAL(currentIndexChanged(int)), this, SLOT(showCat(int)) );
  connect( categoryBox, SIGNAL(currentIndexChanged(int)), view, SLOT(expandAll()) );
  connect( configAct, SIGNAL(triggered()), this, SLOT(showConfigDialog()) );
}
