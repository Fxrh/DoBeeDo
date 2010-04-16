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

#include "systray.h"

SysTray::SysTray( QObject* parent )
    : KStatusNotifierItem(parent)
{
  setCategory( ApplicationStatus );
  setIconByName( "dobeedo" );
}

SysTray::~SysTray()
{
  qDebug("SysTray: destroyed");
}

void SysTray::updateStatusInformation(int overdue, int today, int tomorrow, int nextWeek, int nextMonth, int Future)
{
  if( overdue+today != 0 ){
    setIconByName("dobeedo-today");
  }
  else {
    if( tomorrow != 0 ){
      setIconByName( "dobeedo-tomorrow" );
    }
    else{
      setIconByName( "dobeedo" );
    }
  }
}

