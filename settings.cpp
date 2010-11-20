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

#include "settings.h"

#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>

Settings* Settings::instance = 0;

Settings* Settings::self()
{
  if( instance == 0 ){
    instance = new Settings();
  }
  return instance;
}

void Settings::destroy()
{
  if( instance!=0 ){
    delete instance;
    instance = 0;
  }
}

QList<TodoObject>* Settings::getTodoList()
{
  QList<TodoObject>* list = new QList<TodoObject>;
  
  QFile file(QString(getPath()+"todo.data"));
  if( ! file.open(QIODevice::ReadOnly) ){
    return (QList<TodoObject>*)0;
  }
  QDataStream in(&file);
  
  quint32 magic;
  quint16 data;
  in >> magic >> data;
  if( magic != magicNumber ){
    qDebug() << "todo.data: bad file";
    return (QList<TodoObject>*)0;
  }
  
  while( in.status() == QDataStream::Ok ){
    TodoObject obj("");
    in >> obj;
    if( in.status() == QDataStream::Ok )
      list->push_back(obj);
  }
  return list;
}

void Settings::setCategories(QStringList *list)
{
  delete categoriesList;
  categoriesList = new QStringList(*list);
  //categoriesList = list;
  qDebug() << *categoriesList;
}

void Settings::setTodoList( QList<TodoObject>* list )
{
  if( list == 0 ){
    return;
  }
  QFile file(QString(getPath()+"todo.data"));
  if( ! file.open(QIODevice::WriteOnly) ){
    return;
  }
  QDataStream out(&file);
  out << magicNumber << dataVersion;
  
  foreach( const TodoObject &obj, *list ){
    if( Settings::self()->getRemoveTaskStyle() == Settings::RemoveAfterSession && obj.getChecked() ){
      continue; // don't save that object
    }
    out << obj;
  }
  //file.flush();
  delete list;
}

void Settings::emitConfigChanged()
{
  emit sigConfigChanged();
  qDebug() << "Emitted: " << *categoriesList;
}

Settings::Settings()
  : magicNumber(0x87F2468B),
  dataVersion(0x0001)
{
  load();
}

Settings::~Settings()
{
  save();
}

void Settings::load()
{
  qDebug() << "Settings: load";
  settingsFile = new QSettings( "dobeedo", "dobeedo" ,this);
  position = settingsFile->value("WindowPosition", QVariant::fromValue(QPoint(0,0))).toPoint();
  size = settingsFile->value("WindowSize", QVariant::fromValue(QSize(360,410))).toSize();
  useOwnColor = settingsFile->value("UseOwnPriorityColor", QVariant::fromValue(false)).toBool();
  priority1 = settingsFile->value("Priority1Color", QColor::fromRgbF(0.917327, 0.854505, 0.863172)).value<QColor>();
  priority2 = settingsFile->value("Priority2Color", QColor::fromRgbF(0.985306, 0.946593, 0.900237)).value<QColor>();
  priority3 = settingsFile->value("Priority3Color", QColor::fromRgbF(0.875319, 0.938064, 0.800534)).value<QColor>();
  removeTaskStyle = RemoveTaskStyle(settingsFile->value("RemoveTaskStyle", RemoveAfterSession).toInt());
  categoriesList = new QStringList( settingsFile->value("categories", QVariant::fromValue(QStringList("Standard"))).toStringList() );
  settingsFile->sync();
}

void Settings::save()
{
  settingsFile->setValue("WindowPosition", QVariant::fromValue(position));
  settingsFile->setValue("WindowSize", QVariant::fromValue(size));
  settingsFile->setValue("UseOwnPriorityColor", useOwnColor);
  settingsFile->setValue("Priority1Color", priority1 );
  settingsFile->setValue("Priority2Color", priority2 );
  settingsFile->setValue("Priority3Color", priority3 );
  settingsFile->setValue("RemoveTaskStyle", removeTaskStyle);
  settingsFile->setValue("categories", QVariant::fromValue(*categoriesList));
  delete categoriesList;
}

QString Settings::getPath()
{
  QString path = settingsFile->fileName();
  path = path.left( path.lastIndexOf(QDir::separator())+1 );
  if( !QDir(path).exists() ){
    QDir().mkpath(path);
  }
  return path;
}
