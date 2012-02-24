/**
 * =====================================================================================
 *
 *       Filename:  system.hpp
 *
 *    Description:  Class defining a interface to a downstream system
 *          Usage:  
 *                  @code
 *                     System *pSystem = System::getInstance();
 *                     std::ostream stream = pSystem->getStream();
 *                     stream << "Feeding downstream system" << std::endl
 *                  @endcode 
 *
 * =====================================================================================
 */

#ifndef DOWNSTREAM_SYSTEM_HPP
#define DOWNSTREAM_SYSTEM_HPP

#include "system.fwd.hpp"

#include <iostream>

namespace tests { namespace downstream {

class System
{
   public:
      /**
       *--------------------------------------------------------------------------------------
       *       Class:  System
       *      Method:  System :: getInstance
       * Description:  Factory method returning an instance of the interface
       *--------------------------------------------------------------------------------------
       */
      static System *getInstance();

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  System
       *      Method:  System :: getStream
       * Description:  Instance method returning a stream connected to the downstream system
       *--------------------------------------------------------------------------------------
       */
      std::ostream &getStream();

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  System
       *      Method:  System :: getHistory
       * Description:  Utility method that extracts the history of data received by the interface
       *--------------------------------------------------------------------------------------
       */
       std::string getHistory();

   private:
      System();
      ~System();
      System(System const &);  
      System &operator=(System const &);

      struct PImpl;
      PImpl *m_implementation;
};


} } // tests::downstream

#endif // DOWNSTREAM_SYSTEM_HPP
