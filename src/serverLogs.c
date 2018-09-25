#include "serverLogs.h"
#include <stdio.h>//files
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OPEN_MODE "ab+"

/// <members instance>
FILE * m_fileLog;//the file log
char * s_fileDir;//direction to the file log
/// <members instance>

/// <global instances>
logsLevel g_logsLevel = high;
/// <global instances>

/// <privates functions>
void writeDocumentsTitles(struct ArrayOfDocumentFiles * document_USCOREfiles);
void writeDispatchIDs(struct ArrayOfDispatchIds *dispatch_USCOREids);
/// </privates functions>

/// <summary>
/// Returns actual time to the char.
/// <summary>
/// <param name = "string"> Pointer to a string </param>
void getTimeinString(char ** string)
{
  time_t m_rawtime;
  struct tm * m_timeinfo;
  time (&m_rawtime);
  m_timeinfo = localtime(&m_rawtime);//get local time
  (*string) = asctime(m_timeinfo);//convert struct to string
}

/// <summary>
/// Writes in a log file, time of message.
/// </summary>
void writeTimeLine()
{
  char * s_time = malloc(sizeof(char) * 50);//allocating place in memory
  getTimeinString(&s_time);

  fwrite(s_time, 1, strlen(s_time) - 1, m_fileLog);//date of log
  fwrite(":", 1, 1, m_fileLog);//write separator
}

/// <summary>
/// Creates the file which stores logs.
/// <summary>
/// <return> State of the operation. </return>
logsError createLogs()
{
  if(g_logsLevel != none)
  {
    time_t m_time = time(NULL);
    struct tm *m_tm = localtime(&m_time);//get date 
    char s_string[64];
    strftime(s_string, sizeof(s_string), "%c", m_tm);

    m_fileLog = fopen(s_string, OPEN_MODE);//open the log file
    s_fileDir = malloc(sizeof(char) * strlen(s_string) + 1);//malloc a place in memory
    strcpy(s_fileDir, s_string);//copy the dir to file
  }
  if(fopen != NULL)
  {
    fclose(m_fileLog);
    return successful;
  }
  else
    return noOpen;
}

/// <summary>
/// Prints log to the file.
/// </summary>
/// <param name = "line"> The line of log </param>
/// <param name = "type"> Type of log(info/warning/error/debug)
/// <result> State of the operation. </result>
logsError writeLogLine(logsType type, const char * line)
{
  if(g_logsLevel != none)
  {
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();

    switch(type)
    {
      case info:
        fwrite(" [INFO] ", 1, 8, m_fileLog);//type of log 
      break;

      case warning:
        fwrite(" [WARNING] ", 1, 11, m_fileLog);
      break;

      case error:
        fwrite(" [ERROR] ", 1, 9, m_fileLog);
      break;

      case debug:
        fwrite(" [DEBUG] ", 1, 9, m_fileLog);
      break;

      default:
        fwrite(" [INFO] ", 1, 8, m_fileLog);//type of log 
    }
   
    fwrite(line, 1, strlen(line), m_fileLog);//line of log
    fwrite("\n", 1, 1, m_fileLog);//next line sign

    fclose(m_fileLog);//close file
    return successful;
  }
  else
    return cannotWrite;
}

/// <summary>
/// Writes user login and password to log file.
/// </summary>
/// <param name = "login"> User login </param>
/// <param name = "password"> User password </param>
/// <result> State of the operation. </result>
logsError writeLogAcc(const char * login, const char * password)
{
  if(g_logsLevel == high)
  {
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();
    fwrite(" [DEBUG] ", 1, 9, m_fileLog);//line of log

    fwrite("User connected with login:", 1, 26, m_fileLog);
    fwrite(login, 1, strlen(login) - 1, m_fileLog);
    fwrite(" and password: ", 1, 15, m_fileLog);
    fwrite(password, 1, strlen(password), m_fileLog);
    fwrite("\n", 1, 1, m_fileLog);//next line sign

    fclose(m_fileLog);//close file
    return successful;
  }

  return noPermission;
}

/// <summary>
/// Writes dispatch operation to the file.
/// </summary>
/// <param name = login> User login. </param>
/// <param name = "document_USCOREfiles"> Array of documents, encoded in BASE64. </param>
/// <param name = "recipients"> Array of recipients. </param>
/// <param name = "options"> Additional options. </param>
logsError writeDispatch(const char * login, char *msg_USCOREtype, struct ArrayOfDocumentFiles *document_USCOREfiles, struct ArrayOfRecipients *recipients, struct ArrayOfOptions *options)
{
  if(g_logsLevel != none)
  {
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();
    fwrite(" [INFO] ", 1, 8, m_fileLog);//line of log

    fwrite("Dispatch operation | Account:", 1, 29, m_fileLog);
    fwrite(login, 1, strlen(login) - 1, m_fileLog);
    
    fwrite(" Documents titles:", 1, 18, m_fileLog);
    writeDocumentsTitles(document_USCOREfiles);
    fwrite("\n", 1, 1, m_fileLog);//next line sign

    fclose(m_fileLog);
    return successful;
  }
  return noPermission;
}

/// <summary>
/// Writes to the file result of operation.
/// </summary>
/// <param name = "m_dispatchStatus"> Result of operation </param>
logsError writeDispatchResult(struct ns2__dispatchResponse m_dispatchStatus)
{
  if(g_logsLevel != none)
  {
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();
    if(!strcmp(m_dispatchStatus.return_->result, "OK"))//if is no error
    {
      fwrite(" [INFO] ", 1, 8, m_fileLog);//line of log
      fwrite("Dispatch operation ended successful.", 1, 18, m_fileLog);
    }
    else
    {
      fwrite(" [ERROR] ", 1, 9, m_fileLog);//line of log
      fwrite(m_dispatchStatus.return_->result_USCOREdescription, 1, strlen(m_dispatchStatus.return_->result_USCOREdescription), m_fileLog);
    }

    fwrite("\n", 1, 1, m_fileLog);//next line sign
    fclose(m_fileLog);
    return successful;
  }
  return noPermission;
}

/// <summary>
/// Writes to the file result of opeartions.
/// </summary>
/// <param name = "login"> Login </param>
/// <param name = "dispatch_USCOREids"> Pointer to array of dispatch </param>
/// <return> Result of operation </return>
logsError writeGetDispatchStatus(char * login, struct ArrayOfDispatchIds *dispatch_USCOREids)
{
  if(g_logsLevel != none)
  {
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();
    fwrite(" [INFO] ", 1, 8, m_fileLog);//line of log

    fwrite("Get dispatch status operation| Account:", 1, 39, m_fileLog);
    fwrite(login, 1, strlen(login) - 1, m_fileLog);
    fwrite(" Dispatch id's: ", 1, 26, m_fileLog);

    return successful;
  }
  return noPermission;
}

/// <summary>
/// Cautiously close file and 
/// releases memory.
/// </summary>
void closeLogs()
{
  fclose(m_fileLog);//close file 
  free(s_fileDir);//release string dir to file
}

/// <privates functions>

/// <summary>
/// Writes titles of all documents files.
/// </summary>
/// <param name = "document_USCOREfiles"> Pointer to array of documents </param>
void writeDocumentsTitles(struct ArrayOfDocumentFiles * document_USCOREfiles)
{
  for(int i = 0; i < document_USCOREfiles->__size && document_USCOREfiles->__size > 0; i++)
  {
    fwrite(document_USCOREfiles->__ptr[i]->file_USCOREname, 1, strlen(document_USCOREfiles->__ptr[i]->file_USCOREname), m_fileLog);
  }
}

/// <summary>
/// Writes id's of dispatch to the log file.
/// <param name = "dispatch_USCOREids"> Pointer to an array of dispatch id's </param>
/// </summary>
void writeDispatchIDs(struct ArrayOfDispatchIds *dispatch_USCOREids)
{
  for(int i = 0; i < dispatch_USCOREids->__size && dispatch_USCOREids->__size > 0; i++)
  {
    fwrite(dispatch_USCOREids->__ptr[0], 1, strlen(dispatch_USCOREids->__ptr[0]), m_fileLog);
  }
}

/// </privates functions>