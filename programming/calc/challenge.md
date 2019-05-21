# Produce for me a functioning OS.VKDSK image that accomplishes to following

 
1. Print  `Calc>` to the screan, then wait for user input

2. Retrive a string from the user comprised of a number `###` an opperator `opperand` and anopther operator `###` the program is expected to handle
'+' '-' '*' '/' and '%'

3. The output should be followed by a newline character

examples of expectations are as follows, note your program will be tested throughly!

~~~~
  Calc> 1 + 1
  2
  Calc> 2 - 1
  1
  Calc> 2 * 2
  4
  Calc> 52 / 13
  4
  Calc>17 % 3
  2
~~~~

first you must realise that you have a small boot sector to work with, so set up your stack variables and determine
how youy want your memory layed out, and get to that point.

function calls are not handled for you, this is were you have to make several decisions about how you want functions to work!

You have not been given any math instructions. these are functions you have to make with basic logic gates!

Figure out how you want to handle user inpuit. The trick here is that you must use interupts, the interupt you have been given for input only reads one character at a time!

finaly output must be handled appropriatly. 

Good luck ctf contestent!
