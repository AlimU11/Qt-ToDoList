#include "TagsDialog.h"
#include "ui_TagsDialog.h"
#include <qdebug.h>	
#include <qmessagebox.h>
#include <QInputDialog>


TagsDialog::TagsDialog(QWidget * parent) : QDialog(parent), ui(new Ui::TagsDialog) {
	ui->setupUi(this);
}

TagsDialog::~TagsDialog() {
	delete ui;
}

QStringList TagsDialog::getTags() {
	QStringList l;
	for (int i = 0; i < ui->tagsList->count(); i++) {
		l.append(ui->tagsList->item(i)->text());
	}

	return l;
}

QStringList TagsDialog::getSelectedTags() {
	QStringList temp;

	for (int i = 0; i < ui->tagsList->count(); i++) {
		if (ui->tagsList->item(i)->checkState() == Qt::Checked) {
			temp.append(ui->tagsList->item(i)->text());
		}
	}
	return temp;
}

void TagsDialog::setTags(QStringList tags) {
	ui->tagsList->addItems(tags);

	for (int i = 0; i < ui->tagsList->count(); i++) {
		ui->tagsList->item(i)->setCheckState(Qt::Unchecked);
	}
}

void TagsDialog::setCurrentTags(QStringList tags) {
	for (int i = 0; i < tags.count(); i++) {
		for (int j = 0; j < ui->tagsList->count(); j++) {
			if (ui->tagsList->item(j)->text() == tags.value(i)) {
				ui->tagsList->item(j)->setCheckState(Qt::Checked);
			}
		}
	}
}

void TagsDialog::on_addNewTagButton_clicked() {
	QString tag = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		tr("New tag:"), QLineEdit::Normal);

	bool isin = false;

	for (int i = 0; i < ui->tagsList->count(); i++) {
		if (ui->tagsList->item(i)->text() == tag) {
			isin = true;
			break;
		}
	}

	if (!tag.isEmpty()) {
		if (!isin) {
			ui->tagsList->addItem(tag);
			ui->tagsList->item(ui->tagsList->count() - 1)->setCheckState(Qt::Checked);
		}
		else {
			QMessageBox mes;
			mes.setWindowTitle("Error");
			mes.setText("Tag already exists or name is invalid");
			mes.exec();
		}
	}
}
