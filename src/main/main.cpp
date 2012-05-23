/** 
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Test binary that checks whether contracts can be inserted into a database and read back
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <iterator>
#include <iostream>
#include <sstream>

#include <sqlite/sqlite3.h>
#include <transaction/contract.hpp>

namespace ctransaction = tests::transaction;

namespace 
{

char const * szDATABASE = "test.db";
const int EXPECTED_NUMBER_OF_CONTRACTS = 2;

void openDatabase(char const *szDatabase, sqlite3 **pdb)
{
   sqlite3 *db = 0;

   if(sqlite3_open(szDatabase, &db))
   {
     std::cerr <<  "Can't open database: " << sqlite3_errmsg(db) << std::endl;
     sqlite3_close(db);
     
     return;
   }
   *pdb = db;
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
 *   (optional_ Defautls to 0
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

/** 
 * ===  FUNCTION  ======================================================================
 *         Name:  setUpDatabase
 *  Description:  Prepare the database for the test:
 *                   _ if the contracts table exist, zap it
 *                   _ if the contracts table does not exist, create it
 * =====================================================================================
 */

void setUpDatabase()
{
   sqlite3 *db = 0;
   bool errorRaised = false;

   openDatabase(szDATABASE, &db);
   errorRaised = NULL == db;
   if(!errorRaised)
   {
      std::ostringstream request;
      request << "create table if not exists CONTRACTS_DBF(M_REFERENCE double, M_SOURCE text, M_PARTY text)";
      errorRaised = executeRequest(db, request.str().c_str());
   }
   if(!errorRaised)
   {
      std::ostringstream request;
      request << "delete from CONTRACTS_DBF";
      errorRaised = executeRequest(db, request.str().c_str());
   }
   if(db)
   {
      sqlite3_close(db);
   }
}

/**
 * ===  FUNCTION  ======================================================================
 *         Name:  populateDatabase
 *  Description:  Insert two contracts in the database
 * =====================================================================================
 */

void populateDatabase()
{
   sqlite3 *db = 0;
   bool errorRaised = false;

   openDatabase(szDATABASE, &db);
   errorRaised = NULL == db;
   if(!errorRaised)
   {
      ctransaction::Contract contract;   

      contract.setSource("portfolio");
      contract.setParty("Citibank");
      errorRaised = contract.save(db);
   }
   if(!errorRaised)
   {
      ctransaction::Contract contract;   

      contract.setSource("very long portfolio");
      contract.setParty("JP Morgan and Chase");
      errorRaised = contract.save(db);
   }
   if(db)
   {
      sqlite3_close(db);
   }
}

/** 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkDatabase
 *  Description:  Executes a request to retrive all the contracts in the database.
 *                The expected number should be 2: 2 contracts were inserted by the call to populateDatabase
 * =====================================================================================
 */

struct SelectRequestData
{
   SelectRequestData() : numberOfContracts(0) {}

   int numberOfContracts;
   std::ostringstream result;
};

int readContracts(void *pData, int argc, char **argv, char **aszColumns)
{
   SelectRequestData *data = reinterpret_cast<SelectRequestData *>(pData);

   data->numberOfContracts += 1;
   for(int i=0; i<argc; i++)
   {
      data->result << aszColumns[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
   }
   data->result << "---" << std::endl;

   return 0;
}

void checkDatabase()
{
   sqlite3 *db = 0;
   bool errorRaised = false;
   SelectRequestData result;

   openDatabase(szDATABASE, &db);
   errorRaised = NULL == db;
   if(!errorRaised)
   {
      std::ostringstream request;
      request << "select * from CONTRACTS_DBF";
      std::cout << request.str() << std::endl;
      errorRaised = executeRequest(db, request.str().c_str(), readContracts, &result);
   }
   if(!errorRaised)
   {
      if(EXPECTED_NUMBER_OF_CONTRACTS != result.numberOfContracts)
      {
         std::cerr << "[FAILURE] Wrong number of contracts retrieved: " << result.numberOfContracts << " (" << EXPECTED_NUMBER_OF_CONTRACTS << " expected)." << std::endl;
         std::cerr << result.result.str() << std::endl;
      }
      else
      {
         std::cout << "[SUCCESS] Right number of contracts retrieved." << std::endl;
         std::cout <<  result.result.str() << std::endl;
      }
   }
   if(db)
   {
      sqlite3_close(db);
   }
}
   
/** 
 * ===  FUNCTION  ======================================================================
 *         Name:  readFromDatabase
 *  Description:  Assess that contracts can be read from the database
 *                Execute a request to retrive all the contracts in the database and read the records into a list of contracts
 *                The expected contracts number should be 2: 2 contracts were inserted by the call to populateDatabase
 * =====================================================================================
 */

void readFromDatabase()
{
   sqlite3 *db = 0;
   bool errorRaised = false;
   ctransaction::Contracts contracts;

   openDatabase(szDATABASE, &db);
   errorRaised = NULL == db;
   if(!errorRaised)
   {
      std::cout << "Read contracts from database" << std::endl;
      errorRaised = ctransaction::Contract::loadAll(db, &contracts);
   }
   if(!errorRaised)
   {
      if(EXPECTED_NUMBER_OF_CONTRACTS != contracts.size())
      {
         std::cerr << "[FAILURE] Wrong number of contracts retrieved: " << contracts.size() << " (" << EXPECTED_NUMBER_OF_CONTRACTS << " expected)." << std::endl;
         errorRaised = true;
      }
      else
      {
         std::cout << "[SUCCESS] Right number of contracts retrieved." << std::endl;
      }

      ctransaction::Contracts::const_iterator itBegin = contracts.begin();
      ctransaction::Contracts::const_iterator itEnd = contracts.end();

      for(ctransaction::Contracts::const_iterator it = itBegin; it != itEnd; ++it)
      {
         it->toStream(errorRaised ? std::cerr : std::cout);
      }
   }
   if(db)
   {
      sqlite3_close(db);
   }
}
   
} // namespace

int main()
{
   setUpDatabase();
   populateDatabase();
   checkDatabase();
   readFromDatabase();
}

