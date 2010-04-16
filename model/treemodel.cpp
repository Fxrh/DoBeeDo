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

#include "treeitem.h"
#include "treemodel.h"

#include <QDebug>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
  rootItem = new TreeItem();
  reset();
 }

TreeModel::~TreeModel()
{
  delete rootItem;
  qDebug() << "TreeModel: Destroyed";
}

void TreeModel::addSection(QString name, int daysTo)
{
  TreeItem* item = new TreeItem( name, daysTo, rootItem );
  
  int i=0;
  if( item->sectionDaysTo() == -2 ){ // -2 == Future/Not set
    rootItem->appendChild(item);
    return;
  }
  for( i=0; i < rootItem->childCount(); i++ ){
    if( rootItem->child(i)->sectionDaysTo() == -2 ){ // Again, Future
      break;
    }
    if( rootItem->child(i)->sectionDaysTo() > item->sectionDaysTo() ){
      break;
    }
  }
  beginInsertRows(QModelIndex(), i, i );
  rootItem->insertChild(item, i);
  endInsertRows();
}

QModelIndex TreeModel::addTodo(const TodoObject &object)
{
  if( object.getName() == "" ){
    qDebug() << "Empty Todo...";
    return QModelIndex();
  }
  TreeItem* item;
  // Invalid:
  if( object.getDate().isNull() ){
    int last = rootItem->childCount()-1;
    item = new TreeItem( object, rootItem->child( last ) );
    return addTodoToSection(item,rootItem->child(rootItem->childCount()-1));
  }
  for( int i=0; i < rootItem->childCount(); i++ ){
    if( rootItem->child(i)->sectionDaysTo() == -2 ){ // Again, we are at the end
      item = new TreeItem( object, rootItem->child(i) );
      return addTodoToSection(item,rootItem->child(i));
    }
    if( rootItem->child(i)->sectionDaysTo() >= object.getDaysTo() ){
      item = new TreeItem( object, rootItem->child(i) );
      return addTodoToSection(item,rootItem->child(i));
    }
  }
  qDebug() << "Whoops, your todo object was added nowhere..";
  return QModelIndex();
}

void TreeModel::removeTodo(const QModelIndex &index)
{
  if( !index.isValid() ){
    qDebug() << "Index invalid!";
    return;
  }
  TreeItem* itemToDelete = static_cast<TreeItem*>(index.internalPointer());
  if( !itemToDelete->isTodo() ){
    return;
  }
  TreeItem* parentDelete = itemToDelete->parent();
  if( parentDelete == 0 ){
    //parentDelete = rootItem;
    qDebug() << "Trying to delete root";
    return; //We cannot remove root item
  }
  beginRemoveRows(index.parent(), itemToDelete->row(), itemToDelete->row() );
  parentDelete->removeChild( itemToDelete->row() );  
  endRemoveRows();
  // Here we also have to update section
  emit dataChanged( index.parent(), index.parent() );
}

QModelIndex TreeModel::updateTodo(const TodoObject &newObj, const QModelIndex &oldIndex)
{
  removeTodo( oldIndex );
  return addTodo( newObj ); 
}

TodoObject TreeModel::getTodo(const QModelIndex &index)
{
  if( !index.isValid() ){
    qDebug() << "Index invalid!";
    return TodoObject("");
  }
  TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
  TodoObject object( *(item->todo()) );
  return object;
}

QList<TodoObject>* TreeModel::getAllTodo()
{
  QList<TodoObject>* list = new QList<TodoObject>();
  for(int i=0; i<rootItem->childCount(); i++){
    TreeItem* tmpObj = rootItem->child(i);
    for( int j=0; j<tmpObj->childCount(); j++){
      list->push_back( *tmpObj->child(j)->todo() );
    }
  }
  return list;
}

void TreeModel::resetAllTodo( QList<TodoObject>* list )
{
  for( int i=0; i<rootItem->childCount(); i++ ){
    TreeItem* item = rootItem->child(i);
    for( int j=0; j<item->childCount(); i++){
      item->removeChild(j);
    }
  }
  
  if( list == 0 ){
    return;
  }
  
  foreach( TodoObject obj, *list ){
    addTodo( obj );
  } 
  delete list;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  else
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  
  if (role != Qt::DisplayRole)
    return QVariant();
  
  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
  
  return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return 0;
  
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
    if( section == 0 ){
      return "Name";
    } else {
      return "Date";
    }
  }

  return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  TreeItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TreeItem*>(parent.internalPointer());
  
  TreeItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);
  else
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
    return QModelIndex();
  
  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parent();

  if (parentItem == rootItem)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  TreeItem *parentItem;
  if (parent.column() > 0)
    return 0;
  
  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TreeItem*>(parent.internalPointer());

  return parentItem->childCount();
}

QModelIndex TreeModel::addTodoToSection(TreeItem* item, TreeItem *section)
{
  int i=0;
  while( i < section->childCount() ){ // sort by priority
    if( item->todo()->getPriority() <= section->child(i)->todo()->getPriority() ){
      break;
    }
    i++;
  }
  // sort by date
  while( i < section->childCount() 
         && item->todo()->getPriority() == section->child(i)->todo()->getPriority() ){
    if( item->todo()->getDate() <= section->child(i)->todo()->getDate() ){
      break;
    }
    i++;
  }
  // sort by name
  while( i < section->childCount() 
         && item->todo()->getPriority() == section->child(i)->todo()->getPriority()
         && item->todo()->getDate() == section->child(i)->todo()->getDate() ){
    if( item->todo()->getName().toLower() < section->child(i)->todo()->getName().toLower() ){
      break;
    }
    i++;
  }
  
  beginInsertRows( index(section->row(),0,QModelIndex()), i, i );
  section->insertChild(item, i);
  endInsertRows();
  // check if section is empty now
  emit dataChanged( index(section->row(),0,QModelIndex()), index(section->row(),0,QModelIndex()) );
  qDebug() << "dataChanged: " << section->row();
  return index( i, 0, index(section->row(), 0, QModelIndex()) ); // return index of new element
}

//QModelIndex TreeModel::addItem( QList<QVariant>& data, const QModelIndex& parent )
//{
//  TreeItem* parentItem;
//  if( !parent.isValid() ){
//    parentItem = rootItem;
//  }
//  else {
//    parentItem = static_cast<TreeItem*>(parent.internalPointer());
//  }
//  TreeItem* item = new TreeItem(data, parentItem);
//  parentItem->appendChild(item);
//  return createIndex( item->row(), 0, item);
//}
