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
   people = new Kobold::List();

   curStep = World::STEP_BUILDINGS;
}

/*************************************************************************
 *                                    end                                *
 *************************************************************************/
void World::end()
{
   if(people)
   {
      delete people;
      people = NULL;
   }
   if(buildings)
   {
      delete buildings;
      buildings = NULL;
   }
   if(faiths)
   {
      delete faiths;
      faiths = NULL;
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
 *                               addPerson                               *
 *************************************************************************/
void World::addPerson(Person* person)
{
   people->insert(person);
}

/*************************************************************************
 *                             removePerson                              *
 *************************************************************************/
void World::removePerson(Person* person)
{
   people->removeWithoutDelete(person);
}

/*************************************************************************
 *                                 step                                  *
 *************************************************************************/
void World::step()
{
   switch(curStep)
   {
      case STEP_BUILDINGS:
      {
         Building* building = (Building*) buildings->getFirst();
         for(int i = 0; i < buildings->getTotal(); i++)
         {
            building->step();
            building = (Building*) building->getNext();
         }
         curStep = STEP_PEOPLE;
      }
      break;
      case STEP_PEOPLE:
      {
         Person* person = (Person*) people->getFirst();
         for(int i = 0; i < people->getTotal(); i++)
         {
            person->step();
            person = (Person*) person->getNext();
         }
         curStep = STEP_BUILDINGS;
      }
      break;
   }

}

/*************************************************************************
 *                                Variables                              *
 *************************************************************************/
Kobold::List* World::faiths = NULL;
Kobold::List* World::buildings = NULL;
Kobold::List* World::people = NULL;
World::SimulationStep World::curStep = World::STEP_BUILDINGS; 

