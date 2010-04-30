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

#ifndef CATEGORYWIDGET
#define CATEGORYWIDGET

#include <QWidget>

class QStringListModel;
class QListView;
class QVBoxLayout;
class QHBoxLayout;
class KPushButton;

class CategoryWidget : public QWidget
{
  Q_OBJECT
public:
  CategoryWidget( QWidget* parent=0 );
  ~CategoryWidget();
  
  /* catOpList contains operations done on the settings list, catIdList the associated
   * ids of the categories. Apply those to the Todo objects (if removed set the Todo to 
   * standard and all Todos with higher categories have to get a decreased category number 
   */
  const QStringList* getCatOpList();
  const QList<int>* getCatIdList();
  
public slots:
  void save();
  void restore();
  
private slots:
  void add();
  void rename();
  void remove();
  
private:
  void setupUi();
  
  QStringList* catOpList;
  QList<int>* catIdList;
  QStringListModel* model;
  QListView* view;
  KPushButton* addBtn;
  KPushButton* renameBtn;
  KPushButton* removeBtn;
  QVBoxLayout* buttonLayout;
  QHBoxLayout* mainLayout;
  
};

#endif //CATEGORYWIDGET
