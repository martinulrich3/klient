#ifndef GUI
#define GUI
#include "hlavni.h"
#include "dialogprihlaseni.h"
	class gui :public QMainWindow 
	{
Q_OBJECT
	public:
		gui ();
		void nastavHodnoty (udaje &mojeudaje);
		void PacketFromData (packet & p,QByteArray *data);
	QByteArray DataFromPacket (packet p);
	private:
		udaje prihlasovaciUdaje;
	QPushButton *odeslat;
	QLineEdit * editProText;
	QTextBrowser *textChatu;
	QComboBox * seznamKlientu;
	QHBoxLayout * Hlayout;
	QVBoxLayout * Vlayout;
	QWidget * widgetVlayout,*widgetHlayout;
	dialog *mujdialog;
	packet mujpacket;
	QTcpSocket * socket;
	QHostAddress adresa;
	QByteArray prijimanaData;
	void init ();
	void initLayout ();
	void connectSignal ();
	void login ();
	void getError (int error);
	public slots:
		void send ();
		void initNet ();
		void cti ();
		void pripojeno ();
		void tiskniStav (QAbstractSocket::SocketState);
	};
#endif GUI