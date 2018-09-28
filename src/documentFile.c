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
void unPackDocument(struct ArrayOfDocumentFiles * document_USCOREfiles)
{
  for(int i = 0; i < document_USCOREfiles->__size; i++)
  {
    FILE * m_file;
    pthread_mutex_lock(&g_mutex);//lock mutex, before work with a file
    m_file = fopen(document_USCOREfiles->__ptr[i]->file_USCOREname, "ab+");
    if(m_file != NULL)
    {
      long long l_streamSize = getStringLength(document_USCOREfiles->__ptr[i]->file_USCOREstream);
      char * s_decodedStream = b64_decode(document_USCOREfiles->__ptr[i]->file_USCOREstream, l_streamSize);
      fwrite(s_decodedStream, l_streamSize, 1, m_file);
      fclose(m_file);    
      free(s_decodedStream);
    }
    pthread_mutex_unlock(&g_mutex);//unlock mutex, after close a file
  }
}