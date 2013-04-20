#ifndef DIALOG_H
#define DIALOG_H
#include "hlavni.h"
class dialog:public QDialog
{
	Q_OBJECT
private:
	QLineEdit * editJmeno,*editHeslo;
	QComboBox * druhSite,*druhPrihlaseni;
	QPushButton * prihlasit;
	QFormLayout * layout;
	QString jmeno,heslo;
	QWidget *hlayout1,*hlayout2;
	udaje mojeudaje;
public:
	udaje & vratUdaje ();
	dialog ();
	public slots:
	void nastav ();
};
#endif DIALOG_H