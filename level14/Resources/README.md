# Level 14

- Once logged in, you get nothing. Yes, notihing.

```
???$ ssh level14@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level14@localhost's password:
level14@SnowCrash:~$ ls
level14@SnowCrash:~$ ls -ls
total 0
level14@SnowCrash:~$
```

let's try `getflag` and reverse.

```
level14@SnowCrash:~$ gdb getflag
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /bin/getflag...(no debugging symbols found)...done.
(gdb) run
Starting program: /bin/getflag
You should not reverse this
[Inferior 1 (process 24274) exited with code 01]
(gdb)
```

Once we disassemble the program, there is a line checks `eax`

```
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
   0x08048946 <+0>:	push   ebp
   0x08048947 <+1>:	mov    ebp,esp
   0x08048949 <+3>:	push   ebx
   0x0804894a <+4>:	and    esp,0xfffffff0
   0x0804894d <+7>:	sub    esp,0x120
   0x08048953 <+13>:	mov    eax,gs:0x14
   0x08048959 <+19>:	mov    DWORD PTR [esp+0x11c],eax
   0x08048960 <+26>:	xor    eax,eax
   0x08048962 <+28>:	mov    DWORD PTR [esp+0x10],0x0
   0x0804896a <+36>:	mov    DWORD PTR [esp+0xc],0x0
   0x08048972 <+44>:	mov    DWORD PTR [esp+0x8],0x1
   0x0804897a <+52>:	mov    DWORD PTR [esp+0x4],0x0
   0x08048982 <+60>:	mov    DWORD PTR [esp],0x0
   0x08048989 <+67>:	call   0x8048540 <ptrace@plt>
   0x0804898e <+72>:	test   eax,eax
   0x08048990 <+74>:	jns    0x80489a8 <main+98>
   0x08048992 <+76>:	mov    DWORD PTR [esp],0x8048fa8
   0x08048999 <+83>:	call   0x80484e0 <puts@plt>
   0x0804899e <+88>:	mov    eax,0x1
   0x080489a3 <+93>:	jmp    0x8048eb2 <main+1388>
   0x080489a8 <+98>:	mov    DWORD PTR [esp],0x8048fc4
   0x080489af <+105>:	call   0x80484d0 <getenv@plt>
   0x080489b4 <+110>:	test   eax,eax
   0x080489b6 <+112>:	je     0x80489ea <main+164>
   0x080489b8 <+114>:	mov    eax,ds:0x804b040
   0x080489bd <+119>:	mov    edx,eax
   0x080489bf <+121>:	mov    eax,0x8048fd0
   0x080489c4 <+126>:	mov    DWORD PTR [esp+0xc],edx
   0x080489c8 <+130>:	mov    DWORD PTR [esp+0x8],0x25
   0x080489d0 <+138>:	mov    DWORD PTR [esp+0x4],0x1
   0x080489d8 <+146>:	mov    DWORD PTR [esp],eax
   0x080489db <+149>:	call   0x80484c0 <fwrite@plt>
   0x080489e0 <+154>:	mov    eax,0x1
   0x080489e5 <+159>:	jmp    0x8048eb2 <main+1388>
   0x080489ea <+164>:	mov    DWORD PTR [esp+0x4],0x0
   0x080489f2 <+172>:	mov    DWORD PTR [esp],0x8048ff6
   0x080489f9 <+179>:	call   0x8048500 <open@plt>
   0x080489fe <+184>:	test   eax,eax
   0x08048a00 <+186>:	jle    0x8048a34 <main+238>
   0x08048a02 <+188>:	mov    eax,ds:0x804b040
   0x08048a07 <+193>:	mov    edx,eax
   0x08048a09 <+195>:	mov    eax,0x8048fd0
   0x08048a0e <+200>:	mov    DWORD PTR [esp+0xc],edx
   0x08048a12 <+204>:	mov    DWORD PTR [esp+0x8],0x25
   0x08048a1a <+212>:	mov    DWORD PTR [esp+0x4],0x1
   0x08048a22 <+220>:	mov    DWORD PTR [esp],eax
   0x08048a25 <+223>:	call   0x80484c0 <fwrite@plt>
   0x08048a2a <+228>:	mov    eax,0x1
   0x08048a2f <+233>:	jmp    0x8048eb2 <main+1388>
   0x08048a34 <+238>:	mov    DWORD PTR [esp+0x4],0x0
   0x08048a3c <+246>:	mov    DWORD PTR [esp],0x8049009
   0x08048a43 <+253>:	call   0x804871c <syscall_open>
   0x08048a48 <+258>:	mov    DWORD PTR [esp+0x14],eax
   0x08048a4c <+262>:	cmp    DWORD PTR [esp+0x14],0xffffffff
   0x08048a51 <+267>:	jne    0x8048e88 <main+1346>
   0x08048a57 <+273>:	mov    eax,ds:0x804b040
   0x08048a5c <+278>:	mov    edx,eax
   0x08048a5e <+280>:	mov    eax,0x804901c
   0x08048a63 <+285>:	mov    DWORD PTR [esp+0xc],edx
   0x08048a67 <+289>:	mov    DWORD PTR [esp+0x8],0x46
   0x08048a6f <+297>:	mov    DWORD PTR [esp+0x4],0x1
   0x08048a77 <+305>:	mov    DWORD PTR [esp],eax
---Type <return> to continue, or q <return> to quit---q
Quit
```
The system call `ptrace`**(0x08048989)** is where the `eax` is set to -1, the program cannot proceed further.

```
(gdb) run
Starting program: /bin/getflag

Breakpoint 3, 0x0804898e in main ()
(gdb) print $eax
$8 = -1

(gdb) cont
Continuing.
You should not reverse this
[Inferior 1 (process 26595) exited with code 01]
```

let's change the value to 0, and continue

```
Starting program: /bin/getflag

Breakpoint 3, 0x0804898e in main ()
(gdb) print $eax
$9 = -1
(gdb) set $eax=0
(gdb) cont
Continuing.
Check flag.Here is your token :
Nope there is no token here for you sorry. Try again :)
[Inferior 1 (process 27685) exited normally]
(gdb)
```

We at least know the program is now runnable.

now, let's try swapping the `uid` and try if the token can be achieved

```
(gdb) run
Starting program: /bin/getflag

Breakpoint 1, 0x0804898e in main ()
(gdb) b getuid
Breakpoint 2 at 0xb7ee4cc0
(gdb) step
Single stepping until exit from function getuid,
which has no line number information.
0x08048b02 in main ()
(gdb) print $eax
$2 = 2014
```

the uid for `flag14` is `3014`

```
level14@SnowCrash:~$ id flag14
uid=3014(flag14) gid=3014(flag14) groups=3014(flag14),1001(flag)
```

moving on...

```
(gdb) set $eax=3014
(gdb) step
Single stepping until exit from function main,
which has no line number information.
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```
