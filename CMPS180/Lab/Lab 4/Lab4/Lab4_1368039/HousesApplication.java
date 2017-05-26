import java.sql.*;
import java.util.*;

/**
 * The class implements methods of the Houses database
 * interface.
 *
 * All methods of the class receive a Connection object through which all
 * communication to the database should be performed. Note: the
 * Connection object should not be closed by any method.
 *
 * Also, no method should throw any exceptions. In particular, in case
 * that an error occurs in the database, then the method should print an
 * error message and call System.exit(-1);
 */
public class HousesApplication {

    private Connection connection;
    
    /*
     * Constructor
     */
    public HousesApplication(Connection connection) {
        this.connection = connection;
    }
    
    public Connection getConnection()
    {
        return connection;
    }
    
     /**
     * Takes as argument an integer called numberOfHouses.
     * Returns a list of SSNs for tenants that lease apartments in at least numberOfHouses different houses
     * For example, if we set numberOfHouses to 2, and a tenant leases two apartments in a house and one apartment in another
     * house, that tenant's SSN must be in the result. A tenant who leases a total of two apartments in the same house
     * must not appear in the result as he/she rents apartments in only one house.
     */
    public List<Integer> getLeaseTenantsWithApartmentsInManyHouses(int numberOfHouses)
    {
    List<Integer> result = new ArrayList<Integer>();
        // your code here
        String query = "SELECT leasetenantSSN FROM Tenants t GROUP BY leasetenantSSN HAVING COUNT (DISTINCT HouseID) >= ?";
        try{
        PreparedStatement stmt = connection.prepareStatement(query);
        stmt.setInt(1, numberOfHouses);
        ResultSet rst = stmt.executeQuery();
        while(rst.next())
            result.add(rst.getInt("leasetenantSSN"));

        }
        catch (SQLException e){
            System.out.println("Error while querying the database: " + e);
            e.printStackTrace();
            System.exit(-1);
        }
        
        // end of your code
        return result;
    }

    /**
     * Takes as arguments a name and a raise, and changes the salary of every person who has that
     * specified name, incrementing their salaries by the specified raise amount.  Since name is not UNIQUE
     * in Persons, there may be multiple people with that name.  If there are no people with that name, 
     * raiseSalary should do nothing.  raiseSalary should be performed as a single SQL statement.
     * 
     */
    
    public void raiseSalary(String name, double raise) {
        // your code here
        // UPDATE Persons SET salary = salary + ?  where name = ?;
        String query = "UPDATE Persons SET salary = salary + ?  where name = ?";
        try{
        PreparedStatement stmt = connection.prepareStatement(query);
        stmt.setDouble(1, raise);
        stmt.executeUpdate();
        }    
        catch (SQLException e){
            System.out.println("Error while querying the database: " + e);
            e.printStackTrace();
            System.exit(-1);
        }

        // end of your code
    }
    
    
    /**
     * The movePersonToApartment function takes as arguments an SSN, an address and an apartment number and
     * calls the movePerson stored function with those arguments. The assignment gives the details on
     * how the stored function movePerson moves a person to a new address. The function movePersonToApartment
     * must use a single SQL statement to call the stored function and must return the integer result of
     * the movePerson stored function.
     */
    public int movePersonToApartment(int SSN, String address, int ApartmentNumber)
    {
        int storedFunctionResult = 0;
        // your code here
        try{
            PreparedStatement stmt = connection.prepareStatement("SELECT * FROM movePerson (?, ?, ?)");
            stmt.setInt(1, SSN);
            stmt.setString(2, address);
            stmt.setInt(3, ApartmentNumber);
            int number_of_rows_updated = stmt.executeUpdate();
            }
        catch (SQLException e) {
            System.out.println("Error in the database: " + e);
            e.printStackTrace();
            System.exit(-1);
        }
        // end of your code
        return storedFunctionResult;
        
    }

};
