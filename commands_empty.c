/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -m 100 commands_empty.gperf.c  */
/* Computed positions: -k'1,3' */

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


#define COMMANDS_EMPTY_TOTAL_KEYWORDS 40
#define COMMANDS_EMPTY_MIN_WORD_LENGTH 2
#define COMMANDS_EMPTY_MAX_WORD_LENGTH 16
#define COMMANDS_EMPTY_MIN_HASH_VALUE 4
#define COMMANDS_EMPTY_MAX_HASH_VALUE 43
/* maximum key range = 40, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash_command_empty (register const char *str, register size_t len)
{
  static const unsigned char asso_values[] =
    {
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
      44, 44, 44, 44, 44, 44, 44,  0,  3,  9,
       2, 19, 24, 25, 44, 24, 44, 44,  0, 23,
      12, 22,  7, 44,  9,  0,  4, 17, 10, 44,
       4, 44, 44, 44, 44, 44, 44, 44
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

static const char * const commands_empty[] =
  {
    (char*)0, (char*)0, (char*)0, (char*)0,
    "load",
    "add",
    "search",
    "listall",
    "delete",
    "searchadd",
    "setvol",
    "rm",
    "subscribe",
    "listplaylists",
    "save",
    "disableoutput",
    "listplaylistinfo",
    "channels",
    "single",
    "decoders",
    "next",
    "playlistsearch",
    "repeat",
    "sendmessage",
    "shuffle",
    "update",
    "stop",
    "random",
    "consume",
    "pause",
    "lsinfo",
    "enableoutput",
    "replay_gain_mode",
    "clear",
    "previous",
    "crop",
    "mixrampdb",
    "move",
    "clearerror",
    "mixrampdelay",
    "crossfade",
    "toggleoutput",
    "noidle",
    "findadd"
  };

const char *
is_command_empty (register const char *str, register size_t len)
{
  if (len <= COMMANDS_EMPTY_MAX_WORD_LENGTH && len >= COMMANDS_EMPTY_MIN_WORD_LENGTH)
    {
      register unsigned int key = hash_command_empty (str, len);

      if (key <= COMMANDS_EMPTY_MAX_HASH_VALUE)
        {
          register const char *s = commands_empty[key];

          if (s && *str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return s;
        }
    }
  return 0;
}
#line 57 "commands_empty.gperf.c"


#define commands_empty_n \
  (sizeof(commands_empty)/sizeof(*commands_empty))

