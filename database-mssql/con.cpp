#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

main() {
  SQLHENV env; //environment handle
  SQLHDBC dbc; //connection handle
  SQLRETURN ret; //return status

  SQLCHAR outstr[1024]; // output string
  SQLSMALLINT outstrlen; // output string length

  SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env); //allocate environment handle
  SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0); // ODBC version 3
  SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc); // allocate connection handle

  // Connect to a DSN
  ret = SQLDriverConnect(dbc, NULL, 
    (SQLCHAR*)"DSN=mssqlserver;UID=sa;PWD=password", SQL_NTS,
    outstr, sizeof(outstr), &outstrlen,
    SQL_DRIVER_NOPROMPT);
  if (SQL_SUCCEEDED(ret)) {
    printf("Connected\n");
    printf("Returned connection string was:\n\t%s\n", outstr);
    if (ret == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported diagnostics\n");
    }
    SQLDisconnect(dbc); // disconnect
  } else {
    printf("Failed to connect\n");
  }
  
  // free up allocated handles
  SQLFreeHandle(SQL_HANDLE_DBC, dbc);
  SQLFreeHandle(SQL_HANDLE_ENV, env);
}
