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
#include <KColorScheme>
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
  KColorScheme colorScheme( option.palette.currentColorGroup() );
  
//  if( option.state & QStyle::State_Selected ){
//    painter->fillRect(option.rect, option.palette.highlight() );
//  }
  
  QPoint originPoint = option.rect.topLeft();
  originPoint.rx()++;
  originPoint.ry()++;
  
  QMap<QString,QVariant> map( index.data().toMap() );
  
  QStyleOptionViewItem newOption = option;
  if( map["type"] == 1 ){
    switch( map["priority"].toInt() ){
    case 1:
      newOption.palette.setColor(QPalette::Background, colorScheme.background(KColorScheme::NegativeBackground).color());
      painter->fillRect(newOption.rect, newOption.palette.background());
      break;
    case 2:
      newOption.palette.setColor(QPalette::Background, colorScheme.background(KColorScheme::NeutralBackground).color());
      painter->fillRect(newOption.rect, newOption.palette.background());
      break;
    case 3:
      newOption.palette.setColor(QPalette::Background, colorScheme.background(KColorScheme::PositiveBackground).color());
      painter->fillRect(newOption.rect, newOption.palette.background());
      break;
    default:
      break;
    }
  }  
  QStyledItemDelegate::paint(painter,newOption,index);
  
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
    QString text = cutString( map["name"].toString(), QRect( writePoint, newOption.rect.bottomRight() ), boldFont );
    painter->drawText( QRect( writePoint, newOption.rect.bottomRight() ), text );
    painter->restore();
  }
  
  if( map["type"] == 1 ){
    if( index.column() == 0 ){
      QString text = map["name"].toString();
//      if( map["priority"].toInt() == 4 ){
//        text.prepend("- ");
//      } else {
//        text.prepend( QString::number(map["priority"].toInt()) + " " );
//      }
      text = cutString( text, QRect(originPoint,newOption.rect.bottomRight()), standardFont );
      painter->drawText( QRect(originPoint,newOption.rect.bottomRight()), text );
    } else {
      QString text = cutString( map["date"].toDate().toString(), QRect(originPoint,newOption.rect.bottomRight()), standardFont );
      painter->drawText( QRect(originPoint,newOption.rect.bottomRight()), text);
      if(map["date"].toDate().isNull()){
        painter->drawText( QRect(originPoint,newOption.rect.bottomRight()), "-");
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
      return metrics.boundingRect("- "+map["name"].toString()).size();
    return metrics.boundingRect(map["date"].toDate().toString()).size()+QSize(2,2);
  }
  return QSize();
}

QString TodoDelegate::cutString( const QString &string, const QRect &size, const QFont &font) const
{
  QString myString(string);
  QFontMetrics metrics(font);
  if( metrics.boundingRect(myString).width()+5 < size.width() ){ // I had to add 5, else it didn't work
    return myString;
  }
  myString.append("...");
  while( metrics.boundingRect(myString).width()+5 >= size.width() ){
    myString.remove(myString.count()-4,1);
  }
  qDebug() << myString;
  return myString;
}
