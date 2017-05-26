DROP SCHEMA Lab3 CASCADE;
CREATE SCHEMA Lab3;

CREATE TABLE Persons(
SSN INT PRIMARY KEY,
Name CHAR(30) NOT NULL,
HouseID INT,
ApartmentNumber INT,
Salary DECIMAL(7,2));

CREATE TABLE Houses(
HouseID INT PRIMARY KEY,
HouseAddress VARCHAR(40) UNIQUE,
ApartmentCount INT,
Color VARCHAR(40));

CREATE TABLE Landlords(
LandlordID INT PRIMARY KEY,
OwnerSSN INT NOT NULL UNIQUE,
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
LeaseTenantSSN INT NOT NULL,
LeaseStartDate DATE NOT NULL,
LeaseExpirationDate DATE,
Rent DECIMAL(7,2),
LastRentPaidDate DATE,
RentOverdue BOOLEAN,
PRIMARY KEY(HouseID, ApartmentNumber));

CREATE TABLE NewRentPayments(
HouseID INT,
ApartmentNumber INT,
LeaseTenantSSN INT NOT NULL,
Rent DECIMAL(7,2),
DatePaid DATE,
PRIMARY KEY(HouseID, ApartmentNumber));

