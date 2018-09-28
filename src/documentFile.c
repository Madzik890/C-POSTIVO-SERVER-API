#include "documentFile.h"
#include "base64/base64Decode.h"
#include <stdio.h>//files
#include "mutex.h"


/// <summary>
/// Gets the length of string.
/// Sizeof and strlen functions, return bad value.
/// </summary>
/// <return> Size of string </param>
long long getStringLength(char *s)
{
  int i_step = 0;
  long long l_length = 0;

  while (s[i_step] != '\0')
    l_length++, i_step++;

  return l_length;
 }

/// <summary>
/// Unpacks and decrypts, file coded in base64.
/// </summary>
/// <param name = "document"> Pointer to an array of documents </param>
void unPackDocument(char * s_folderDir, struct ArrayOfDocumentFiles * document_USCOREfiles)
{
  for(int i = 0; i < document_USCOREfiles->__size; i++)
  {
    FILE * m_file;
    char * s_fileDir = malloc(sizeof(char) * 255);
    pthread_mutex_lock(&g_mutex);//lock mutex, before work with a file
    strcpy(s_fileDir, s_folderDir);
    strcat(s_fileDir, document_USCOREfiles->__ptr[i]->file_USCOREname);
    m_file = fopen(s_fileDir, "ab+");
    if(m_file != NULL)
    {
      long long l_streamSize = getStringLength(document_USCOREfiles->__ptr[i]->file_USCOREstream);
      char * s_decodedStream = b64_decode(document_USCOREfiles->__ptr[i]->file_USCOREstream, l_streamSize);
      fwrite(s_decodedStream, l_streamSize, 1, m_file);
      fclose(m_file);    
      free(s_decodedStream);
    }
    free(s_fileDir);
    pthread_mutex_unlock(&g_mutex);//unlock mutex, after close a file
  }
}