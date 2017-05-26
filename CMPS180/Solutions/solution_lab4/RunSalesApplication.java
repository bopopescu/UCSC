import java.sql.*;
import java.io.*;
import java.util.*;

/**
 * A class that connects to PostgreSQL and disconnects.
 * You will need to change your credentials below, to match the usename and password of your account
 * in the PostgreSQL server.
 * The name of your database in the server is the same as your username.
 * You are asked to include code that tests the methods of the SalesApplication class
 * in a similar manner to the sample RunStoreApplication.java program.
*/


public class RunSalesApplication
{
    public static void main(String[] args) {
    	
    	Connection connection = null;
    	try {
    		//Register the driver
    		Class.forName("org.postgresql.Driver"); 
    		// Make the connection.
            // You will need to fill in your real username
            // and password for your Postgres account in the arguments of the
            // get Connection method below.
            connection = DriverManager.getConnection(
                                                     "jdbc:postgresql://cmps180-db.lt.ucsc.edu/vassilis",
                                                     "vassilis",
                                                     "");
            
            if (connection != null)
                System.out.println("Connected to the database!");

            /* Include your code below to test the methods of the SalesApplication class
             * The sample code in RunStoresApplication.java should be useful.
             * That code tests other methods for a different database schema.
             * Your code below: */
            
            SalesApplication app = new SalesApplication(connection);
            
            double total_price = 5.0;
            
            List<String> names = app.getProductNamesWithTotalPriceLargerThan(total_price);
            
            System.out.println("Product names");
            for (String name:names)
                System.out.println(name);
            
            
            String name = "Corn Flakes";
            String manufacturer = "Kellogg";
            
            int product_id = app.addProduct(name,manufacturer);
            
            System.out.println("Product id is :" + product_id);
            
            name = "Corolla 2005";
            manufacturer = "Toyota";
            product_id = app.addProduct(name,manufacturer);
            
            System.out.println("Product id is :" + product_id);

            
            /*******************
            * Your code ends here */
            
    	}
    	catch (SQLException | ClassNotFoundException e) {
    		System.out.println("Error while connecting to database: " + e);
    		e.printStackTrace();
    	}
    	finally {
    		if (connection != null) {
    			// Closing Connection
    			try {
					connection.close();
				} catch (SQLException e) {
					System.out.println("Failed to close connection: " + e);
					e.printStackTrace();
				}
    		}
    	}
    }
}
