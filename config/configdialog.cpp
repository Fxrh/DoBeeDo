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

#include "configdialog.h"
#include "categorywidget.h"
#include "prioritywidget.h"

#include <QLabel>

ConfigDialog::ConfigDialog(QWidget *parent)
  : KPageDialog(parent)
{
  categoryWidget = new CategoryWidget();
  categoryPage = new KPageWidgetItem(categoryWidget, "Categories");
  priorityWidget = new PriorityWidget();
  priorityPage = new KPageWidgetItem(priorityWidget, "Priorities");
  
  addPage(categoryPage);
  addPage(priorityPage);
}

void ConfigDialog::accept()
{
  categoryWidget->save();
  priorityWidget->save();
  KPageDialog::accept();
}

void ConfigDialog::reject()
{
  categoryWidget->restore();
  priorityWidget->restore();
  KPageDialog::reject();
}

void ConfigDialog::clear()
{
  categoryWidget->restore();
  priorityWidget->restore();
}

const QStringList* ConfigDialog::getCatOpList()
{
  return categoryWidget->getCatOpList();
}

const QList<int>* ConfigDialog::getCatIdList()
{
  return categoryWidget->getCatIdList();
}
