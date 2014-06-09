SAP Database Analysis
=====================
***REMOVED***
Setup
-----
***REMOVED***
###Database connection
***REMOVED***
1. Download an install [HANA Client](https://hanadeveditionsapicl.hana.ondemand.com/hanadevedition/) for your platform from SAP. The 64bit version is recommended.
2. In your ODBC panel, add a new HANA instance using the HDBODBC driver which should be available in the list now. Note that in Windows, there are two distinct ODBC panels for 32bit and 64bit so choose the one that matches the HANA Client.
3. Use `HANA` as DNS name since that's what our source code looks for. Specify IP and port of the database server. To check your setup you can try to establish a connection here.
***REMOVED***
For connection from our application to the ODBC driver we use OTL. You can find [code examples](http://otl.sourceforge.net/otl4_gen_odbc_examples.htm) in the documentation of this library.
***REMOVED***
###C++ project
***REMOVED***
Use `include` and `src` as include directories. Compile the application in 32bit or 64bit matching your decision made for the database connection. 64bit programs can only see 64bit ODBC data sources, and the other way.
***REMOVED***
###Viewer
***REMOVED***
You need a web server in order to run the viewer. An lightweight and easy solution is to use the development server that ships with Python. Navigate to the repository root and run `python -m http.server <port>`. Note that the server must run at repository root for the viewer to access the data files. The viewer is now available under `http://localhost:<port>/viewer/` in your browser.
***REMOVED***
The viewer reads its input data from JSON files in `data/root`. To create them, run the C++ application and type in `json` at the root level.
***REMOVED***
Algorithm
---------
***REMOVED***
###Ratios
***REMOVED***
###Hierarchy
***REMOVED***
###Amounts
***REMOVED***
###Differences
***REMOVED***
Team
----
***REMOVED***
Algorithm and applications are created by Danijar Hafner and Jakob Frick. This project is part of our undergraduate studies.
