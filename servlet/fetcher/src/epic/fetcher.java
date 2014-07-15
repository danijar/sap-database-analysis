package epic;
***REMOVED***
import java.io.IOException;
import java.io.PrintWriter;
import java.net.MalformedURLException;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Types;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
***REMOVED***
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
***REMOVED***
***REMOVED***
/**
 * Servlet implementation class fetcher
 */
@WebServlet("/fetcher")
public class fetcher extends HttpServlet {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
***REMOVED***
***REMOVED***
***REMOVED***
	public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws MalformedURLException, IOException {
        doProcess(request, response);
    }
***REMOVED***
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws MalformedURLException, IOException {
        doProcess(request, response);
    }
    
	public static String fetch_from_DB(String tabID, java.sql.Connection connection) throws SQLException {
		
		Statement stmt = connection.createStatement();
		ResultSet tabNameSet = stmt.executeQuery("SELECT NAME FROM ABAP.ANALYSIS_NAMES WHERE ID='" + tabID + "'");
		String tabname = "";
		if(tabNameSet.next()) {
			tabname = tabNameSet.getString("NAME");
		}
		else {
			System.out.println("Error in fetch_from_DB: Found no name for ID");
			return "";
		}
		
		
		String query = "SELECT FIELDNAME AS name, KEYFLAG AS key, ROLLNAME AS role, DOMNAME as domain, DATATYPE as type, LENG as length FROM ABAP.DD03L WHERE TABNAME='" + tabname + "' ORDER BY POSITION ASC"; 
		//System.out.println("Tabname is " + tabname);
		ResultSet rs = stmt.executeQuery(query);
		ResultSetMetaData rsmd = rs.getMetaData();
		
		String res = "[";
		
		int fetch_len = rsmd.getColumnCount();
		
		String delim = "";
		while (rs.next()) {		
			res += delim;
			res += "{\"" + rsmd.getColumnLabel(1).toLowerCase() + "\":\"" + rs.getString(1) + "\"";
			for (int i = 2; i < fetch_len+1; i++) {
				res += ",\"" + rsmd.getColumnLabel(i).toLowerCase() + "\":\"" + rs.getString(i) + "\"";
				
			}
			delim = ",";
			res += "}";
		//	System.out.print("\n");
		}
		//System.out.println("balldalkf" + rs.toString());
		res += "]";
		return res;
	}
	
	public static String fetch_single(String id, String field, java.sql.Connection connection) throws SQLException {
		return fetch_single(id, field, connection, false);
	}
	
	
	public static String fetch_single(String id, String field, java.sql.Connection connection, boolean translate_boolean) throws SQLException {
		Statement stmt = connection.createStatement();
		
		String query = "SELECT " + field + " FROM ABAP.ANALYSIS_META WHERE ID='" + id + "'"; 
		//System.out.println("Tabname is " + tabname);
		ResultSet rs = stmt.executeQuery(query);
		ResultSetMetaData rsmd = rs.getMetaData();
		int fetch_len = rsmd.getColumnCount();
		if(fetch_len > 1)
			System.out.println("Warning found multiple entries for id");
		
		String res = "";
		if (rs.next()) {	
			if(rsmd.getColumnType(1) == Types.VARCHAR) {
				res += "\"" + rs.getString(1) +"\"";
			}
			else
				if(translate_boolean)
					switch(rs.getInt(1)) {
						case 0: 
							res += "false";
							break;
						case 1: 
							res += "true";
							break;
					}
				else
					res += rs.getString(1);
		}
		
		return res;
	}
	
	public static String fetch_array(String id, String tableName, String fieldName, java.sql.Connection connection) throws SQLException {
		Statement stmt = connection.createStatement();
		String query;
		query = "SELECT " + fieldName + " FROM ABAP.ANALYSIS_" + tableName + " WHERE ID ='" + id + "'"; 
		//System.out.println("Tabname is " + tabname);
		ResultSet rs = stmt.executeQuery(query);
		ResultSetMetaData rsmd = rs.getMetaData();
		
		String res = "[";
		boolean first = true;
		String delim = "";
		while (rs.next()) {		
			res += delim;
			if(rsmd.getColumnType(1) == Types.VARCHAR) {
				res += "\"" + rs.getString(1) +"\"";
			}
			else
				res += rs.getString(1);
			
			delim = ",";
		}
		//System.out.println("balldalkf" + rs.toString());
		res += "]";
		
		return res;
	}
	
	/**
	 * Fetches a summary of all the data stored in the different tables
	 * @param id 			= The distinct id of the node
	 * @param connection	= the existing db connection
	 * @return
	 * @throws SQLException
	 */
	public static String getSummary(String id, java.sql.Connection connection) throws SQLException {
		String allData = "{\"id\":" + id + ",";
		allData += "\"names\":" + fetch_array(id, "NAMES", "name", connection) + ",";
		allData += "\"amount\":" + fetch_single(id, "amount", connection) + ",";
		allData += "\"ratio\":" + fetch_single(id, "ratio", connection) + ",";
		allData += "\"changes\":" + fetch_single(id, "changes", connection) + ",";
		allData += "\"removing\":" + fetch_single(id, "removing", connection, true) + ",";
		allData += "\"children\":" + fetch_array(id, "CHILDREN", "child", connection) + ",";
		allData += "\"added\":" + fetch_array(id, "ADDED", "field ", connection) + ",";
		allData += "\"removed\":" + fetch_array(id, "REMOVED", "field ", connection) ;
		allData += "}";
		return allData;
	}
	
	public static String getAllChildrenData(String id, java.sql.Connection connection) throws SQLException {
		String childrenData = "[";
		// Get all children from DB
		Statement stmt = connection.createStatement();
		String childrenQuery = "SELECT CHILD FROM ABAP.ANALYSIS_CHILDREN WHERE ID='" + id + "'";
		ResultSet rs = stmt.executeQuery(childrenQuery);
		
		String delim = "";
		while (rs.next()) {
			childrenData += delim;
			childrenData += getSummary(rs.getString("CHILD"), connection);
			delim = ",";
		}
		
		childrenData += "]";		
		return childrenData;
	}
	
	public static void doProcess(HttpServletRequest request,
            HttpServletResponse response) throws IOException {
		
		String pathInfo = request.getPathInfo();
	//	System.out.println("Pathinfo was: " + pathInfo);
		// We could parse the table id, but we need string anyway
		Pattern pattern = Pattern.compile("^/([0-9]+)/([a-z]+)");
		Matcher m = pattern.matcher(pathInfo);
		if(!m.find()) {
			System.out.println("Wrong request! Path failed");
			return;
		}
		
		String tabID 	= m.group(1);
		String operation= m.group(2);
				
		if(tabID == "" || operation == "") {
			System.out.println("Got wrong query tabID was " + (tabID != "") + " and operation was " + (operation != ""));
			return;
		}
		
		System.out.println("Request was: " + tabID + "\"" + operation);
		
		PrintWriter output = response.getWriter();	
		response.setContentType("application/json");	
		response.setHeader("Access-Control-Allow-Origin", "*");
		
		String result = "";
		try {
					
			Class.forName("com.sap.db.jdbc.Driver");     	
			java.sql.Connection conn = java.sql.DriverManager.getConnection("jdbc:sap://***REMOVED***","***REMOVED***","***REMOVED***");    	
			
			switch (operation) {
			case "fields":
				System.out.println("Printing fields ....");
				result = fetch_from_DB(tabID, conn);
				break;
			case "children":
				System.out.println("Printing chilren ....");
				result = getAllChildrenData(tabID, conn);
				break;	
			case "summary":
				System.out.println("Printing summary ....");
				result = getSummary(tabID, conn);
				break;
			default:
				break;
			}
						
		} catch (SQLException e) {
		//	System.out.println("Sql excepiton" + e.getMessage());
			output.write("{ \"TABNAME\": \"SQL error in Databaseconnection "+ e.getMessage() + "\" }");
			return;
		
		} catch (ClassNotFoundException e) {
			System.out.println("Class was not found!");
			e.printStackTrace();
		}
		
		//System.out.println("Response was : " + result);
		output.println(result);
	}
}
