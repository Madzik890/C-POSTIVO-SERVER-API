#include "serverOptions.h"
#include <stdio.h>//files
#include <stdlib.h>
#include <string.h>

#define CONFIG_NAME "serverConfig.txt"

/// <global instances>
struct serverOptions g_serverOptions;
/// </global instances>

void createOptionsFile();
void defaultOptions();

/// <summary>
/// Converts a config line to parameter.
/// </summary>
/// <param name = line> Line read from config file </param>
void setOptionsParam(char line[50])
{
  char s_param[50];
  if(strstr(line, "[SERVER PORT]:"))
  {
    strncpy(s_param, line + 14, strlen(line) - 14);
    g_serverOptions.u_port = atoi(s_param);
  }
  else
  if(strstr(line, "[ACCEPT TIMEOUT]:"))
  {
    strncpy(s_param, line + 17, strlen(line) - 17);
    g_serverOptions.u_acceptTimeout = atoi(s_param);
  }
  else
  if(strstr(line, "[SEND TIMEOUT]:"))
  {
    strncpy(s_param, line + 15, strlen(line) - 15);
    g_serverOptions.u_sendTimeout = atoi(s_param);
  }
  else
  if(strstr(line, "[RECEIVE TIMEOUT]:"))
  {
    strncpy(s_param, line + 18, strlen(line) - 18);
    g_serverOptions.u_recvTimeout = atoi(s_param);
  }
  else
  if(strstr(line, "[LOGS LEVEL]:"))
  {
    strncpy(s_param, line + 13, strlen(line) - 13);
    g_serverOptions.u_logsLevel = atoi(s_param);
  }
}

/// <summary>
/// Loads options about server configuration.
/// Server options:
/// -ip
/// -server
/// -accept timeout
/// -receive timeout
/// When did not read a file, server is setting by default options.
/// <summary>
void loadServerOptions()
{
  FILE * m_file = NULL;

  m_file = fopen(CONFIG_NAME, "r");
  if(m_file != NULL)
  {
    char s_buffer[50];
    while (fgets(s_buffer, sizeof(s_buffer), m_file) != NULL)
    {
      s_buffer[strlen(s_buffer) - 1] = '\0'; //delete a newline sign
      setOptionsParam(s_buffer);
    }
    fclose(m_file);
  }
  else
  {
    printf("Cannot open the config file \n");
    createOptionsFile();
    defaultOptions();
  }
}

/// <summary>
/// Creates a options file with default values.
/// <summary>
void createOptionsFile()
{
  FILE * m_file = NULL;

  m_file = fopen(CONFIG_NAME, "ab+");
  if(m_file != NULL)
  {
    printf("Creating a new config file. \n");
    fwrite("[SERVER PORT]:65463 \n", 1, 21, m_file);
    fwrite("[ACCEPT TIMEOUT]:200 \n", 1, 22, m_file);
    fwrite("[SEND TIMEOUT]:5 \n", 1, 18, m_file);
    fwrite("[RECEIVE TIMEOUT]:5 \n", 1, 21, m_file);
    fwrite("[LOGS LEVEL]:1 \n", 1, 16, m_file);
    fclose(m_file);
  }
}

/// <summary>
/// When did not read a config file, 
/// server is set by this default options.
/// </summary>
void defaultOptions()
{
  printf("Loading default options. \n");  

  g_serverOptions.u_port = 65463;//default port
  printf("Server port:65464 \n");  

  g_serverOptions.u_acceptTimeout = 200;//200 minutes
  printf("Accept timeout:200 \n");  

  g_serverOptions.u_sendTimeout = 5;//5 seconds
  printf("Send timout:5 \n");  

  g_serverOptions.u_recvTimeout = 5;//5 seconds
  printf("Receive timeout:5 \n");  

  g_serverOptions.u_logsLevel = 1;//5 seconds
  printf("Logs level:1(normal) \n");  

  printf("----------------- \n");
}
