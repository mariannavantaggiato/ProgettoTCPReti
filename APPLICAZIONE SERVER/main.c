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

struct sockaddr_in IndirizzoServer;
struct sockaddr_in IndirizzoClient;

/*
struct sockaddr_in {
    short sin_family;
    u_short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};
*/
void stampaMSGerror(char *error)
{
    printf("%s\n",error);
}


#include <stdio.h>
void PulisciWinSock(){
    #if defined WIN32
        WSACleanup();
    #endif
}

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
    //int socket(int pf,int type,int protocol);
    /*
    * pf -> protocol family, fa parte della famiglia dei protocolli di internet
    * type -> tipo del socket
    * protocol -> protocollo adatto per il tipo di socket
    */
    //CREAZIONE SOCKET SERVER
    int socketServer = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socketServer==-1)
    {
        printf("ERRORE CREAZIONE SOCKET!\n");
        PulisciWinSock();
    }
    IndirizzoServer.sin_family = AF_INET;
    IndirizzoServer.sin_addr = ("127.0.0.1"); //localhost ip server
    IndirizzoServer.sin_port = htons(4999); //indirizzo porta

    if(bind(socketServer,(struct sockaddr*) &IndirizzoServer,sizeof (IndirizzoServer))<0)
    {
        stampaMSGerror("Errore bind()\n");
        closesocket(socketServer);
        return -1;
    }
    int maxRequ=6;
    if(listen(socketServer,maxRequ)<0)
    {
        stampaMSGerror("Errore listen()\n");
        closesocket(socketServer);
        return -1;
    }
    //SOCKET SERVER E' LA SOCKET DI BENVENUTO
    //ORA DOBBIAMO CREARE LE "SOTTO SOCKET"
    int socketClient;
    int clientLen;
    printf("\n\nIn attessa di connessione...");
    while(1) //lasciale il server in ascolto, quando la connessione con il client sarà finita
    {
        clientLen = sizeof(IndirizzoClient);
        if((socketClient= accept(socketServer,(struct sockaddr *) &IndirizzoClient,&clientLen))<0)
        {
            stampaMSGerror("Errore di connessione col client\n");
            closesocket(socketServer);
            PulisciWinSock();
            return -1;
        }
        printf("Connessione avvennuta CLIENT: %s\n", inet_ntoa(IndirizzoClient.sin_addr));
    }
    closesocket(socketServer);
    PulisciWinSock();


    return 0;
}
