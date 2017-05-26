import java.sql.*;
import java.util.*;

/**
 * The class implements methods of the Sales database
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
public class SalesApplication {

    private Connection connection;
    
    /*
     * Constructor
     */
    public SalesApplication(Connection connection) {
        this.connection = connection;
    }
    
    public Connection getConnection()
    {
        return connection;
    }
    
     /**
     * Return list of product names for products whose total sales 
     *  is greater than some specified amount
     * 
     */
    public List<String> getProductNamesWithTotalPriceLargerThan(double amount) {
        List<String> result = new ArrayList<String>();
        // your code here
        String query = "SELECT name FROM Products P, Sales S WHERE P.product_id = S.product_id GROUP BY p.product_id, name HAVING SUM(unit_price * quantity) >"+ Double.toString(amount)+ ";";
        try{
        Statement stmt = connection.createStatement();
        ResultSet rst = stmt.executeQuery(query);
        while(rst.next())
            result.add(rst.getString("name"));
        
        }
        catch (SQLException e) {
            System.out.println("Error while querying the database: " + e);
            e.printStackTrace();
            System.exit(-1);
        }
        
        // end of your code
        return result;  
    }

    /**
     * Add a product to the database. If the product’s name and manufacturer
     * already exists in the database, return the product’s id. Otherwise,
     * add the product to the database, and return the new product id.
     * When a new product is added to the database, its category should be NULL.
     *
     * Adding a product and a manufacturer should be done
     * within a transaction. The isolation level should be Serializable.
     *
     * You will lose credit if this is not done in a transaction; you will get extra
     * credit if you do this in a stored procedure.
     */
    
    
    
    public int addProduct(String name, String manufacturer) {
        int productId = 0;
        // your code here
        
        try{
            connection.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
            connection.setAutoCommit(false);
            
            PreparedStatement probe_stmt = connection.prepareStatement("SELECT product_id FROM Products WHERE name = ? AND manufacturer = ?");
            
            probe_stmt.setString(1,name);
            probe_stmt.setString(2,manufacturer);
            
            ResultSet rst = probe_stmt.executeQuery();
            
            while (rst.next())
            {
                System.out.println("Product already exists!");
                connection.commit();
                return (rst.getInt(1));
            }
            
            //if we reach here it means the product does not exist
            
            System.out.println("Product does not exist, will attempt to insert");
            Statement get_max_stmt = connection.createStatement();
            
            String get_max_query = "SELECT max(product_id) FROM Products";
            
            rst = get_max_stmt.executeQuery(get_max_query);
    
            int max_product_id = 0; //This initialization takes care of the case of an empty Products table where we insert the first product
            
            while (rst.next())
            {
                max_product_id = rst.getInt(1);
            }
            
            System.out.print("Max product_id is:");
            System.out.println(max_product_id);
            
            max_product_id++;
            
            PreparedStatement insert_stmt = connection.prepareStatement("INSERT INTO Products(product_id, name, manufacturer) VALUES (?,?,?)");
            
            insert_stmt.setInt(1,max_product_id);
            insert_stmt.setString(2,name);
            insert_stmt.setString(3,manufacturer);
            
            int number_of_rows = insert_stmt.executeUpdate();
            
            if (number_of_rows > 0)
                System.out.println("Insert statement went through!");
            productId = max_product_id;
            connection.commit();
            
        }
        catch (SQLException e) {
            System.out.println("Error in the database: " + e);
            e.printStackTrace();
            System.exit(-1);
        }
        // end of your code
        return productId;
    }
     
    
    /* Below is an alternative implementation using a stored procedure.
     * In this example, the function addProduct returns the product_id of the existing or new product so there is a single query to the database.
     * Of course, there exist different ways.
    public int addProduct(String name, String manufacturer) {
        int productId = 0;
        // your code here
        
        try{
            connection.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
            connection.setAutoCommit(false);
            
            Statement declaration = connection.createStatement();
            
            
            String stored_procedure_declaration =
            "create or replace function addProduct (product_name char(20), product_manufacturer char(20)) " +
            "returns integer " +
            "language plpgsql "+
            "as $$ "+
            "declare "+
            "result integer; "+
            "max_product_id integer; "+
            "begin "+
            "select product_id from products where name = product_name and manufacturer = product_manufacturer into result; "+
            "if result is null then "+
            "select max(product_id) from products into max_product_id; "+
            "if max_product_id IS NULL then max_product_id = 0; end if; "+
            "max_product_id := max_product_id + 1; "+
            "insert into Products(product_id,name,manufacturer) values (max_product_id, product_name, product_manufacturer); "+
            "result := max_product_id; "+
            "end if; "+
            "return result; "+
            "end $$; ";
            
            declaration.executeUpdate(stored_procedure_declaration);
            
            PreparedStatement stmt = connection.prepareStatement("SELECT * FROM addProduct(?,?)");
            stmt.setString(1,name);
            stmt.setString(2,manufacturer);
            
            ResultSet rst = stmt.executeQuery();
            
            while(rst.next())
            {
                productId = rst.getInt(1);
            }
            
            connection.commit();
            
            
        }
        catch (SQLException e) {
            System.out.println("Error in the database: " + e);
            e.printStackTrace();
            System.exit(-1);
        }
        // end of your code
        return productId;
    }
     */

};
