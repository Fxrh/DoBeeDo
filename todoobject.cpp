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

#include "todoobject.h"
#include "settings.h"
#include <QDebug>
#include <QStringList>

TodoObject::TodoObject( QString _name, QDate _date )
{
  name = _name;
  date = _date;
  description = "";
  priority = 4;
  category = 0;
}

TodoObject::TodoObject( const TodoObject& old )
{
  name = old.getName();
  date = old.getDate();
  description = old.getDescription();
  priority = old.getPriority();
  category = old.getCategory();
}

TodoObject::~TodoObject()
{
}

void TodoObject::setPriority(int num)
{
  if( num > 4 || num < 1 ){
    num = 4;
  }
  priority = num;
}

void TodoObject::setCategory(int cat)
{
  if( cat > Settings::self()->categories()->count() || cat < 0 ){
    cat = 0;
  }
  category = cat;
}

int TodoObject::getDaysTo() const 
{
  //qDebug() << name << ": " << QDate::currentDate().daysTo(date);
  return QDate::currentDate().daysTo(date);
}

QDataStream& operator<<( QDataStream& out, const TodoObject& object )
{
  out << object.getName() << object.getDescription() << object.getDate() << object.getPriority() << object.getCategory();
  return out;
}

QDataStream& operator>>( QDataStream& in, TodoObject& object )
{
  QString name;
  QString description;
  QDate date;
  int priority;
  int category;
  in >> name >> description >> date >> priority >> category;
  object = TodoObject(name, date);
  object.setDescription(description);
  object.setPriority(priority);
  object.setCategory(category);
  return in;
}
