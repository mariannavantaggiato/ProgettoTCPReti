#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
//serve per le funzioni di socket(),bind(),connect()
#include <arpa/inet.h>
//serve per sockaddrin()
#include <unistd.h>
//serve per la chiusura
#endif

#include <stdio.h>

/*
 * pf -> protocol family, fa parte della famiglia dei protocolli di internet
 * type -> tipo del socket
 *
 */
int main()
{
    #if defined WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
    //MAKEWORD(2,2) SPECIFICA IL NUMERO DELLA VERSIONE DI WINSOCK
    if(iResult != 0)
    {
        printf("Errore con WSAStartup()\n");
        return 0;
    }
    #endif
    int mysocket;

    /*
     * CODICE SERVER
     */




    closesocket(mysocket);
    #if defined WIN32
        WSACleanup();
    #endif


    return 0;
}
