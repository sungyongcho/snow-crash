# Level 09

- Once logged in, you will see a binary file `level09` and the `token` file
```
???$ ssh level09@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level09@localhost's password:
level09@SnowCrash:~$
level09@SnowCrash:~$ ls
level09  token
level09@SnowCrash:~$ ls -ls
total 12
8 -rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
4 ----r--r-- 1 flag09 level09   26 Mar  5  2016 token
level09@SnowCrash:~$ file ./*
./level09: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x0e1c5a0dfb537112250e1c78d5afec3104abb143, not stripped
./token:   data
```
Once you run `level09`, it behaves like below
```
level09@SnowCrash:~$ ./level09
You need to provied only one arg.
level09@SnowCrash:~$ ./level09 token
tpmhr
level09@SnowCrash:~$ ltrace ./level09 token
__libc_start_main(0x80487ce, 2, 0xbffff7e4, 0x8048aa0, 0x8048b10 <unfinished ...>
ptrace(0, 0, 1, 0, 0xb7e2fe38)                                               = -1
puts("You should not reverse this"You should not reverse this
)                                          = 28
+++ exited (status 1) +++
level09@SnowCrash:~$ ./level09 aaaaa
abcde
```
what is the `token` anyway?
```
level09@SnowCrash:~$ cat token
f4kmm6p|=�p�n��DB�Du{��
```
as shown above, it prints some weird characters. To check, let's run `hexdump` and `xxd`

```
level09@SnowCrash:~$ hexdump token
0000000 3466 6d6b 366d 7c70 823d 707f 6e82 8283
0000010 4244 4483 7b75 8c7f 0a89
000001a
level09@SnowCrash:~$ xxd token
0000000: 6634 6b6d 6d36 707c 3d82 7f70 826e 8382  f4kmm6p|=..p.n..
0000010: 4442 8344 757b 7f8c 890a                 DB.Du{....
```

from inspecting both files, we could assume the binary `level09` takes input and prints out the character in 'the different way', and the token may be the one needs to be affected.
as the output of `./level09 aaaa` is `abcde`, the characters may be in wrong order

To do so, I created a simple c program below:

```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char **argv){
	char	buf[BUFF_SIZE];
	int		fd;
	int		len;
	int		i;

	if ( 0 < ( fd = open(argv[1], O_RDONLY))){
		len = read( fd, buf, sizeof(buf));
		buf[len] = '\0';
		close(fd);
	} else {
	  printf("file read error\n");
	}

	i = 0;
	while (buf[i] != '\0')
	{
		printf("%c", buf[i] - i);
		i++;
	}
	printf("\n");
	return 0;
}
```

```
level09@SnowCrash:/tmp$ gcc decode.c
level09@SnowCrash:/tmp$ ./a.out ~/token
f3iji1ju5yuevaus41q1afiuq�
```
let's try

```
level09@SnowCrash:/tmp$ su flag09
Password:
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
flag09@SnowCrash:~$
```
