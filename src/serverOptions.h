#ifndef SERVEROPTIONS_H
#define SERVEROPTIONS_H

/// <summary>
/// Contains all the server options.
/// </summary>
typedef struct serverOptions serverOptions;
struct serverOptions
{
  unsigned long u_port;
  unsigned long u_acceptTimeout;
  unsigned long u_sendTimeout;
  unsigned long u_recvTimeout;
  unsigned long u_logsLevel;
};

/// <global instances>
extern struct serverOptions g_serverOptions;
/// </global instances>

void loadServerOptions();

#endif
