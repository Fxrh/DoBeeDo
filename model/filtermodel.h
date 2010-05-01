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

#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>

class FilterModel : public QSortFilterProxyModel
  /* FilterModel is between the view and the model desiding which row 
   * should be shown. Empty sections are fitered out. Furthermore, if set,
   * it only shows todo items from a special category (see setCategoryFilter).
   */
{
  Q_OBJECT
public:
  FilterModel( QObject* parent=0 );
  
  // decide if a row should be shown
  bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
  // set the category which should be exclusivly shown. If cat_num is -1, then all
  // categories are shown.
  void setCategoryFilter( int cat_num );
  // returns the number of the category that is shown. Returns -1 if all are shown.
  int categoryFilter();
  
private:
  int catFilterNum;
};

#endif //FILTERMODEL_H
