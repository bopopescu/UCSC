/*
Seongwoo Choi
scho29
1368039
CMPS180 - Winter 2017
*/

SELECT DISTINCT p.name, t.Rent
FROM Home_Landlords h, Tenants t, Persons p
WHERE h.SSN = t.LeaseTenantSSN
AND h.SSN = p.SSN
AND t.RentOverdue = 'TRUE';

DELETE FROM Tenants
WHERE HouseID = '1000' AND ApartmentNumber = '2';

DELETE FROM Tenants
WHERE HouseID = '1100' AND ApartmentNumber = '2';