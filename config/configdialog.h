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

class GeneralWidget;
class CategoryWidget;
class PriorityWidget;

class ConfigDialog : public KPageDialog
  /* The main config dialog. It has one page to edit the categories and one
   * to edit the colors of the priorities at the moment. 
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
  KPageWidgetItem* generalPage;
  GeneralWidget* generalWidget;
  KPageWidgetItem* categoryPage;
  CategoryWidget* categoryWidget;
  KPageWidgetItem* priorityPage;
  PriorityWidget* priorityWidget;
};

#endif // CONFIGDIALOG_H
