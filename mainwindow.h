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

#include <KXmlGuiWindow>
#include <QModelIndex>

class KLineEdit;
class KPushButton;
class KAction;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QTreeView;
class KComboBox;
class QToolButton;
class TreeModel;
class FilterModel;
class TodoDelegate;
class ConfigDialog;
class SysTray;

class MainWindow : public KXmlGuiWindow
  /* MainWindow handles the TodoObjects model and the corresponding view.
   * All the modifications the user makes on the todo list are controlled
   * by MainWindow. MainWindow needs a pointer to the system tray icon to
   * inform it about changes in the todo list.
   */
{
    Q_OBJECT
  public:
    explicit MainWindow( SysTray* _systray, QWidget* parent = 0 );
    ~MainWindow();
    
  protected:
    void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *event);
    
  private slots:
    // adds todo item by reading from doEdit and categoryBox
    void newTodo();
    // shows context menu in the view
    void showContextMenu( QPoint point );
    void removeTodo();
    void editTodo();
    // select the categoy shown in the view. If comboIndex is -1, then
    // all categories are shown.
    void showCat( int comboIndex );
    // expands a section if anything is changed in it
    void expandSections( const QModelIndex& index, const QModelIndex& );
    void showConfigDialog();
    void configChanged();
    
  private:
    // inform the system tray about changes
    void todosChanged();
    void setupGui();
    
    QWidget* mainWidget;
    TreeModel* model;
    FilterModel* filterModel;
    TodoDelegate* delegate;
    ConfigDialog* configDialog;
    SysTray* systray;
    QTreeView* view;
    KLineEdit* doEdit;
    QToolButton* doAddBtn;
    KPushButton* doneBtn;
    KPushButton* editBtn;
    KComboBox* timeBox;
    KComboBox* categoryBox;
    KComboBox* addSelectCatBox;
    QGridLayout* addLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* bottomLayout;
    
    KAction* doneAct;
    KAction* editAct;
    KAction* configAct;
    
    // to check for day change
    QDate* curDate;
    int dateCheckTimer;
};

#endif //MAINWINDOW_H
