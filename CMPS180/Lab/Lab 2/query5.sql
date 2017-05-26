/*
Find the addresses and landlord names for single-dwelling homes, 
i.e., houses which have only one apartment.
*/

SELECT p.Name, h.HouseAddress
FROM Persons p, Houses h, Landlords l, Ownerships o
WHERE h.ApartmentCount = 1
AND p.SSN = l.OwnerSSN
AND l.LandlordID = o.LandlordID
AND o.HouseID = h.HouseID;