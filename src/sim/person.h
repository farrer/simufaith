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

#ifndef _simufaith_person_h
#define _simufaith_person_h

#include "faith.h"
#include <kobold/list.h>
#include <goblin/model3d.h>

namespace SimuFaith
{
   /*! A single person - potentially a faith follower - in the game */
   class Person
   {
      public:
         /*! Personal info about a Faith. */
         class FaithInfo : public Kobold::ListElement
         {
            public:
               /*! Constructor 
                * \param faith pointer to Faith of this info is related to */
               FaithInfo(Faith* faith);
               /*! Destructor */
               ~FaithInfo();

               /*! \return Faith related to this info */
               Faith* getFaith();

               /*! \return [0..100] of how much like related Faith */
               unsigned char getLikeness();

               /*! \return [0..100] of how much dislike related Faith */
               unsigned char getDislikeness();

               /*! Set how much like and dislike related Faith */
               void set(unsigned char likeness, unsigned char dislikeness);

            private:
               Faith* faith; /**< Faith which this info is related to */
               unsigned char likeness;  /**< [0..100] of how much like it  */
               unsigned char dislikeness; /**< [0..100] of how much dislike */
         };

         /*! What is inside a person's mind. Faiths, faiths everywhere. */
         class Mind
         {
            public:
               /*! Constructor */
               Mind();
               /*! Destructor */
               ~Mind();

               /*! Get personal information about a Faith
                * \param faith pointer to faith to get info
                * \return FaithInfo found or NULL if none. */
               FaithInfo* getFaithInfo(Faith* faith);

               /*! Define current person's faith (which one person's 
                * must like). */
               void defineCurrentFaith();

               /*! \return current person's Faith, or NULL, if none choosed
                * by the person. */
               Faith* getFaith();

            private:
               Kobold::List faiths; /**< Each faith info */
               FaithInfo* curFaith; /**< Info about current adopted faith */
         };

      private:
         Mind mind; /**< Person's mind */
         int age; /**< Person's age */

         // TODO: where is their home? 
         //
         // TODO: where is their work?
         //
         // TODO: have work? is it related to a Faith? 

         

         Goblin::Model3d* model; /**< Person's model */
         //TODO: portrait? 
   };

}

#endif

