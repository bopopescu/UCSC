/*
Find the names of all persons who lease an apartment whose rent is 
higher than half of that person’s salary

ONE COLUMN
*/

SELECT p.Name
FROM Persons p, Tenants t
WHERE t.Rent > (p.Salary/2)
AND p.SSN = t.LeaseTenantSSN;