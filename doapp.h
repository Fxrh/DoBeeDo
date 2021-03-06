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

#ifndef DOAPP_H
#define DOAPP_H

#include <KApplication>

class MainWindow;
class SysTray;

class DoApp : public KApplication
  /* DoApp represents the instance of the application, created in main().
   * It does not much here, it just takes care of the creating and destroying
   * of the main window and the system tray icon.
   */
{
  public:
    DoApp();
    ~DoApp();
    
    void commitData(QSessionManager& sm);
    
  private:
    MainWindow* window;
    SysTray* systray;
};

#endif //DOAPP_H
