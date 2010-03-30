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

#ifndef TODOOBJECT_H
#define TODOOBJECT_H

#include <QString>
#include <QDate>
#include <QDataStream>

class TodoObject
{
  public:
    TodoObject( QString _name, QDate _date=QDate::currentDate() );
    TodoObject( const TodoObject& old );
    ~TodoObject();
    
    void setName( QString _name ) { name = _name; }
    void setDate( QDate _date ) { date = _date; }
    QString getName() const { return name; }
    QDate getDate() const { return date; }
    int getDaysTo() const;
    bool isValid() const { return (name != ""); }
    
  private:
    QString name;
    QDate date;
};

QDataStream& operator<<( QDataStream& out, const TodoObject& object );
QDataStream& operator>>( QDataStream& in, TodoObject& object );

#endif //TODOOBJECT_H
