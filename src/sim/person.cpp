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

#include "person.h"
#include "world.h"

#include <assert.h>
using namespace SimuFaith;

/***********************************************************************
 *                                FaithInfo                            *
 ***********************************************************************/
Person::FaithInfo::FaithInfo(Faith* faith)
{
   this->faith = faith;

   /* By default, faith is initially unknown to a new person,
    * until it got references of it. */
   this->likeness = 0;
   this->dislikeness = 0;
}

/***********************************************************************
 *                               ~FaithInfo                            *
 ***********************************************************************/
Person::FaithInfo::~FaithInfo()
{
}

/***********************************************************************
 *                                getFaith                             *
 ***********************************************************************/
Faith* Person::FaithInfo::getFaith()
{
   return faith;
}

/***********************************************************************
 *                             getLikeness                             *
 ***********************************************************************/
unsigned char Person::FaithInfo::getLikeness()
{
   return likeness;
}

/***********************************************************************
 *                           getDislikeness                            *
 ***********************************************************************/
unsigned char Person::FaithInfo::getDislikeness()
{
   return dislikeness;
}

/***********************************************************************
 *                                 set                                 *
 ***********************************************************************/
void Person::FaithInfo::set(unsigned char likeness, unsigned char dislikeness)
{
   this->likeness = likeness;
   this->dislikeness = dislikeness;
}

/***********************************************************************
 *                                  Mind                               *
 ***********************************************************************/
Person::Mind::Mind()
{
   /* Let's create each FaithInfo */
   Kobold::List* gameFaiths = World::getFaiths();
   Faith* faith = (Faith*) gameFaiths->getFirst();
   for(int i = 0; i < gameFaiths->getTotal(); i++)
   {
      faiths.insert(new FaithInfo(faith));
      faith = (Faith*) faith->getNext();
   }

   /* Later, we must check the current faith */
   curFaith = NULL;
}

/***********************************************************************
 *                                 ~Mind                               *
 ***********************************************************************/
Person::Mind::~Mind()
{
}

/***********************************************************************
 *                            getFaithInfo                             *
 ***********************************************************************/
Person::FaithInfo* Person::Mind::getFaithInfo(Faith* faith)
{
   FaithInfo* f = (FaithInfo*) faiths.getFirst();
   for(int i = 0; i < faiths.getTotal(); i++)
   {
      if(f->getFaith() == faith)
      {
         return f;
      }
      f = (FaithInfo*) f->getNext();
   }

   return NULL;
}

/***********************************************************************
 *                        defineCurrentFaith                           *
 ***********************************************************************/
void Person::Mind::defineCurrentFaith()
{
   //TODO: create unit test for this function.
   FaithInfo* f = (FaithInfo*) faiths.getFirst();
   for(int i = 0; i < faiths.getTotal(); i++)
   {
      /* Will change faith if liked a new one (>50) and liked it more
       * than the current one (if any), or, if equally liked, if disliked
       * it lesser than the current one (if any). */
      if((f != curFaith) && (f->getLikeness() > 50) &&
         ((curFaith == NULL) || 
          ((f->getLikeness() > curFaith->getLikeness()) ||
           ((f->getLikeness() == curFaith->getLikeness()) &&
            (f->getDislikeness() < curFaith->getDislikeness()) ))))
      {
         curFaith = f;
      }
      f = (FaithInfo*) f->getNext();
   }
}

/***********************************************************************
 *                              getFaith                               *
 ***********************************************************************/
Faith* Person::Mind::getFaith()
{
   if(curFaith)
   {
      return curFaith->getFaith();
   }
   return NULL;
}

/***********************************************************************
 *                               Child                                 *
 ***********************************************************************/
Person::Child::Child(Person* person)
{
   this->person = person;
}

/***********************************************************************
 *                               ~Child                                *
 ***********************************************************************/
Person::Child::~Child()
{
}

/***********************************************************************
 *                              getPerson                              *
 ***********************************************************************/
Person* Person::Child::getPerson()
{
   return person;
}

/***********************************************************************
 *                                Person                               *
 ***********************************************************************/
Person::Person(Kobold::String name, int age, Person* parentA, Person* parentB,
      Kobold::String filename, Ogre::SceneManager* sceneManager)
{
   /* Define things */
   this->name = name;
   this->age = age;
   this->parentA = parentA;
   if(parentA)
   {
      parentA->addChild(this);
   }
   this->parentB = parentB;
   if(parentB)
   {
      parentB->addChild(this);
   }

   /* Initilly unemployed and homeless */
   this->worker = NULL;
   this->inhabitant = NULL;

   /* Load its model */
   this->model = new Goblin::Model3d("person" + 
         Kobold::StringUtil::toString(count), filename, sceneManager);
   count++;
}

/***********************************************************************
 *                               ~Person                               *
 ***********************************************************************/
Person::~Person()
{
   if(worker)
   {
      worker->getOffice()->removeWorker(worker);
   }
   if(inhabitant)
   {
      inhabitant->getHouse()->removeInhabitant(inhabitant);
   }
   if(model)
   {
      delete model;
   }
}

/***********************************************************************
 *                              getFaith                               *
 ***********************************************************************/
Faith* Person::getFaith()
{
   return mind.getFaith();
}

/***********************************************************************
 *                              getParentA                             *
 ***********************************************************************/
Person* Person::getParentA()
{
   return parentA;
}

/***********************************************************************
 *                              getParentB                             *
 ***********************************************************************/
Person* Person::getParentB()
{
   return parentB;
}

/***********************************************************************
 *                              setAsWorker                            *
 ***********************************************************************/
void Person::setAsWorker(Office::Worker* worker)
{
   this->worker = worker;
}

/***********************************************************************
 *                               getWorker                             *
 ***********************************************************************/
Office::Worker* Person::getWorker()
{
   return worker;
}

/***********************************************************************
 *                          setAsInhabitant                            *
 ***********************************************************************/
void Person::setAsInhabitant(House::Inhabitant* inhabitant)
{
   this->inhabitant = inhabitant;
}

/***********************************************************************
 *                            getInhabitant                            *
 ***********************************************************************/
House::Inhabitant* Person::getInhabitant()
{
   return inhabitant;
}

/***********************************************************************
 *                               addChild                              *
 ***********************************************************************/
void Person::addChild(Person* child)
{
   children.insert(new Child(child));
}

/***********************************************************************
 *                              removeChild                            *
 ***********************************************************************/
void Person::removeChild(Person* child)
{
   Child* c = (Child*) children.getFirst();
   for(int i = 0; i < children.getTotal(); i++)
   {
      if(c->getPerson() == child)
      {
         children.remove(c);
         break;
      }
      c = (Child*) c->getNext();
   }
}

/***********************************************************************
 *                              static vars                            *
 ***********************************************************************/
int Person::count = 0;

