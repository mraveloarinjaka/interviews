/**
 * =====================================================================================
 *
 *       Filename:  serializer.hpp
 *
 *    Description:  Interface that can be used by any backend that can serialize a contract
 *
 * =====================================================================================
 */

#ifndef TRANSACTION_SERIALIZER_HPP
#define TRANSACTION_SERIALIZER_HPP

#include "contract.fwd.hpp"

namespace tests { namespace transaction {

class Serializer
{
   public:

      /**
       *--------------------------------------------------------------------------------------
       *       Class:  Serializer
       *      Method:  Serializer :: save
       * Description:  Serialize the contract into the backend 
       * 
       * @param contract the contract to serialize
       * @return false if there is no error
       *--------------------------------------------------------------------------------------
       */
      bool save(const Contract &contract) = 0;
};

} } // tests::transaction

#endif

