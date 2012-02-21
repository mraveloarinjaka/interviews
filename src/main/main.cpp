/** 
 * Main test
 */

#include <cstdlib>
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
 * Populates database
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
      request << "create table if not exists CONTRACTS_DBF(M_REFERENCE double, M_SOURCE text)";
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
 * Creates and serialize contracts
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
      errorRaised = contract.save(db);
   }
   if(!errorRaised)
   {
      ctransaction::Contract contract;   

      contract.setSource("very long portfolio");
      errorRaised = contract.save(db);
   }
   if(db)
   {
      sqlite3_close(db);
   }
}

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

/** 
 * Checks database
 *
 * Executes a request to retrive all the contracts in the database.
 * The expected number should be 2:
 *   _ 2 inserted by the call to populateDatabase (@see populateDatabase)
 */
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
      errorRaised = executeRequest(db, request.str().c_str(), readContracts, &result);
   }
   if(!errorRaised)
   {
      if(EXPECTED_NUMBER_OF_CONTRACTS != result.numberOfContracts)
      {
         std::cerr << "[FAILURE] Wrong number of contracts retrieved: " << result.numberOfContracts << " (" << EXPECTED_NUMBER_OF_CONTRACTS << " expected)." << std::endl;
         std::cerr << "select * from CONTRACTS_DBF" << std::endl << result.result.str() << std::endl;
      }
      else
      {
         std::cout << "[SUCCESS] Right number of contracts retrieved." << std::endl;
         std::cout << "select * from CONTRACTS_DBF" << std::endl << result.result.str() << std::endl;
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
   // Clean the database
   setUpDatabase();
   // Create programatically two contracts and save them in the database
   populateDatabase();
   // Check the content of the database
   checkDatabase();
}

