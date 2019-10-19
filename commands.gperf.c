/* This file exports the list of commands with callbacks / answers
 * as well as the is_command() function. */

%define constants-prefix COMMANDS_
%define hash-function-name hash_command
%define lookup-function-name is_command
%define word-array-name commands

%global-table
%readonly-tables
%compare-strncmp
%null-strings
%struct-type
%switch=1
%7bit

struct mpd_command_t {
	const char *name;
	char type;
	const void *data;
}

/* List of commands: */
%%
add,                's', NULL
channels,           's', NULL
clear,              's', NULL
clearerror,         's', NULL
commands,           'f', cmd_commands
consume,            's', NULL
crop,               's', NULL
crossfade,          's', NULL
currentsong,        's', MPD_CURRENTSONG_ANSWER
decoders,           's', NULL
delete,             's', NULL
disableoutput,      's', NULL
enableoutput,       's', NULL
find,               's', MPD_FIND_ANSWER
findadd,            's', NULL
list,               'f', cmd_list
listall,            's', NULL
listplaylistinfo,   's', NULL
listplaylists,      's', NULL
load,               's', NULL
lsinfo,             's', NULL
mixrampdb,          's', NULL
mixrampdelay,       's', NULL
move,               's', NULL
next,               's', NULL
noidle,             's', NULL
outputs,            's', MPD_OUTPUTS_ANSWER
pause,              's', NULL
play,               'f', cmd_play
playid,             'f', cmd_play
playlistinfo,       's', MPD_PLCHANGES_ANSWER
playlistsearch,     's', NULL
plchanges,          's', MPD_PLCHANGES_ANSWER
previous,           's', NULL
random,             's', NULL
repeat,             's', NULL
replay_gain_mode,   's', NULL
replay_gain_status, 's', MPD_REPLAY_GAIN_STATUS_ANSWER
rm,                 's', NULL
save,               's', NULL
search,             's', NULL
searchadd,          's', NULL
sendmessage,        's', NULL
setvol,             's', NULL
shuffle,            's', NULL
single,             's', NULL
stats,              's', MPD_STATS_ANSWER
status,             's', MPD_STATUS_ANSWER
stop,               's', NULL
subscribe,          's', NULL
tagtypes,           's', MPD_TAGTYPES_ANSWER
toggleoutput,       's', NULL
update,             's', NULL
%%

#define commands_n \
  (sizeof(commands)/sizeof(*commands))

