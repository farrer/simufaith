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

#ifndef _simufaith_house_h
#define _simufaith_house_h

#include "building.h"
#include "person.h"

namespace SimuFaith
{
   /*! A house is a building where people live. */
   class House: public Building
   {
      public:
         /*! A House inhabitant definition */
         class Inhabitant : public Kobold::ListElement
         {
            public:
               /*! Constructor */
               Inhabitant(Person* person);
               /*! Destructor */
               ~Inhabitant();

               /*! Get the person of this inhabitant */
               Person* getPerson();

            private:
               Person* person; /**< A single inhabitant */
         };

         /*! Constructor */
         House(int capacity, Kobold::String filename, 
               Ogre::SceneManager* sceneManager); 
         /*! Destructor */
         ~House();

         /*! Add a person to inhabit the house.
          * \param person pointer to the person to inhabit the house */
         void addInhabitant(Person* person);

         /*! Remove an inhabitant from the house (ie: the person will no 
          * longer inhabit the house, but still exists as a person).
          * \param person pointer to the person to no more inhabit here. */
         void removeInhabitant(Person* person);

         /*! \return max capacity of the house */
         int getCapacity();

         /*! \return total current inhabitants */
         int getTotalInhabitants();

         /*! \return total space left for new inhabitants */
         int getAvailableSpace();

      private:
         int capacity;             /**< House max capacity */
         Kobold::List inhabitants; /**< Current house inhabitants */
   };

}

#endif

