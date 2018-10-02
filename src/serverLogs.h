#ifndef SERVERLOGS_H
#define SERVERLOGS_H

#include "soap/soapH.h"

typedef enum logsError logsError;
enum logsError
{
  successful, //successful
  noOpen,      //cannot read a file
  cannotWrite,  //cannot write to a file
  noPermission  //logs level is to low
};

typedef enum logsLevel logsLevel;
enum logsLevel
{
  none,       //no logs                                 |0
  normal,     //save errors, warnings and infos         |1
  high       //saves errors, warnings, infos and debug |2
};

typedef enum logsType logsType;
enum logsType
{
  info,
  warning,
  error,
  debug
};

/// <global instances>
extern logsLevel g_logsLevel;
extern unsigned int u_logMaxSize;
/// <global instances>

logsError createLogs();
logsError writeLogLine(logsType type, const char * line);
logsError writeLogLineW(logsType type, const char * line, const int numOfArgs, const char * variable, ...);
void closeLogs();

#endif
