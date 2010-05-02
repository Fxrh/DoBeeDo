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
  /* TodoObject contains the data of one todo item, including its name, 
   * due date, longer description, the number of the category it is assigned
   * to and its priority (priority of 4 means no priority).
   */
{
  public:
    explicit TodoObject( QString _name, QDate _date=QDate::currentDate() );
    TodoObject( const TodoObject& old );
    ~TodoObject();
    
    void setName( QString _name ) { name = _name; }
    void setDescription( QString des ) { description = des; } 
    void setDate( QDate _date ) { date = _date; }
    void setPriority( int num );
    void setCategory( int cat );
    QString getName() const { return name; }
    QString getDescription() const { return description; } 
    QDate getDate() const { return date; }
    int getPriority() const { return priority; }
    int getCategory() const { return category; }
    // returns the amount of days until this task have to be done (0 == today)
    // daysTo == -2 means that the TodoObjects have no date set ("future")
    int getDaysTo() const;
    // check if the TodoObject has a name. I don't want any TodoObjects without
    // a name, so they will be likely sorted out by other classes
    bool isValid() const { return (name != ""); }
    
  private:
    QString name;
    QString description;
    QDate date;
    int priority;
    int category;
};

// To save the todo data as binary file
QDataStream& operator<<( QDataStream& out, const TodoObject& object );
QDataStream& operator>>( QDataStream& in, TodoObject& object );

#endif //TODOOBJECT_H
