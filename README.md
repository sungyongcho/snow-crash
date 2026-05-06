# snow-crash

> Wargame-style CTF — Linux misconfigurations, simple reversing, weak-credential discovery, and intro web exploitation.

## Overview

A 14-level wargame on a hardened Linux box, accessed via SSH (`ssh levelXX@localhost -p 4242`). Each level requires obtaining the next user's password through some combination of file-permission hunting, simple binary inspection, password recovery from various sources (logs, packet captures, custom-encoded tokens), CGI vulnerabilities, scripting-language sandbox escapes, and race conditions.

The introductory cybersecurity project at 42 — a foundation for the deeper binary-exploitation work in [rainfall](https://github.com/sungyongcho/rainfall) and [override](https://github.com/sungyongcho/override).

This project was built as part of the 42 school cybersecurity track (offensive-security branch) · Score: 125/100.

## Tech Stack

| Layer | Technologies |
|-------|-------------|
| OS | Linux |
| Tools | Bash, GDB, `strings`, `file`, packet inspection, basic web exploitation |
| Bug classes | Misconfiguration, weak credentials, simple reversing, CGI, race conditions, sandbox escapes |

## Key Features

- File-permission and setuid analysis
- Weak credentials — recovery from logs, disk artifacts, packet captures, and custom-encoded tokens
- Simple binary inspection — `strings`, decompilation, control-flow tweaks
- CGI / web vulnerabilities — command injection, parameter tampering
- Symlink race conditions and timing attacks
- Scripting-language sandbox escapes (Lua, etc.)
- Crypto missteps — predictable randomness, encoding mistakes

## Architecture

```
snow-crash/
├── level00/
│   ├── Resources/       # files / hints / per-level walkthrough
│   └── flag             # captured credentials
├── level01/
│   ├── Resources/
│   └── flag
├── ...
├── level13/
└── level14/             # final / congratulations stage
```

Each `Resources/` directory contains the artifacts that came with the challenge — source files, packet captures, custom-encoded tokens, scripts — alongside a per-level walkthrough in `README.md`. The `flag` file holds the captured credential.

## What This Demonstrates

- **Adversarial mindset**: looking at a system from the perspective of "where is the trust boundary, and how can I cross it?"
- **Tool fluency**: navigating Linux quickly with `find`, `grep`, `strings`, `file`, `ls -la`, GDB, and packet-capture utilities.
- **Foundation for deeper work**: each technique here scales up — the binary-inspection muscle from later levels maps directly onto the pwn challenges in [rainfall](https://github.com/sungyongcho/rainfall) and [override](https://github.com/sungyongcho/override).

## Note

Solutions are published here as a record of completed coursework, post-graduation. They are not intended as walkthroughs for current students of the program.

## License

This project was built as part of the 42 school curriculum.

---

*Part of [sungyongcho](https://github.com/sungyongcho)'s project portfolio.*
