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

#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDebug>

#include "../settings.h"
#include "generalwidget.h"

GeneralWidget::GeneralWidget(QWidget *parent)
  : QWidget(parent)
{
  setupUi();
  restore();
}

void GeneralWidget::save()
{
  int num = removeTaskBox->currentIndex();
  switch( num ){
    case 0:
      Settings::self()->setRemoveTaskStyle(Settings::NeverRemove);
      break;
    case 1:
      Settings::self()->setRemoveTaskStyle(Settings::RemoveAfterSession);
      break;
    case 2:
      Settings::self()->setRemoveTaskStyle(Settings::RemoveImmediately);
      break;
    default:
      qDebug() << "GeneralWidget::save(): removeTaskBox should not have that value: " << num;
      break;
  }
}

void GeneralWidget::restore()
{
  switch( Settings::self()->getRemoveTaskStyle() ){
    case Settings::NeverRemove:
      removeTaskBox->setCurrentIndex(0);
      break;
    case Settings::RemoveAfterSession:
      removeTaskBox->setCurrentIndex(1);
      break;
    case Settings::RemoveImmediately:
      removeTaskBox->setCurrentIndex(2);
      break;
  }
}

void GeneralWidget::setupUi()
{
  removeTaskLabel = new QLabel("When to remove done tasks: ");
  removeTaskBox = new QComboBox();
  removeTaskBox->addItem("Never remove done tasks");
  removeTaskBox->addItem("Remove done tasks after Session");
  removeTaskBox->addItem("Remove done tasks immediately");
  
  mainLayout = new QVBoxLayout();
  mainLayout->addWidget(removeTaskLabel);
  mainLayout->addWidget(removeTaskBox);
  mainLayout->addStretch();
  setLayout(mainLayout);
}
