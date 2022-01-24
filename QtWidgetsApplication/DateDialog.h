#pragma once
#include <QDialog>
#include <QDate>
#include <QCalendarWidget>
#include <QDialogButtonBox>


namespace Ui {
	class DateDialog;
}

class DateDialog : public QDialog {
	Q_OBJECT

public:
	DateDialog(QWidget *parent = 0);
	~DateDialog();

	QDate getDate();
	void setCurrentDate(QDate date);

private:
	Ui::DateDialog* ui;
};