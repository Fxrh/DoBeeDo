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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include "todoobject.h"

class QSettings;
class QStringList;

class Settings : public QObject
  /* Settings is the configuration manager of DoBeeDo. It is a sigleton class,
   * so if you want to use it, call for an instance with Settings::self().
   * To save the changes you have to call destroy() when exiting the application.
   */
{
  Q_OBJECT
public:
  // call to get an instance of the Settings class
  static Settings* self();
  // delete the instance and save all data
  static void destroy();
  
  // Position of the main window
  QPoint getPosition() { return position; }
  // Size of the main window
  QSize getSize() { return size; }
  // The saved list of the todo items, saved in todo.data
  QList<TodoObject>* getTodoList();
  // The categories we have atm
  QStringList* categories() const { return categoriesList; }
  void setPosition( QPoint pos ) { position = pos; }
  void setSize( QSize _size ) { size = _size; }
  void setCategories( QStringList* list ); 
  void setTodoList( QList<TodoObject>* list );
  
  void emitConfigChanged();// { emit configChanged(); qDebug("Emitted"); }
  
signals:
  void sigConfigChanged();
  
private:
  Settings();
  Settings( const Settings& cc );
  ~Settings();
  
  void load();
  void save();
  QString getPath();
  
  static Settings* instance;
  
  QSettings* settingsFile;
  QPoint position;
  QSize size;
  QStringList* categoriesList;
  
  const quint32 magicNumber;
  const quint16 dataVersion;// = 0x0001;
};

#endif //SETTINGS_H
