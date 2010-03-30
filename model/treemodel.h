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
{
    Q_OBJECT
  public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();
    
    void addSection( QString name, int daysTo );
    void addTodo( const TodoObject& object );
    void removeTodo( const QModelIndex& index );
    void updateTodo( const TodoObject& newObj, const QModelIndex& oldIndex);
    TodoObject getTodo( const QModelIndex& index );
    QList<TodoObject>* getAllTodo();
    void resetAllTodo( QList<TodoObject>* list );

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    
    //QModelIndex addItem( QList<QVariant>& data, const QModelIndex& parent=QModelIndex() );
    
  private:
    void addTodoToSection( TreeItem* item, TreeItem* section );
    
    TreeItem* rootItem;
};

#endif //TREEMODEL_H
