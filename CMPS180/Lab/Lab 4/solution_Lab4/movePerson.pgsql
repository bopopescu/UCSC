create or replace function movePerson (theSSN integer, theAddress varchar(40), theApartmentNumber integer)
returns integer
language plpgsql
as $$
declare
    house_identifier integer;
    matching_SSN integer;
begin
/* Obtain the HouseID for given address into variable house_identifier.
If there is no house in that address the variable is null and we return -1 */
    SELECT HouseID
    FROM Houses
    WHERE HouseAddress = theAddress AND theApartmentNumber <= ApartmentCount AND theApartmentNumber >= 1
    INTO house_identifier;
/* A select query that returns the matching SSN if it exists (if null we return -1) */
    SELECT SSN
    FROM Persons
    WHERE SSN = theSSN INTO matching_SSN;
/*If either apartment or ssn do not exist we return -1 */ 
    if house_identifier IS NULL OR matching_SSN IS NULL then
       return -1;
    end if;
/* Update persons table to move the person with given ssn to the designated house. */ 
    UPDATE PERSONS P
    SET HouseID = house_identifier, ApartmentNumber = theApartmentNumber
    WHERE P.SSN = theSSN; 
    return house_identifier;
end $$;

