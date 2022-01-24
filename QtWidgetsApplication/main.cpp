#include "QtWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <chrono>
#include <thread>
#include <crtdbg.h>
#include <iostream>
#include <vld.h>

int method(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QtWidgetsApplication w;
	w.setWindowTitle("ToDo List");
	w.show();

	return a.exec();
}

int main(int argc, char *argv[]) {
	method(argc, argv);

	return 0;
}
