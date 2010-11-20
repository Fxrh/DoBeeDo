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

#ifndef PRIORITYWIDGET_H
#define PRIORITYWIDGET_H

#include <QWidget>

class QCheckBox;
class QLabel;
class QGridLayout;
class KColorButton;

class PriorityWidget : public QWidget
    /* In this part of the config dialog, the user can choose the background
     * colors of the different priorities if he don't want to use the 
     * standard system colors. Call restore before reusing this widget.
     */
{
    Q_OBJECT
  public:
    PriorityWidget( QWidget* parent=0 );
  
  public slots:
    void save();
    void restore();
    
  private:
    void setupUi();
    
    QCheckBox* useOwnBox;
    QCheckBox* useOwnFontBox;
    QLabel* pri1Label;
    QLabel* pri2Label;
    QLabel* pri3Label;
    QLabel* pri1FontLabel;
    QLabel* pri2FontLabel;
    QLabel* pri3FontLabel;
    KColorButton* pri1Button;
    KColorButton* pri2Button;
    KColorButton* pri3Button;
    KColorButton* pri1FontButton;
    KColorButton* pri2FontButton;
    KColorButton* pri3FontButton;
    QGridLayout* mainLayout;
};

#endif //PRIORITYWIDGET_H
