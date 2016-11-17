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
#include "person.h"
using namespace SimuFaith;

/*************************************************************************
 *                               Inhabitant                              *
 *************************************************************************/
House::Inhabitant::Inhabitant(Person* person, House* house)
{
   this->person = person;
   this->house = house;
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

/*************************************************************************
 *                               getHouse                                *
 *************************************************************************/
House* House::Inhabitant::getHouse()
{
   return house;
}

/*************************************************************************
 *                                 House                                 *
 *************************************************************************/
House::House(int capacity, Kobold::String filename, 
      Ogre::SceneManager* sceneManager)
      :Building(sceneManager, filename)
{
   this->capacity = capacity;
}

/*************************************************************************
 *                                ~House                                 *
 *************************************************************************/
House::~House()
{
}

/*************************************************************************
 *                            addInhabitant                              *
 *************************************************************************/
void House::addInhabitant(Person* person)
{
   Inhabitant* inh = new Inhabitant(person, this);
   person->setAsInhabitant(inh);
   inhabitants.insert(inh);
}

/*************************************************************************
 *                           removeInhabitant                            *
 *************************************************************************/
void House::removeInhabitant(House::Inhabitant* inhabitant)
{
   inhabitant->getPerson()->setAsInhabitant(NULL);
   inhabitants.remove(inhabitant);
}

/*************************************************************************
 *                             getCpacity                                *
 *************************************************************************/
int House::getCapacity()
{
   return capacity;
}

/*************************************************************************
 *                         getTotalInhabitants                           *
 *************************************************************************/
int House::getTotalInhabitants()
{
   return inhabitants.getTotal();
}

/*************************************************************************
 *                          getAvailableSpace                            *
 *************************************************************************/
int House::getAvailableSpace()
{
   return capacity - inhabitants.getTotal();
}

/*************************************************************************
 *                                step                                   *
 *************************************************************************/
void House::step()
{
}

