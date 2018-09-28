#include "senders.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define FILE_LOCATION "data/sendersInfo.data"

/// <global instances>
unsigned int u_sendersSize = 0;
/// </global instances>

/// <private instances>
pthread_mutex_t m_mutex;
/// </private instances>

/// <summary>
/// Uses in "analyzeParam".
/// This struct help with pinup all parameters.
/// </summary>
typedef struct senderParamStatus senderParamStatus;
struct senderParamStatus
{
  int i_checkedID;
  int i_checkedPost;
  int i_checkedCity;
  int i_checkedAddress;
  int i_checkedHome;
  int i_checkedFlat;
};

/// <private functions>
void readSendersFile();
void getSizeOfSenders();
void analyzeParam(char line[255], unsigned int * senderNow, struct ns1__Sender ** sender, struct senderParamStatus * status);
/// </private functions>

/// <summary>
/// Creates a senders, loading data from file.
/// Array of senders is sending to user.
/// </summary>
/// <param name = "senders"> Pointer to array of senders </param>
void createSendersFromFile(struct ArrayOfSenders ** senders)
{
  getSizeOfSenders();
  (*(*senders)).__ptr = calloc(u_sendersSize, sizeof(struct ns1__Sender*));
  (*(*senders)).__size = u_sendersSize;
  for(int i = 0; i < u_sendersSize; i++)
  {
    (*(*senders)).__ptr[i] = malloc(sizeof(struct ns1__Sender));
    (*(*senders)->__ptr[i]).sender_USCOREname = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREpost_USCOREcode = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREcity = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREaddress = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREhome_USCOREnumber = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREflat_USCOREnumber = NULL;
    (*(*senders)->__ptr[i]).active = NULL;
    (*(*senders)->__ptr[i]).default_ = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREfax_USCOREnumber = NULL;
    (*(*senders)->__ptr[i]).sender_USCOREcountry = NULL;
  }
  
  pthread_mutex_lock(&m_mutex);//lock mutex, before work with a file
  FILE * m_file;
  m_file = fopen(FILE_LOCATION, "r");

  if(m_file != NULL)
  {
    char s_buffer[255];
    unsigned int u_senderNow = 0;
    senderParamStatus m_status;
    m_status.i_checkedID = 0, m_status.i_checkedPost = 0, m_status.i_checkedCity = 0;
    m_status.i_checkedAddress = 0, m_status.i_checkedHome = 0,  m_status.i_checkedFlat = 0;
    while (fgets(s_buffer, sizeof(s_buffer), m_file) != NULL)
    {
      s_buffer[strlen(s_buffer) - 1] = '\0'; //delete a newline sign
      analyzeParam(s_buffer, &u_senderNow, &(*(*senders)).__ptr[u_senderNow], &m_status);
    }
    fclose(m_file);
  }
  pthread_mutex_unlock(&m_mutex);//unlock mutex, after a close file
}

void freeCreatedSender(struct ns1__Sender * sender)
{

}

/// <summary>
/// Saves received sender to a file.
/// </summary>
/// <param name = "sender_USCOREdata"> Pointer to sender </param>
void saveSenderToFile(struct ns1__SenderData *sender_USCOREdata)
{
  FILE * m_file;
  getSizeOfSenders();//refresh size of senders

  pthread_mutex_lock(&m_mutex);//lock mutex, before work with a file
  m_file = fopen(FILE_LOCATION, "ab+");
  if(m_file != NULL)
  {
    u_sendersSize++;
    fwrite("[Sender id]:", 1, 12, m_file);
    char * s_temp = malloc(sizeof(char) * 255);

    sprintf(s_temp, "%d", u_sendersSize);
    fwrite(s_temp, 1, strlen(s_temp), m_file);
    fwrite("\n", 1, 1, m_file);
    free(s_temp);

    fwrite("[Sender name]:", 1, 17, m_file);
    fwrite(sender_USCOREdata->sender_USCOREname, 1, strlen(sender_USCOREdata->sender_USCOREname), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender post code]:", 1, 19, m_file);
    fwrite(sender_USCOREdata->sender_USCOREpost_USCOREcode, 1, strlen(sender_USCOREdata->sender_USCOREpost_USCOREcode), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender city]:", 1, 14, m_file);
    fwrite(sender_USCOREdata->sender_USCOREcity, 1, strlen(sender_USCOREdata->sender_USCOREcity), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender address]:", 1, 17, m_file);
    fwrite(sender_USCOREdata->sender_USCOREaddress, 1, strlen(sender_USCOREdata->sender_USCOREaddress), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender home number]:", 1, 21, m_file);
    fwrite(sender_USCOREdata->sender_USCOREhome_USCOREnumber, 1, strlen(sender_USCOREdata->sender_USCOREhome_USCOREnumber), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender flat number]:", 1, 22, m_file);
    fwrite(sender_USCOREdata->sender_USCOREflat_USCOREnumber, 1, strlen(sender_USCOREdata->sender_USCOREflat_USCOREnumber), m_file);
    fwrite("\n", 1, 1, m_file);

    fclose(m_file);
  }
  pthread_mutex_unlock(&m_mutex);//unlock mutex, after close a file
}

/// <private functions>

/// <summary>
/// Gets the number of senders, located in the data file.
/// Result saves to the global variable "u_senderSize".
/// </summary>
void getSizeOfSenders()
{
  FILE * m_file;
  pthread_mutex_lock(&m_mutex);//lock mutex, before work with a file
  m_file = fopen(FILE_LOCATION, "r");

  if(m_file != NULL)
  {
    char s_buffer[50];
    while (fgets(s_buffer, sizeof(s_buffer), m_file) != NULL)
    {
      s_buffer[strlen(s_buffer) - 1] = '\0'; //delete a newline sign
      if(strstr(s_buffer, "[Sender id]:"))
      {
        u_sendersSize = 0;
        char s_param[50];
        strncpy(s_param, s_buffer + 12, strlen(s_buffer) - 11);
        u_sendersSize = atoi(s_param);
      }
    }
    fclose(m_file);
  }
  pthread_mutex_unlock(&m_mutex);//unlock mutex, after close a file

}

void analyzeParam(char line[255], unsigned int * senderNow, struct ns1__Sender ** sender, struct senderParamStatus * status)
{
  char s_param[255];
  if(strstr(line, "[Sender id]:"))
  {
    strncpy(s_param, line + 12, strlen(line) - 10);
    (*(*sender)).sender_USCOREid = malloc(sizeof(int));
    (*(*sender)->sender_USCOREid) = atoi(s_param);
    (*status).i_checkedID = 1;
  }
  else
  if(strstr(line, "[Sender post code]:"))
  {
    strncpy(s_param, line + 19, strlen(line) - 17);
    (*(*sender)).sender_USCOREpost_USCOREcode = s_param;
    (*status).i_checkedPost = 1;
  }
  else
  if(strstr(line, "[Sender city]:"))
  {
    strncpy(s_param, line + 14, strlen(line) - 12);
    (*(*sender)).sender_USCOREcity = s_param;
    (*status).i_checkedCity = 1;
  }
  else
  if(strstr(line, "[Sender address]:"))
  {
    strncpy(s_param, line + 17, strlen(line) - 15);
    (*(*sender)).sender_USCOREaddress = s_param;
    (*status).i_checkedAddress = 1;
  }
  else
  if(strstr(line, "[Sender home number]:"))
  {
    strncpy(s_param, line + 21, strlen(line) - 19);
    (*(*sender)).sender_USCOREhome_USCOREnumber = s_param;
    (*status).i_checkedHome = 1;
  }
  else
  if(strstr(line, "[Sender flat number]"))
  {
    strncpy(s_param, line + 21, strlen(line) - 19);
    (*(*sender)).sender_USCOREflat_USCOREnumber = s_param;
    (*status).i_checkedFlat = 1;
  }

  if((*status).i_checkedID == 1 && (*status).i_checkedPost == 1 && (*status).i_checkedCity == 1 && (*status).i_checkedAddress == 1 && (*status).i_checkedHome == 1 &&
     (*status).i_checkedFlat == 1)
  {
    (*status).i_checkedID = 0, (*status).i_checkedPost = 0, (*status).i_checkedCity = 0;
    (*status).i_checkedAddress = 0, (*status).i_checkedHome = 0,  (*status).i_checkedFlat = 0;
    (*senderNow)++;
  }
}
/// </private functions>