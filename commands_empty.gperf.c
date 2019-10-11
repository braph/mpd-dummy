/* This file exports the list of command names that should return an empty
 * response as well as the is_command_empty() function. */

%define constants-prefix COMMANDS_EMPTY_
%define hash-function-name hash_command_empty
%define lookup-function-name is_command_empty
%define word-array-name commands_empty

%global-table
%readonly-tables
%compare-strncmp
%null-strings
%7bit

/* List of command names: */
%%
add
channels
clear
clearerror
consume
crop
crossfade
decoders
delete
disableoutput
enableoutput
findadd
listall
listplaylistinfo
listplaylists
load
lsinfo
mixrampdb
mixrampdelay
move
next
noidle
pause
playlistsearch
previous
random
repeat
replay_gain_mode
rm
save
search
searchadd
sendmessage
setvol
shuffle
single
stop
subscribe
toggleoutput
update
%%

#define commands_empty_n \
  (sizeof(commands_empty)/sizeof(*commands_empty))

