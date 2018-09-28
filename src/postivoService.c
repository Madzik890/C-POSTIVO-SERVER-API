/*
 *  This section creates a mirror server which is using only to saves operations logs.
 */
#include "soap/Postivo_x002eplBinding.nsmap"
#include "soap/soapH.h"
#include "clientsData.h"
#include "documentFile.h"
#include "shipments.h"
#include "senders.h"

clientStatus checkUserLogging(client * client, char * login, char *api_USCOREpass)
{
  login[strlen(login) - 1] = '\0'; //delete a newline sign
  api_USCOREpass[strlen(api_USCOREpass) - 1] = '\0'; //delete a newline sign

  (*client).s_login = login;
  (*client).s_password = api_USCOREpass;
  return checkClient(client);
}

/// <summary>
/// Creates a dispatch, using a information which sent user.
/// Sends a result to user.
/// Saves logs of whole operation.
/// </summary>
/// <param name = soap> User connection. </param>
/// <param name = login> User login. </param>
/// <param name = api_USCOREpass> User password. </param>
/// <param name = "msg_USCOREtype"> Type of dispatch. </param>
/// <param name = "document_USCOREfiles"> Array of documents, encoded in BASE64. </param>
/// <param name = "recipients"> Array of recipients. </param>
/// <param name = "options"> Additional options. </param>
/// <param name = "_param_1"> The result of connections. </param>
int ns2__dispatch(struct soap* soap, char *login, char *api_USCOREpass, char *msg_USCOREtype, struct ArrayOfDocumentFiles *document_USCOREfiles, struct ArrayOfRecipients *recipients, struct ArrayOfOptions *options, struct ns2__dispatchResponse *_param_1)
{
  struct client m_client;
  if(checkUserLogging(&m_client, login, api_USCOREpass) == successfulFind)
  { 
    (*_param_1).return_ = malloc(sizeof(struct ns1__DispatchReturnObject));//malloc place in memory
    (*_param_1->return_).shipments = malloc(sizeof(struct ArrayOfShipments));
    (*_param_1->return_->shipments).__size = recipients->__size;
    (*_param_1->return_->shipments).__ptr = calloc(recipients->__size, sizeof(struct ns1__Shipment*));

   // char * s_command = malloc(sizeof(255));
    //system("mkdir -p foo/bar/xyz");
    convertRecipientToShipment(recipients, &(*_param_1).return_->shipments);
    unPackDocument(document_USCOREfiles);//unpacks all documents
    
    (*_param_1).return_->result = "OK";
    (*_param_1).return_->result_USCOREcode = "000";
    (*_param_1).return_->result_USCOREdescription = "SUCCESSFUL";
  }
  else
  {
    (*_param_1).return_ = malloc(sizeof(struct ns1__DispatchReturnObject));
    (*_param_1).return_->shipments = NULL;
    (*_param_1).return_->result = "ERR";
    (*_param_1).return_->result_USCOREcode = "001";
    (*_param_1).return_->result_USCOREdescription = "BAD LOGIN OR PASSWORD";
  }

  return SOAP_OK;
}

/// <summary>
/// Gets a results and sends it to the user.
/// Saves logs of whole operation.
/// </summary>
/// <param name = soap> User connection. </param>
/// <param name = login> User login. </param>
/// <param name = api_USCOREpass> User password. </param>
/// <param name = dispatch_USCOREids"> IDs of dispatchs. </param>
/// <param name = "_param_1"> The result of connections. </param>
int ns2__getDispatchStatus(struct soap* soap, char *login, char *api_USCOREpass, struct ArrayOfDispatchIds *dispatch_USCOREids, struct ns2__getDispatchStatusResponse *_param_1)
{
  return SOAP_OK;
}

/// <summary>
/// Gets a balance of the user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = soap> User connection. </param>
/// <param name = login> User login. </param>
/// <param name = api_USCOREpass> User password. </param>
/// <param name = "_param_1"> The result of connections. </param>
int ns2__getBalance(struct soap* soap, char *login, char *api_USCOREpass, struct ns2__getBalanceResponse *_param_1)
{ 
  struct client m_client;
  if(checkUserLogging(&m_client, login, api_USCOREpass) == successfulFind)
  {
    (*_param_1).return_ = malloc(sizeof(struct ns1__BalanceReturnObject));//malloc place in memory

    (*_param_1).return_->balance = malloc(sizeof(float));//malloc place in memory
    (*_param_1->return_->balance) = m_client.f_balance;//sing the user balance

    (*_param_1).return_->limit = malloc(sizeof(float));//malloc place in memory
    (*_param_1->return_->limit) = m_client.f_limit;//sing the user limit

    (*_param_1).return_->postpaid = malloc(sizeof(int));//malloc place in memory
    (*_param_1->return_->postpaid) = m_client.i_type;//sing the user account type

    _param_1->return_->result = "OK";
    _param_1->return_->result_USCOREcode = "000";
    _param_1->return_->result_USCOREdescription = "SUCCESSFUL";
  }
  else
  {
    (*_param_1).return_ = malloc(sizeof(struct ns1__BalanceReturnObject));
    (*_param_1).return_->balance = NULL;//disable to release in "soapServer.c" function
    (*_param_1).return_->limit = NULL;//disable to release in "soapServer.c" function
    (*_param_1).return_->postpaid = NULL;//disable to release in "soapServer.c" function
    (*_param_1).return_->result = "ERR";
    (*_param_1).return_->result_USCOREcode = "001";
    (*_param_1).return_->result_USCOREdescription = "BAD LOGIN OR PASSWORD";
  }
  return SOAP_OK;
}

/// <summary>
/// Gets a price of shipping.
/// Saves logs of whole operation.
/// </summary>
/// <param name = soap> User connection. </param>
/// <param name = login> User login. </param>
/// <param name = api_USCOREpass> User password. </param>
/// <param name = "msg_USCOREtype"> Type of dispatch. </param>
/// <param name = "document_USCOREfiles"> Array of documents, encoded in BASE64. </param>
/// <param name = "recipients"> Array of recipients. </param>
/// <param name = "options"> Additional options. </param>
/// <param name = "_param_1"> The result of connections. </param>
int ns2__getPrice(struct soap* soap, char *login, char *api_USCOREpass, char *msg_USCOREtype, struct ArrayOfDocumentFiles *document_USCOREfiles, struct ArrayOfRecipients *recipients, int config_USCOREid, struct ns2__getPriceResponse *_param_1)
{
  struct client m_client;
  if(checkUserLogging(&m_client, login, api_USCOREpass) == successfulFind)
  { 
    (*_param_1).return_ = malloc(sizeof(struct ns1__PriceReturnObject));//malloc place in memory
    (*_param_1->return_).shipments_USCOREprice = malloc(sizeof(struct ArrayOfShipmentsPrice));
    (*_param_1->return_->shipments_USCOREprice).__size  = recipients->__size;
    (*_param_1->return_->shipments_USCOREprice).__ptr = calloc(recipients->__size, sizeof(struct ns1__ShipmentPrice*));

    convertRecipientToShipmentPrice(recipients, &(*_param_1).return_->shipments_USCOREprice);
    
    (*_param_1).return_->result = "OK";
    (*_param_1).return_->result_USCOREcode = "000";
    (*_param_1).return_->result_USCOREdescription = "SUCCESSFUL";
  }
  else
  {
    (*_param_1).return_ = malloc(sizeof(struct ns1__DispatchReturnObject));
    (*_param_1).return_->shipments_USCOREprice = NULL;
    (*_param_1).return_->result = "ERR";
    (*_param_1).return_->result_USCOREcode = "001";
    (*_param_1).return_->result_USCOREdescription = "BAD LOGIN OR PASSWORD";
  }
  return SOAP_OK;
}

/// <summary>
/// Gets config profiles from user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = soap> User connection. </param>
/// <param name = login> User login. </param>
/// <param name = "api_USCOREpass"> User password. </param>
/// <param name = "msg_USCOREtype"> Type of dispatch. </param>
/// <param name = "_param_1"> Array of config profiles. </param>
int ns2__getConfigProfiles(struct soap* soap, char *login, char *api_USCOREpass, char *msg_USCOREtype, struct ns2__getConfigProfilesResponse *_param_1)
{
  return SOAP_OK;
}

/// <summary>
/// Gets senders from the user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = "soap"> User connection. </param>
/// <param name = "login"> User login. </param>
/// <param name = "api_USCOREpass"> User password. </param>
/// <param name = "_param_1"> Array of sendes. </param>
int ns2__getSenders(struct soap* soap, char *login, char *api_USCOREpass, struct ns2__getSendersResponse *_param_1)
{
  struct client m_client;
  if(checkUserLogging(&m_client, login, api_USCOREpass) == successfulFind)
  { 
    (*_param_1).return_ = malloc(sizeof(struct ns1__SendersReturnObject));
    (*_param_1->return_).senders = malloc(sizeof(struct ArrayOfSenders));
    
    createSendersFromFile(&(*_param_1->return_).senders);
    if((*_param_1->return_->senders).__size != 0)
    {
      (*_param_1).return_->result = "OK";
      (*_param_1).return_->result_USCOREcode = "000";
      (*_param_1).return_->result_USCOREdescription = "SUCCESSFUL";
    }
    else
    {
      (*_param_1).return_->result = "ERR";
      (*_param_1).return_->result_USCOREcode = "030";
      (*_param_1).return_->result_USCOREdescription = "LIST OF SENDERS IS EMPTY";
    }
  }
  else
  {
    (*_param_1).return_ = malloc(sizeof(struct ns1__SendersReturnObject));
    (*_param_1).return_->result = "ERR";
    (*_param_1).return_->result_USCOREcode = "001";
    (*_param_1).return_->result_USCOREdescription = "BAD LOGIN OR PASSWORD";
  }

  return SOAP_OK;
}

/// <summary>
/// Gets certificates of the user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = soap> User connection. </param>
/// <param name = login> User login. </param>
/// <param name = "api_USCOREpass"> User password. </param>
/// <param name = "dispatch_USCOREid"> Dispatch id. </param>
/// <param name = "_param_1"> Result of connection. </param>
int ns2__getCertificate(struct soap* soap, char *login, char *api_USCOREpass, char *dispatch_USCOREid, int certificate_USCOREtype, struct ns2__getCertificateResponse *_param_1)
{
  return SOAP_OK;
}

/// <summary>
/// Adds senderes to user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = "soap"> User connection. </param>
/// <param name = "login"> User login. </param>
/// <param name = "sender_USCOREdata"> Array of senders. </param>
/// <param name = "accept_USCOREterms"> Status of accepting terms. </param>
/// <param name = "_param_1"> Result of connection. </param>
int ns2__addSender(struct soap* soap, char *login, char *api_USCOREpass, struct ns1__SenderData *sender_USCOREdata, enum xsd__boolean accept_USCOREterms, struct ns2__addSenderResponse *_param_1)
{
  struct client m_client;
  if(checkUserLogging(&m_client, login, api_USCOREpass) == successfulFind)
  { 
    (*_param_1).return_ = malloc(sizeof(struct ns1__AddSenderReturnObject));//malloc place in memory

    (*_param_1->return_).sender_USCOREaddress = NULL;
    (*_param_1->return_).sender_USCOREcity = NULL;
    (*_param_1->return_).sender_USCOREcountry = NULL;
    (*_param_1->return_).sender_USCOREfax_USCOREnumber = NULL;
    (*_param_1->return_).sender_USCOREflat_USCOREnumber = NULL;
    (*_param_1->return_).sender_USCOREhome_USCOREnumber = NULL;
    (*_param_1->return_).sender_USCOREid = NULL;
    (*_param_1->return_).sender_USCOREname = NULL;
    (*_param_1->return_).sender_USCOREpost_USCOREcode = NULL;
    (*_param_1->return_).shipment_USCOREid = NULL;

    saveSenderToFile(sender_USCOREdata);

    (*_param_1).return_->result = "OK";
    (*_param_1).return_->result_USCOREcode = "000";
    (*_param_1).return_->result_USCOREdescription = "SUCCESSFUL";
  }
  else
  {
    (*_param_1).return_ = malloc(sizeof(struct ns1__AddSenderReturnObject));
    (*_param_1).return_->result = "ERR";
    (*_param_1).return_->result_USCOREcode = "001";
    (*_param_1).return_->result_USCOREdescription = "BAD LOGIN OR PASSWORD";
  }

  return SOAP_OK;
}

/// <summary>
/// Adds senderes from user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = "soap"> User connection. </param>
/// <param name = "login"> User login. </param>
/// <param name = "sender_USCOREid"> ID of senders. </param>
/// <param name = "verification_USCOREcode"> Code of verification. </param>
/// <param name = "_param_1"> Result of connection. </param>
int ns2__verifySender(struct soap* soap, char *login, char *api_USCOREpass, int sender_USCOREid, char *verification_USCOREcode, struct ns2__verifySenderResponse *_param_1)
{
  return SOAP_OK;
}

/// <summary>
/// Removes a sender from user account.
/// Saves logs of whole operation.
/// </summary>
/// <param name = "soap"> User connection. </param>
/// <param name = "login"> User login. </param>
/// <param name = "sender_USCOREid"> Array of senders. </param>
/// <param name = "_param_1"> Result of connection. </param>
int ns2__removeSender(struct soap* soap, char *login, char *api_USCOREpass, int sender_USCOREid, struct ns2__removeSenderResponse *_param_1)
{
  return SOAP_OK;
}
