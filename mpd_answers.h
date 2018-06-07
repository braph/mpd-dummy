#ifndef _MPD_ANSWERS_H
#define _MPD_ANSWERS_H

#define MPD_HELLO "OK MPD 0.25.0\n"

#define MPD_STATUS_ANSWER \
"volume: 100\n"           \
"repeat: 0\n"             \
"random: 0\n"             \
"single: 0\n"             \
"consume: 0\n"            \
"playlist: 1\n"           \
"playlistlength: 1\n"     \
"mixrampdb: 0.000000\n"   \
"state: stop\n"

#define MPD_OUTPUTS_ANSWER \
"outputid: 0\n"            \
"outputname: Start MPD\n"  \
"outputenabled: 1\n"       

#define MPD_PLCHANGES_ANSWER \
"file: Start MPD\n"          \
"Artist: Start MPD\n"        \
"Title: Start MPD\n"         \
"Album: Start MPD\n"         \
"Pos: 0\n"                   \
"Id: 1\n"                    

#define MPD_CURRENTSONG_ANSWER          \
"file: Start MPD\n"                     \
"Last-Modified: 2000-01-01T00:00:00Z\n" \
"Artist: Start MPD\n"                   \
"Title: Start MPD\n"                    \
"Album: Start MPD\n"                    \
"Time: 1\n"                             \
"duration: 1.0\n"                       \
"Pos: 0\n"                              \
"Id: 1\n"

#define MPD_TAGTYPES_ANSWER \
"tagtype: Artist\n"         \
"tagtype: Title\n"          \
"tagtype: Album\n"          \
"tagtype: Track\n"          

#define MPD_FIND_ANSWER                 \
"file: Start MPD\n"                     \
"Last-Modified: 2000-01-01T00:00:00Z\n" \
"Time: 1\n"                             \
"duration: 1.0\n"                       \
"Artist: Start MPD\n"                   \
"Title: Start MPD\n"                    \
"Album: Start MPD\n"                    \
"Track: 1\n"

#define MPD_STATS_ANSWER \
"uptime: 1\n"      \
"playtime: 0\n"    \
"artists: 1\n"     \
"albums: 1\n"      \
"songs: 1\n"       \
"db_playtime: 1\n" \
"db_update: 1\n"

#define MPD_REPLAY_GAIN_STATUS_ANSWER \
"replay_gain_mode: off\n"

#endif
