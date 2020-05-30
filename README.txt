I made the assumption that the max length of one line is 80 and max number of
tokens on one line is 20.
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
Executing the commands in certain order may cause glitches with execvp so please
 try again if that happens.

Thank you.

Command used to compile: gcc A2.c -o A2.out

Some sample testing outputs:
azhang@csci3120:~/A2$ ./a.out
$ date
Sat May 30 01:40:21 ADT 2020
$ ls
A2.c  a.out
$ who
smahmood pts/1        May 30 01:08 (24.215.119.69)
gysun    pts/3        May 30 00:31 (24.224.205.111)
haoz     pts/4        May 29 23:14 (47.55.120.59)
jdiamond pts/6        May 29 18:05 (142.167.140.186)
parsons1 pts/8        May 29 23:21 (24.138.65.161)
benson   pts/12       May 30 00:43 (76.11.72.117)
allanj   pts/15       May 29 20:47 (134.41.117.26)
azhang   pts/16       May 30 01:39 (47.55.123.137)
yuqiaol  pts/17       May 29 22:12 (142.68.26.96)
smahmood pts/21       May 30 00:29 (24.215.119.69)
$ ls -l
total 32
-rw-r--r--. 1 azhang csugrad  6985 May 30 01:36 A2.c
-rwxr-xr-x. 1 azhang csugrad 21856 May 30 01:40 a.out
$ who am i
azhang   pts/16       May 30 01:39 (47.55.123.137)
$ exit
azhang@csci3120:~/A2$ ./a.out
$ ls -l | grep rwx
-rwxr-xr-x. 1 azhang csugrad 21856 May 30 01:40 a.out
$ sleep 10 & date
$ Sat May 30 01:50:36 ADT 2020
$ date ; sleep 10 ; date
$ Sat May 30 01:52:07 ADT 2020
Sat May 30 01:52:17 ADT 2020
$ ls & date ; sleep 5 ; date
Process 28600 terminated
$ Sat May 30 01:53:46 ADT 2020
A2.c  a.out
Sat May 30 01:53:51 ADT 2020
Process 28994 terminated
$