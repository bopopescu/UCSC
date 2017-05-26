/*
Seongwoo Choi
scho29
1368039
CMPS180 - Winter 2017
*/

UPDATE Tenants t
SET LastRentPaidDate = n.DatePaid, RentOverdue = FALSE
FROM NewRentPayments n
WHERE n.HouseID = t.HouseID 
AND n.ApartmentNumber = t.ApartmentNumber
AND n.LeaseTenantSSN = t.LeaseTenantSSN
AND n.Rent = t.Rent;

/* -------------------------------------------------------------------- */
INSERT INTO Tenants (HouseID, ApartmentNumber, LeaseTenantSSN, LeaseStartDate, LeaseExpirationDate, Rent, LastRentPaidDate, RentOverdue)
(SELECT HouseID, ApartmentNumber, LeaseTenantSSN, current_date, NULL, Rent, DatePaid, FALSE
 FROM NewRentPayments n
 WHERE NOT EXISTS (SELECT * 
 					FROM Tenants t 
 					WHERE t.HouseID = n.HouseID 
 					AND t.ApartmentNumber = n.ApartmentNumber));
