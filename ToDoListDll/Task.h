#ifndef __TASK_H
#define __TASK_H

#include "platform.h"
#include <string>
#include "PriorityEnum.h"

struct DLL_SPEC Task {
	public:
		Task() {};
		Task(std::string text, bool isCompleted, std::string* tags, int tag_i, int tag_size,
			std::string category, PriorityEnum priority,
			time_t timestamp);
		~Task();

		void setText(std::string text);
		std::string getText();

		void setCompletion(bool isCompleted);
		bool getCompletion();

		void setCategory(std::string category);
		std::string getCategory();

		void setPriority(PriorityEnum priority);
		PriorityEnum getPriority();

		void setTimestamp(time_t timestamp);
		time_t getTimestamp();

		void addTag(std::string tag);
		void removeTag(int i);

		std::string* getTags();
		int getTagsCurrentSize();
		int getTagMaxSize();

		std::string toString();

		int dateComparator(Task *obj);
		int tagComparator(Task *obj);
		int textComparator(Task *obj);
		int priorityComparator(Task *obj);

	private:
		std::string _text;
		bool _isCompleted;

		std::string* _tags;
		int _tag_i;
		int _tag_size;

		std::string _category;
		PriorityEnum _priority;
		time_t _timestamp;
};

#endif