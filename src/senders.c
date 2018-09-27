#include "senders.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LOCATION "data/sendersInfo.data"

/// <global instances>
unsigned int u_sendersSize = 0;
/// </global instances>

/// <private functions>
void readSendersFile();
void getSizeOfSenders();
/// </private functions>

/// <summary>
/// Creates a senders, loading data from file.
/// Array of senders is sending to user.
/// </summary>
/// <param name = "senders"> Pointer to array of senders </param>
void createSendersFromFile(struct ns1__Sender ** senders)
{
  (*senders) = malloc(u_sendersSize * sizeof(struct ns1__Sender*));
}

/// <summary>
/// Saves received sender to a file.
/// </summary>
/// <param name = "sender_USCOREdata"> Pointer to sender </param>
void saveSenderToFile(struct ns1__SenderData *sender_USCOREdata)
{
  FILE * m_file;
  getSizeOfSenders();

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

    fwrite("[Sender address]:", 1, 17, m_file);
    fwrite(sender_USCOREdata->sender_USCOREname, 1, strlen(sender_USCOREdata->sender_USCOREname), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender post code]:", 1, 19, m_file);
    fwrite(sender_USCOREdata->sender_USCOREpost_USCOREcode, 1, strlen(sender_USCOREdata->sender_USCOREpost_USCOREcode), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender city]:", 1, 14, m_file);
    fwrite(sender_USCOREdata->sender_USCOREcity, 1, strlen(sender_USCOREdata->sender_USCOREcity), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender address prefix]:", 1, 24, m_file);
    fwrite(sender_USCOREdata->sender_USCOREaddress_USCOREprefix, 1, strlen(sender_USCOREdata->sender_USCOREaddress_USCOREprefix), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender address]:", 1, 17, m_file);
    fwrite(sender_USCOREdata->sender_USCOREname, 1, strlen(sender_USCOREdata->sender_USCOREname), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender home number]:", 1, 21, m_file);
    fwrite(sender_USCOREdata->sender_USCOREhome_USCOREnumber, 1, strlen(sender_USCOREdata->sender_USCOREhome_USCOREnumber), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[Sender flat number]:", 1, 22, m_file);
    fwrite(sender_USCOREdata->sender_USCOREflat_USCOREnumber, 1, strlen(sender_USCOREdata->sender_USCOREflat_USCOREnumber), m_file);
    fwrite("\n", 1, 1, m_file);

    fclose(m_file);
  }
}

/// <private functions>

/// <summary>
/// Gets the number of senders, located in the data file.
/// Result saves to the global variable "u_senderSize".
/// </summary>
void getSizeOfSenders()
{
  FILE * m_file;
  m_file = fopen(FILE_LOCATION, "r");

  if(m_file != NULL)
  {
    struct ns1__SenderData m_senderData;
    char s_buffer[50];
    while (fgets(s_buffer, sizeof(s_buffer), m_file) != NULL)
    {
      s_buffer[strlen(s_buffer) - 1] = '\0'; //delete a newline sign
      if(strstr(s_buffer, "[Sender id]:"))
      {
        char s_param[50];
        strncpy(s_param, s_buffer + 12, strlen(s_buffer) - 12);
        u_sendersSize = atoi(s_param);
      }
    }
    fclose(m_file);
  }

}
/// </private functions>