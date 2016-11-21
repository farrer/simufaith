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
#include "util.h"

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
int Person::FaithInfo::getLikeness()
{
   return likeness;
}

/***********************************************************************
 *                           getDislikeness                            *
 ***********************************************************************/
int Person::FaithInfo::getDislikeness()
{
   return dislikeness;
}

/***********************************************************************
 *                                 set                                 *
 ***********************************************************************/
void Person::FaithInfo::set(int likeness, int dislikeness)
{
   this->likeness = likeness;
   this->dislikeness = dislikeness;
}

/***********************************************************************
 *                             addLikeness                             *
 ***********************************************************************/
void Person::FaithInfo::addLikeness(int value)
{
   likeness += value;

   /* Apply limits. */
   if(likeness > FAITH_OPINION_MAX_VALUE)
   {
      likeness = FAITH_OPINION_MAX_VALUE;
   } else if(likeness < 0)
   {
      likeness = 0;
   }
}

/***********************************************************************
 *                           addDislikeness                            *
 ***********************************************************************/
void Person::FaithInfo::addDislikeness(int value)
{
   dislikeness += value;

   /* Apply limits. */
   if(dislikeness > FAITH_OPINION_MAX_VALUE)
   {
      dislikeness = FAITH_OPINION_MAX_VALUE;
   } else if(dislikeness < 0)
   {
      dislikeness = 0;
   }
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
   FaithInfo* f = (FaithInfo*) faiths.getFirst();
   for(int i = 0; i < faiths.getTotal(); i++)
   {
      /* Will change faith if liked a new one (>HALF) and liked it more
       * than the current one (if any), or, if equally liked, if disliked
       * it lesser than the current one (if any). */
      if((f != curFaith) && (f->getLikeness() > FAITH_OPINION_HALF_VALUE) &&
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
 *                             checkRandom                             *
 ***********************************************************************/
bool Person::Mind::checkRandom(int likeOrDislikeValue)
{
   int randVal = getRandom(FAITH_OPINION_MAX_VALUE);

   /* Should apply if our random value is lesser than like or dislike value.
    * This way, the greater the likeness or dislikeness value, the greater is
    * its probability to influence others (and if Maximum, will always 
    * influence). */
   return likeOrDislikeValue >= randVal;
}

/***********************************************************************
 *                           applyInfluence                            *
 ***********************************************************************/
void Person::Mind::applyInfluence(Person* target, int value)
{
   /* Note that if the likeness or dislikeness is lesser than the
    * target likeness or dislikeness, no influence will happen (as the target
    * is much more convicted of its opinion than the person). */

   /* Firstly, let's apply current Faith as a likeness-only one (although a
    * person can dislike somethings of its current faith, it tends to not
    * show it to other people). */
   if(curFaith)
   {
      /* Only influence if this person like it more than the
       * target's current faith likeness (if any) */
      FaithInfo* tgtFaith = target->mind.getFaithInfo(curFaith->getFaith());
      if( (curFaith->getLikeness() > tgtFaith->getLikeness()) &&
          ((!target->mind.curFaith) || 
          (curFaith->getLikeness() > target->mind.curFaith->getLikeness())) )
      {
         if(checkRandom(curFaith->getLikeness()))
         {
            tgtFaith->addLikeness(value);
         }
      }
   }

   /* Make sure faiths list are of equivalent size. */
   assert(faiths.getTotal() == target->mind.faiths.getTotal());

   /* Let's apply each other faith likeness / dislikeness */
   FaithInfo* f = (FaithInfo*) faiths.getFirst();
   FaithInfo* tgt = (FaithInfo*) target->mind.faiths.getFirst();
   for(int i = 0; i < faiths.getTotal(); i++)
   {
      /* Make sure we are doing at the same faith for person and target */
      assert(f->getFaith() == tgt->getFaith());

      /* No need to apply person's current target again. */
      if(f != curFaith)
      {
         /* Let's check if will apply likeness to it */
         if((f->getLikeness() > tgt->getLikeness()) &&
            (checkRandom(f->getLikeness())))
         {
            tgt->addLikeness(value);
         }

         /* And check if will apply dislikeness. note that at this case,
          * we also check the person's dislikeness against target likeness,
          * as we the target like it a lot, it tends to ignore person's
          * arguments on dislikeness. */
         if((f->getDislikeness() > tgt->getDislikeness()) &&
            (f->getDislikeness() >= tgt->getLikeness()))
         {
            tgt->addDislikeness(value);
         }
      }

      /* Let's get next faith info for both person and target */
      f = (FaithInfo*) f->getNext();
      tgt = (FaithInfo*) tgt->getNext();
   }
}

/***********************************************************************
 *                             toString                                *
 ***********************************************************************/
Kobold::String Person::Mind::toString()
{
   Kobold::String ret = "";

   FaithInfo* f = (FaithInfo*) faiths.getFirst();
   for(int i = 0; i < faiths.getTotal(); i++)
   {
      ret += "\t";
      ret += f->getFaith()->getName();
      ret += " - likeness: ";
      ret += Kobold::StringUtil::toString(f->getLikeness());
      ret += " dislikeness: ";
      ret += Kobold::StringUtil::toString(f->getDislikeness());
      ret += "\n";
      f = (FaithInfo*) f->getNext();
   }

   return ret;
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

   if(sceneManager)
   {
      /* Load its model */
      this->model = new Goblin::Model3d("person" + 
            Kobold::StringUtil::toString(count), filename, sceneManager);
   }
   else
   {
      /* No model, we are for sure running on a TestCase */
      this->model = NULL;
   }
   count++;

   World::addPerson(this);
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
   World::removePerson(this);
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
 *                             getName                                 *
 ***********************************************************************/
Kobold::String Person::getName()
{
   return name;
}

/***********************************************************************
 *                               getMind                               *
 ***********************************************************************/
Person::Mind* Person::getMind()
{
   return &mind;
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
 *                                 step                                *
 ***********************************************************************/
void Person::step()
{
   /* Apply both parents influence */
   if(parentA)
   {
      parentA->mind.applyInfluence(this, 5);
   }
   if(parentB)
   {
      parentB->mind.applyInfluence(this, 5);
   }

   if(!inhabitant)
   {
      /* Current person is homeless and more vulnerable */
      //TODO
   }

   if(!worker)
   {
      /* Current person doesn't have a job. It seems more vulnerable to 
       * dislike its current faith. */
      //TODO
   }

   /* After that, let's redefine current person's faith, if any */
   mind.defineCurrentFaith();
}

/***********************************************************************
 *                              static vars                            *
 ***********************************************************************/
int Person::count = 0;

