/*
 *  https://gist.github.com/barrysteyn/7308212
 */
#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>

int base64Decode(char* b64message, unsigned char** buffer, size_t* length); //Decodes a base64 encoded string

#endif