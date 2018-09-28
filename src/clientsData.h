#ifndef CLIENTSDATA_H
#define CLIENTSDATA_H

typedef struct client client;
struct client
{ 
  char * s_login;
  char * s_password;
  float f_balance;
  float f_limit;
  int i_type;
};

typedef enum clientStatus clientStatus;
enum clientStatus
{
  noFind,
  badPassword,
  successfulFind
};

void freeClient(client * client);
clientStatus checkClient(client * client);

#endif