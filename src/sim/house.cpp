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

#include "house.h"
using namespace SimuFaith;

/*************************************************************************
 *                               Inhabitant                              *
 *************************************************************************/
House::Inhabitant::Inhabitant(Person* person)
{
   this->person = person;
}

/*************************************************************************
 *                              ~Inhabitant                              *
 *************************************************************************/
House::Inhabitant::~Inhabitant()
{
}

/*************************************************************************
 *                               getPerson                               *
 *************************************************************************/
Person* House::Inhabitant::getPerson()
{
   return person;
}

House::House(int capacity, Kobold::String filename, 
      Ogre::SceneManager* sceneManager)
      :Building(sceneManager, filename)
{
   this->capacity = capacity;
}

House::~House()
{
}

void House::addInhabitant(Person* person)
{
   inhabitants.insert(new Inhabitant(person));
}

void House::removeInhabitant(Person* person)
{
   Inhabitant* hab = (Inhabitant*) inhabitants.getFirst();
   for(int i = 0; i < inhabitants.getTotal(); i++)
   {
      if(hab->getPerson() == person)
      {
         inhabitants.remove(hab);
         break;
      }
   }
}

int House::getCapacity()
{
   return capacity;
}

int House::getTotalInhabitants()
{
   return inhabitants.getTotal();
}

int House::getAvailableSpace()
{
   return capacity - inhabitants.getTotal();
}

