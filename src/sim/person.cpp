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

