/*
Seongwoo Choi
scho29
1368039
CMPS180 - Winter 2017
*/

INSERT INTO Persons VALUES (223298795, 'Seongwoo Choi', 1500, 3, 65676.00);
INSERT INTO Tenants VALUES (1900, 1, 723069206, '05/15/2016', '09/10/2017', 1802.40, '01/01/2017', TRUE);
INSERT INTO Ownerships VALUES (400, 1700, '08/10/1972', 10241.21);

-- general constraints
-- constraint 1
UPDATE Ownerships
SET PropertyTax = 12
WHERE LandlordID = 100;

UPDATE Ownerships
SET PropertyTax = -12
WHERE LandlordID = 200;
-- constraint 2
UPDATE Tenants
SET Rent = 1000.00
WHERE HouseID = 100;

UPDATE Tenants
SET Rent = 0
WHERE HouseID = 200;

-- constraint 3
UPDATE Tenants
SET LeaseExpirationDate = NULL
WHERE HouseID = 200;

UPDATE Tenants
SET LeaseExpirationDate = '02/01/2014'
WHERE HouseID = 100;

-- constraint 4
UPDATE Tenants
SET LastRentPaidDate = current_date
WHERE HouseID = 600
AND RentOverdue = FALSE;

UPDATE Tenants
SET LastRentPaidDate = current_Date
WHERE ApartmentNumber = 2;