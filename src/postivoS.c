#include "server.h"
#include "serverLogs.h"
#include "serverOptions.h"
#include <pthread.h>
#include "mutex.h"

int main()
{
  //createLogs();
  pthread_mutex_init(&g_mutex, NULL);
  loadServerOptions();
  g_logsLevel = (logsLevel)g_serverOptions.u_logsLevel;

  initServer();

  if (soap_valid_socket(g_soapSocket))
  {
    while (soap_valid_socket(soap_accept(g_soap)))//when accept a new user
    {
      pthread_t th_connection;//thread 
      if(pthread_create(&th_connection, NULL, (void*)requestClient, g_soap))//create a thread for new user
      {
        printf("Error creating thread\n");//error while making thread
        return 1;
      }

      if(pthread_join(th_connection, NULL))
      {
        printf("Error joining thread\n");
        return 2;
      }
    }
  }
  else
    soap_print_fault(g_soap, stderr);//print error

  closeServer();
  //closeLogs();
  pthread_mutex_destroy(&g_mutex);
  return 0;
}
