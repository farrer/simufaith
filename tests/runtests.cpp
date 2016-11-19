/*
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


#include <kobold/platform.h>

#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_WINDOWNS
   #include "windows.h"
#endif

#include "testperson.h"

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS &&\
                       KOBOLD_PLATFORM != KOBOLD_PLATFORM_ANDROID
/***********************************************************************
 *                                main                                 *
 ***********************************************************************/
#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_WINDOWNS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
      LPSTR lpCmdLine, int nCmdShow)
#else
int main (int argc, char *argv[])
#endif
{
   SimuFaithTests::TestPerson testPerson;
   testPerson.run();

   return 0;
}
#endif

