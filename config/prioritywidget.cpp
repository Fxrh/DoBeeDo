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

#include "prioritywidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <KColorButton>
#include <KColorDialog>
#include "../settings.h"

PriorityWidget::PriorityWidget(QWidget* parent)
  : QWidget(parent)
{
  setupUi();
  connect( useOwnBox, SIGNAL(toggled(bool)), pri1Button, SLOT(setEnabled(bool)) );
  connect( useOwnBox, SIGNAL(toggled(bool)), pri2Button, SLOT(setEnabled(bool)) );
  connect( useOwnBox, SIGNAL(toggled(bool)), pri3Button, SLOT(setEnabled(bool)) );
  restore();
}

void PriorityWidget::save()
{
  Settings::self()->setUseOwnColor( useOwnBox->isChecked() );
  if( useOwnBox->isChecked() ){
    Settings::self()->setPriority1(pri1Button->color());
    Settings::self()->setPriority2(pri2Button->color());
    Settings::self()->setPriority3(pri3Button->color());
  }
}

void PriorityWidget::restore()
{
  bool useOwn = Settings::self()->getUseOwnColor();
  useOwnBox->setChecked( useOwn );
  pri1Button->setColor( Settings::self()->getPriority1() );
  pri2Button->setColor( Settings::self()->getPriority2() );
  pri3Button->setColor( Settings::self()->getPriority3() );
  pri1Button->setEnabled( useOwn );
  pri2Button->setEnabled( useOwn );
  pri3Button->setEnabled( useOwn );
}

void PriorityWidget::setupUi()
{
  useOwnBox = new QCheckBox("Use own background colors");
  pri1Label = new QLabel("Color for priority 1: ");
  pri2Label = new QLabel("Color for priority 2: ");
  pri3Label = new QLabel("Color for priority 3: ");
  pri1Button = new KColorButton();
  pri2Button = new KColorButton();
  pri3Button = new KColorButton();
  
  mainLayout = new QGridLayout;
  mainLayout->addWidget(useOwnBox, 0, 0, 1, 2 );
  mainLayout->addWidget(pri1Label, 1, 0);
  mainLayout->addWidget(pri2Label, 2, 0);
  mainLayout->addWidget(pri3Label, 3, 0);
  mainLayout->addWidget(pri1Button, 1, 1);
  mainLayout->addWidget(pri2Button, 2, 1);
  mainLayout->addWidget(pri3Button, 3, 1);
  setLayout(mainLayout);
}
