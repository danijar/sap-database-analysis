package epic;
***REMOVED***
import java.io.IOException;
import java.io.PrintWriter;
import java.net.MalformedURLException;
import java.sql.PreparedStatement;
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
			
			// Output of keyflags shall be true / false
			if(rs.getString(2).isEmpty())
				res += ",\"" + rsmd.getColumnLabel(2).toLowerCase() + "\":false";
			else
				res += ",\"" + rsmd.getColumnLabel(2).toLowerCase() + "\":true";
			
			for (int i = 3; i < fetch_len+1; i++) {
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
	
	public static String fetch_single(String id, java.sql.Connection connection, PreparedStatement prepStatement) throws SQLException {
		return fetch_single(id, connection, prepStatement, false);
	}
	
	
	public static String fetch_single(String id, java.sql.Connection connection, PreparedStatement prepStatement, boolean translate_boolean) throws SQLException {
		//Statement stmt = connection.createStatement();
		
		//String query = "SELECT " + field + " FROM ABAP.ANALYSIS_META WHERE ID='" + id + "'"; 
		//System.out.println("Tabname is " + tabname);
		prepStatement.setString(1, id);
		ResultSet rs = prepStatement.executeQuery();
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
	
	public static String fetch_array(String id, java.sql.Connection connection, PreparedStatement prepStatement) throws SQLException {	
		prepStatement.setString(1, id);
		
		ResultSet rs = prepStatement.executeQuery();
		ResultSetMetaData rsmd = rs.getMetaData();
		
		String res = "[";
		//boolean first = true;
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
	
	private static PreparedStatement fetch_names_stmt = null;
	private static PreparedStatement fetch_amount_stmt = null;
	private static PreparedStatement fetch_ratio_stmt = null;
	private static PreparedStatement fetch_changes_stmt = null;
	private static PreparedStatement fetch_removing_stmt = null;
	
	private static PreparedStatement fetch_children_stmt = null;
	private static PreparedStatement fetch_removed_stmt = null;
	private static PreparedStatement fetch_added_stmt = null;
	
	private static void prepareSummaryStatements(java.sql.Connection connection) throws SQLException {
		if(fetch_names_stmt != null)
			return;
		
		// Prepare all the statements for the queries on the db
		fetch_names_stmt = connection.prepareStatement("SELECT name FROM ABAP.ANALYSIS_NAMES WHERE ID=?");
		fetch_amount_stmt = connection.prepareStatement("SELECT amount FROM ABAP.ANALYSIS_META WHERE ID=?");
	}
	
	private static void prepareDetailStatements(java.sql.Connection connection) throws SQLException {
		if(fetch_children_stmt != null)
			return;
		prepareSummaryStatements(connection);
		
		fetch_children_stmt = connection.prepareStatement("SELECT child FROM ABAP.ANALYSIS_CHILDREN WHERE ID=?");
		fetch_added_stmt = connection.prepareStatement("SELECT field FROM ABAP.ANALYSIS_ADDED WHERE ID=?");
		fetch_removed_stmt = connection.prepareStatement("SELECT field FROM ABAP.ANALYSIS_REMOVED WHERE ID=?");
		
		fetch_ratio_stmt = connection.prepareStatement("SELECT ratio FROM ABAP.ANALYSIS_META WHERE ID=?");
		fetch_changes_stmt = connection.prepareStatement("SELECT changes FROM ABAP.ANALYSIS_META WHERE ID=?");
		fetch_removing_stmt = connection.prepareStatement("SELECT removing FROM ABAP.ANALYSIS_META WHERE ID=?");
	}
	
	
	/**
	 * Fetches a summary of all the data stored in the different tables
	 * @param id 			= The distinct id of the node
	 * @param connection	= the existing db connection
	 * @return
	 * @throws SQLException
	 */
	public static String getDetail(String id, java.sql.Connection connection) throws SQLException {
		prepareDetailStatements(connection);
		
		String allData = "{\"id\":" + id + ","
		 + "\"names\":" + fetch_array(id, connection, fetch_names_stmt) + ","
		 + "\"amount\":" + fetch_single(id, connection, fetch_amount_stmt) + ","
		 + "\"ratio\":" + fetch_single(id, connection, fetch_ratio_stmt) + ","
		 + "\"changes\":" + fetch_single(id, connection, fetch_changes_stmt) + ","
		 + "\"removing\":" + fetch_single(id, connection, fetch_removing_stmt, true) + ","
		 + "\"children\":" + fetch_array(id, connection, fetch_children_stmt) + ","
		 + "\"added\":" + fetch_array(id, connection, fetch_added_stmt) + ","
		 + "\"removed\":" + fetch_array(id, connection, fetch_removed_stmt) + "}";
		return allData;
	}
	
	public static String getSummary(String id, java.sql.Connection connection) throws SQLException {
		prepareSummaryStatements(connection);
		
		String allData = "{\"id\":" + id + ","
		 + "\"names\":" + fetch_array(id, connection, fetch_names_stmt) + ","
		 + "\"amount\":" + fetch_single(id, connection, fetch_amount_stmt) + "}";
		return allData;
	}
	
	
	private static PreparedStatement children_stmt = null;
	
	public static String getAllChildrenDetail(String id, java.sql.Connection connection) throws SQLException {
		if(children_stmt == null) {
			children_stmt = connection.prepareStatement("SELECT CHILD FROM ABAP.ANALYSIS_CHILDREN WHERE ID= ?");
		}
		
		String childrenData = "{";
		// Get all children from DB
		children_stmt.setString(1, id);
		ResultSet rs = children_stmt.executeQuery();
		
		String delim = "";
		while (rs.next()) {
			childrenData += delim;
			childrenData += "\"" + rs.getString("CHILD") + "\":" + getDetail(rs.getString("CHILD"), connection);
			delim = ",";
		}
		
		childrenData += "}";		
		return childrenData;
	}
	
	public static String getAllChildrenSummary(String id, java.sql.Connection connection) throws SQLException {
		if(children_stmt == null) {
			children_stmt = connection.prepareStatement("SELECT CHILD FROM ABAP.ANALYSIS_CHILDREN WHERE ID= ?");
		}
		
		String childrenData = "{";
		// Get all children from DB
		children_stmt.setString(1, id);
		ResultSet rs = children_stmt.executeQuery();
		
		String delim = "";
		while (rs.next()) {
			childrenData += delim;
			childrenData += "\"" + rs.getString("CHILD") + "\":" + getSummary(rs.getString("CHILD"), connection);
			delim = ",";
		}
		
		childrenData += "}";		
		return childrenData;
	}
	
	public static void doProcess(HttpServletRequest request,
            HttpServletResponse response) throws IOException {
		
		String pathInfo = request.getPathInfo();
		//System.out.println("Path info was " + request.getPathInfo());
		// We could parse the table id, but we need string anyway
		Pattern pattern = Pattern.compile("^/([0-9]+)(/[a-z]+)?(/[a-z]+)?");
		Matcher m = pattern.matcher(pathInfo);
		
		if(!m.find()) {
			System.out.println("Wrong request! Path failed");
			return;
		}
		
		String tabID 		= m.group(1);
		String operation 	= "";
		if(m.group(2) != null)
			operation += m.group(2).substring(1);
		String sub_operation= "";
		if(m.group(3) != null)
			sub_operation += m.group(3).substring(1);
		
		if(tabID == "") {
			System.out.println("Got wrong query tabID was " + (tabID != "") + " and operation was " + (operation != ""));
			response.setStatus(400);
			return;
		}
		if(operation == "")
			operation = "detail";
			
		//System.out.println("Request was: " + tabID + "\t" + operation + "|" + sub_operation);
		
		PrintWriter output = null;
		
		response.setContentType("application/json");	
		response.setHeader("Access-Control-Allow-Origin", "*");
		response.setStatus(200);
		
		try {
			output = response.getWriter();
		} catch (IOException e1) {
			response.setStatus(500);
			e1.printStackTrace();
		}	
		
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
				switch (sub_operation) {
					case "":
					case "detail":
						System.out.println("Printing children details ....");
						result = getAllChildrenDetail(tabID, conn);
						break;
					case "summary":
						System.out.println("Printing children summary ....");
						result = getAllChildrenSummary(tabID, conn);
						break;
				}
				break;	
			case "detail":
				System.out.println("Printing details ....");
				result = getDetail(tabID, conn);
				break;
			case "summary":
				System.out.println("Printing summary ....");
				result = getSummary(tabID, conn);
				break;	
			default:
				break;
			}
						
		} catch (SQLException e) {
			System.out.println("Sql excepiton\t" + e.getMessage());
			output.write("{ \"TABNAME\": \"SQL error in Databaseconnection "+ e.getMessage() + "\" }");
			response.setStatus(404);
			return;
		
		} catch (ClassNotFoundException e) {
			System.out.println("Class was not found!");
			e.printStackTrace();
			response.setStatus(500);
		}
		
		//System.out.println("Response was : " + result);
		output.println(result);
	}
}