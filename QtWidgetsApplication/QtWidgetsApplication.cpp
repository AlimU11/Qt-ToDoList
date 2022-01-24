#include "QtWidgetsApplication.h"

#include "DateDialog.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QModelIndex>
#include <QFileDialog>


QtWidgetsApplication::QtWidgetsApplication(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
	controller = new Controller();
	createConnections();

	ui.folderList->addItem(QString("All"));
	ui.folderList->item(0)->setTextAlignment(Qt::AlignCenter);
	ui.folderList->setCurrentRow(0);
	chooseFolder();

	priorityComboBox << "No priority" << "Low priority" << "Normal priority" << "High priority";
	priority = NO_PRIORITY;
}

QtWidgetsApplication::~QtWidgetsApplication() {
	delete controller;
}

void QtWidgetsApplication::createConnections() {
	QObject::connect(ui.folderList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseFolder()));
	QObject::connect(ui.tagsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseTag()));
	QObject::connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sortBy()));
	QObject::connect(ui.taskList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(setCompletion(QListWidgetItem*)));
}

void QtWidgetsApplication::refreshTasks() {
	Task ** tasks = controller->getTasks();
	ui.taskList->clear();

	for (int i = 0; i < controller->getTasksCurrentSize(); i++) {
		addTaskToList(tasks[i]);
	}
}

void QtWidgetsApplication::refreshFolders() {
	ui.folderList->clear();
	ui.folderList->addItem(QString("All"));

	ui.folderList->addItems(transformStdStrToQtArr(controller->getCategories(), controller->getCategoriesCurrentSize()));

	for (int i = 0; i < ui.folderList->count(); i++) {
		ui.folderList->item(i)->setTextAlignment(Qt::AlignCenter);
	}

	ui.folderList->setCurrentRow(0);
}

void QtWidgetsApplication::refreshTags(QStringList l) {
	ui.tagsList->clear();
	ui.tagsList->addItems(l);

	for (int i = 0; i < ui.tagsList->count(); i++) {
		ui.tagsList->item(i)->setTextAlignment(Qt::AlignCenter);
		controller->addTag(l.value(i).toStdString());
	}
}

void QtWidgetsApplication::addTaskToList(Task * t) {
	QString s;

	s.append(QString::fromStdString(t->getText()));

	if (!t->getCategory().empty()) s.append(" Folder: " + QString::fromStdString(t->getCategory()));

	s.append(" Priority: " + priorityComboBox.value(t->getPriority()));

	if (t->getTagsCurrentSize() != 0) {
		s.append(" Tags: ");
		for (int j = 0; j < t->getTagsCurrentSize() - 1; j++) {
			s.append(QString::fromStdString(t->getTags()[j]) + ", ");
		}
		s.append(QString::fromStdString(t->getTags()[t->getTagsCurrentSize()-1]));
	}

	if (t->getTimestamp() != 0) s.append(QString(" Due to ") + QDateTime::fromTime_t(t->getTimestamp()).toString("dd.MM.yyyy"));

	ui.taskList->addItem(s);
	if (t->getCompletion()) {
		ui.taskList->item(ui.taskList->count() - 1)->setCheckState(Qt::Checked);
	} else {
		ui.taskList->item(ui.taskList->count() - 1)->setCheckState(Qt::Unchecked);
	}
}

QStringList QtWidgetsApplication::transformStdStrToQtArr(std::string* s, int size) {
	QStringList l;
	for (int i = 0; i < size; i++) l.append(QString::fromStdString(s[i]));
	return l;
}

void QtWidgetsApplication::on_addButton_clicked() {
	if (!ui.textForm->text().isEmpty()) {
		time_t d;

		if (!date.isNull()) d = QDateTime(date).toTime_t();
		else d = 0;

		std::string *l = new std::string[tags.count()];
		for (int i = 0; i < tags.count(); i++) l[i] = tags.value(i).toStdString();

		controller->addTask(ui.textForm->text().toStdString(), l, tags.count(), 0, folder.toStdString(), priority, d);

		refreshTasks();
		date = QDate();
		tags.clear();
		priority = static_cast<PriorityEnum>(0);
		folder = "";
		ui.textForm->clear();
		ui.comboBox->setCurrentIndex(0);
	}
}


void QtWidgetsApplication::on_tagsButton_clicked() {
	TagsDialog dialog;

	dialog.setModal(true);
	dialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	dialog.setTags(transformStdStrToQtArr(controller->getTags(), controller->getTagsCurrentSize()));

	dialog.setCurrentTags(tags);

	if (dialog.exec() == QDialog::Accepted) {
		tags = dialog.getSelectedTags();
	}

	refreshTags(dialog.getTags());
}

void QtWidgetsApplication::on_dateButton_clicked() {
	DateDialog dialog;
	dialog.setModal(true);
	dialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	dialog.setCurrentDate(date);

	if (dialog.exec() == QDialog::Accepted) {
		date = dialog.getDate();
	}
}

void QtWidgetsApplication::on_folderButton_clicked() {
	FolderDialog dialog;
	dialog.setModal(true);
	dialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	dialog.setFolders(transformStdStrToQtArr(controller->getCategories(), controller->getCategoriesCurrentSize()));
	dialog.setSelectedFolder(folder);

	if (dialog.exec() == QDialog::Accepted) {
		folder = dialog.getFolder();
	}

	QStringList l = dialog.getFolders();
	for (int i = 0; i < l.count(); i++) {
		controller->addCategory(l.value(i).toStdString());
	}

	refreshFolders();
}

void QtWidgetsApplication::on_setFolderButton_clicked() {
	int idx = ui.taskList->currentIndex().row();
	if (idx != -1) {
		FolderDialog dialog;
		dialog.setModal(true);
		dialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
		dialog.setFolders(transformStdStrToQtArr(controller->getCategories(), controller->getCategoriesCurrentSize()));
		dialog.setSelectedFolder(QString::fromStdString(controller->getCategory(idx)));

		if (dialog.exec() == QDialog::Accepted) {
			folder = dialog.getFolder();
			controller->setCategory(idx, folder.toStdString());
		}

		QStringList l = dialog.getFolders();
		for (int i = 0; i < l.count(); i++) {
			controller->addCategory(l.value(i).toStdString());
		}

		refreshFolders();
		refreshTasks();
	}
}

void QtWidgetsApplication::on_setPriorityButton_clicked() {
	int idx = ui.taskList->currentIndex().row();
	if (idx != -1) {
		QString str = QInputDialog::getItem(this, tr("QInputDialog::getText()"),
			tr("Choose priority:"), priorityComboBox, controller->getPriority(idx), false);
		controller->setPriority(idx, static_cast<PriorityEnum>(priorityComboBox.indexOf(str)));

		refreshTasks();
	}
}

void QtWidgetsApplication::on_deleteTaskButton_clicked() {
	int idx = ui.taskList->currentIndex().row();
	if (idx != -1) {
		controller->removeTask(idx);
		ui.taskList->takeItem(idx);
	}
}

void QtWidgetsApplication::on_priorityButton_clicked() {
	QString str = QInputDialog::getItem(this, tr("QInputDialog::getText()"),
		tr("Choose priority:"), priorityComboBox, priority, false);

	priority = static_cast<PriorityEnum>(priorityComboBox.indexOf(str));
}

void QtWidgetsApplication::on_setTextButton_clicked() {
	int idx = ui.taskList->currentIndex().row();
	if (idx != -1) {
		
		QString str = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			tr("Change text:"), QLineEdit::Normal);
		if (!str.isEmpty()) {
			controller->setText(idx, str.toStdString());
			refreshTasks();
			if (ui.comboBox->currentText() == "Name") {
				ui.comboBox->setCurrentIndex(0);
			}
		}
	}
}

void QtWidgetsApplication::on_setTagsButton_clicked() {
	int idx = ui.taskList->currentIndex().row();
	if (idx != -1) {
		TagsDialog dialog;

		dialog.setModal(true);
		dialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
		dialog.setTags(transformStdStrToQtArr(controller->getTags(), controller->getTagsCurrentSize()));
		dialog.setCurrentTags(transformStdStrToQtArr(controller->getTagsFromTask(idx), controller->getTagsCurrentSizeFromTask(idx)));
		
		if (dialog.exec() == QDialog::Accepted) {
			tags = dialog.getSelectedTags();

			for (int i = controller->getTagsCurrentSizeFromTask(idx)-1; i >= 0 ; i--) {
				controller->removeTagFromTask(idx, i);
			}

			for (int i = 0; i < tags.count(); i++) {
				controller->addTagToTask(idx, tags.value(i).toStdString());
			}
		}

		refreshTags(dialog.getTags());
		refreshTasks();
	}
}

void QtWidgetsApplication::on_setDateButton_clicked() {
	int idx = ui.taskList->currentIndex().row();
	if (idx != -1) {
		DateDialog dialog;
		dialog.setModal(true);
		dialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
		time_t t = controller->getTimestamp(idx);
		if (t != 0) {
			dialog.setCurrentDate(QDate::fromString(QDateTime::fromTime_t(t).toString("dd.MM.yyyy"), "dd.MM.yyyy"));
		}

		if (dialog.exec() == QDialog::Accepted) {
			date = dialog.getDate();
			controller->setTimestamp(idx, QDateTime(date).toTime_t());

			if (ui.comboBox->currentText() == "Date") {
				ui.comboBox->setCurrentIndex(0);
			}
		}

		refreshTasks();
	}
}

void QtWidgetsApplication::chooseFolder() {
	QString folder = ui.folderList->currentItem()->text();

	ui.label->setText("Folder name: ");
	ui.labelTitle->setText(folder);
	ui.tagsList->clearSelection();

	ui.comboBox->clear();
	QStringList l;
	l << "" << "Name" << "Priority" << "Date" << "Tag";
	ui.comboBox->addItems(l);


	for (int i = 0; i < controller->getTasksCurrentSize(); i++) {
		if (controller->getTasks()[i]->getCategory() != folder.toStdString() && folder != "All") {
			ui.taskList->item(i)->setHidden(true);
		} else {
			ui.taskList->item(i)->setHidden(false);
		}
	}
}

void QtWidgetsApplication::chooseTag() {
	QString tag = ui.tagsList->currentItem()->text();
	ui.label->setText("Tag name: ");
	ui.labelTitle->setText(tag);
	ui.folderList->clearSelection();

	ui.comboBox->clear();
	QStringList l;
	l << "" << "Name" << "Priority" << "Date";
	ui.comboBox->addItems(l);

	for (int i = 0; i < controller->getTasksCurrentSize(); i++) {
		bool isin = false;
		for (int j = 0; j < controller->getTagsCurrentSizeFromTask(i); j++) {
			if (tag.toStdString() == controller->getTagsFromTask(i)[j]) {
				isin = true;
				break;
			}
		}
		if (!isin) {
			ui.taskList->item(i)->setHidden(true);
		} else {
			ui.taskList->item(i)->setHidden(false);
		}
	}
}

void QtWidgetsApplication::sortBy() {
	if (ui.comboBox->currentText() == "Name") {
		controller->sortByName();
	}
	else if (ui.comboBox->currentText() == "Date") {
		controller->sortByDate();
	}
	else if (ui.comboBox->currentText() == "Priority") {
		controller->sortByPriority();
	}
	else if (ui.comboBox->currentText() == "Tag") {
		controller->sortByTag();
	}

	refreshTasks();
}

void QtWidgetsApplication::setCompletion(QListWidgetItem * it) {
	int idx = -1;
	for (int i = 0; i < ui.taskList->count(); i++) {
		if (ui.taskList->item(i) == it) {
			idx = i;
			break;
		}
	}

	if (idx != -1) {
		if (it->checkState() == Qt::Checked) {
			controller->setCompletion(idx, true);
		} else {
			controller->setCompletion(idx, false);
		}
	}
}

void QtWidgetsApplication::on_addFolderButton_clicked() {
	QString folder = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		tr("New folder:"), QLineEdit::Normal);

	bool isin = false;

	for (int i = 0; i < ui.folderList->count(); i++) {
		if (ui.folderList->item(i)->text() == folder) {
			isin = true;
			break;
		}
	}

	if (!folder.isEmpty()) {
		if (folder != "All" && !isin) {
			ui.folderList->addItem(folder);
			ui.folderList->item(ui.folderList->count()-1)->setTextAlignment(Qt::AlignCenter);
			controller->addCategory(folder.toStdString());
			refreshFolders();
		}
		else {
			QMessageBox mes;
			mes.setWindowTitle("Error");
			mes.setText("Folder already exists or name is invalid");
			mes.exec();
		}
	}
}

void QtWidgetsApplication::on_addTagButton_clicked() {
	QString tag = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		tr("New tag:"), QLineEdit::Normal);

	bool isin = false;

	for (int i = 0; i < ui.tagsList->count(); i++) {
		if (ui.tagsList->item(i)->text() == tag) {
			isin = true;
			break;
		}
	}

	if (!tag.isEmpty()) {
		if (!isin) {
			ui.tagsList	->addItem(tag);

			ui.tagsList->item(ui.tagsList->count() - 1)->setTextAlignment(Qt::AlignCenter);
			controller->addTag(tag.toStdString());
		} else {
			QMessageBox mes;
			mes.setWindowTitle("Error");
			mes.setText("Tag already exists or name is invalid");
			mes.exec();
		}
	}
}

void QtWidgetsApplication::on_exportButton_clicked() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
		"home/output.csv", tr("Text (*.csv)"));
	if (!fileName.isEmpty()) {
		controller->toCSV(fileName.toStdString());
	}
}

void QtWidgetsApplication::on_importButton_clicked() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"),
		"home/output.csv", tr("Text (*.csv)"));
	if (!fileName.isEmpty()) {
		controller->fromCSV(fileName.toStdString());
		refreshTasks();
		refreshFolders();
		refreshTags(transformStdStrToQtArr(controller->getTags(), controller->getTagsCurrentSize()));
	}
}

void QtWidgetsApplication::on_deleteFolderButton_clicked() {	
	int idx = ui.folderList->currentIndex().row();
	if (idx > 0) {
		controller->removeCategory(idx-1);
		ui.folderList->takeItem(idx);

		ui.folderList->setCurrentRow(0);
		chooseFolder();
	}
}

void QtWidgetsApplication::on_deleteTagButton_clicked() {
	int idx = ui.tagsList->currentIndex().row();
	if (idx != -1) {
		controller->removeTag(idx);
		ui.tagsList->takeItem(idx);

		ui.tagsList->clearSelection();
		ui.folderList->setCurrentRow(0);
		chooseFolder();
	}
}
