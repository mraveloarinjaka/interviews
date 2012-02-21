#ifndef TRANSACTION_CONTRACT_FWD_HPP
#define TRANSACTION_CONTRACT_FWD_HPP

#include <vector>

namespace tests {
namespace transaction {

class Contract;
typedef std::vector<Contract> Contracts;
const int CONTRACT_SOURCE_LEN = 11;
const int CONTRACT_PARTY_LEN = 11;


} } // tests::transaction

#endif // TRANSACTION_CONTRACT_FWD_HPP

