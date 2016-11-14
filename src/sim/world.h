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

#ifndef _simufaith_world_h
#define _simufaith_world_h

#include "faith.h"
#include "building.h"

#include <kobold/list.h>

namespace SimuFaith
{

   /*! The entry point class of simulation, the world is where everithing
    * related to the game simulation is glued into. Most used as an static
    * class. */
   class World
   {
      public:
         /*! Initialize the world to use. */
         static void init();
         /*! Done with current world use. */
         static void end();

         /*! Create a Faith 
          * \param name faith's name
          * \return pointer to the created Faith. */
         static Faith* createFaith(Kobold::String name);

         /*! \return current list of Faiths */
         static Kobold::List* getFaiths();

         /*! Add a building to current buildings list
          * \param building pointer to building to add */
         static void addBuilding(Building* building);

         /*! Remove a building from the list (but without deleting it).
          * \param building pointer to the building to remove from the list */
         static void removeBuilding(Building* building);

      private:
         static Kobold::List* faiths; /**< Current faiths */
         static Kobold::List* buildings; /**< Overall list of buildings */
   };

}


#endif

