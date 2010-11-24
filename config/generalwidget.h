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

#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

#include <QWidget>

class QLabel;
class QComboBox;
class QVBoxLayout;

class GeneralWidget : public QWidget
    /* This Widget is part of the config dialog. Here, you can decide
       what happens to done (checked) tasks (never remove automatically,
       remove after closing this application or remove immediately).
     */
{
    Q_OBJECT
  public:
    GeneralWidget( QWidget* parent=0 );
    
    // save current state in the settings
    void save();
    // load the settings to the widgets
    void restore();
    
  private:
    void setupUi();
    
    QLabel* removeTaskLabel;
    QComboBox* removeTaskBox;
    QVBoxLayout* mainLayout;
};

#endif //GENERALWIDGET_H
