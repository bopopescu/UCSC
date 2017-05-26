/*
Find the names and SSN for persons whose salary is 
more than 20,000.
*/

SELECT p.Name, p.SSN
FROM Persons p
WHERE p.Salary > 20000;