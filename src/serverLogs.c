#include "serverLogs.h"
#include <stdio.h>//files
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mutex.h"

#define OPEN_MODE "ab+"

/// <members instance>
FILE * m_fileLog;//the file log
char * s_fileDir;//direction to the file log
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
    pthread_mutex_lock(&g_mutex);//lock mutex, before work with a file
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
    pthread_mutex_unlock(&g_mutex);//unlock mutex, after close a file
    return successful;
  }
  else
    return cannotWrite;
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
