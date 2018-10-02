#include "serverLogs.h"
#include <stdio.h>//files
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>//stats of file
#include <stdarg.h>//multiply arguments
#include "mutex.h"

#define OPEN_MODE "ab+"

/// <members instance>
FILE * m_fileLog;//the file log
unsigned int u_logMaxSize = 6291456;//maximum size of log file
const char * s_fileDir = "log.log";//direction to the file log
/// <members instance>

/// <global instances>
logsLevel g_logsLevel = high;
/// <global instances>

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
/// Gets size of a log file.
/// </summary>
/// <return> Size of file(in bytes) </return>
int getSizeOfLog()
{
  struct stat st;
  stat(s_fileDir, &st);
  return (int)st.st_size;//bytes
}

/// <summary>
/// Creates the file which stores logs.
/// When size of a log file, is bigger than 6MB, deletes it.
/// <summary>
/// <return> State of the operation. </return>
logsError createLogs()
{
  if(g_logsLevel != none)
  {
    if(getSizeOfLog() >= u_logMaxSize)//if log file is bigger than 6MB
      remove(s_fileDir);

    m_fileLog = fopen(s_fileDir, OPEN_MODE);//open the log file
    if(fopen != NULL)
    {
     fclose(m_fileLog);
     return successful;
    }
    else
      return noOpen;
  }
  else
    return noPermission;
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
    pthread_mutex_lock(&g_mutex);//lock mutex, before work with a file
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();

    int i_approve = 1;
    switch(type)
    {
      case info:
        fwrite(" [INFO] ", 1, 8, m_fileLog);//type of log 
      break;

      case warning:
        if(g_logsLevel == high)
          fwrite(" [WARNING] ", 1, 11, m_fileLog);
        else
          i_approve = 0;
      break;

      case error:
        fwrite(" [ERROR] ", 1, 9, m_fileLog);
      break;

      case debug:
        if(g_logsLevel == high)
          fwrite(" [DEBUG] ", 1, 9, m_fileLog);
        else
          i_approve = 0;
      break;

      default:
        fwrite(" [INFO] ", 1, 8, m_fileLog);//type of log 
    }
   
    if(i_approve == 1)
    {
      fwrite(line, 1, strlen(line), m_fileLog);//line of log
      fwrite("\n", 1, 1, m_fileLog);//next line sign
    }

    fclose(m_fileLog);//close file
    pthread_mutex_unlock(&g_mutex);//unlock mutex, after close a file
    return successful;
  }
  else
    return cannotWrite;
}

/// <summary>
/// Prints log to the file.
/// </summary>
/// <param name = "line"> The line of log </param>
/// <param name = "type"> Type of log(info/warning/error/debug)
/// <result> State of the operation. </result>
logsError writeLogLineW(logsType type, const char * line, const int numOfArgs, const char * variable, ...)
{
  if(g_logsLevel != none)
  {
    pthread_mutex_lock(&g_mutex);//lock mutex, before work with a file
    m_fileLog = fopen(s_fileDir, OPEN_MODE);
    writeTimeLine();

    int i_approve = 1;
    switch(type)
    {
      case info:
        fwrite(" [INFO] ", 1, 8, m_fileLog);//type of log 
      break;

      case warning:
        if(g_logsLevel == high)
          fwrite(" [WARNING] ", 1, 11, m_fileLog);
        else
          i_approve = 0;
      break;

      case error:
        fwrite(" [ERROR] ", 1, 9, m_fileLog);
      break;

      case debug:
        if(g_logsLevel == high)
          fwrite(" [DEBUG] ", 1, 9, m_fileLog);
        else
          i_approve = 0;
      break;

      default:
        fwrite(" [INFO] ", 1, 8, m_fileLog);//type of log
    }

    if(i_approve == 1)
    {
      fwrite(line, 1, strlen(line), m_fileLog);//line of log
      fwrite(variable, 1, strlen(variable), m_fileLog);
      /// <multiply arguments>
      va_list m_argList;
      va_start(m_argList, variable);
      char * s_tempString;
      for (int i = 0; i < numOfArgs; i++) 
      {
        s_tempString = va_arg(m_argList, char *);
        fwrite(s_tempString, 1, strlen(s_tempString) - 1, m_fileLog);//line of log
      }
      va_end(m_argList);
      /// </multiply arguments>
      fwrite("\n", 1, 1, m_fileLog);//next line sign
    }

    fclose(m_fileLog);//close file
    pthread_mutex_unlock(&g_mutex);//unlock mutex, after close a file
    return successful;
  }
  else
    return cannotWrite;
}