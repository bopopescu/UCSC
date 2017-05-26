DROP SCHEMA Lab1 CASCADE;
CREATE SCHEMA Lab1;

CREATE TABLE Persons(
SSN INT PRIMARY KEY,
Name CHAR(30),
HouseID INT,
ApartmentNumber INT,
Salary DECIMAL(7,2));

CREATE TABLE Houses(
HouseID INT PRIMARY KEY,
HouseAddress VARCHAR(40),
ApartmentCount INT,
Color VARCHAR(40));

CREATE TABLE Landlords(
LandlordID INT PRIMARY KEY,
OwnerSSN INT,
LandlordAddress VARCHAR(40));

CREATE TABLE Ownerships(
LandlordID INT,
HouseID INT,
PurchaseDate DATE,
PropertyTax DECIMAL(7,2),
PRIMARY KEY(LandlordID, HouseID));

CREATE TABLE Tenants(
HouseID INT,
ApartmentNumber INT,
LeaseTenantSSN INT,
LeaseStartDate DATE,
LeaseExpirationDate DATE,
Rent DECIMAL(7,2),
LastRentPaidDate DATE,
RentOverdue BOOLEAN,
PRIMARY KEY(HouseID, ApartmentNumber));
