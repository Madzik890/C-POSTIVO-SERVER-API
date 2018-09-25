#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

int Base64Decode(char* b64message, unsigned char** buffer, size_t* length); //Decodes a base64 encoded string
int Base64Encode(const unsigned char* buffer, size_t length, char** b64text); //Encodes a binary safe base 64 string

#endif