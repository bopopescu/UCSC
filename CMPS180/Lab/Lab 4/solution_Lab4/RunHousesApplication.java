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
            
            //password for connecting has intentionally been left blank
            connection = DriverManager.getConnection(
                                                     "jdbc:postgresql://cmps180-db.lt.ucsc.edu/username",
                                                     "username",
                                                     "");
            
            if (connection != null)
                System.out.println("Connected to the database!");

            /* Include your code below to test the methods of the HousesApplication class
             * The sample code in RunStoresApplication.java should be useful.
             * That code tests other methods for a different database schema.
             * Your code below: */
            HousesApplication app = new HousesApplication(connection);
            
            //testing method getLeaseTenantsWithApartmentsInManyHouses
            int numberOfHouses = 4;
            List<Integer> ssns = app.getLeaseTenantsWithApartmentsInManyHouses(numberOfHouses);
            
            /*
            *Output of getLeaseTenantsWithApartmentsInManyHouses *when the parameter numberOfHouses is 4.
             641078001
             699061306
            */
            //printing results
            for (Integer ssn : ssns)
                System.out.println(ssn);

            //testing method raiseSalary
            String name = "John Smith";
            double raise = 10000;
            app.raiseSalary(name, raise);

            //testing method movePersonToApartment
            int ssn = 631952071;
            String address = "401 Heller Drive";
            int apartmentno = 1;
            int house_id = app.movePersonToApartment(ssn, address, apartmentno);
            System.out.println("Result for test 1:" + house_id);
            ssn = 563960185;
            apartmentno = 10;
            house_id = app.movePersonToApartment(ssn, address, apartmentno);
            System.out.println("Result for test 2:" + house_id);
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
