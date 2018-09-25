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
/// <global instances>

logsError createLogs();
logsError writeLogLine(logsType type, const char * line);
logsError writeLogAcc(const char * login, const char * password);

logsError writeDispatch(const char * login, char *msg_USCOREtype, struct ArrayOfDocumentFiles *document_USCOREfiles, struct ArrayOfRecipients *recipients, struct ArrayOfOptions *options);
logsError writeDispatchResult(struct ns2__dispatchResponse m_dispatchStatus);
logsError writeGetDispatchStatus(char * login, struct ArrayOfDispatchIds *dispatch_USCOREids);
logsError writeGetDispatchStatusResult(struct ns2__getDispatchStatusResponse m_getDispatchStatus);

void closeLogs();

#endif
