//Decodes Base64
#include "base64Decode.h"
#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <stdint.h>
#include <assert.h>

char *b64_decode(unsigned char *input, int length)
{
  char *res = malloc(length + 1); 
  BIO *bmem = BIO_new_mem_buf(input, length);
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  bmem = BIO_push(b64, bmem);

  long long n = BIO_read(bmem, res, length);
  if (n > 0)
    res[n] = 0;
  else
   res[0] = 0; // note: this is an error state.

  BIO_free_all(bmem);

  return res;
}