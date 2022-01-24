#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QInputDialog>

namespace Ui {
	class FolderDialog;
}

class FolderDialog : public QDialog {
	Q_OBJECT

private slots:
	void on_addFolderButton_clicked();

public:
	FolderDialog(QWidget *parent = 0);
	~FolderDialog();

	QStringList getFolders();
	QString getFolder();
	void setFolders(QStringList folders);
	void setSelectedFolder(QString folder);

private:
	Ui::FolderDialog * ui;
};