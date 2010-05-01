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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <KPageDialog>

class CategoryWidget;

class ConfigDialog : public KPageDialog
  /* The main config dialog. Has only one page to edit the categories at the moment
   */
{
  Q_OBJECT
public:
  ConfigDialog(QWidget *parent = 0);
  
  void accept();
  void reject();
  // Call this before you show this dialog
  void clear();
  
  // see CategoryWidget::getCatOpList()
  const QStringList* getCatOpList();
  // see CategoryWidget::getCatIdList()
  const QList<int>* getCatIdList();
  
private:
  KPageWidgetItem* categoryPage;
  CategoryWidget* categoryWidget;
};

#endif // CONFIGDIALOG_H
