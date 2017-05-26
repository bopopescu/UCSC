create or replace function movePersons (theSSN int, theAddress varchar(40), theApartmentNumber int)
returns integer
language plpgsql
as $$
declare
    result integer;
begin
    SELECT HouseID FROM Lab4.houses h WHERE h.houseAddress = theAddress AND h.ApartmentNumber >= theApartmentNumber INTO result;

    UPDATE Lab4.Persons p SET ApartmentNumber = theApartmentNumber, HouseID = h.HouseID FROM Lab4.Houses h WHERE p.SSN = theSSN AND h.HouseID = result;

if result is null then
    result = -1;
end if;
return result;
end $$;
