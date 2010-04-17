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

#include "filtermodel.h"
#include "settings.h"

#include <QStringList>
#include <QDebug>

FilterModel::FilterModel(QObject *parent)
  : QSortFilterProxyModel(parent)
{
  catFilterNum = -1;
  setDynamicSortFilter(true);
}

bool FilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
  //sections
  if( !source_parent.isValid() ){ 
    // remove empty sections...
    QModelIndex secIndex = sourceModel()->index(source_row, 0, source_parent);
    if( sourceModel()->rowCount(secIndex) == 0 ){
      return false;
    }
    // test if section is empty after categories-specific removing
    if( catFilterNum != -1 ){
      bool hasChildren = false;
      for( int i=0; i<sourceModel()->rowCount( sourceModel()->index(source_row,0,QModelIndex()) ); i++ ){
        if( sourceModel()->index(i,0,secIndex).data().toMap().value("category",0).toInt() == catFilterNum ){
          hasChildren = true;
          break;
        }
      }
      return hasChildren;
    }
    return true;
  }
  
  // now, filter the categories
  if( catFilterNum == -1 ){
    return true; //All categories -> no filtering
  }
  int cat = sourceModel()->index(source_row, 0, source_parent).data().toMap().value("category",0).toInt();
  if( cat == catFilterNum ){
    return true;
  } else {
    return false;
  }
}

void FilterModel::setCategoryFilter(int cat_num)
{
  if( cat_num < -1 || cat_num > Settings::self()->categories()->count()-1 ){
    cat_num = 0;
  }
  catFilterNum = cat_num;
  qDebug() << "CategoryFilter: " << catFilterNum;
  invalidate();
  //sourceModel()->dataChanged( sourceModel()->index(0,0,QModelIndex()), sourceModel()->index( sourceModel()->rowCount(QModelIndex()), 0, QModelIndex() ) );
}

int FilterModel::categoryFilter()
{
  return catFilterNum;
}
