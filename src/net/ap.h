/* ap.h - Attached processor object type and associated definitions. */

#ifndef AP_H
#define AP_H

#include <sys/param.h>

#define NETPORT 8437        /* port number for socket connections */
#define HOSTNAMESZ MAXHOSTNAMELEN /* max length of a hosts name  */

#define SET_ID 1            /* your id is in packet.size */
#define DISCONNECT 2        /* close your connection */
#define CLUSTER_SIZE 3

/* attached processor */

typedef struct {
  int id;
  int sd;  /* socket discriptor mainting link to actuall processor element */
  char name[HOSTNAMESZ];
  int port;
} ap_t;


/* packet type def. */

typedef struct {
  int      cmd;
  long      arg;
  long      arg2;
} packet_t;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#endif
