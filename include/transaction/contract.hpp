/**
 * =====================================================================================
 *
 *       Filename:  contract.hpp
 *
 *    Description:  Class defining a contractual agreement between a source and a party
 *
 * =====================================================================================
 */

#ifndef TRANSACTION_CONTRACT_HPP
#define TRANSACTION_CONTRACT_HPP

#include "contract.fwd.hpp"

#include <iostream>

typedef struct sqlite3 sqlite3;

namespace tests { namespace transaction {

class Contract
{
   public:
      Contract();

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Contract
       *      Method:  Contract :: save
       * Description:  Serialize the contract into a SQL database
       * 
       * @param db the connection to the database
       * @return false if there is no error
       *--------------------------------------------------------------------------------------
       */
      bool save(sqlite3 *db);

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Contract
       *      Method:  Contract :: loadAll
       * Description:  Load all the contracts from a SQL database
       *
       * @param db the connection to the database
       * @param contracts the list of contracts read from the database
       * @return false if there is no error
       *--------------------------------------------------------------------------------------
       */
      static bool loadAll(sqlite3 *db, Contracts *contracts);

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Contract
       *      Method:  Contract :: toStream
       * Description:  Serialize a contract to a stream
       *
       * @param result the destination stream
       *--------------------------------------------------------------------------------------
       */
      void toStream(std::ostream &result) const;

      /**
       * Getters
       */
      double getReference() const;
      char const *getSource() const;
      char const *getParty() const;

      /**
       * Mutators
       */
      Contract &setReference(double);
      Contract &setSource(char const *);
      Contract &setParty(char const *);


   private:
      double m_reference;
      char m_source[CONTRACT_SOURCE_LEN];
      char m_party[CONTRACT_PARTY_LEN];
};

} } // tests::transaction

#endif // TRANSACTION_CONTRACT_HPP

