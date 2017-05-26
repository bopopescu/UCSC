/*
Seongwoo Choi
scho29
1368039
CMPS180 - Winter 2017
*/

CREATE VIEW Home_Landlords AS 
SELECT p.SSN, l.LandlordID, O.HouseID, p.ApartmentNumber
FROM Landlords l, Persons p, Ownerships o
WHERE p.SSN = l.OwnerSSN 
AND p.HouseID = o.HouseID 
AND l.LandlordID = o.LandlordID;
