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

#ifndef _simufaith_temple_h
#define _simufaith_temple_h

#include "building.h"

namespace SimuFaith
{

   /*! The temple is the basic building of a Faith. It's where the followers
    * go for miracles or to just hear Messiah's words by its priests. */
   class Temple : public Building
   {
      public:
         enum TempleLevel
         {
            HUMBLE_TEMPLE,
            SMALL_TEMPLE,
            NORMAL_TEMPLE,
            LARGE_TEMPLE,
            HUGE_TEMPLE,
            TOTAL_LEVELS /**< Total levels. Should not be directly used */
         };

         /*! Temple Constructor.
          * \param level initial temple's level
          * \param sceneManager Ogre's sceneManager used. */
         Temple(TempleLevel level, Ogre::SceneManager* sceneManager);

         /*! Destructor */
         ~Temple();

         /*! \return current temple level */
         TempleLevel getLevel();

         /*! \return current temple capacity (ie: simultaneous followers) */
         int getCapacity();

         /*! \return current temple's atendance */
         int getAttendance();

         /*! Get a distance from a point in the map to the temple.
          * \param x current x coordinate to verify
          * \param z current z coordinate to verify
          * \return distance from (x,z) to temple's position. */
         float getDistance(float x, float z);

         /*! Verify if a position is inner temple's action range. The distance
          * is usually got by a call to #getDistance.
          * \param distance distance of the position to the temple.
          * \return if is in range or not. */
         bool isInRange(float distance);

         /*! Do the temple simulation step */
         void step();

      private:

         static int capacities[TOTAL_LEVELS];
         static int ranges[TOTAL_LEVELS];
         static Kobold::String models[TOTAL_LEVELS];

         TempleLevel level;   /**< Current building level */
         int capacity;        /**< Current temple capacity */
         int attendance;      /**< Current temple attendance */
         int range;           /**< Current temple range */
   };

}

#endif 

