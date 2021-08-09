#include"todoLib.h"

int main()
{
	NowTime nowTime;
	bool isListed = false;

	std::vector<Todo> allTodo = getFromTodo_dataCsv();

	todoSort(allTodo);
	std::cout << std::endl;
	listingTodo(allTodo, nowTime, 5);
	std::cout << "\n何をしますか？ ※コマンドを知りたい場合は help と入力してください" << std::endl;
	std::string command;
	while (std::getline(std::cin, command))
	{
		//commandによって分岐
		//大文字小文字を区別しない用正規表現を使用
		if (std::regex_match(command, std::regex(R"(^help$)", std::regex::icase)))
		{
			showHelp();
		}
		else if (std::regex_match(command, std::regex(R"(^list$)", std::regex::icase)))
		{
			listingTodo(allTodo, nowTime, allTodo.size());
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^list( |->)checked$)", std::regex::icase)))
		{
			listingCheckedTodo(allTodo, nowTime);
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^list( |->)notchecked$)", std::regex::icase)))
		{
			listingNotCheckedTodo(allTodo, nowTime);
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^list( |->)deadline$)", std::regex::icase)))
		{
			listingTodoWithDeadline(allTodo, nowTime);
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^list( |->)nodeadline$)", std::regex::icase)))
		{
			listingTodoWithoutDeadline(allTodo, nowTime);
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^list( |->)priority$)", std::regex::icase)))
		{
			listingTodoWithPriority(allTodo, nowTime);
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^list( |->)(overdeadline|over)$)", std::regex::icase)))
		{
			listingTodoOverDeadline(allTodo, nowTime);
			isListed = true;
		}
		else if (std::regex_match(command, std::regex(R"(^add$)", std::regex::icase)))
		{
			addContentToTodo(allTodo);
		}
		else if (std::regex_match(command, std::regex(R"(^check$)", std::regex::icase)))
		{
			checkTodo(allTodo, nowTime);
		}
		else if (std::regex_match(command, std::regex(R"(^check( |->)\d+$)", std::regex::icase)))
		{
			std::string checkTodoStr = "";
			//コマンドの文字列を走査して数字のみを取り出す
			for (int i = 0; i < command.size(); i++)
			{
				if (std::isdigit(command[i])) checkTodoStr += command[i];
			}
			checkTodo(allTodo, nowTime, checkTodoStr);
		}
		else if (std::regex_match(command, std::regex(R"(^check( |->)all$)", std::regex::icase)))
		{
			checkAllTodo(allTodo, nowTime);
		}
		else if (std::regex_match(command, std::regex(R"(^(delete|del)$)", std::regex::icase)))
		{
			deleteTodo(allTodo, nowTime);
		}
		else if (std::regex_match(command, std::regex(R"(^(delete|del)( |->)\d+$)", std::regex::icase)))
		{
			std::string deleteTodoStr = "";
			//コマンドの文字列を走査して数字のみを取り出す
			for (int i = 0; i < command.size(); i++)
			{
				if (std::isdigit(command[i])) deleteTodoStr += command[i];
			}
			deleteTodo(allTodo, nowTime, deleteTodoStr);
		}
		else if (std::regex_match(command, std::regex(R"(^(delete|del)( |->)all$)", std::regex::icase)))
		{
			deleteAllTodo(allTodo);
		}
		else if (std::regex_match(command, std::regex(R"(^(delete|del)( |->)checked$)", std::regex::icase)))
		{
			deleteAllCheckedTodo(allTodo, nowTime);
		}
		else if (std::regex_match(command, std::regex(R"(^(delete|del)( |->)notchecked$)", std::regex::icase)))
		{
			deleteAllNotCheckedTodo(allTodo, nowTime);
		}
		else if (std::regex_match(command, std::regex(R"(^(delete|del)( |->)(overdeadline|over)$)", std::regex::icase)))
		{
			deleteAllTodoOverDeadline(allTodo, nowTime);
		}
		else if (std::regex_match(command, std::regex(R"(^exit$)", std::regex::icase)))
		{
			//ToDoを保存して終了
			todoSort(allTodo);
			writeToTodo_dataCsv(allTodo);
			return 0;
		}
		
		if (isListed == true)
		{
			isListed = false;
			writeToTodo_dataCsv(allTodo);
		}
		else
		{
			todoSort(allTodo);
			writeToTodo_dataCsv(allTodo);
			std::cout << std::endl;
			listingTodo(allTodo, nowTime, 5);
		}
		std::cout << "\n何をしますか？ ※コマンドを知りたい場合は help と入力してください" << std::endl;
	}
}