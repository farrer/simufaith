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


#ifndef _simufaith_h_
#define _simufaith_h_

#include <goblin/baseapp.h>
#include <kobold/platform.h>

#include "config.h"

namespace SimuFaith
{
   #define APP_NAME             "SimuFaith"
   #define DEFAULT_WINDOW_WIDTH        1024
   #define DEFAULT_WINDOW_HEIGHT        768
   #define WIDTH_TO_DOUBLE_SIZE        2048
   #define BASE_DATA_DIR             "data"

   /*! The core (main entry) class implementation for SimuFaith. It's where
    * the main game loop occur. */
   class Core : public Goblin::BaseApp
   {
      public:

         /*! Constructor */
         Core();
         /*! Destructor */
         ~Core();

      protected:

         /* Direct functions from Goblin::BaseApp */
         const Kobold::String getApplicationUnixName() const 
         {
            return APP_NAME;
         };
         const int getDefaultWindowWidth() const 
         { 
            return DEFAULT_WINDOW_WIDTH; 
         };
         const int getDefaultWindowHeight() const 
         { 
            return DEFAULT_WINDOW_HEIGHT; 
         };
         const Orientation getDefaultOrientation() const 
         { 
            return LANDSCAPE; 
         };
         const int getMinWidthToUseDoubleSizedGui() const 
         { 
            return WIDTH_TO_DOUBLE_SIZE; 
         };
         const Kobold::String getBaseDataDir() const 
         {
            return SIMUFAITH_LOCAL_DATA_PREFIX + Kobold::String(BASE_DATA_DIR);
         };

         /* Functions from Goblin::BaseApp */
         bool doCycleInit(int callCounter, bool& shouldAbort);
         void getDataDirectories(Ogre::String** dataDirectories,
               Ogre::String** dataGroups, int& total);
         void doLowMemoryClean();
         void doSendToBackground();
         void doSendToForeground();
         void doCycle();
         bool shouldQuit();

      private:
   };

}

#endif

