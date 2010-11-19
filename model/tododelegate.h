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

#ifndef TODODELEGATE_H
#define TODODELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QFont>
#include <QModelIndex>

class QPainter;
class QTreeView;

class TodoDelegate : public QStyledItemDelegate
  /* The delegate class in this Qt Model/View architecture. It paints the data
   * in the QTreeView. 
   */
{
  Q_OBJECT
public:
  explicit TodoDelegate( QTreeView* _view, QWidget* parent = 0  );
  
  QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;
  void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
  QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  
private:
  // function that cuts strings to a suitable length using "..." at the end of the cut string
  QString cutString( const QString& string, const QRect& size, const QFont& font ) const;
  
  QFont boldFont;
  QFont standardFont;
  QTreeView* view;
};

#endif //TODODELEGATE_H
