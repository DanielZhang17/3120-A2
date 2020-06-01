I made the assumption that the max length of one line is 80 and max number of
tokens on one line is 40.
Ideally i would dynamically adjust this. Also, little check for user input error
is done, some error would cause the program to behave strangely.
The program may appear to hang after executing background jobs, it's NOT.
It is waiting for user input as the output of the background program do get
printed after the loop prints the prompt ($ ).
If you hit ENTER, the prompt will show up.
If you type a command there it still might work.
Some background jobs will try to output data and in the assignment requirements,
the professor noted that we should not try to handle that.
If an error is reported but that command should work, please restart the program
 and try again.
Executing the commands in certain order may cause glitches so please try again
if that happens.

Thank you.
