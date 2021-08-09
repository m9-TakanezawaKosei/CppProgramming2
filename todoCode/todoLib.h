#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>
#include <vector>
#include <format>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cctype>

class NowTime
{
	int year;
	int month;
	int day;
public:
	NowTime();
	int getYear();
	int getMonth();
	int getDay();
	void renew();
};

class Todo
{
	std::string content;
	bool isChecked;
	int year;
	int month;
	int day;
	int priority;
public:
	Todo();
	Todo(const std::string& newContent, int newisChecked, int newYear, int newMonth, int newDay, int newPriority);
	std::string getContent();
	bool getIsChecked();
	int getYear();
	int getMonth();
	int getDay();
	int getPriority();
	void setisChecked(bool trueOrFalse);
};


void showHelp();

void todoSort(std::vector<Todo>& allTodo);
bool getIsOverDeadline(Todo& todo, NowTime& nowTime);
int getNumberOfTodoOverDeadline(std::vector<Todo>& allTodo, NowTime& nowTime);
void showTodo(Todo& todo, NowTime& nowTime, int maxYear, int maxPriority);
void showOneTodo(Todo& todo, NowTime& nowTime);

void listingTodo(std::vector<Todo>& allTodo, NowTime& nowTime, int n);
void listingCheckedTodo(std::vector<Todo>& allTodo, NowTime& nowTime);
void listingNotCheckedTodo(std::vector<Todo>& allTodo, NowTime& nowTime);
void listingTodoWithDeadline(std::vector<Todo>& allTodo, NowTime& nowTime);
void listingTodoWithoutDeadline(std::vector<Todo>& allTodo, NowTime& nowTime);
void listingTodoWithPriority(std::vector<Todo>& allTodo, NowTime& nowTime);
void listingTodoOverDeadline(std::vector<Todo>& allTodo, NowTime& nowTime);

void addContentToTodo(std::vector<Todo>& allTodo);
void addDeadlineToTodo(std::vector<Todo>& allTodo, std::string content, bool isValidDeadline);
std::vector<int> splitInputOfDeadline(std::string deadlineStr);
void addPriorityToTodo(std::vector<Todo>& allTodo, std::string content, std::vector<int> deadlineVec, bool isValidPriority);
void addTodo(std::vector<Todo>& allTodo, std::string content, std::vector<int> deadlineVec, int priority);

void checkTodo(std::vector<Todo>& allTodo, NowTime nowTime);
void checkTodo(std::vector<Todo>& allTodo, NowTime nowTime, std::string checkStr);
void checkAllTodo(std::vector<Todo>& allTodo, NowTime nowTime);

void deleteTodo(std::vector<Todo>& allTodo, NowTime nowTime);
void deleteTodo(std::vector<Todo>& allTodo, NowTime nowTime, std::string deleteStr);
void deleteAllTodo(std::vector<Todo>& allTodo);
void deleteAllCheckedTodo(std::vector<Todo>& allTodo, NowTime nowTime);
void deleteAllNotCheckedTodo(std::vector<Todo>& allTodo, NowTime& nowTime);
void deleteAllTodoOverDeadline(std::vector<Todo>& allTodo, NowTime& nowTime);

std::vector<Todo> getFromTodo_dataCsv();
void writeToTodo_dataCsv(std::vector<Todo>& allTodo);