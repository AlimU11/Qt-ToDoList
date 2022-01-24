#include "FolderDialog.h"
#include "ui_FolderDialog.h"
#include <qdebug.h>	
#include <qmessagebox.h>

FolderDialog::FolderDialog(QWidget * parent) : QDialog(parent), ui(new Ui::FolderDialog) {
	ui->setupUi(this);
}

FolderDialog::~FolderDialog() {
	delete ui;
}

QStringList FolderDialog::getFolders() {
	QStringList l;
	for (int i = 0; i < ui->folderList->count(); i++) {
		l.append(ui->folderList->item(i)->text());
	}
	return l;
}

QString FolderDialog::getFolder() {
	if (!ui->folderList->selectedItems().isEmpty()) {
		return ui->folderList->selectedItems().first()->text();
	}
	return "";
}

void FolderDialog::setFolders(QStringList folders) {
	ui->folderList->addItems(folders);
}

void FolderDialog::setSelectedFolder(QString folder) {
	int idx = -1;
	for (int i = 0; i < ui->folderList->count(); i++) {
		if (ui->folderList->item(i)->text() == folder) {
			idx = i;
			break;
		}
	}
	if (idx != -1) ui->folderList->setCurrentRow(idx);
}

void FolderDialog::on_addFolderButton_clicked() {
	QString folder = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		tr("New folder:"), QLineEdit::Normal);

	bool isin = false;

	for (int i = 0; i < ui->folderList->count(); i++) {
		if (ui->folderList->item(i)->text() == folder) {
			isin = true;
			break;
		}
	}

	if (!folder.isEmpty()) {
		if (folder != "All" && !isin) {
			ui->folderList->addItem(folder);
			ui->folderList->setCurrentRow(ui->folderList->count() - 1);
		} else {
			QMessageBox mes;
			mes.setWindowTitle("Error");
			mes.setText("Folder already exists or name is invalid");
			mes.exec();
		}
	}
}