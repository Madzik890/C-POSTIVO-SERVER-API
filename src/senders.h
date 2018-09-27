#ifndef SENDERS_H
#define SENDERS_H

#include "soap/soapH.h"

extern unsigned int u_sendersSize;

void createSendersFromFile(struct ns1__Sender ** senders);
void saveSenderToFile(struct ns1__SenderData *sender_USCOREdata);

#endif