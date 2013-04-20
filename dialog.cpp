#include "dialogprihlaseni.h"

dialog::dialog ()
{
	editJmeno=new QLineEdit ();
	editHeslo=new QLineEdit ();
	druhSite=new QComboBox ();
	druhPrihlaseni=new QComboBox ();
	druhSite=new QComboBox ();
	prihlasit=new QPushButton ("prihlasit");
	layout=new QFormLayout ();
	druhPrihlaseni->addItem ("prihlasit",QVariant (1));
	druhPrihlaseni->addItem ("registrace",QVariant (2));
	druhSite->addItem ("moje sit",QVariant (1));
	druhSite->addItem ("facebook",QVariant (2));
layout->addRow (tr("prihlasovaci jmeno"),editJmeno);
layout->addRow (tr("heslo"),editHeslo);
layout->addRow (tr("druh site"),druhSite);
layout->addRow (tr("prihlasit nebo registrovat"),druhPrihlaseni);
layout->addRow (prihlasit);
setLayout (layout);
connect (prihlasit,SIGNAL (clicked ()),this,SLOT (nastav ()));
}
void dialog::nastav ()
{
	jmeno=editJmeno->text ();
	heslo=editHeslo->text ();
	mojeudaje.jmeno=jmeno;
	mojeudaje.heslo=heslo;
	mojeudaje.druhPrihlaseni=druhPrihlaseni->currentIndex ();
	mojeudaje.druhSite=druhSite->currentIndex ();
	done (0);
}
udaje &dialog::vratUdaje ()
{
	return mojeudaje;
};