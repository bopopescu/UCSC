/*
Seongwoo Choi
scho29
1368039
CMPS180 - Winter 2017
*/

ALTER TABLE Ownerships ADD CHECK (PropertyTax >= 0);
ALTER TABLE Tenants ADD CONSTRAINT positive_rent CHECK(Rent > 0);

ALTER TABLE Tenants 
	ADD CHECK (LeaseExpirationDate > LeaseStartDate
	OR LeaseExpirationDate IS NULL);

ALTER TABLE Tenants 
	ADD CHECK (RentOverdue = FALSE 
	OR LastRentPaidDate <> current_date);



