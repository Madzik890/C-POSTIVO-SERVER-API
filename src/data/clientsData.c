#include "clientsData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define DATABASE_DIR "data/clientsInfo.data"

/// <private instances>
struct client m_loadedClient;
pthread_mutex_t m_mutex;
/// </private instances>

/// <private functions>
void loadClient(char line[50]);
short compareClient(client * logging);
/// <private functions>


void freeClient(client * client)
{
  if(client->s_login != NULL)
    free(client->s_login);

  if(client->s_password != NULL)
    free(client->s_password);
}

/// <summary>
/// Loads file with all users data.
/// Checks if given user, is in "database".
/// If user is in the "database", receives permission to doing 
/// operations on this account.
/// </summary>
/// <param name = "client"> A Client information </param>
/// <return> State of logged user </return>
clientStatus checkClient(client * client)
{ 
  m_loadedClient.s_login = NULL;
  m_loadedClient.s_password = NULL;

  FILE * m_file;
  pthread_mutex_lock(&m_mutex);//lock mutex, before work with a file
  m_file = fopen(DATABASE_DIR, "r");
  if(m_file != NULL)
  {
    char s_buffer[50];
    while (fgets(s_buffer, sizeof(s_buffer), m_file) != NULL)
    {
      s_buffer[strlen(s_buffer) - 1] = '\0'; //delete a newline sign

      loadClient(s_buffer);

      if(m_loadedClient.s_login != NULL && m_loadedClient.s_password != NULL && compareClient(client) == 1)
        return successfulFind;
    }
    fclose(m_file);
  }
  pthread_mutex_unlock(&m_mutex);//unlock mutex, after close a file
  return noFind;
}

/// <private functions>
short compareClient(client * logging)
{
  if(strcmp(logging->s_login, m_loadedClient.s_login) == 0 && strcmp(logging->s_password, m_loadedClient.s_password) == 0)
  {
    (*logging) = m_loadedClient;
    if(m_loadedClient.s_login != NULL)
      free(m_loadedClient.s_login);
    if(m_loadedClient.s_password != NULL)
      free(m_loadedClient.s_password);
    return 1;
  }

  return 0;
}

void loadClient(char line[50])
{ 
  char s_param[50];
  if(strstr(line, "[LOGIN]:"))
  {
    strncpy(s_param, line + 8, strlen(line) - 8);

    if(m_loadedClient.s_login != NULL)
      free(m_loadedClient.s_login);
    m_loadedClient.s_login = malloc(strlen(s_param) - 1);
    strcpy(m_loadedClient.s_login, s_param);
  }
  else 
  if(strstr(line, "[PASSWORD]:"))
  {
    strncpy(s_param, line + 11, strlen(line) - 10);
    if(m_loadedClient.s_password != NULL)
      free(m_loadedClient.s_password);
    m_loadedClient.s_password = malloc(strlen(s_param) - 1);
    strcpy(m_loadedClient.s_password, s_param);
  }
  else 
  if(strstr(line, "[BALANCE]:"))
  {
    strncpy(s_param, line + 10, strlen(line) - 10);
    m_loadedClient.f_balance = atof(s_param);
  }
  else 
  if(strstr(line, "[LIMIT]:"))
  {
    strncpy(s_param, line + 8, strlen(line) - 8);
    m_loadedClient.f_limit = atof(s_param);
  }
  else 
  if(strstr(line, "[TYPE]:"))
  {
    strncpy(s_param, line + 7, strlen(line) - 7);
    m_loadedClient.i_type = atoi(s_param);
  }
}
/// <private functions>
