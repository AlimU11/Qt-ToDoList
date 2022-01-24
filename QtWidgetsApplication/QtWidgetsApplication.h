#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication.h"	
#include <QDate>
#include "Controller.h"
#include <QInputDialog>
#include "FolderDialog.h"
#include "TagsDialog.h"

class QtWidgetsApplication : public QMainWindow
{
	Q_OBJECT

public:
    QtWidgetsApplication(QWidget *parent = Q_NULLPTR);
	~QtWidgetsApplication();

private slots:
	void on_addButton_clicked();
	void on_tagsButton_clicked();
	void on_dateButton_clicked();
	void on_folderButton_clicked();
	void on_priorityButton_clicked();

	void on_setTextButton_clicked();
	void on_setTagsButton_clicked();
	void on_setDateButton_clicked();
	void on_setFolderButton_clicked();
	void on_setPriorityButton_clicked();

	void on_deleteTaskButton_clicked();
	void on_deleteFolderButton_clicked();
	void on_deleteTagButton_clicked();

	void on_addFolderButton_clicked();
	void on_addTagButton_clicked();
	
	void on_exportButton_clicked();
	void on_importButton_clicked();

	void chooseFolder();
	void chooseTag();
	void sortBy();
	void setCompletion(QListWidgetItem* it);

private:
	QStringList priorityComboBox;

	QString folder;
	QStringList tags;
	QDate date;
	PriorityEnum priority;

	Ui::QtWidgetsApplicationClass ui;
	Controller* controller;

	void createConnections();
	void refreshTasks();
	void refreshFolders();
	void refreshTags(QStringList l);
	void addTaskToList(Task* t);
	QStringList transformStdStrToQtArr(std::string* s, int size);
};
