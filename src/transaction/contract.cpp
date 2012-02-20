#include <transaction/contract.hpp>

#include <cstring>

#include <sqlite/sqlite3.h>

namespace tests { namespace transaction {

Contract::Contract()
{
}

double Contract::getReference() const
{
   return m_reference;
}

char const *Contract::getSource() const
{
   return m_source;
}


Contract &Contract::setReference(double reference)
{
   m_reference = reference;

   return *this;
}

Contract &Contract::setSource(char const *source)
{
   if(source)
   {
      strncpy(m_source, source, CONTRACT_SOURCE_LEN - 1);
      m_source[CONTRACT_SOURCE_LEN - 1] = 0;
   }
   else
   {
      m_source[0] = 0;
   }
   return *this;
}
 
bool Contract::save(sqlite3 *db)
{
   return false;
}


} } // tests::transaction

