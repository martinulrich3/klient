#ifndef HLAVNI
#define HLAVNI
#include <qtwidgets\qlayout.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qmainwindow.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qtextbrowser.h>
#include <QtWidgets\qcombobox.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qformlayout.h>
#include <QtCore\qstring.h>
#include <QtCore\qbytearray.h>
#include <QtNetwork\qtcpsocket.h>
#include <QtNetwork\qhostaddress.h>
#include <QtWidgets\qdialog.h>
#include <QtWidgets\qmessagebox.h>
#include <QtCore\qvector.h>
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
typedef struct
{
	QString jmeno;
	QString heslo;
	int druhPrihlaseni;
	int druhSite;
}udaje ;
typedef struct
	{
	unsigned int flag;
	QByteArray data;
	QString sender;
	QString receiver;
	int options;
}packet;
#endif HLAVNI