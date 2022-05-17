# Level 01

## Login

- Login with the `flag` given out from last level, i.e. `flag of level00`

```
ssh level01@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level01@localhost's password:
level01@SnowCrash:~$
```

## Checking password

```
level01@SnowCrash:~$ cat /etc/passwd

...
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
...
level01@SnowCrash:~$
```

- use `john` for decrypting the password
	- [John The Ripper](https://www.openwall.com/john/)

but john is not installed on the machine

## SCP

copy `passwd` file to somewhere where `john` is installed by using:

```
scp -P 4242 level01@localhost:/etc/passwd .

level01@localhost's password: x24ti5gi3x0ol2eh4esiuxias
passwd                       100% 2477     4.9MB/s   00:00
```

### For macOS
- install `john` from `homebrew`, by using the command:

```
brew install john
```

### For Linux
- I chose to use kali, so `john` is installed by default.

On debian/ubuntu, the installation command would be:
```
sudo apt install john
```

- cracking the passcode with the command:
```
john ./password
```

the output should be
```
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 64/64])
No password hashes left to crack (see FAQ)
```

- To see the password

```
john --show ./passwd                                                                                                                                                                            ✔
flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash

1 password hash cracked, 0 left
```

- check password with this code `abcdef` for `flag01`
