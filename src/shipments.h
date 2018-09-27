#ifndef SHIPMENTS_H
#define SHIPMENTS_H

#include "soap/soapH.h"

void convertRecipientToShipment(struct ArrayOfRecipients *recipients, struct ArrayOfShipments **shipments);
void convertRecipientToShipmentPrice(struct ArrayOfRecipients *recipients, struct ArrayOfShipmentsPrice **shipments);

#endif