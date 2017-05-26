COPY lab3.Stores FROM stdin USING DELIMITERS '|';
100|Walgreens|201 Front St|Robert Johnson
200|CVS|600 Front St|David Smith
300|Computer Zone|314 Laurel St|Shel Finkelstein
400|Best Buy|2650 41st Ave|John Williams
500|Home Depot|2600 41st Ave|\N
600|Pacific Surf Shop|1502 Pacific Ave|Shel Finkelstein
700|Marshalls|1664 Commercial Way|Peter Davis
800|Safeway|2111 Mission St|George Jetson
900|Bookshop Santa Cruz|1520 Pacific Ave|Shel Finkelstein
\.

COPY lab3.Customers FROM stdin USING DELIMITERS '|';
1|George Gomez|401 Heller Dr|george@mail.com
2|Mary Betancourt|304 Cliff St|mary@mail.com
3|Anne Jameson|1735 Alma St|anne@mail.com
4|Angie Smith|411 Broadway St|\N
5|Lisa Garcia|1795 Holly St|lisa@mail.com
6|Shel Finkelstein|3039 River St|shel@ucsc.edu
7|Kathy Jones|1984 Forest Ave|\N
8|Robert Johnson|1213 Bridge Ave|\N
9|Debora Peterson|4912 Water Str|debora@mail.com
10|Catherine Washington|5050 River Str|catherine@mail.com
11|Juan Rodriguez|1090 Folsom Str|juan@mail.com
\.

COPY lab3.Products FROM stdin USING DELIMITERS '|';
1000|Iphone 7|Electronics|Apple 
2000|Tide Liquid|Detergent|Tide 
3000|Rice Krispies|Food|Kellogg  
4000|Sprite|Beverage|The Coca-Cola Co. 
5000|Corn Flakes|Food|Kellogg 
6000|HP Deskjet 1112|Electronics|HP
7000|Samsung Galaxy S7|Electronics|Samsung
8000|Motorola Droid 3|Electronics|Motorola
9000|HP Pro Book 465|Electronics|HP
\.

COPY lab3.Sales FROM stdin USING DELIMITERS '|';
200|1|1000|09/15/2016|1|762.35|TRUE
200|2|1000|09/15/2016|1|762.35|TRUE
200|3|1000|09/15/2016|1|762.35|TRUE
200|4|1000|09/30/2016|1|702.68|FALSE
100|2|2000|10/01/2016|2|10.18|TRUE
100|4|2000|10/01/2016|3|10.18|TRUE
800|7|3000|07/04/2016|2|3.40|TRUE
800|9|3000|07/04/2016|3|3.40|TRUE
300|3|3000|10/01/2016|10|3.54|TRUE
800|1|5000|10/01/2016|1|3.25|TRUE
800|2|5000|10/01/2016|3|9.75|TRUE
800|10|3000|10/01/2016|15|3.34|TRUE
800|6|3000|07/04/2016|20|3.25|TRUE
800|6|5000|07/04/2016|20|3.25|TRUE
800|5|5000|10/02/2016|30|3.50|FALSE
300|8|8000|10/21/2016|2|220.30|TRUE
300|2|7000|10/22/2016|3|112.40|FALSE
\.

COPY lab3.NewSales FROM stdin USING DELIMITERS '|';
200|5|1000|09/30/2016|1|702.68
200|6|1000|09/30/2016|1|702.68
300|8|8000|10/21/2016|2|220.3
500|10|8000|10/21/2016|1|220.30
500|11|9000|10/23/2016|1|468.20
\.
