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

#include <QStringList>
#include <QDebug>

#include "treeitem.h"

TreeItem::TreeItem(const TodoObject& data, TreeItem* parent)
{
  parentItem = parent;
  dataObj = new TodoObject(data);
  type = Todo;
  name = "";
  daysTo = -2;
  numColumns = 2;
  childItems.clear();
}

TreeItem::TreeItem(QString sectionName, int days, TreeItem* parent )
{
  parentItem = parent;
  dataObj = 0;
  type = Section;
  name = sectionName;
  daysTo = days;
  numColumns = 2;
  childItems.clear();
}

TreeItem::TreeItem()
{
  parentItem = 0;
  dataObj = 0;
  type = Root;
  name = "";
  daysTo = -2;
  numColumns = 2;
  childItems.clear();
}

TreeItem::~TreeItem()
{
  qDebug() << "Childs: " << childItems.count();
  qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
  if( type == Root ){
    if( item->sectionDaysTo() == -2 ){ // -2 == Future/Not set
      childItems.append(item);
      return;
    }
    for( int i=0; i < childItems.count(); i++ ){
      if( childItems.at(i)->sectionDaysTo() == -2 ){ // Again, Future
        childItems.insert(i, item);
        return;
      }
      if( childItems.at(i)->sectionDaysTo() > item->sectionDaysTo() ){
        childItems.insert(i, item);
        return;
      }
    }
    childItems.append(item);
  }
  if( type == Section ){
    childItems.append(item);
  }
  if( type == Todo ){
    qDebug() << "Todo objects should have no childs!";
    return;
  }
  
}

void TreeItem::insertChild(TreeItem *child, int pos)
{
  if( type == Todo )
    return;
  
  childItems.insert(pos,child);
}

void TreeItem::removeChild(int row)
{
  delete childItems.at(row);
  childItems.removeAt(row);
}

TreeItem *TreeItem::child(int row)
{
  return childItems.value(row);
}

int TreeItem::childCount() const
{
  return childItems.count();
}

int TreeItem::columnCount() const
{
  return numColumns;
}

QVariant TreeItem::data(int column) const
{
  if( type == Root ){
    return QVariant();
  }
  QMap<QString,QVariant> map;
  if( type == Section ){
    map[QString("type")] = QVariant::fromValue(0);
    map[QString("name")] = QVariant::fromValue(name);
  } else {
    map[QString("type")] = QVariant::fromValue(1);
    map[QString("name")] = QVariant::fromValue(dataObj->getName());
    map[QString("date")] = QVariant::fromValue(dataObj->getDate());
    map[QString("priority")] = QVariant::fromValue(dataObj->getPriority());
    map[QString("category")] = QVariant::fromValue(dataObj->getCategory());
  }
  return map;
//  if( type == Section ){
//    if( column == 0 ){
//      return name;
//    }
//  }
//  if( type == Root ){
//    return QVariant();
//  }
//  if( type == Todo ){
//    switch( column ){
//      case 0:
//        return dataObj->getName();
//        break;
//      case 1:
//        return dataObj->getDate();
//        break;
//      default:
//        break;
//    }
//  }
  return QVariant();
}

TreeItem *TreeItem::parent()
{
  return parentItem;
}

int TreeItem::row() const
{
  if (parentItem != 0)
    return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
  
  return 0;
}
