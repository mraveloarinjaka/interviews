/**
 * SQLite test
 *
 * Basic demonstration of how to use the SQLite C interface.
 * The resulting program executes a SQL command onto a given database.
 *
 * Usage:
 * sqlite_test.exe DATABASE SQL-STATEMENT
 */

#include <sqlite/sqlite3.h>

#include <cstring>
#include <iostream>

namespace
{

int callback(void *NotUsed, int argc, char **argv, char **aszColName)
{
   for(int i=0; i<argc; i++)
   {
      std::cout << aszColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
   }
   return 0;
}

}

int main(int argc, char **argv)
{
   sqlite3 *db;
   char *szErrMsg = 0;
   int rc;

   if( argc!=3 )
   {
      std::cerr <<  "Usage: " << argv[0] << " DATABASE SQL-STATEMENT" << std::endl;

      return(1);
   }
   rc = sqlite3_open(argv[1], &db);
   if( rc )
   {
     std::cerr <<  "Can't open database: " << sqlite3_errmsg(db) << std::endl;
     sqlite3_close(db);
     
     return(1);
   }
   rc = sqlite3_exec(db, argv[2], callback, 0, &szErrMsg);
   if( rc!=SQLITE_OK )
   {
     std::cerr <<  "SQL error: " << szErrMsg << std::endl;
     sqlite3_free(szErrMsg);
   }
   sqlite3_close(db);

   return 0;       
}
