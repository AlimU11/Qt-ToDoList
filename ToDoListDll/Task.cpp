#include <strstream>
#include <iostream>
#include "Task.h"

Task::Task(std::string text, bool isCompleted, std::string * tags, int tag_i, int tag_size,
	std::string category, PriorityEnum priority, time_t timestamp) : _text(text),
	_isCompleted(isCompleted),
	_tags(tags),
	_category(category),
	_priority(priority),
	_timestamp(timestamp) {
	_tag_i = 0;
	_tag_size = 1;
	_tags = new std::string[_tag_size];

	for (int i = 0; i < tag_i; i++) {
		addTag(tags[i]);
	}
}

Task::~Task() {
	delete[] _tags;
}

void Task::setText(std::string text) {
	_text = text;
}

std::string Task::getText() {
	return _text;
}

void Task::setCompletion(bool isCompleted) {
	_isCompleted = isCompleted;
}

bool Task::getCompletion() {
	return _isCompleted;
}

void Task::setCategory(std::string category) {
	_category = category;
}

std::string Task::getCategory() {
	return _category;
}

void Task::setPriority(PriorityEnum priority) {
	_priority = priority;
}

PriorityEnum Task::getPriority() {
	return _priority;
}

void Task::setTimestamp(time_t timestamp) {
	_timestamp = timestamp;
}

time_t Task::getTimestamp() {
	return _timestamp;
}

void Task::addTag(std::string tag) {
	bool isin = false;

	for (int i = 0; i < _tag_i; i++) {
		if (_tags[i] == tag) {
			isin = true;
		}
	}

	if (!isin) {
		if (_tag_i == _tag_size) {
			std::string *temp = new std::string[_tag_size * 2];
			for (int i = 0; i < _tag_size; i++) {
				temp[i] = _tags[i];
			}

			delete[] _tags;
			_tags = temp;
			_tag_size *= 2;
		}

		_tags[_tag_i] = tag;
		_tag_i++;
	}
}

void Task::removeTag(int i) {
	if (i < 0 || i >= _tag_i) {
		throw std::out_of_range("i out of range");
	}

	for (int k = 0; k < _tag_i; k++) {
		if (k == i) {
			for (; k < _tag_i - 1; k++) {
				_tags[k] = _tags[k + 1];
			}
		}
	}
	_tags[_tag_i - 1] = "";
	_tag_i--;
}

std::string* Task::getTags() {
	return _tags;
}

int Task::getTagsCurrentSize() {
	return _tag_i;
}

int Task::getTagMaxSize() {
	return _tag_size;
}

std::string Task::toString() {
	std::strstream ss;

	ss << _text << ",";
	ss << _isCompleted << ",";
	ss << _tag_i << ",";
	ss << _tag_size << ",";

	for (int i = 0; i < _tag_i; i++) {
		ss << _tags[i] << ",";
	}

	ss << _category << ",";
	ss << _priority << ",";
	ss << _timestamp << std::endl << std::ends;

	return ss.str();
}

int Task::dateComparator(Task *obj) {
	if (_timestamp > obj->getTimestamp()) {
		return 1;
	}
	else if (_timestamp == obj->getTimestamp()) {
		return 0;
	}
	return -1;
}

int Task::tagComparator(Task *obj) {
	std::string min_t;
	if (_tag_i == 0) {
		min_t = "";
	} else if (_tag_i == 1) {
		min_t = _tags[0];
	} else {
		min_t = _tags[0];
		for (int i = 1; i < _tag_i; i++) {
			if (min_t > _tags[i]) {
				min_t = _tags[i];
			}
		}
	}

	std::string min_t_obj;
	if (obj->getTagsCurrentSize() == 0) {
		min_t_obj = "";
	} else if (obj->getTagsCurrentSize() == 1) {
		min_t_obj = obj->getTags()[0];
	} else {
		min_t_obj = obj->getTags()[0];
		for (int i = 1; i < obj->getTagsCurrentSize(); i++) {
			if (min_t_obj > obj->getTags()[i]) {
				min_t_obj = obj->getTags()[i];
			}
		}
	}

	return min_t.compare(min_t_obj);
}

int Task::textComparator(Task *obj) {
	return _text.compare(obj->getText());
}

int Task::priorityComparator(Task *obj) {
	if (_priority > obj->getPriority()) {
		return 1;
	}
	else if (_priority == obj->getPriority()) {
		return 0;
	}
	return -1;
}
