# Level 00

- Brief explanation of the project
	- the HINT is on the video
https://elearning.intra.42.fr/notions/snow-crash/subnotions/snow-crash/videos/snow-crash

```
FIND this first file who can run only as flag00...
```

- use `find` to find files that can be run by `flag00`

## `find / -user flag00 2> /dev/null`

```
level00@SnowCrash:~$ find / -user flag00 2> /dev/null
/usr/sbin/john
/rofs/usr/sbin/john
```

```
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
```
the output may be shifted by [ROT13](https://en.wikipedia.org/wiki/ROT13)

## ROT13
- use this webstite for decode
	- https://www.dcode.fr/caesar-cipher

output is: `nottoohardhere`, with ROT11

## With script
```
level00@SnowCrash:~$ alias rot11="tr A-Za-z L-ZA-Kl-za-k"
level00@SnowCrash:~$ cat /usr/sbin/john | rot11
nottoohardhere
```

## Check the password and getting the flag (and for later..)

```
level00@SnowCrash:~$ su flag00
Password: nottoohardhere
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```
