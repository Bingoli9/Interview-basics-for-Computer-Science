## file expression

-e filename: if filename exists, then return true

-d filename: if filename is directory, then return true

-f filename: if filename is file, then return true

-L filename: if filename is symbol link, then return true

-r filename: if filename is readable, then return true

-w filename: if filename is writeable, then return true

-x filename: if filename is executable, then return true

-s filename: if filename's length is not zero, then return true

-h filename: if filename is soft link, return true

filename1 -nt filename2: if filename1 is newer than filename2, then return true

filename1 -ot filename2: if filename1 is older than filename2, then return true

## Other expression

-eq: equal

-ne: not equal

-gt: greater than

-ge: equal or greater than

-lt: less than

-le: equal or less than

-a: logic and

-o: logic or
