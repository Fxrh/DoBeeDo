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
#include "todoobject.h"

class QSettings;
class QStringList;

class Settings : public QObject
{
public:
  static Settings* self();
  static void destroy();
  
  QList<TodoObject>* getTodoList();
  QStringList* categories() const { return categoriesList; }
  void setCategories( QStringList* list ); 
  void setTodoList( QList<TodoObject>* list );
  
private:
  Settings();
  Settings( const Settings& cc );
  ~Settings();
  
  void load();
  void save();
  QString getPath();
  
  static Settings* instance;
  
  QSettings* settingsFile;
  QStringList* categoriesList;
  
  const quint32 magicNumber;
  const quint16 dataVersion;// = 0x0001;
};

#endif //SETTINGS_H
