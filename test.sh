#!/usr/bin/env bash

PORT=6699

killall mpdummy

./mpdummy -p $PORT -v

function mpc() {
   command mpc -p $PORT "$@"
}

set -e
set -v

mpc status
mpc add 'uri'
#mpc crop
mpc current
mpc del 1
#mpc play 
#mpc play 1
mpc next
mpc prev
mpc pause
#mpc pause-if-playing
#mpc toggle
mpc cdprev
mpc stop
#mpc seek 100
mpc clear
mpc outputs
mpc enable 1
mpc disable 1
mpc toggleoutput 1
mpc shuffle
mpc move 1 2
mpc playlist
mpc playlist 'playlist'
mpc listall 'file'
mpc ls 'directory'
mpc lsplaylists
mpc load 'file'
mpc insert 'uri'
mpc save 'file'
mpc rm 'file'
mpc volume 100
mpc repeat
mpc repeat on
mpc random
mpc random on
mpc single
mpc single on
mpc consume
mpc consume on
mpc search 'Artist' 'query'
mpc searchadd 'Artist' 'query'
mpc find 'Artist' 'query'
mpc findadd 'Artist' 'query'
#mpc searchplay <pattern>
#mpc list <type> [<type> <query>]
mpc crossfade
mpc crossfade 10
mpc clearerror
mpc mixrampdb
mpc mixrampdb 10
mpc mixrampdelay
mpc mixrampdelay 10
mpc update
#mpc sticker <uri> <get|set|list|delete|find> [args..] Sticker management
mpc stats
mpc version
#mpc idle [events]
#mpc idleloop [events]
mpc replaygain
mpc replaygain on
mpc channels
mpc sendmessage 1 'message'
#mpc waitmessage 1
#mpc subscribe 1
mpc play || echo "OK"
