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

#ifndef _simufaith_faith_h
#define _simufaith_faith_h

#include <kobold/kstring.h>
#include <kobold/list.h>

namespace SimuFaith
{

   /*! A Faith (Religion) in the game. It's the 'playable entity', one for
    * each player, and container of almost all other simulation entities. */
   class Faith : public Kobold::ListElement
   {
      public:
         /*! Constructor
          * \param name the name for which this Faith is known */
         Faith(Kobold::String name);
         /*! The evil special function to destroy a Faith */
         ~Faith();

         /*! \return faith's name */
         Kobold::String getName();

      private:

         Kobold::String name; /**< Name for which people known this Faith */

         Kobold::List priests; /**< List of priests professing this Faith */
         Kobold::List temples; /**< Temples owned by the Faith */

         int followers;   /**< Current number of followers */
   };

}

#endif

