#include "hlavni.h"
#include "gui.h"
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	gui * mojegui=new gui ();	
	return app.exec();
}