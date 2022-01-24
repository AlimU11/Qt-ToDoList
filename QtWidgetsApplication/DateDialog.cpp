#include "DateDialog.h"
#include "ui_DateDialog.h"

DateDialog::DateDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DateDialog) {
	ui->setupUi(this);
}

DateDialog::~DateDialog() {
	delete ui;
}

QDate DateDialog::getDate() {
	return ui->calendarWidget->selectedDate();
}

void DateDialog::setCurrentDate(QDate date) {
	ui->calendarWidget->setSelectedDate(date);
}
