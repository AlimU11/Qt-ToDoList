#pragma once

#include "Controller.h"

Controller::Controller() {
	todo = new ToDoList();
}

Controller::~Controller() {
	delete todo;
}

void Controller::addTask(std::string text, std::string * tags, int tag_i, int tag_size, std::string category, int priority, time_t date) {
	todo->addTask(text, tags, tag_i, tag_size, category, priority, date);
}

Task * Controller::removeTask(int i) {
	return todo->removeTask(i);
}

void Controller::setText(int i, std::string text) {
	todo->getTasks()[i]->setText(text);
}

std::string Controller::getText(int i) {
	return todo->getTasks()[i]->getText();
}

void Controller::setCompletion(int i, bool isCompleted) {
	todo->getTasks()[i]->setCompletion(isCompleted);
}

bool Controller::getCompletion(int i) {
    return todo->getTasks()[i]->getCompletion();
}

void Controller::setCategory(int i, std::string category) {
	todo->getTasks()[i]->setCategory(category);
}

std::string Controller::getCategory(int i) {
    return todo->getTasks()[i]->getCategory();
}

void Controller::setPriority(int i, PriorityEnum priority) {
	todo->getTasks()[i]->setPriority(priority);
}

PriorityEnum Controller::getPriority(int i) {
    return todo->getTasks()[i]->getPriority();
}

void Controller::setTimestamp(int i, time_t timestamp) {
	todo->getTasks()[i]->setTimestamp(timestamp);
}

time_t Controller::getTimestamp(int i) {
    return todo->getTasks()[i]->getTimestamp();
}

void Controller::addTagToTask(int i, std::string tag) {
	todo->getTasks()[i]->addTag(tag);
}

void Controller::removeTagFromTask(int i, int idx) {
	return todo->getTasks()[i]->removeTag(idx);
}

std::string* Controller::getTagsFromTask(int i) {
    return todo->getTasks()[i]->getTags();
}

int Controller::getTagsCurrentSizeFromTask(int i) {
    return todo->getTasks()[i]->getTagsCurrentSize();
}

int Controller::getTagsMaxSizeFromTask(int i) {
    return todo->getTasks()[i]->getTagMaxSize();
}

void Controller::addCategory(std::string category) {
	todo->addCategory(category);
}

void Controller::editCategory(std::string categoryOld, std::string categoryNew) {
	todo->editCategory(categoryOld, categoryNew);
}

void Controller::editCategory(int i, std::string categoryNew) {
	todo->editCategory(i, categoryNew);
}

std::string Controller::removeCategory(std::string category) {
    return todo->removeCategory(category);
}

std::string Controller::removeCategory(int i) {
    return todo->removeCategory(i);
}

void Controller::addTag(std::string tag) {
	todo->addTag(tag);
}

void Controller::editTag(std::string tagOld, std::string tagNew) {
	todo->editTag(tagOld, tagNew);
}

void Controller::editTag(int i, std::string tagNew) {
	todo->editTag(i, tagNew);
}

std::string Controller::removeTag(std::string tag) {
    return todo->removeTag(tag);
}

std::string Controller::removeTag(int i) {
    return todo->removeTag(i);
}

Task **Controller::getTasks() {
    return todo->getTasks();
}

int Controller::getTasksCurrentSize() {
    return todo->getTasksCurrentSize();
}

int Controller::getTasksMaxSize() {
    return todo->getTasksMaxSize();
}

std::string *Controller::getCategories() {
    return todo->getCategories();
}

int Controller::getCategoriesCurrentSize() {
    return todo->getCategoriesCurrentSize();
}

int Controller::getCategoriesMaxSize() {
    return todo->getCategoriesMaxSize();
}

std::string *Controller::getTags() {
    return todo->getTags();
}

int Controller::getTagsCurrentSize() {
    return todo->getTagsCurrentSize();
}

int Controller::getTagsMaxSize() {
    return todo->getTagsMaxSize();
}

void Controller::sortByDate() {
	todo->sortByDate();
}

void Controller::sortByTag() {
	todo->sortByTag();
}

void Controller::sortByName() {
	todo->sortByName();
}

void Controller::sortByPriority() {
	todo->sortByPriority();
}

void Controller::toCSV(std::string name) {
	todo->toCSV(name);
}

void Controller::fromCSV(std::string name) {
	todo->fromCSV(name);
}
