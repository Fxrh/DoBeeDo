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

#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <KStatusNotifierItem>

class SysTray : public KStatusNotifierItem
  /* The system tray icon. It has different colors, depending of the tasks
   * you have to do today and tomorrow.
   */
{
  public:
    SysTray( QObject* parent = 0 );
    ~SysTray();
    
    // called by MainWindow to inform SysTray of the amount of tasks per section
    void updateStatusInformation( int overdue, int today, int tomorrow, int nextWeek, int nextMonth, int Future );
};

#endif //SYSTRAY_H
