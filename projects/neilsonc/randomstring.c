/* Chris Neilson - CS 362

When writing the inputChar function, I first looked at the testme function to see what types 
of characters it was looking for.  Once I confirmed that it was using both letters and 
symbols, I looked up the ASCII table to see what the number value was for those characters.  
I identified numbers 32 through 126 from the table as the characters I would need, which is
is a total of 94 characters. So when using the rand function, I used rand() % 95 to give 
me a random number between 0 and 94.  I then added 32 to that number to ensure that the 
result would be in my desired range of 32-126.  I then put that result in a char variable 
and returned it.

When writing the inputString function, I checked the testme function to see how long 
the string needed to be. I then set up a for loop so it would run the correct amount of times.  
Initially, I tried calling the inputChar function inside the for loop and appending each of 
the returned characters to a string.  Even though that technically accomplished generating 
a random string, it was not coming up with an exact match to what was needed (even when I 
let it run over a million iterations).  Since the desired result was using only lower case 
letters, I decided to no longer use the inputChar function to generate a random string and 
instead create a new random generator.  I used the same method as the inputChar function, 
but this time used the numbers 97-122 from the ASCII table as those are the lower case letters.
Like my previous attempt, this method technically generated random strings, but even after 
over a million iterations, it also wasn't coming up with a match to the desired result.  Finally,
I resorted to narrowing the pool down to just the letters used in the desired string.  Since 
there were 4 different letters, I generated a random number from 0 to 4 and assigned a letter 
to each number (0 = 'r', 1 = 's', and so on). This achieved the goal of generating a random 
string and matched the desired result after a couple thousand iterations to get the error message.

*/