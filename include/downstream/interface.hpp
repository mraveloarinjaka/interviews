/**
 * =====================================================================================
 *
 *       Filename:  interface.hpp
 *
 *    Description:  Class defining a interface to a downstream system
 *          Usage:  
 *                  @code
 *                     Interface *pInterface = Interface::getInstance();
 *                     std::ostream stream = pInterface->getStream();
 *                     stream << "Feeding downstream system" << std::endl
 *                  @endcode 
 *
 * =====================================================================================
 */

#ifndef DOWNSTREAM_INTERFACE_HPP
#define DOWNSTREAM_INTERFACE_HPP

#include "interface.fwd.hpp"

#include <iostream>

namespace tests { namespace downstream {

class Interface
{
   public:
      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Interface
       *      Method:  Interface :: getInstance
       * Description:  Factory method returning an instance of the interface
       *--------------------------------------------------------------------------------------
       */
      static Interface *getInstance();

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Interface
       *      Method:  Interface :: getStream
       * Description:  Instance method returning a stream connected to the downstream system
       *--------------------------------------------------------------------------------------
       */
      std::ostream &getStream();

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Interface
       *      Method:  Interface :: getHistory
       * Description:  Utility method that extracts the history of data received by the interface
       *--------------------------------------------------------------------------------------
       */
       std::string getHistory();

   private:
      Interface();
      ~Interface();
      Interface(Interface const &);  
      Interface &operator=(Interface const &);

      struct PImpl;
      PImpl *m_implementation;
};


} } // tests::downstream

#endif // DOWNSTREAM_INTERFACE_HPP
