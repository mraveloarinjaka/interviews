/**
 * =====================================================================================
 *
 *       Filename:  interface.cpp
 *
 *    Description:  Class defining a interface to a downstream system
 *
 * =====================================================================================
 */

#include <downstream/interface.hpp>

#include <sstream>

namespace tests { namespace downstream {

Interface *Interface::getInstance()
{
   static Interface instance;

   return &instance;
}

struct Interface::PImpl
{
   std::ostringstream m_stream;
};

std::ostream &Interface::getStream()
{
   return m_implementation->m_stream;
}

std::string Interface::getHistory()
{
   return m_implementation->m_stream.str();
}

Interface::Interface() : m_implementation(new PImpl)
{
}

Interface::~Interface()
{
   if(m_implementation)
   {
      delete(m_implementation);
      m_implementation = NULL;
   }
}

} } // tests::downstream

