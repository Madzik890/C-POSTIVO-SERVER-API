#include "shipments.h"
#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"


/// <private functions>
void saveShipmentToFile(struct ns1__Shipment * shipment);
/// </private functions>

/// <summary>
/// Converts recipient object to shipment struct.
/// </summary>
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

    saveShipmentToFile((*shipments)->__ptr[i]);
  }
}

/// <summary>
/// </summary>
void convertRecipientToShipmentPrice(struct ArrayOfRecipients *recipients, struct ArrayOfShipmentsPrice **shipments)
{
  for(int i = 0; i < recipients->__size; i++)
  {
    (*shipments)->__ptr[i] = calloc(1, sizeof(struct ns1__ShipmentPrice));

    (*(*shipments)->__ptr[i]).recipient_USCOREname = recipients->__ptr[i]->recipient_USCOREname;
    (*shipments)->__ptr[i]->recipient_USCOREaddress = recipients->__ptr[i]->recipient_USCOREaddress;
    (*shipments)->__ptr[i]->recipient_USCOREhome_USCOREnumber = recipients->__ptr[i]->recipient_USCOREhome_USCOREnumber;
    (*shipments)->__ptr[i]->recipient_USCOREflat_USCOREnumber = recipients->__ptr[i]->recipient_USCOREflat_USCOREnumber;
    (*shipments)->__ptr[i]->recipient_USCOREpost_USCOREcode = recipients->__ptr[i]->recipient_USCOREpost_USCOREcode;
    (*shipments)->__ptr[i]->recipient_USCOREcity = recipients->__ptr[i]->recipient_USCOREcity;
    (*shipments)->__ptr[i]->dispatch_USCOREcarrier = "Poczta polska";
    (*shipments)->__ptr[i]->dispatch_USCOREtype = "Priority";

    (*shipments)->__ptr[i]->page_USCOREnumber = malloc(sizeof(int));
    (*(*shipments)->__ptr[i]->page_USCOREnumber) = 2;
    (*shipments)->__ptr[i]->price = malloc(sizeof(float));
    (*(*shipments)->__ptr[i]->price) = 1.64f;
  }
}

/// <private functions>
/// <summary>
/// Saves shipment object to file.
/// </summary>
/// <param name = "shipment"> Pointer to shipment object </param>
void saveShipmentToFile(struct ns1__Shipment * shipment)
{
  FILE * m_file;
  char * s_fileDir;
  //strcpy(s_fileDir, "dispatches/");       // copies "one" into str_output
  strcat(s_fileDir, shipment->recipient_USCOREname);
  pthread_mutex_lock(&g_mutex);//lock mutex, before work with a file
  m_file = fopen(s_fileDir, "ab+");
  if(m_file != NULL)
  {
    fwrite("[RECIPIENT NAME]:", 1, 17, m_file);
    fwrite(shipment->recipient_USCOREname, 1, strlen(shipment->recipient_USCOREname), m_file);
    fwrite("\n", 1, 1, m_file);
    
    fwrite("[RECIPIENT POST CODE]:", 1, 22, m_file);
    fwrite(shipment->recipient_USCOREpost_USCOREcode, 1, strlen(shipment->recipient_USCOREpost_USCOREcode), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[RECIPIENT CITY]:", 1, 18, m_file);
    fwrite(shipment->recipient_USCOREcity, 1, strlen(shipment->recipient_USCOREcity), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[RECIPIENT ADDRESS]:", 1, 20, m_file);
    fwrite(shipment->recipient_USCOREaddress, 1, strlen(shipment->recipient_USCOREaddress), m_file);
    fwrite("\n", 1, 1, m_file);
    
    fwrite("[RECIPIENT HOME NUMBER]:", 1, 24, m_file);
    fwrite(shipment->recipient_USCOREhome_USCOREnumber, 1, strlen(shipment->recipient_USCOREhome_USCOREnumber), m_file);
    fwrite("\n", 1, 1, m_file);

    fwrite("[RECIPIENT FLAT NUMBER]:", 1, 24, m_file);
    fwrite(shipment->recipient_USCOREflat_USCOREnumber, 1, strlen(shipment->recipient_USCOREflat_USCOREnumber), m_file);
    fwrite("\n", 1, 1, m_file);

    fclose(m_file);
  }
  pthread_mutex_unlock(&g_mutex);//unlock mutex, after work with a file
}
/// </private functions>