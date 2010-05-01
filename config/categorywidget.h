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
  /* This class is part of the config dialog. Here, the user can edit the
   * categories. Be sure to adjust all TodoObjects after editing the categories
   * (see getCatOpList() and getCatIdList() for more information). Call restore()
   * if you want to use this dialog a second time.
   */
{
  Q_OBJECT
public:
  CategoryWidget( QWidget* parent=0 );
  ~CategoryWidget();
  
  // catOpList contains the operations done to the category list. At the moment, the only
  // operation is "REMOVE". Together with getCatIdList, you can adjust the category number 
  // of all TodoObjects (you need to set all TodoObjects with where assigned to the removed
  // category to the category Standard (0), and you have to decrease all category numbers of
  // TodoObjects with a category number higher than the one just removed).
  const QStringList* getCatOpList();
  // returns a list of category numbers on which the user made modifictions. Together with 
  // getCatOpList you can adjust the category numbers of the TodoObjects.
  const QList<int>* getCatIdList();
  
public slots:
  void save();
  void restore();
  
private slots:
  // open a dialog to add a category
  void add();
  // open a dialog to rename the selected category
  void rename();
  // removes the selected category
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
