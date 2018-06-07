/*
 * mpdummy.c - mpd dummy that invokes the real mpd server
 *
 * Copyright (C) 2017 Benjamin Abendroth
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * MPD dummy server that just displays a "Start MPD" entry.
 *
 * Useful for stopping/starting the MPD inside ncmpcpp:
 *
 *    ~/.ncmpcpp/bindings:
 *       def_key "S"
 *          stop
 *          run_external_command "killall mpd"
 *          run_external_command "mpdummy"
 */

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "mpd_answers.h"

#define COMMAND_LEN 1024
#define STATE_LIST 1
#define STATE_LIST_OK 2
#define COMMAND_OK 0
#define COMMAND_UNKNOWN 1

char *MPD_EXECVP[] = { "mpd", 0 };
int verbose = 0;

#define log(...) do {\
   if (verbose) \
      fprintf(stderr, __VA_ARGS__); \
   } while (0);

void *conn_handler(void *);

int cmd_play(int, const char *);
int cmd_list(int, const char *);
int cmd_commands(int, const char *);

struct command_mapping_s {
   const char *command;
   char type;
   void *data;
} command_mapping[] = {
   { "play",               'f', cmd_play },
   { "playid",             'f', cmd_play },
   { "list",               'f', cmd_list },
   { "commands",           'f', cmd_commands },
   { "find",               's', MPD_FIND_ANSWER },
   { "stats",              's', MPD_STATS_ANSWER },
   { "status",             's', MPD_STATUS_ANSWER },
   { "outputs",            's', MPD_OUTPUTS_ANSWER },
   { "tagtypes",           's', MPD_TAGTYPES_ANSWER },
   { "plchanges",          's', MPD_PLCHANGES_ANSWER },
   { "playlistinfo",       's', MPD_PLCHANGES_ANSWER },
   { "currentsong",        's', MPD_CURRENTSONG_ANSWER },
   { "replay_gain_status", 's', MPD_REPLAY_GAIN_STATUS_ANSWER }
};
#define command_mapping_n (sizeof(command_mapping)/sizeof(struct command_mapping_s))

const char *command_empty[] = {
   "add",      "delete",  "move",    "rm",
   "load",     "save",
   "stop",     "pause",
   "next",     "previous",
   "enableoutput",
   "disableoutput",
   "toggleoutput",
   "repeat",   "random",  "consume", "single",
   "clear",    "crop",
   "replay_gain_mode",
   "clearerror",
   "noidle",
   "decoders",
   "crossfade",
   "lsinfo",
   "listall",
   "listplaylists",
   "listplaylistinfo",
   "mixrampdb", "mixrampdelay",
   "search",
   "searchadd",
   "findadd",
   "playlistsearch",
   "shuffle",
   "setvol",
   "update",
   "channels",
   "sendmessage",
   "subscribe"
};
#define command_empty_n (sizeof(command_empty)/sizeof(char *))

static int v_strcmp(const void *v1, const void *v2) {
   return strcmp(*(char **) v1, *(char **) v2);
}

static int
command_mapping_cmp(const void *v1, const void *v2) {
   struct command_mapping_s *s1 = (struct command_mapping_s *) v1;
   struct command_mapping_s *s2 = (struct command_mapping_s *) v2;
   return strcmp(s1->command, s2->command);
}

int main(int argc, char **argv)
{
   qsort(command_empty, command_empty_n, sizeof(char *), v_strcmp);
   qsort(command_mapping, command_mapping_n, sizeof(struct command_mapping_s), command_mapping_cmp);

   int port = 6600;
   int option;
   char *endptr;

   while ((option = getopt(argc, argv, "hp:v")) != -1)
      switch (option)
      {
         case 'h':
            printf("Usage: %s [-h] [-v] [-p port]\n", argv[0]);
            return 0;
         case 'v':
            verbose = 1;
            break;
         case 'p':
            errno = 0;
            port = strtoimax(optarg, &endptr, 10);
            if (errno || endptr == optarg) {
               fprintf(stderr, "Invalid port number: %s\n", optarg);
               return 1;
            }
            break;
         case '?':
            if (optopt == 'p')
               fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
               fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
               fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
         default:
            abort();
      }

   if (! verbose) {
      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);

      int fd = open("/dev/null", O_RDWR, 0);
      if (fd != -1) {
         dup2(fd, STDIN_FILENO);
         dup2(fd, STDOUT_FILENO);
         dup2(fd, STDERR_FILENO);

         if (fd > 2)
            close(fd);
      }
   }

   int server_sock;
   struct sockaddr_in server;

   // Socket stuff
   for (int try = 0; try <= 5; ++try) {
      sleep(try);

      if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
         continue;

      int enable = 1;
      setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

      struct linger lo = { 1, 0 };
      setsockopt(server_sock, SOL_SOCKET, SO_LINGER, &lo, sizeof(lo));

      server.sin_family = AF_INET;
      server.sin_addr.s_addr = INADDR_ANY;
      server.sin_port = htons(port);

      if (bind(server_sock, (struct sockaddr *) &server, sizeof(server)) < 0)
         continue;

      if (listen(server_sock, 3) < 0)
         continue;

      break;
   }

   // We're listening now, let's fork
   switch(fork()) {
      case -1: err(1, NULL);
      case  0: break;
      default: return 0;
   }

   pthread_t thread_id;
   for (int client_sock = -1 ;; client_sock = accept(server_sock, 0, 0))
   {
      if (client_sock < 0)
         continue;

      if (pthread_create(&thread_id, NULL, conn_handler, (void *) &client_sock) < 0)
         perror("pthread_create");
   }
}

int exec_command(int sock, const char *command);

void write_ok(int sock) {
   write(sock, "OK\n", strlen("OK\n"));
}

void write_fail(int sock, int code, int line, const char *msg) {
   char err[1024];
   snprintf(err, sizeof err, "ACK [%d@%d] {} %s\n", code, line, msg);
   write(sock, err, strlen(err));
}

int cmd_play(int sock, const char *command) {
   write_ok(sock);

   /* We're bruteforcing all FDs to shutdown.
    * This also terminates the conn_handler()-threads
    * listening on them.
    *
    * Finally we invoke the real MPD.
    */
   for (sock = getdtablesize(); sock; --sock) 
      close(sock);

   int fd = open("/dev/null", O_RDWR, 0);
   if (fd != -1) {
      dup2(fd, STDIN_FILENO);
      dup2(fd, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);

      if (fd > 2)
         close (fd);
   }

   execvp(MPD_EXECVP[0], MPD_EXECVP);
   exit(0);
   return 0;
}

static size_t split_line(const char *str, char ***parts)
{
	size_t n_parts = 0;
	char  *part_buf = NULL;
	size_t part_buf_size = 0;
	size_t part_i = 0;

	while(*str) {
		while (*str && !isspace(*str)) {
			if (part_i >= part_buf_size) {
				part_buf_size += 16;
				if (! (part_buf = realloc(part_buf, part_buf_size * sizeof(char))))
               abort();
			}

			part_buf[part_i] = *str;
			++part_i;
			++str;
		}

		while (*str && isspace(*str)) {
			++str;
		}

		if (part_buf) {
			if (! (part_buf = realloc(part_buf, (part_i + 1) * sizeof(char))))
				abort();
			part_buf[part_i] = '\0';

			if (! (*parts = realloc(*parts, (n_parts + 1) * sizeof(char **))))
				abort();

			(*parts)[n_parts] = part_buf;
			++n_parts;
			part_buf = NULL;
			part_buf_size = 0;
			part_i = 0;
		}
	}

	return n_parts;
}

void free_char_array(char **a, size_t size) {
   while (size)
      free(a[--size]);
   free(a);
}

int cmd_list(int sock, const char *command) {
   char **argv = NULL;
   size_t argc = split_line(command, &argv);
   char answer[1024];

   if (argc == 2) {
      snprintf(answer, sizeof answer, "%s: Start MPD\n", argv[1]);
      write(sock, answer, strlen(answer));
      return 0;
   }

   return -1;
}

int cmd_commands(int sock, const char *command) {
   int i;
   char answer[1024];

   for (int i = 0; i < command_empty_n; ++i) {
      snprintf(answer, sizeof answer, "command: %s\n", command_empty[i]);
      write(sock, answer, strlen(answer));
   }

   for (i = 0; i < command_mapping_n; ++i) {
      snprintf(answer, sizeof answer, "command: %s\n", command_mapping[i].command);
      write(sock, answer, strlen(answer));
   }

   return 0;
}

int exec_command(int sock, const char *command) {
   char *command_name = strndup(command, strcspn(command, " \n"));

   const char *found = bsearch(&command_name, command_empty,
      command_empty_n, sizeof(char *), v_strcmp);

   if (found != NULL) {
      free(command_name);
      return 0;
   }

   struct command_mapping_s search, *command_mapping_found;
   search.command = command_name;

   command_mapping_found = bsearch(&search, command_mapping, command_mapping_n,
      sizeof(struct command_mapping_s), command_mapping_cmp);

   if (command_mapping_found != NULL) {
      free(command_name);

      if (command_mapping_found->type == 's') {
         const char *s = (const char *) command_mapping_found->data;
         write(sock, s, strlen(s));
         return 0;
      }
      else if (command_mapping_found->type == 'f') {
         int (*func)(int sock, const char *command) = command_mapping_found->data;
         return func(sock, command);
      }
   }

   log("unknow command: %s\n", command_name);
   free(command_name);
   return COMMAND_UNKNOWN;
}

struct list_s {
   size_t size;
   char **list;
};

void list_add(struct list_s *list, const char *line)
{
   list->list = realloc(list->list, ++(list->size) * sizeof(char*));
   if (! list->list)
      abort();
   list->list[list->size - 1] = strdup(line);
}

void list_clear(struct list_s *list)
{
   while (list->size)
      free(list->list[--(list->size)]);
   free(list->list);
   list->list = NULL;
}

void list_execute(struct list_s *list, int sock, int type)
{
   int ret;

   for (int i = 0; i < list->size; ++i) {
      ret = exec_command(sock, list->list[i]);

      if (ret != COMMAND_OK) {
         if (ret == COMMAND_UNKNOWN)
            write_fail(sock, 5, i, "UNKNOWN COMMAND");
         else
            write_fail(sock, 5, i, "COMMAND FAILED");

         goto end;
      }

      if (type == STATE_LIST_OK)
         write(sock, "list_OK\n", strlen("list_OK\n"));
   }

   write_ok(sock);
end:
   list_clear(list);
}

void *conn_handler(void *client_socket_desc)
{
   int sock = *(int*)client_socket_desc;
   int read_size;
   char buf[COMMAND_LEN];
   char line[COMMAND_LEN];
   int line_pos = 0;
   int list_state = 0;

   struct list_s command_list;

   // Send MPD version and OK
   write(sock, MPD_HELLO, strlen(MPD_HELLO));

   while ((read_size = recv(sock, buf, sizeof buf, 0)) > 0)
   {
      for (int i = 0; i < read_size; ++i) {
         if (line_pos == sizeof buf) {
            line_pos = 0;
         }

         if (buf[i] == '\n') {
            line[line_pos] = '\0';
            log("handling line: %s\n", line);
            line_pos = 0;

            if (list_state) {
               if (! strcmp(line, "command_list_end")) {
                  list_execute(&command_list, sock, list_state);
                  list_state = 0;
               }
               else {
                  list_add(&command_list, line);
               }
            }
            else if (! strcmp(line, "command_list_begin"))
               list_state = STATE_LIST;
            else if (! strcmp(line, "command_list_ok_begin"))
               list_state = STATE_LIST_OK;
            else if (! strncmp(line, "idle", 4))
               ;
            else {
               switch (exec_command(sock, line)) {
               case COMMAND_OK:
                  write_ok(sock);
                  break;
               case COMMAND_UNKNOWN:
                  write_fail(sock, 5, 0, "UNKNOWN COMMAND");
                  break;
               default:
                  write_fail(sock, 5, 0, "COMMAND FAILED");
                  break;
               }
            }
         }
         else {
            line[line_pos++] = buf[i];
         }
      }
   }

   list_clear(&command_list);
   return NULL;
}
