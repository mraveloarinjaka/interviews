/**
 * =====================================================================================
 *
 *       Filename:  contract.cpp
 *
 *    Description:  Class defining a contractual agreement between a source and a party
 *
 * =====================================================================================
 */

#include <transaction/contract.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include <sqlite/sqlite3.h>

namespace tests { namespace transaction {

namespace {

const int UNIQUE_ID = 1000;

int getUniqueID()
{
   static int uniqueId = UNIQUE_ID;

   return uniqueId++;
}

/** 
 * Executes a request
 * Executes a SQL request on a open database
 * @param db The database connection
 * @param szRequest The SQL request
 * @param callback 
 *   The callback to process the results set 
 *   (optional) Defaults to 0
 * @param data 
 *   The user data passed to the callback
 *   (optional) Defautls to 0
 */

typedef int (*ResultsSetCB)(void *, int , char **, char **);
   
bool executeRequest(sqlite3 *db, char const *szRequest, ResultsSetCB callback = 0, void *data=0)
{
   bool sqlErrorRaised = false;
   char *szErrMsg = 0;
   int errorCode = 0;

   errorCode = sqlite3_exec(db, szRequest, callback, data, &szErrMsg);
   if(SQLITE_OK != errorCode)
   {
      sqlErrorRaised = true;
      std::cerr <<  "SQL error: " << szErrMsg << std::endl;
      sqlite3_free(szErrMsg);
   }
   return sqlErrorRaised;
}


std::string createSaveRequest(Contract const &contract)
{
   std::ostringstream request;

   request << "insert into CONTRACTS_DBF values (" << contract.getReference() << ", " 
           << "'" << contract.getSource()  << "', "
           << "'" << contract.getParty() << "');" << std::endl;

   return request.str();
}

std::string createLoadAllRequest()
{
   std::ostringstream request;

   request << "select M_REFERENCE, M_SOURCE, M_PARTY from CONTRACTS_DBF";

   return request.str();
}

enum ContractColumn
{
   ContractColumnReference = 0,
   ContractColumnSource,
   ContractColumnParty,
   ContractColumn_
};

bool readAttribute(ContractColumn column, char *szAttribute, Contract *contract)
{
   bool errorRaised = false;

   switch(column)
   {
      case ContractColumnReference:
      {
         contract->setReference(std::atof(szAttribute));
         break;
      }
      case ContractColumnSource:
      {
         contract->setSource(szAttribute);
         break;
      }
      case ContractColumnParty:
      {
         contract->setParty(szAttribute);
         break;
      }
      default:
      {
         errorRaised = true; // unknown column
      }

   }
   return errorRaised;
}

int loadContract(void *pvContracts, int argc, char **argv, char **szColumNames)
{
   bool errorRaised = false;
   Contracts *contracts = static_cast<Contracts *>(pvContracts);
   Contract contract;

   for(int i=0; i < argc && !errorRaised; ++i)
   {
      errorRaised = readAttribute(static_cast<ContractColumn>(i), argv[i], &contract);
   }
   if(!errorRaised)
   {
      contracts->push_back(contract);
   }
   return errorRaised ? 1 : 0;
}


} // namespace
 
Contract::Contract() : m_reference(0)
{
   m_source[0] = 0;
}

double Contract::getReference() const
{
   return m_reference;
}

char const *Contract::getSource() const
{
   return m_source.c_str();
}

char const *Contract::getParty() const
{
   return m_party.c_str();
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
      m_source = source;
   }
   else
   {
      m_source.erase();
   }
   return *this;
}

Contract &Contract::setParty(char const *party)
{
   if(party)
   {
      m_party = party;
   }
   else
   {
      m_party.erase();
   }
   return *this;
}

bool Contract::save(sqlite3 *db)
{
   bool errorRaised = NULL == db;

   if(!errorRaised)
   {
      if(m_reference <= 0)
      {
         m_reference = getUniqueID();
      }
      errorRaised = executeRequest(db, createSaveRequest(*this).c_str());
   }
   return errorRaised;
}

bool Contract::loadAll(sqlite3 *db, Contracts *contracts)
{
   bool errorRaised = NULL == db || NULL == contracts;

   if(!errorRaised)
   {
      errorRaised = executeRequest(db, createLoadAllRequest().c_str(), loadContract, contracts);
   }
   return errorRaised;
}

void Contract::toStream(std::ostream &result) const
{
   result << "Contract (reference: " << m_reference 
          << ", source: " << m_source 
          << ", party: " << m_party << ")" << std::endl;
}


} } // tests::transaction

