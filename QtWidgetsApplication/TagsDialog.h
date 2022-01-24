#pragma once
#include <QDialog>
#include <QDate>
#include <QCalendarWidget>
#include <QDialogButtonBox>


namespace Ui {
	class TagsDialog;
}

class TagsDialog : public QDialog {
	Q_OBJECT

public:
	TagsDialog(QWidget *parent = 0);
	~TagsDialog();

	QStringList getTags();
	QStringList getSelectedTags();
	void setTags(QStringList tags);
	void setCurrentTags(QStringList tags);

private slots:
	void on_addNewTagButton_clicked();

private:
	Ui::TagsDialog* ui;
};