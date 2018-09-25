#include "documentFile.h"
#include "base64/base64.h"
#include <stdio.h>//files

void unPackDocument(struct ns1__DocumentFile * document)
{
  FILE * m_file;
  m_file = fopen(document->file_USCOREname, "ab+");
  if(m_file != NULL)
  {
    char * s_decodedStream;
    //Base64Decode(document->file_USCOREstream, &s_decodedStream, strlen(document->file_USCOREstream));
    //fwrite(s_decodedStream, 1, strlen(s_decodedStream), m_file);
    fclose(m_file);    
    free(s_decodedStream);
  }
}