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

#include "world.h"
using namespace SimuFaith;

/*************************************************************************
 *                                   Init                                *
 *************************************************************************/
void World::init()
{
   faiths = new Kobold::List();
   buildings = new Kobold::List();
}

/*************************************************************************
 *                                    end                                *
 *************************************************************************/
void World::end()
{
   if(faiths)
   {
      delete faiths;
      faiths = NULL;
   }
   if(buildings)
   {
      delete buildings;
      buildings = NULL;
   }
}

/*************************************************************************
 *                              createFaith                              *
 *************************************************************************/
Faith* World::createFaith(Kobold::String name)
{
   Faith* faith = new Faith(name);
   faiths->insert(faith);

   return faith;
}

/*************************************************************************
 *                               getFaiths                               *
 *************************************************************************/
Kobold::List* World::getFaiths()
{
   return faiths;
}

/*************************************************************************
 *                              addBuilding                              *
 *************************************************************************/
void World::addBuilding(Building* building)
{
   buildings->insert(building);
}

/*************************************************************************
 *                            removeBuilding                             *
 *************************************************************************/
void World::removeBuilding(Building* building)
{
   buildings->removeWithoutDelete(building);
}


/*************************************************************************
 *                                Variables                              *
 *************************************************************************/
Kobold::List* World::faiths = NULL;
Kobold::List* World::buildings = NULL;

