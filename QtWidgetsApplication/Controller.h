#pragma once
#include <ToDoList.h>

class Controller {
	public:
		Controller();
		~Controller();

		void addTask(std::string text, std::string * tags, int tag_i, int tag_size,
			std::string category, int priority, time_t date);
		Task* removeTask(int i);

		void setText(int i, std::string text);
		std::string getText(int i);

		void setCompletion(int i, bool isCompleted);
		bool getCompletion(int i);

		void setCategory(int i, std::string category);
		std::string getCategory(int i);

		void setPriority(int i, PriorityEnum priority);
		PriorityEnum getPriority(int i);

		void setTimestamp(int i, time_t timestamp);
		time_t getTimestamp(int i);

		void addTagToTask(int i, std::string tag);
		void removeTagFromTask(int i, int idx);

		std::string* getTagsFromTask(int i);
		int getTagsCurrentSizeFromTask(int i);
		int getTagsMaxSizeFromTask(int i);

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
		ToDoList* todo;
};