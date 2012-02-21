/**
 * =====================================================================================
 *
 *       Filename:  system.cpp
 *
 *    Description:  Class defining an interface to a downstream system
 *
 * =====================================================================================
 */

#include <downstream/system.hpp>

#include <sstream>

namespace tests { namespace downstream {

System *System::getInstance()
{
   static System instance;

   return &instance;
}

struct System::PImpl
{
   std::ostringstream m_stream;
};

std::ostream &System::getStream()
{
   return m_implementation->m_stream;
}

std::string System::getHistory()
{
   return m_implementation->m_stream.str();
}

System::System() : m_implementation(new PImpl)
{
}

System::~System()
{
   if(m_implementation)
   {
      delete(m_implementation);
      m_implementation = NULL;
   }
}

} } // tests::downstream

