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

#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>

#include "doapp.h"

int main( int argc, char** argv )
{
  KAboutData aboutData( "dobeedo",
                        0,
                        ki18n( "DoBeeDo" ),
                        "0.2.1",
                        ki18n( "A todo list manager for KDE" ),
                        KAboutData::License_GPL_V3,
                        ki18n( "(c) 2010 Felix Rohrbach" ),
                        ki18n(" "), //further description
                        "http://github.com/fxrh/dobeedo/", //Website
                        "fxrh@gmx.de" );
  
  aboutData.setTranslator(ki18nc("NAME OF TRANSLATORS", "Your names"),
                          ki18nc("EMAIL OF TRANSLATORS", "Your emails"));
  
  KCmdLineArgs::init( argc, argv, &aboutData );
  DoApp app;
  return app.exec();
}
                        
