/* Two columns 

Find the different colors and apartment counts of houses 
where persons named John Smith live. The
output of your query should not contain duplicates; 
that is, the same color and apartment count should
not appear more than once.
*/

SELECT DISTINCT h.Color, h.ApartmentCount 
FROM Persons p, Houses h
WHERE p.Name = 'John Smith'
AND p.HouseID = h.HouseID;