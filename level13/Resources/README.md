# Level 13

- Once logged in, you will see a binary `level13`
```
???$ ssh level13@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level13@localhost's password:
level13@SnowCrash:~$ ls
level13
level13@SnowCrash:~$ ls -ls
total 8
8 -rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
level13@SnowCrash:~$
```

Once you execute, you will see the follwing
```
level13@SnowCrash:~$ ./level13
UID 2013 started us but we we expect 4242
```

As noticable, the current user id is `2013`

```
level13@SnowCrash:~$ id $USER
uid=2013(level13) gid=2013(level13) groups=2013(level13),100(users)
```

So, the goal is to execute the program with user ID 4242.
In order to do so, a `gdb` will be used

```
level13@SnowCrash:~$ gdb ./level13
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level13/level13...(no debugging symbols found)...done.
(gdb)
```

let\`s change the syntax of assembly to `intel`, and take a look at main function (as any of the C program has `main` function)

```
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
   0x0804858c <+0>:	push   ebp
   0x0804858d <+1>:	mov    ebp,esp
   0x0804858f <+3>:	and    esp,0xfffffff0
   0x08048592 <+6>:	sub    esp,0x10
   0x08048595 <+9>:	call   0x8048380 <getuid@plt> #getuid
   0x0804859a <+14>:	cmp    eax,0x1092 #compare
   0x0804859f <+19>:	je     0x80485cb <main+63> #jump if equal, to main:63
   0x080485a1 <+21>:	call   0x8048380 <getuid@plt>
   0x080485a6 <+26>:	mov    edx,0x80486c8
   0x080485ab <+31>:	mov    DWORD PTR [esp+0x8],0x1092
   0x080485b3 <+39>:	mov    DWORD PTR [esp+0x4],eax
   0x080485b7 <+43>:	mov    DWORD PTR [esp],edx
   0x080485ba <+46>:	call   0x8048360 <printf@plt>
   0x080485bf <+51>:	mov    DWORD PTR [esp],0x1
   0x080485c6 <+58>:	call   0x80483a0 <exit@plt>
   0x080485cb <+63>:	mov    DWORD PTR [esp],0x80486ef
   0x080485d2 <+70>:	call   0x8048474 <ft_des>
   0x080485d7 <+75>:	mov    edx,0x8048709
   0x080485dc <+80>:	mov    DWORD PTR [esp+0x4],eax
   0x080485e0 <+84>:	mov    DWORD PTR [esp],edx
   0x080485e3 <+87>:	call   0x8048360 <printf@plt>
   0x080485e8 <+92>:	leave
   0x080485e9 <+93>:	ret
End of assembler dump.
(gdb)
```
from the line where `cmp` operator is called, and right above, we can assume `getuid` is called for getting `UID` and comparing the value in between.

Let's run a program
```
(gdb) run
Starting program: /home/user/level13/level13
UID 2013 started us but we we expect 4242
[Inferior 1 (process 3027) exited with code 01]
```
if program is just ran by the `run` command, it will execute and the following output will come out.

setting a breakpoint where `getuid` called, and stepping in, and checking the value stored in `eax` will actually show how the pid is actually compared.

So, let's set a breakpoint on `getuid`

```
(gdb) break getuid
Breakpoint 1 at 0xb7ee4cc0
```

and run the program

```
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 1, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6
```
let's check the `eax` now

```
(gdb) print $eax
$1 = 1
```
seems nothing has set

let's continue
```
(gdb) continue
Continuing.

Breakpoint 1, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6
(gdb)
```
and check `eax` again

```
(gdb) print $eax
$2 = 2013
```

now we are sure that the value from `getuid` is stored on `eax`. Moving on..

```
(gdb) continue
Continuing.
UID 2013 started us but we we expect 4242
[Inferior 1 (process 5021) exited with code 01]
(gdb)
```

Changing the value on `eax` to `4242` will move onto the condition where expected.

In order to do so, set a breakpoint on `getuid` and step in, or directly set a breakpoint on `cmp` operator

```
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 1, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6
(gdb) step
Single stepping until exit from function getuid,
which has no line number information.
0x0804859a in main ()
(gdb) print $eax
$4 = 2013
(gdb) set $eax=0x1092
(gdb) step
Single stepping until exit from function main,
which has no line number information.
your token is 2A31L79asukciNyi8uppkEuSx
0xb7e454d3 in __libc_start_main () from /lib/i386-linux-gnu/libc.so.6
(gdb) cont
Continuing.
[Inferior 1 (process 16389) exited with code 050]
```
**OR**

(the address 0x0804859a is from above)
```
(gdb) break *0x0804859a
Breakpoint 2 at 0x804859a
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 2, 0x0804859a in main ()
(gdb) print $eax
$5 = 2013
(gdb) set $eax=0x1092
(gdb) continue
Continuing.
your token is 2A31L79asukciNyi8uppkEuSx
[Inferior 1 (process 29645) exited with code 050]
(gdb)
```
