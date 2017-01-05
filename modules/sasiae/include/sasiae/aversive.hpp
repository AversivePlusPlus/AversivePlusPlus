/*
    Aversive++
    Copyright (C) 2014 Eirbot

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AVERSIVE_HPP
#define AVERSIVE_HPP

namespace SASIAE {

  //! \class Aversive aversive.hpp <aversive.hpp>
  //! \brief Aversive++ main class.
  class Aversive {
  public:
    //! \brief Initialize Aversive++.
    //! It must be the first operation done at the beginning of the main.
    //! Please refer to "Create a project" tutorial.
    static void init(void);

    //! \brief Sleep for a certain amount of time
    //! \param ms : the amount of milliseconds to sleep.
    static void sleep(int ms);

    //! \brief Synchronize the main while loop(s).
    //! \return Boolean telling if the application must keep running.
    //! It must be used for simulation purpose.
    //! Please refer to "Create a project" tutorial.
    static bool sync(void);

    //! \brief Tell the application it has to stop.
    static void stop(void);

    //! \brief Uninitialize Aversive++.
    //! \return The current application's return code.
    //! It must be used to properly uninitialize Aversive++ before the main returns.
    //! Please refer to "Create a project" tutorial.
    static int exit(void);

    //! \brief Tell whether Aversive++ has been initialized or not.
    static bool isInitialized(void);

    //! \brief Tell whether the application is running or in the process of stopping.
    static bool isRunning(void);

    //! \brief Tell the current return code of the application.
    //! \return The current application's return code.
    static int returnCode(void);

    //! \brief Change the return code of the application.
    //! \param returnCode : the new return code.
    static void setReturnCode(int returnCode = 0);

    //! \brief Class holding the configuration of Aversive++.
    class Config;
  };

}

#endif//AVERSIVE_HPP
