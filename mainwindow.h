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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class KLineEdit;
class KPushButton;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QTreeView;
class QComboBox;
class TreeModel;
class FilterModel;
class TodoDelegate;

class MainWindow : public QWidget
{
    Q_OBJECT
  public:
    MainWindow( QWidget* parent = 0 );
    ~MainWindow();
    
  private slots:
    void newTodo();
    void showContextMenu( QPoint point );
    void removeTodo();
    void editTodo();
    
  private:
    void setupGui();
    
    TreeModel* model;
    FilterModel* filterModel;
    TodoDelegate* delegate;
    QTreeView* view;
    KLineEdit* doEdit;
    KPushButton* doAddBtn;
    KPushButton* doneBtn;
    KPushButton* editBtn;
    QComboBox* timeBox;
    QGridLayout* addLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* bottomLayout;
    
    QAction* doneAct;
    QAction* editAct;
};

#endif //MAINWINDOW_H
