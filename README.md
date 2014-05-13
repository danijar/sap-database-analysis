SAP Database Analysis
=====================
***REMOVED***
Set up environment
------------------
***REMOVED***
1. Download an install [HANA Client](https://hanadeveditionsapicl.hana.ondemand.com/hanadevedition/) for your platform from SAP. The 64bit version is recommended.
2. In your ODBC panel, add a new HANA instance using the HDBODBC driver which should be available in the list now. Note that in Windows, there are two distinct ODBC panels for 32bit and 64bit so choose the one that matches the HANA Client.
3. Use `HANA` as DNS name since that's what our source code looks for. Specify IP and port of the database server. To check your setup you can try to establish a connection here.
***REMOVED***
Make sure you compile the application in 32bit or 64bit matching your decision made above. 64bit programs can only see 64bit ODBC data sources, and the other way. The shipped Visual Studio project files default to 64bit.
***REMOVED***
Database connection
-------------------
***REMOVED***
For connection to the ODBC driver we use OTL. You can find [code examples](http://otl.sourceforge.net/otl4_gen_odbc_examples.htm) in the documentation of this library.
