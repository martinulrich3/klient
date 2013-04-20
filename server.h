#ifndef SERVER_H
#define SERVER_H
#define LOGIN 0
#define SEND 1
#define SENDALL 2
#define RECV 3
#define KICK 4
#define KICKALL 5
#define CHANGESTAT 6
#define LOGOUT 7
#define REGISTER 8
#define LOGINOK 9
#define LOGINFALSE 10
#define START 11
#define STOP 12
#include "hlavni.h"
class network
{
private:
	QTcpSocket * socket;
	QHostAddress adresa;
	QByteArray * data;
	struct packet;
public:
	network ();
	void start ();
	void stop ();
	
};
#endif SERVER_H