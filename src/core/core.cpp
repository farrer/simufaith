/* 
   SimuFaith
   Copyright (C) DNTeam <simufaith@dnteam.org>

   This file is part of SimuFaith.

   SimuFaith is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   SimuFaith is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with SimuFaith.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "core.h"
#include <farso/controller.h>
using namespace SimuFaith;

/************************************************************************
 *                              Constructor                             *
 ************************************************************************/
Core::Core()
{
}

/************************************************************************
 *                               Destructor                             *
 ************************************************************************/
Core::~Core()
{
   Farso::Controller::finish();
}

/************************************************************************
 *                                doInit                                *
 ************************************************************************/
bool Core::doCycleInit(int callCounter, bool& shouldAbort)
{
   /* Initialize Farso and set our skin */
   Farso::Controller::init(Farso::RENDERER_TYPE_OGRE3D, DEFAULT_WINDOW_WIDTH,
         DEFAULT_WINDOW_HEIGHT, 32, "", getSceneManager());
   Farso::FontManager::setDefaultFont("LiberationSans-Regular.ttf");
   Farso::Controller::loadSkin("skins/scifi.skin");
   Farso::Controller::setCursor("cursor/sel.png");
   
   /* Done */
   return true;
}

/************************************************************************
 *                         getDataDirectories                           *
 ************************************************************************/
void Core::getDataDirectories(Ogre::String** dataDirectories,
      Ogre::String** dataGroups, int& total)
{
   static Ogre::String dirs[] = {"gui", "textures", "models", "fonts"};
   (*dataDirectories) = &dirs[0];
   (*dataGroups) = &dirs[0];
   total = 4;
}

/************************************************************************
 *                           doLowMemoryClean                           *
 ************************************************************************/
void Core::doLowMemoryClean()
{
}

/************************************************************************
 *                         doSendToBackground                           *
 ************************************************************************/
void Core::doSendToBackground()
{
}

/************************************************************************
 *                         doSendToForeground                           *
 ************************************************************************/
void Core::doSendToForeground()
{
}

/************************************************************************
 *                               doCycle                                *
 ************************************************************************/
void Core::doCycle()
{
   Farso::Controller::verifyEvents(leftButtonPressed, false, mouseX, mouseY);
}

/************************************************************************
 *                              shouldQuit                              *
 ************************************************************************/
bool Core::shouldQuit()
{
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS &&\
    OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
   return Kobold::Keyboard::isKeyPressed(Kobold::KOBOLD_KEY_ESCAPE);
#endif
   return false;
}


