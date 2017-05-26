DROP SCHEMA Lab2 CASCADE;
CREATE SCHEMA Lab2;
ALTER ROLE scho29 SET SEARCH_PATH to Lab2;

CREATE TABLE Persons(
SSN INT PRIMARY KEY,
Name CHAR(30) NOT NULL,
HouseID INT, 
ApartmentNumber INT,
Salary DECIMAL(7,2));

CREATE TABLE Houses(
HouseID INT PRIMARY KEY,
HouseAddress VARCHAR(40),
ApartmentCount INT,
Color VARCHAR(40),
UNIQUE (HouseAddress));

CREATE TABLE Landlords(
LandlordID INT PRIMARY KEY,
OwnerSSN INT NOT NULL, 
LandlordAddress VARCHAR(40),
UNIQUE (OwnerSSN));

CREATE TABLE Ownerships(
LandlordID INT,
HouseID INT,
PurchaseDate DATE,
PropertyTax DECIMAL(7,2),
PRIMARY KEY(LandlordID, HouseID));

CREATE TABLE Tenants(
HouseID INT,
ApartmentNumber INT,
LeaseTenantSSN INT NOT NULL,
LeaseStartDate DATE NOT NULL,
LeaseExpirationDate DATE,
Rent DECIMAL(7,2),
LastRentPaidDate DATE,
RentOverdue BOOLEAN,
PRIMARY KEY(HouseID, ApartmentNumber),
UNIQUE (LeaseTenantSSN, LeaseStartDate));
