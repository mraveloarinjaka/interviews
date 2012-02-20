#ifndef TRANSACTION_CONTRACT_HPP
#define TRANSACTION_CONTRACT_HPP

#include "contract.fwd.hpp"

typedef struct sqlite3 sqlite3;

namespace tests { namespace transaction {

class Contract
{
   public:
      Contract();

      bool save(sqlite3 *);

      double getReference() const;
      char const *getSource() const;

      Contract &setReference(double);
      Contract &setSource(char const *);


   private:
      double m_reference;
      char m_source[CONTRACT_SOURCE_LEN];
};

} } // tests::transaction

#endif // TRANSACTION_CONTRACT_HPP

