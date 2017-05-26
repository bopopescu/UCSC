/*
For the tenancies that have an overdue rent, 
find the address and apartment number of the tenancy, 
the ssn, name and salary of the lease tenant, 
and the name of the landlord of the leased apartment.  
In the result for Query6, the attribute for the lease tenant’s name 
should appear as TenantName, 
and the attribute for the landlord’s name should appear as LandlordName.
*/

SELECT p1.name as TenantName, p2.name as LandlordName, p1.ApartmentNumber, p1.ssn, p1.salary, h.HouseAddress
FROM Persons p1, Persons p2, Tenants t, Houses h, Landlords l, Ownerships o
WHERE t.RentOverdue = TRUE
AND t.HouseID = p1.HouseID
AND t.LeaseTenantSSN = p1.SSN
AND t.HouseID = h.HouseID
AND t.HouseID = o.HouseID
AND o.LandlordID = l.LandlordID
AND l.OwnerSSN = p2.SSN;