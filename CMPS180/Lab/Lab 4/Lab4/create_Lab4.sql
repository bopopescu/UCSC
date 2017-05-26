DROP SCHEMA Lab4 CASCADE;
CREATE SCHEMA Lab4;

CREATE TABLE Lab4.Persons(
SSN INT PRIMARY KEY,
Name CHAR(30) NOT NULL,
HouseID INT,
ApartmentNumber INT,
Salary DECIMAL(7,2));

CREATE TABLE Lab4.Houses(
HouseID INT PRIMARY KEY,
HouseAddress VARCHAR(40) UNIQUE,
ApartmentCount INT,
Color VARCHAR(40));

CREATE TABLE Lab4.Landlords(
LandlordID INT PRIMARY KEY,
OwnerSSN INT NOT NULL UNIQUE,
LandlordAddress VARCHAR(40));

CREATE TABLE Lab4.Ownerships(
LandlordID INT,
HouseID INT,
PurchaseDate DATE,
PropertyTax DECIMAL(7,2),
PRIMARY KEY(LandlordID, HouseID));

CREATE TABLE Lab4.Tenants(
HouseID INT,
ApartmentNumber INT,
LeaseTenantSSN INT NOT NULL,
LeaseStartDate DATE NOT NULL,
LeaseExpirationDate DATE,
Rent DECIMAL(7,2),
LastRentPaidDate DATE,
RentOverdue BOOLEAN,
PRIMARY KEY(HouseID, ApartmentNumber));