/* HOUSES, and Persons JOINT Query

Find the different names of all persons who live at 1730 Alma Street. 
The output of your query should not
contain duplicates; that is, the same name should not 
appear more than once.
*/

SELECT DISTINCT p.Name
FROM Persons p, Houses h 
WHERE p.HouseID = h.HouseID
AND h.HouseAddress = '1730 Alma Street';