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

#include "temple.h"

#include <OGRE/OgreMath.h>

using namespace SimuFaith;

/*************************************************************************
 *                                 Constructor                           *
 *************************************************************************/
Temple::Temple(Temple::TempleLevel level, Ogre::SceneManager* sceneManager)
       :Building(sceneManager, models[level])
{
   this->level = level;
   this->capacity = capacities[level];
   this->range = ranges[level];
   this->attendance = 0;
}

/*************************************************************************
 *                                  Destructor                           *
 *************************************************************************/
Temple::~Temple()
{
}

/*************************************************************************
 *                                 getLevel                              *
 *************************************************************************/
Temple::TempleLevel Temple::getLevel()
{
   return level;
}

/*************************************************************************
 *                                getCapacity                            *
 *************************************************************************/
int Temple::getCapacity()
{
   return capacity;
}

/*************************************************************************
 *                              getAttendance                            *
 *************************************************************************/
int Temple::getAttendance()
{
   return attendance;
}

/*************************************************************************
 *                              getDistance                              *
 *************************************************************************/
float Temple::getDistance(float x, float z)
{
   Ogre::Vector3 pos = getModel()->getPosition();
   float difX = pos[0] - x;
   float difZ = pos[2] - z;

   return Ogre::Math::Sqrt((difX * difX) + (difZ * difZ));
}

/*************************************************************************
 *                               isInRange                               *
 *************************************************************************/
bool Temple::isInRange(float distance)
{
   return distance <= range;
}

/* Capacity values: in number of persons. */
int Temple::capacities[TOTAL_LEVELS] = {30, 80, 200, 500, 2000};

/* Range values, in meters */
int Temple::ranges[TOTAL_LEVELS] = {100, 200, 2000, 10000, 30000};

Kobold::String Temple::models[TOTAL_LEVELS] = 
      {"building/temples/humble.mesh", "building/temples/small.mesh",
         "building/temples/normal.mesh", "building/temples/large.mesh",
         "building/temples/huge.mesh"};
