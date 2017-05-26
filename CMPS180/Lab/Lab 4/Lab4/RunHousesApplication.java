import java.sql.*;
import java.io.*;
import java.util.*;

/**
 * A class that connects to PostgreSQL and disconnects.
 * You will need to change your credentials below, to match the usename and password of your account
 * in the PostgreSQL server.
 * The name of your database in the server is the same as your username.
 * You are asked to include code that tests the methods of the HousesApplication class
 * in a similar manner to the sample RunStoresApplication.java program.
*/


public class RunHousesApplication
{
    public static void main(String[] args) {
    	
    	Connection connection = null;
    	try {
    		//Register the driver
    		Class.forName("org.postgresql.Driver"); 
    		// Make the connection.
            // You will need to fill in your real username
            // and password for your Postgres account in the arguments of the
            // getConnection method below.
            connection = DriverManager.getConnection(
                                                     "jdbc:postgresql://cmps180-db.lt.ucsc.edu/scho29",
                                                     "scho29",
                                                     "passwordseongwoo");
            
            if (connection != null)
                System.out.println("Connected to the database!");

            /* Include your code below to test the methods of the HousesApplication class
             * The sample code in RunStoresApplication.java should be useful.
             * That code tests other methods for a different database schema.
             * Your code below: */
            
            // First Test
            HousesApplication app = new HousesApplication(connection);

            int numberOfHouses = 4;
            
            List<Integer> ssns = app.getLeaseTenantsWithApartmentsInManyHouses(numberOfHouses);

            System.out.println("Result of getLeaseTenantsWithApartmentsInManyHouses is ");
            for (Integer SSN:ssns)
                System.out.println(SSN);
            
            app.raiseSalary("John Smith", 10000);

            int resultmove = app.movePersonToApartment(631952071, "401 Heller Drive", 1);
            int resultmoveP = app.movePersonToApartment(563960185, "401 Heller Drive", 10);

            System.out.println("Result of movePersonToApartment is ");
            System.out.println(resultmove);

            System.out.println("Result of movePersonToApartment is ");
            System.out.println(resultmoveP);

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
