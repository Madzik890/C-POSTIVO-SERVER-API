#include "server.h"
#include "serverLogs.h"
#include "serverOptions.h"
#include <pthread.h>
#include "mutex.h"

int main()
{
  pthread_mutex_init(&g_mutex, NULL);
  loadServerOptions();
  g_logsLevel = (logsLevel)g_serverOptions.u_logsLevel;
  createLogs();

  initServer();

  if (soap_valid_socket(g_soapSocket))
  {
    while (soap_valid_socket(soap_accept(g_soap)))//when accept a new user
    {
      struct soap * m_soap = soap_copy(g_soap);
      pthread_t th_connection;
      if(pthread_create(&th_connection, NULL, (void*)requestClient, m_soap))//create a thread for new user
      {
        writeLogLine(error, "Error while creating thread");
        return 1;
      }

      if(pthread_join(th_connection, NULL))
      {
        writeLogLine(error, "Error while joining thread");
        return 2;
      }
    }
  }
  else
    soap_print_fault(g_soap, stderr);//print error

  closeServer();
  closeLogs();
  pthread_mutex_destroy(&g_mutex);
  return 0;
}
