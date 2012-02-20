#ifndef TRANSACTION_CONTRACT_HPP
#define TRANSACTION_CONTRACT_HPP

namespace tests {
namespace transaction {

class Contract
{
   public:
      Contract();

      double m_reference;
      char m_source[11];
};

} } // tests::transaction

#endif // TRANSACTION_CONTRACT_HPP

