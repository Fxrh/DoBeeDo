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

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>
#include "../todoobject.h"

class TreeItem
{
  public:
    TreeItem( const TodoObject& data, TreeItem* parent );
    TreeItem( QString sectionName, int days, TreeItem* parent );
    TreeItem();
    ~TreeItem();
    
    bool isRoot() const { return type == Root; }
    bool isSection() const { return type == Section; }
    bool isTodo() const { return type == Todo; }
    TodoObject* todo() { return dataObj; }
    QString sectionName() const { return name; }
    int sectionDaysTo() const { return daysTo; }
    
    void appendChild(TreeItem *child);
    void insertChild(TreeItem *child, int pos);
    void removeChild(int row);
    
    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();
    
 private:
    QList<TreeItem*> childItems;
    TreeItem *parentItem;
    int numColumns;
    enum { Root, Section, Todo } type;
    TodoObject* dataObj;
    QString name;
    int daysTo;
};

#endif //TREEITEM_H
