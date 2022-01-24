#ifndef __TODOLIST_H
#define __TODOLIST_H

#include "platform.h"
#include "Task.h"

class DLL_SPEC ToDoList {
	public:
		ToDoList();
		~ToDoList();

		void addTask(std::string text, std::string* tags, int tag_i, int tag_size,
			std::string category, int priority, time_t date);
		Task* removeTask(int i);

		void addCategory(std::string category);
		void editCategory(std::string categoryOld, std::string categoryNew);
		void editCategory(int i, std::string categoryNew);
		std::string removeCategory(std::string category);
		std::string removeCategory(int i);

		void addTag(std::string tag);
		void editTag(std::string tagOld, std::string tagNew);
		void editTag(int i, std::string tagNew);
		std::string removeTag(std::string tag);
		std::string removeTag(int i);

		Task** getTasks();
		int getTasksCurrentSize();
		int getTasksMaxSize();

		std::string* getCategories();
		int getCategoriesCurrentSize();
		int getCategoriesMaxSize();

		std::string* getTags();
		int getTagsCurrentSize();
		int getTagsMaxSize();

		void sortByDate();
		void sortByTag();
		void sortByName();
		void sortByPriority();

		void toCSV(std::string name);
		void fromCSV(std::string name);

	private:
		Task** _taskArray;
		int _task_i;
		int _task_size;

		std::string* _categoryArray;
		int _cat_i;
		int _cat_size;

		std::string* _tagArray;
		int _tag_i;
		int _tag_size;
};

#endif