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

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "../todoobject.h"

class TreeItem;

class TreeModel : public QAbstractItemModel
  /* The TreeModel class is a model that is specialized for TodoObjects.
   * It implements the functions needed to be a tree model class and adds
   * some functions to make working with it easier.
   * The TodoObjects saved in the tree model are divided in different sections,
   * based on their due date (to be done today, to be done tomorrow).
   */
{
    Q_OBJECT
  public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();
    
    // adds a section with name and the maximal number of days the tasks in this
    // section should have until they have to be done (example: addSection( "today", 0 ).
    // daysTo == -2 means that the TodoObjects have no date set, or have higher daysTo 
    // than any section ("future")
    void addSection( QString name, int daysTo );
    // Adds a TodoObject to the tree model. It is automatically added to a section.
    // If the TodoObject is invalid, it will be ignored. Returns the index where the
    // object was added.
    QModelIndex addTodo( const TodoObject& object );
    void removeTodo( const QModelIndex& index );
    // mostly a combination of deleting the old object and adding the new one
    QModelIndex updateTodo( const TodoObject& newObj, const QModelIndex& oldIndex);
    TodoObject getTodo( const QModelIndex& index );
    // get a list of all TodoObjects in the model. You need to take care of removing the list.
    QList<TodoObject>* getAllTodo();
    // deletes all TodoObjects in the model and adds the ones in the list. This will delete the
    // list afterwards.
    void resetAllTodo( QList<TodoObject>* list );

    // the following functions are only needed by the view and delegate, so if you don't want to
    // change anything in the model/view architecture, you don't need to care about these.
    
    QVariant data(const QModelIndex &index, int role) const;
    // used to let the user change the checked-state
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCountActive(const QModelIndex &parent = QModelIndex() ) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    
    //QModelIndex addItem( QList<QVariant>& data, const QModelIndex& parent=QModelIndex() );
    
  signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    
  private slots:
    // remove checked todos
    void delayedRemove();
    
  private:
    QModelIndex addTodoToSection( TreeItem* item, TreeItem* section );
    
    TreeItem* rootItem;
    QList<QModelIndex>* removeDelayList;
};

#endif //TREEMODEL_H
