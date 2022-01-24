#include "ToDoList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

ToDoList::ToDoList() {
	_task_i = 0;
	_task_size = 1;
	_taskArray = new Task*[_task_size];

	_tag_i = 0;
	_tag_size = 1;
	_tagArray = new std::string[_tag_size];

	_cat_i = 0;
	_cat_size = 1;
	_categoryArray = new std::string[_cat_size];
}

ToDoList::~ToDoList() {
	for (int i = 0; i < _task_i; i++) {
		delete _taskArray[i];
	}

	delete[] _taskArray;
	delete[] _categoryArray;
	delete[] _tagArray;
}

void ToDoList::addTask(std::string text, std::string * tags, int tag_i, int tag_size,
	std::string category, int priority, time_t date) {
	if (_task_i >= _task_size) {
		Task** temp = new Task*[_task_size * 2];
		for (int i = 0; i < _task_i; i++) {
			temp[i] = _taskArray[i];
		}

		delete[] _taskArray;
		_taskArray = temp;

		_task_size *= 2;
	}

	_taskArray[_task_i] = new Task(text, false, tags, tag_i, tag_size, category, static_cast<PriorityEnum>(priority), date);
	_task_i++;

	for (int i = 0; i < tag_i; i++) {
		addTag(tags[i]);
	}

	addCategory(category);


	delete[] tags;
}

Task* ToDoList::removeTask(int i) {
	if (i < 0 || i >= _task_i) {
		throw std::out_of_range("task index out of range");
	}

	Task* temp = _taskArray[i];

	for (int k = 0; k < _task_i; k++) {
		if (k == i) {
			for (; k < _task_i - 1; k++) {
				_taskArray[k] = _taskArray[k + 1];
			}
		}
	}

	_task_i--;

	return temp;
}

void ToDoList::addCategory(std::string category) {
	bool isin = false;
	for (int i = 0; i < _cat_i; i++) {
		if (_categoryArray[i] == category) {
			isin = true;
		}
	}

	if (!isin && category != "") {
		if (_cat_i >= _cat_size) {
			std::string* temp = new std::string[_cat_size * 2];

			for (int i = 0; i < _cat_i; i++) {
				temp[i] = _categoryArray[i];
			}

			delete[] _categoryArray;
			_categoryArray = temp;

			_cat_size *= 2;
		}

		_categoryArray[_cat_i] = category;
		_cat_i++;
	}
}

void ToDoList::editCategory(std::string categoryOld, std::string categoryNew) {
	bool isin = false;
	int idx = -1;
	for (int i = 0; i < _cat_i; i++) {
		if (_categoryArray[i] == categoryOld) {
			isin = true;
			idx = i;
		}
	}

	if (!isin) {
		throw std::invalid_argument("category not exist");
	}

	_categoryArray[idx] = categoryNew;
}

void ToDoList::editCategory(int i, std::string categoryNew) {
	if (i < 0 || i >= _cat_i) {
		throw std::out_of_range("category index out of range");
	}

	_categoryArray[i] = categoryNew;
}

std::string ToDoList::removeCategory(std::string category) {
	bool isin = false;
	int idx = -1;
	for (int i = 0; i < _cat_i; i++) {
		if (_categoryArray[i] == category) {
			isin = true;
			idx = i;
		}
	}

	if (!isin) {
		throw std::invalid_argument("category not exist");
	}

	return removeCategory(idx);
}

std::string ToDoList::removeCategory(int i) {
	if (i < 0 || i >= _cat_i) {
		throw std::out_of_range("category index out of range");
	}

	std::string temp = _categoryArray[i];

	for (int k = 0; k < _cat_i; k++) {
		if (k == i) {
			for (; k < _cat_i - 1; k++) {
				_categoryArray[k] = _categoryArray[k + 1];
			}
		}
	}

	for (int i = 0; i < _task_i; i++) {
		if (_taskArray[i]->getCategory() == temp) {
			_taskArray[i]->setCategory("");
		}
	}

	_categoryArray[_cat_i - 1] = "";
	_cat_i--;

	return temp;
}

void ToDoList::addTag(std::string tag) {
	bool isin = false;
	for (int i = 0; i < _tag_i; i++) {
		if (_tagArray[i] == tag) {
			isin = true;
		}
	}

	if (!isin) {
		if (_tag_i >= _tag_size) {
			std::string* temp = new std::string[_tag_size * 2];

			for (int i = 0; i < _tag_i; i++) {
				temp[i] = _tagArray[i];
			}

			delete[] _tagArray;
			_tagArray = temp;

			_tag_size *= 2;
		}

		_tagArray[_tag_i] = tag;
		_tag_i++;
	}
}

void ToDoList::editTag(std::string tagOld, std::string tagNew) {
	bool isin = false;
	int idx = -1;

	for (int i = 0; i < _tag_i; i++) {
		if (_tagArray[i] == tagOld) {
			isin = true;
			idx = i;
			break;
		}
	}

	if (isin) {
		for (int i = 0; i < _task_i; i++) {
			for (int j = 0; j < _taskArray[i]->getTagsCurrentSize(); j++) {
				if (_taskArray[i]->getTags()[j] == tagOld) {
					_taskArray[i]->removeTag(j);
					_taskArray[i]->addTag(tagNew);
				}
			}
		}

		_tagArray[idx] = tagNew;
	}
}

void ToDoList::editTag(int idx, std::string tagNew) {
	if (idx < 0 || idx >= _tag_i) {
		throw std::out_of_range("tag index out of range");
	}

	for (int i = 0; i < _task_i; i++) {
		for (int j = 0; j < _taskArray[i]->getTagsCurrentSize(); j++) {
			if (_taskArray[i]->getTags()[j] == _tagArray[idx]) {
				_taskArray[i]->removeTag(j);
				_taskArray[i]->addTag(tagNew);
			}
		}
	}

	_tagArray[idx] = tagNew;
}

std::string ToDoList::removeTag(std::string tag) {
	bool isin = false;
	int idx = -1;
	for (int i = 0; i < _tag_i; i++) {
		if (_tagArray[i] == tag) {
			isin = true;
			idx = i;
			break;
		}
	}

	if (!isin) {
		throw std::invalid_argument("category not exist");
	}
	std::cout << std::endl << "text";
	return removeTag(idx);
}

std::string ToDoList::removeTag(int i) {
	if (i < 0 || i >= _tag_i) {
		throw std::out_of_range("tag index out of range");
	}

	std::string temp = _tagArray[i];

	for (int k = 0; k < _tag_i; k++) {
		if (k == i) {
			for (; k < _tag_i - 1; k++) {
				_tagArray[k] = _tagArray[k + 1];
			}
		}
	}

	_tagArray[_tag_i - 1] = "";
	_tag_i--;

	for (int k = 0; k < _task_i; k++) {
		bool isin = false;
		int idx = -1;

		for (int j = 0; j < _taskArray[k]->getTagsCurrentSize(); j++) {
			if (_taskArray[k]->getTags()[j] == temp) {
				isin = true;
				idx = j;
			}
		}

		if (isin) {
			_taskArray[k]->removeTag(idx);
		}
	}
	return temp;
}

Task** ToDoList::getTasks() {
	return _taskArray;
}

int ToDoList::getTasksCurrentSize() {
	return _task_i;
}

int ToDoList::getTasksMaxSize() {
	return _task_size;
}

std::string* ToDoList::getCategories() {
	return _categoryArray;
}

int ToDoList::getCategoriesCurrentSize() {
	return _cat_i;
}

int ToDoList::getCategoriesMaxSize() {
	return _cat_size;
}

std::string* ToDoList::getTags() {
	return _tagArray;
}

int ToDoList::getTagsCurrentSize() {
	return _tag_i;
}

int ToDoList::getTagsMaxSize() {
	return _tag_size;
}

void ToDoList::sortByDate() {
	for (int step = 1; step < _task_i; step++) {
		Task* key = _taskArray[step];
		int j = step - 1;

		while (j >= 0 && key->dateComparator(_taskArray[j]) < 0) {
			_taskArray[j + 1] = _taskArray[j];
			--j;
		}
		_taskArray[j + 1] = key;
	}
}

void ToDoList::sortByTag() {
	for (int step = 1; step < _task_i; step++) {
		Task* key = _taskArray[step];
		int j = step - 1;

		while (j >= 0 && key->tagComparator(_taskArray[j]) < 0) {
			_taskArray[j + 1] = _taskArray[j];
			--j;
		}
		_taskArray[j + 1] = key;
	}
}

void ToDoList::sortByName() {
	for (int step = 1; step < _task_i; step++) {
		Task* key = _taskArray[step];
		int j = step - 1;

		while (j >= 0 && key->textComparator(_taskArray[j]) < 0) {
			_taskArray[j + 1] = _taskArray[j];
			--j;
		}
		_taskArray[j + 1] = key;
	}
}

void ToDoList::sortByPriority() {
	for (int step = 1; step < _task_i; step++) {
		Task* key = _taskArray[step];
		int j = step - 1;

		while (j >= 0 && key->priorityComparator(_taskArray[j]) < 0) {
			_taskArray[j + 1] = _taskArray[j];
			--j;
		}
		_taskArray[j + 1] = key;
	}
}

void ToDoList::toCSV(std::string name) {
	std::ofstream output(name);

	if (output.is_open()) {
		output << _task_i << std::endl;

		for (int i = 0; i < _task_i; i++) {
			output << _taskArray[i]->toString();
		}

		output << _tag_i << std::endl;
		for (int i = 0; i < _tag_i; i++) {
			output << _tagArray[i] << std::endl;
		}

		output << _cat_i << std::endl;
		for (int i = 0; i < _cat_i; i++) {
			output << _categoryArray[i] << std::endl;
		}

		output.close();
	}
	else {
		throw std::exception("file not opened exception");
	}
}

void ToDoList::fromCSV(std::string name) {
	std::ifstream input(name);

	std::string line;
	int max;

	if (input.is_open()) {
		_tag_i = 0;
		_cat_i = 0;
		_task_i = 0;

		std::getline(input, line);
		max = std::stoi(line);
		for (int i = 0; i < max; i++) {
			std::getline(input, line);
			std::istringstream f(line);
			std::string token;

			std::getline(f, token, ',');
			std::string text = token;

			std::getline(f, token, ',');
			bool isCompleted = std::stoi(token);

			std::getline(f, token, ',');
			int tag_i = std::stoi(token);

			std::getline(f, token, ',');
			int tag_size = std::stoi(token);

			std::string* tags = new std::string[tag_i];
			for (int j = 0; j < tag_i; j++) {
				std::getline(f, token, ',');
				tags[j] = token;
			}

			std::getline(f, token, ',');
			std::string category = token;

			std::getline(f, token, ',');
			PriorityEnum priority = static_cast<PriorityEnum>(std::stoi(token));

			std::getline(f, token, ',');
			time_t timestamp = std::stoi(token);

			addTask(text, tags, tag_i, tag_size, category, priority, timestamp);
		}

		std::getline(input, line);
		max = std::stoi(line);
		for (int i = 0; i < max; i++) {
			std::getline(input, line);
			addTag(line);
		}

		std::getline(input, line);
		max = std::stoi(line);
		for (int i = 0; i < max; i++) {
			std::getline(input, line);
			addCategory(line);
		}

		input.close();
	}
	else {
		throw std::exception("file not opened exception");
	}
}
