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

#include "tododelegate.h"
#include <QStyle>
#include <QPainter>
#include <QPoint>
#include <QTreeView>
#include <KIcon>
#include <QDebug>
#include "treeitem.h"

TodoDelegate::TodoDelegate( QTreeView* _view, QWidget* parent )
  : QStyledItemDelegate(parent),
  view(_view)
{
  boldFont.setBold(true);
  boldFont.setPointSize(11);
}

void TodoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyledItemDelegate::paint(painter,option,index);
//  if( option.state & QStyle::State_Selected ){
//    painter->fillRect(option.rect, option.palette.highlight() );
//  }
  
  QPoint originPoint = option.rect.topLeft();
  originPoint.rx()++;
  originPoint.ry()++;
  
  QMap<QString,QVariant> map( index.data().toMap() );
  
  if( map["type"] == 0 ){
    if( index.column() != 0 ){
      return;
    }
    QString iconName;
    if( view->isExpanded(index) ){
      iconName = "arrow-down";
    } else {
      iconName = "arrow-right";
    }
    QRect iconRect(originPoint, QSize(15,15));
    painter->drawPixmap(iconRect, KIcon(iconName).pixmap(QSize(15,15)) );
    painter->save();
    painter->setFont(boldFont);
    QPoint writePoint( originPoint + QPoint(iconRect.size().width()+5,0) );
    QRect rect();
    painter->drawText( QRect( writePoint, option.rect.bottomRight() ), map["name"].toString() );
    painter->restore();
  }
  
  if( map["type"] == 1 ){
    if( index.column() == 0 ){
      painter->drawText( QRect(originPoint,option.rect.bottomRight()), map["name"].toString() );
    } else {
      painter->drawText( QRect(originPoint,option.rect.bottomRight()), map["date"].toDate().toString());
      if(map["date"].toDate().isNull()){
        painter->drawText( QRect(originPoint,option.rect.bottomRight()), "-");
      }
    }
  }
}

QSize TodoDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QMap<QString,QVariant> map( index.data().toMap() );
  if( map["type"] == 0 ){
    if( index.column() != 0 )
      return QSize();
    QFontMetrics metrics(boldFont);
    return metrics.boundingRect(map["name"].toString()).size()+QSize(22,2);
  }
  if( map["type"] == 1 ){
    QFontMetrics metrics(standardFont);
    if( index.column() == 0 )
      return metrics.boundingRect(map["name"].toString()).size();
    return metrics.boundingRect(map["date"].toDate().toString()).size()+QSize(2,2);
  }
  return QSize();
}
