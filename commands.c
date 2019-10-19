/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -m 100 commands.gperf.c  */
/* Computed positions: -k'2,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 17 "commands.gperf.c"
struct mpd_command_t {
	const char *name;
	char type;
	const void *data;
}

/* List of commands: */;

#define COMMANDS_TOTAL_KEYWORDS 53
#define COMMANDS_MIN_WORD_LENGTH 2
#define COMMANDS_MAX_WORD_LENGTH 18
#define COMMANDS_MIN_HASH_VALUE 6
#define COMMANDS_MAX_HASH_VALUE 80
/* maximum key range = 75, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash_command (register const char *str, register size_t len)
{
  static const unsigned char asso_values[] =
    {
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 42, 34, 81,
      18,  0, 81, 27, 38, 13, 81, 81, 28,  3,
      16,  3, 31, 81, 24,  4, 14, 17, 81, 81,
      81, 28, 81, 81, 81, 81, 81, 81
    };
  return len + asso_values[(unsigned char)str[1]] + asso_values[(unsigned char)str[len - 1]];
}

static const struct mpd_command_t commands[] =
  {
#line 46 "commands.gperf.c"
    {"delete", 's', NULL},
#line 57 "commands.gperf.c"
    {"move", 's', NULL},
#line 66 "commands.gperf.c"
    {"rm", 's', NULL},
#line 59 "commands.gperf.c"
    {"noidle", 's', NULL},
#line 42 "commands.gperf.c"
    {"consume", 's', NULL},
#line 70 "commands.gperf.c"
    {"sendmessage", 's', NULL},
#line 45 "commands.gperf.c"
    {"decoders", 's', NULL},
#line 54 "commands.gperf.c"
    {"lsinfo", 's', NULL},
#line 25 "commands.gperf.c"
    {"commands",           'f', cmd_commands},
#line 65 "commands.gperf.c"
    {"replay_gain_mode", 's', NULL},
#line 58 "commands.gperf.c"
    {"next", 's', NULL},
#line 73 "commands.gperf.c"
    {"single", 's', NULL},
#line 64 "commands.gperf.c"
    {"repeat", 's', NULL},
#line 34 "commands.gperf.c"
    {"replay_gain_status", 's', MPD_REPLAY_GAIN_STATUS_ANSWER},
#line 35 "commands.gperf.c"
    {"stats",              's', MPD_STATS_ANSWER},
#line 36 "commands.gperf.c"
    {"status",             's', MPD_STATUS_ANSWER},
#line 53 "commands.gperf.c"
    {"load", 's', NULL},
#line 75 "commands.gperf.c"
    {"subscribe", 's', NULL},
#line 69 "commands.gperf.c"
    {"searchadd", 's', NULL},
#line 29 "commands.gperf.c"
    {"outputs",            's', MPD_OUTPUTS_ANSWER},
#line 76 "commands.gperf.c"
    {"toggleoutput", 's', NULL},
#line 52 "commands.gperf.c"
    {"listplaylists", 's', NULL},
#line 28 "commands.gperf.c"
    {"list",               'f', cmd_list},
#line 51 "commands.gperf.c"
    {"listplaylistinfo", 's', NULL},
#line 44 "commands.gperf.c"
    {"crossfade", 's', NULL},
#line 71 "commands.gperf.c"
    {"setvol", 's', NULL},
#line 27 "commands.gperf.c"
    {"find",               's', MPD_FIND_ANSWER},
#line 62 "commands.gperf.c"
    {"previous", 's', NULL},
#line 77 "commands.gperf.c"
    {"update", 's', NULL},
#line 49 "commands.gperf.c"
    {"findadd", 's', NULL},
#line 38 "commands.gperf.c"
    {"add", 's', NULL},
#line 47 "commands.gperf.c"
    {"disableoutput", 's', NULL},
#line 33 "commands.gperf.c"
    {"plchanges",          's', MPD_PLCHANGES_ANSWER},
#line 48 "commands.gperf.c"
    {"enableoutput", 's', NULL},
#line 32 "commands.gperf.c"
    {"playlistinfo",       's', MPD_PLCHANGES_ANSWER},
#line 68 "commands.gperf.c"
    {"search", 's', NULL},
#line 72 "commands.gperf.c"
    {"shuffle", 's', NULL},
#line 67 "commands.gperf.c"
    {"save", 's', NULL},
#line 60 "commands.gperf.c"
    {"pause", 's', NULL},
#line 50 "commands.gperf.c"
    {"listall", 's', NULL},
#line 74 "commands.gperf.c"
    {"stop", 's', NULL},
#line 39 "commands.gperf.c"
    {"channels", 's', NULL},
#line 63 "commands.gperf.c"
    {"random", 's', NULL},
#line 31 "commands.gperf.c"
    {"playid",             'f', cmd_play},
#line 56 "commands.gperf.c"
    {"mixrampdelay", 's', NULL},
#line 37 "commands.gperf.c"
    {"tagtypes",           's', MPD_TAGTYPES_ANSWER},
#line 26 "commands.gperf.c"
    {"currentsong",        's', MPD_CURRENTSONG_ANSWER},
#line 55 "commands.gperf.c"
    {"mixrampdb", 's', NULL},
#line 40 "commands.gperf.c"
    {"clear", 's', NULL},
#line 43 "commands.gperf.c"
    {"crop", 's', NULL},
#line 30 "commands.gperf.c"
    {"play",               'f', cmd_play},
#line 41 "commands.gperf.c"
    {"clearerror", 's', NULL},
#line 61 "commands.gperf.c"
    {"playlistsearch", 's', NULL}
  };

const struct mpd_command_t *
is_command (register const char *str, register size_t len)
{
  if (len <= COMMANDS_MAX_WORD_LENGTH && len >= COMMANDS_MIN_WORD_LENGTH)
    {
      register unsigned int key = hash_command (str, len);

      if (key <= COMMANDS_MAX_HASH_VALUE && key >= COMMANDS_MIN_HASH_VALUE)
        {
          register const struct mpd_command_t *resword;

          switch (key - 6)
            {
              case 0:
                resword = &commands[0];
                goto compare;
              case 1:
                resword = &commands[1];
                goto compare;
              case 2:
                resword = &commands[2];
                goto compare;
              case 3:
                resword = &commands[3];
                goto compare;
              case 4:
                resword = &commands[4];
                goto compare;
              case 5:
                resword = &commands[5];
                goto compare;
              case 6:
                resword = &commands[6];
                goto compare;
              case 7:
                resword = &commands[7];
                goto compare;
              case 9:
                resword = &commands[8];
                goto compare;
              case 10:
                resword = &commands[9];
                goto compare;
              case 12:
                resword = &commands[10];
                goto compare;
              case 13:
                resword = &commands[11];
                goto compare;
              case 14:
                resword = &commands[12];
                goto compare;
              case 16:
                resword = &commands[13];
                goto compare;
              case 17:
                resword = &commands[14];
                goto compare;
              case 18:
                resword = &commands[15];
                goto compare;
              case 19:
                resword = &commands[16];
                goto compare;
              case 20:
                resword = &commands[17];
                goto compare;
              case 21:
                resword = &commands[18];
                goto compare;
              case 22:
                resword = &commands[19];
                goto compare;
              case 23:
                resword = &commands[20];
                goto compare;
              case 24:
                resword = &commands[21];
                goto compare;
              case 25:
                resword = &commands[22];
                goto compare;
              case 26:
                resword = &commands[23];
                goto compare;
              case 27:
                resword = &commands[24];
                goto compare;
              case 28:
                resword = &commands[25];
                goto compare;
              case 29:
                resword = &commands[26];
                goto compare;
              case 30:
                resword = &commands[27];
                goto compare;
              case 31:
                resword = &commands[28];
                goto compare;
              case 32:
                resword = &commands[29];
                goto compare;
              case 33:
                resword = &commands[30];
                goto compare;
              case 34:
                resword = &commands[31];
                goto compare;
              case 35:
                resword = &commands[32];
                goto compare;
              case 36:
                resword = &commands[33];
                goto compare;
              case 37:
                resword = &commands[34];
                goto compare;
              case 38:
                resword = &commands[35];
                goto compare;
              case 39:
                resword = &commands[36];
                goto compare;
              case 40:
                resword = &commands[37];
                goto compare;
              case 41:
                resword = &commands[38];
                goto compare;
              case 42:
                resword = &commands[39];
                goto compare;
              case 43:
                resword = &commands[40];
                goto compare;
              case 44:
                resword = &commands[41];
                goto compare;
              case 45:
                resword = &commands[42];
                goto compare;
              case 46:
                resword = &commands[43];
                goto compare;
              case 47:
                resword = &commands[44];
                goto compare;
              case 48:
                resword = &commands[45];
                goto compare;
              case 49:
                resword = &commands[46];
                goto compare;
              case 50:
                resword = &commands[47];
                goto compare;
              case 51:
                resword = &commands[48];
                goto compare;
              case 53:
                resword = &commands[49];
                goto compare;
              case 54:
                resword = &commands[50];
                goto compare;
              case 56:
                resword = &commands[51];
                goto compare;
              case 74:
                resword = &commands[52];
                goto compare;
            }
          return 0;
        compare:
          {
            register const char *s = resword->name;

            if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
              return resword;
          }
        }
    }
  return 0;
}
#line 78 "commands.gperf.c"


#define commands_n \
  (sizeof(commands)/sizeof(*commands))

