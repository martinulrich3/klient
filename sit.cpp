#include "server.h"
struct network::packet
	{
	unsigned int flag;
	QByteArray data;
	QString sender;
	QString receiver;
	int options;
};
network::network ()
{
}