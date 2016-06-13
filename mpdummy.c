#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MPD_HELLO "OK MPD 0.25.0\n"
#define MPD_STATUS_ANSWER \
"volume: 0\n"             \
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

#define COMMAND_LEN 100
#define MAX_CONNECTIONS 30

char *MPD_EXECVP[] = { "mpd", 0 };

int strpre(const char*, const char*);
void *conn_handler(void *);


int main(int argc, char **argv)
{
   int server_sock;
   struct sockaddr_in server;

   // Socket stuff
   if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      err(1, NULL);

   int enable = 1;
   if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
      err(1, NULL);

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(6600);

   if (bind(server_sock, (struct sockaddr *) &server, sizeof(server)) < 0)
      err(1, NULL);

   if (listen(server_sock, 3) < 0)
      err(1, NULL);

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

void * conn_handler(void *client_socket_desc)
{
   int sock = *(int*)client_socket_desc;
   int read_size;
   char command[COMMAND_LEN];

   // Send MPD version and OK
   write(sock, MPD_HELLO, strlen(MPD_HELLO));

   while ((read_size = recv(sock, command, COMMAND_LEN, 0)) > 0)
   {
      // Replace newline with NUL
      command[read_size - 1] = 0;

      // Debug
      //fprintf(stderr, "Got MPD Command: %s\n", command);

      if (! strcmp(command, "idle")) {
         continue; // We don't answer the idle command
      }

      if (strpre(command, "playid")) {

         /* We're bruteforcing all FDs to shutdown.
          * This also terminates the conn_handler()-threads
          * listening on them.
          *
          * Finally we invoke the real MPD.
          */

         for (sock = 3; sock < MAX_CONNECTIONS; ++sock) {
            shutdown(sock, SHUT_RDWR);
         }

         execvp(MPD_EXECVP[0], MPD_EXECVP);
      }

      if (! strcmp(command, "status")) {
         write(sock, MPD_STATUS_ANSWER, strlen(MPD_STATUS_ANSWER));
      }
      else if (! strcmp(command, "outputs")) {
         write(sock, MPD_OUTPUTS_ANSWER, strlen(MPD_OUTPUTS_ANSWER));
      }
      else if (strpre(command, "plchanges")) {
         write(sock, MPD_PLCHANGES_ANSWER, strlen(MPD_PLCHANGES_ANSWER));
      }

      write(sock, "OK\n", 3);
   }
}

int strpre(const char *str, const char *prefix)
{
   return strncmp(prefix, str, strlen(prefix)) == 0;
}
