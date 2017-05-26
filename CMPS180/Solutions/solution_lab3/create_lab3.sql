DROP SCHEMA lab3 CASCADE;
CREATE SCHEMA lab3;

CREATE TABLE lab3.Stores
( store_id INT PRIMARY KEY,
  name CHAR(20),
  address VARCHAR(50),
  manager CHAR(20));

CREATE TABLE lab3.Customers
( customer_id INT PRIMARY KEY,
  name CHAR(20),
  address VARCHAR(50),
  email CHAR(20));

CREATE TABLE lab3.Products
( product_id INT PRIMARY KEY,
  name CHAR(20),
  category CHAR(20),
  manufacturer CHAR(20));

CREATE TABLE lab3.Sales
( store_id INT,
  customer_id INT,
  product_id INT,
  purchase_date DATE,
  quantity INT,
  unit_price DECIMAL(6,2),
  shipped BOOLEAN,
  PRIMARY KEY(store_id, customer_id, product_id, purchase_date) );

CREATE TABLE lab3.NewSales
( store_id INT,
  customer_id INT,
  product_id INT,
  purchase_date DATE,
  quantity INT,
  unit_price DECIMAL(6,2),
  PRIMARY KEY(store_id, customer_id, product_id, purchase_date) );
  