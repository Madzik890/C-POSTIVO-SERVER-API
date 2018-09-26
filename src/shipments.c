#include "shipments.h"

void convertRecipientToShipment(struct ArrayOfRecipients *recipients, struct ArrayOfShipments **shipments)
{
  for(int i = 0; i < recipients->__size; i++)
  {
    (*shipments)->__ptr[i] = calloc(1, sizeof(struct ns1__Shipment));
    (*(*shipments)->__ptr[i]).id = "1";
    (*(*shipments)->__ptr[i]).recipient_USCOREname = recipients->__ptr[i]->recipient_USCOREname;
    (*shipments)->__ptr[i]->recipient_USCOREaddress = recipients->__ptr[i]->recipient_USCOREaddress;
    (*shipments)->__ptr[i]->recipient_USCOREhome_USCOREnumber = recipients->__ptr[i]->recipient_USCOREhome_USCOREnumber;
    (*shipments)->__ptr[i]->recipient_USCOREflat_USCOREnumber = recipients->__ptr[i]->recipient_USCOREflat_USCOREnumber;
    (*shipments)->__ptr[i]->recipient_USCOREpost_USCOREcode = recipients->__ptr[i]->recipient_USCOREpost_USCOREcode;
    (*shipments)->__ptr[i]->recipient_USCOREcity = recipients->__ptr[i]->recipient_USCOREcity;
    (*shipments)->__ptr[i]->dispatch_USCOREcarrier = "Poczta polska";
    (*shipments)->__ptr[i]->dispatch_USCOREtype = "Priority";
    (*shipments)->__ptr[i]->status = "In implementation";

    (*shipments)->__ptr[i]->page_USCOREnumber = malloc(sizeof(int));
    (*(*shipments)->__ptr[i]->page_USCOREnumber) = 2;
    (*shipments)->__ptr[i]->price = malloc(sizeof(float));
    (*(*shipments)->__ptr[i]->price) = 2.56f;
  }
}