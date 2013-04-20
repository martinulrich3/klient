
#include "gui.h"
gui::gui ()
{
	init ();
	initLayout ();
}
void gui::init ()
{
	odeslat=new QPushButton ("odeslat");
	editProText=new QLineEdit ();
	textChatu=new QTextBrowser ();
	seznamKlientu=new QComboBox ();
	Hlayout=new QHBoxLayout ();
	Vlayout=new QVBoxLayout ();
	widgetVlayout=new QWidget ();
	widgetHlayout=new QWidget ();
	mujdialog=new dialog ();
	connect (mujdialog,SIGNAL (finished(int)),SLOT (initNet ()));
	connect (odeslat,SIGNAL (clicked ()),SLOT (send ()));
	mujdialog->exec ();
}
void gui::initLayout ()
{
	Hlayout->addWidget (editProText);
	Hlayout->addWidget (seznamKlientu);
	Hlayout->addWidget (odeslat);
	widgetHlayout->setLayout (Hlayout);
	Vlayout->addWidget (textChatu);
	Vlayout->addWidget (widgetHlayout);
	widgetVlayout->setLayout (Vlayout);
	setCentralWidget (widgetVlayout);
	show ();
}
void gui::send ()
{
}
void gui::tiskniStav (QAbstractSocket::SocketState stat)
{
	switch (stat)
	{
	case QAbstractSocket::UnconnectedState:
		qDebug ("The socket is not connected.");
		break;
	case QAbstractSocket::HostLookupState:
		qDebug ("The socket is performing a host name lookup.");
		break;
	case QAbstractSocket::ConnectingState:
		qDebug ("The socket has started establishing a connection.");
		break;
	case QAbstractSocket::ConnectedState:
		qDebug ("A connection is established.");
		break;
	case QAbstractSocket::BoundState:
		qDebug ("The socket is bound to an address and port (for servers).");
		break;
	case QAbstractSocket::ClosingState:
		qDebug ("The socket is about to close (data may still be waiting to be written).");
		break;
	case QAbstractSocket::ListeningState:
		qDebug ("For internal use only.");
		break;
	}
}
void gui::initNet ()
{
	socket=new QTcpSocket ();
	qRegisterMetaType<QAbstractSocket::SocketState>("SocketState");
	connect (socket,SIGNAL (stateChanged(QAbstractSocket::SocketState)),SLOT (tiskniStav (QAbstractSocket::SocketState)));
	connect (socket,SIGNAL (connected ()),SLOT (pripojeno ()));
	connect (socket,SIGNAL (readyRead ()),this,SLOT (cti ()));
	socket->connectToHost (QHostAddress::LocalHost,6000);
}

void gui::getError (int error)
{
	QMessageBox * chybka=new QMessageBox ();
	switch (error)
	{
	case QAbstractSocket::ConnectionRefusedError:
		chybka->setText ("odmitnuti spojeni nebo vyprseni casu");
		break;
	case QAbstractSocket::RemoteHostClosedError:
		chybka->setText ("server ukoncil pripojeni");
	break;
	case QAbstractSocket::HostNotFoundError:
		chybka->setText ("nelze se pripojit na adresu");
		break;
	case QAbstractSocket::SocketAccessError:
		chybka->setText ("operace se socketem selhala protoze nemate opravneni");
		break;
	case QAbstractSocket::SocketResourceError:
		chybka->setText ("prekroceni zdroju systemu (prilis mnoho socketu)");
		break;
	case QAbstractSocket::SocketTimeoutError:
		chybka->setText ("vyprsel cas pro provedeni operace socketu");
		break;
	case QAbstractSocket::DatagramTooLargeError:
		chybka->setText ("datagram je vetsi nez limit systemu");
		break;
	case QAbstractSocket::NetworkError:
		chybka->setText ("problem se siti");
		break;
	case QAbstractSocket::AddressInUseError:
		chybka->setText ("funkce bind adresa uz je pouzita");
		break;
	case QAbstractSocket::SocketAddressNotAvailableError:
		chybka->setText ("The address specified to QAbstractSocket::bind() does not belong to the host.");
		break;
	case QAbstractSocket::UnsupportedSocketOperationError:
		chybka->setText ("nepodporovana operace se sockety na systemu napr.IPv6");
		break;
	case QAbstractSocket::ProxyAuthenticationRequiredError:
		chybka->setText ("socket vyuziva proxy a proxy potrebuje autentifikaci");
		break;
	case QAbstractSocket::SslHandshakeFailedError:
		chybka->setText ("SSL handshake selhal");
		break;
	case QAbstractSocket::OperationError:
		chybka->setText ("chyba pri provadeni operace");
		break;
	case QAbstractSocket::TemporaryError:
		chybka->setText ("A temporary error occurred(e.g., operation would block and socket is non-blocking).");
		break;
	case QAbstractSocket::UnknownSocketError:
		chybka->setText ("neznama chyba se socketem");
		break;
	}
	chybka->exec ();
}
void gui::pripojeno ()
{
	login ();
}
void gui::cti ()
{
	prijimanaData=socket->readAll ();
	getError (socket->error ());
	PacketFromData (mujpacket,&prijimanaData);
	switch (mujpacket.flag)
	{
	case LOGINOK:
		//uspech->exec ();
		break;
	case LOGINFALSE:
		//neuspech->exec ();
		break;
	}
}
void gui::PacketFromData (packet & p,QByteArray * data)
{
	QVector <int> * poziceLomeno=new QVector <int> (10);
	int index=0;
	int pocatek=0;
	int flag=0;
	int options=0;
	QString receiver,sender ;
	QByteArray flagarray ,optionsarray ,receiverarray ,senderarray ,dataarray ;
	do
	{
	if (data->at (index)=='/')
	{
		poziceLomeno->append (index);
		index ++;
		index++;
	}
	else
	{
		index++;
	}
	}
	while (data->at (index)!='\0');
	for (int poziceVector=0;poziceVector<poziceLomeno->size ();poziceVector++)
	{
		int lomeno=poziceLomeno->at (poziceVector);
		switch (poziceVector)
		{
			case 0:
			flagarray.append (data->left (lomeno));
			p.flag=flagarray.toInt ();
			pocatek=lomeno+2;
			break;
			case 1:
			dataarray.append (data->mid (pocatek,lomeno));
			p.data.append (dataarray);
			pocatek=lomeno+2;
				break;
			case 2:
			receiver.append (data->mid (pocatek,lomeno));
			p.receiver.append (receiver);
			pocatek=lomeno+2;
			break;
			case 3:
			sender.append (data->mid (pocatek,lomeno));
			p.sender.append (sender);
			pocatek=lomeno+2;
			break;
			case 4:
				optionsarray.append (data->at (data->size ()-1));
				p.options=optionsarray.toInt ();
				break;
		}
	}
}
QByteArray gui::DataFromPacket (packet p)
{
	QByteArray data=QByteArray ();
	data.append (QByteArray::number (p.flag));
	data.append ("//");
	data.append (p.data);
	data.append ("//");
	data.append (p.receiver.toLatin1 ());
	data.append ("//");
	data.append (p.sender.toLatin1 ());
	data.append ("//");
	data.append (p.options);
	data.append ('\0');
	return data;
}
void gui::login ()
{
	packet prihlasovaciPacket;
	prihlasovaciPacket.flag=LOGIN;
	prihlasovaciUdaje=mujdialog->vratUdaje ();
	QString jmenoAheslo;
	jmenoAheslo.append (prihlasovaciUdaje.jmeno);
	jmenoAheslo.append ("&");
	jmenoAheslo.append (prihlasovaciUdaje.heslo);
	qDebug  (jmenoAheslo.toLatin1 ());
	prihlasovaciPacket.data=jmenoAheslo.toLatin1 ();
	prihlasovaciPacket.sender=prihlasovaciUdaje.jmeno;
	prihlasovaciPacket.receiver="server";
	prihlasovaciPacket.options=0;
	QByteArray testdata=DataFromPacket (prihlasovaciPacket);
	qDebug (testdata);
	socket->write ("abcd",4);
	int poslano=socket->write (DataFromPacket (prihlasovaciPacket));
	int bytestowrite=socket->bytesToWrite ();
	qDebug (QByteArray::number (bytestowrite));
	qDebug (QByteArray::number (poslano));
	getError (socket->error ());
}

