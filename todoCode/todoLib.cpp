#include"todoLib.h"

NowTime::NowTime()
{
	auto now = std::chrono::system_clock::now();
	std::chrono::sys_seconds now_sec = std::chrono::floor<std::chrono::seconds>(now);
	std::chrono::zoned_time zt{ "Asia/Tokyo", now_sec };
	year = std::stoi(std::format("{:%Y}", zt));
	month = std::stoi(std::format("{:%m}", zt));
	day = std::stoi(std::format("{:%d}", zt));
}
int NowTime::getYear() { return year; }
int NowTime::getMonth() { return month; }
int NowTime::getDay() { return day; }
void NowTime::renew()
{
	auto now = std::chrono::system_clock::now();
	std::chrono::sys_seconds now_sec = std::chrono::floor<std::chrono::seconds>(now);
	std::chrono::zoned_time zt{ "Asia/Tokyo", now_sec };
	year = std::stoi(std::format("{:%Y}", zt));
	month = std::stoi(std::format("{:%m}", zt));
	day = std::stoi(std::format("{:%d}", zt));
}

Todo::Todo()
{
	content = "";
	isChecked = false;
	year = 0;
	month = 0;
	day = 0;
	priority = 0;
}
Todo::Todo(const std::string& newContent, int newisChecked, int newYear, int newMonth, int newDay, int newPriority)
{
	content = newContent;
	if (newisChecked == 1) isChecked = true;
	else isChecked = false;
	year = newYear;
	month = newMonth;
	day = newDay;
	priority = newPriority;
}
std::string Todo::getContent() { return content; }
bool Todo::getIsChecked() { return isChecked; }
int Todo::getYear() { return year; }
int Todo::getMonth() { return month; }
int Todo::getDay() { return day; }
int Todo::getPriority() { return priority; }
void Todo::setisChecked(bool trueOrFalse) { isChecked = trueOrFalse; }


void showHelp()
{
	std::system("cls");
	std::cout << "コマンド一覧 ※大文字小文字は区別しない, ->は「 」(半角スペース)で代用可" << std::endl;
	std::cout << "list" << "\t\t\t\t:" << "ToDoリスト内の全てのToDoを表示する" << std::endl;
	std::cout << "list->checked" << "\t\t\t:" << "ToDoリスト内の全ての達成済ToDoを表示する" << std::endl;
	std::cout << "    ->notchecked" << "\t\t:" << "ToDoリスト内の全ての未達成ToDoを表示する" << std::endl;
	std::cout << "    ->deadline" << "\t\t\t:" << "ToDoリスト内の全ての締切付きToDoを表示する" << std::endl;
	std::cout << "    ->nodeadline" << "\t\t:" << "ToDoリスト内の全ての締切なしToDoを表示する" << std::endl;
	std::cout << "    ->priority" << "\t\t\t:" << "ToDoリスト内の全ての優先度(☆マーク)付きToDoを表示する" << std::endl;
	std::cout << "    ->overdeadline(またはover)" << "\t:" << "ToDoリスト内の全ての締切を過ぎた未達成ToDoを表示する" << std::endl;
	std::cout << std::endl;
	std::cout << "add" << "\t\t\t\t:" << "ToDoリストにToDoを追加する" << std::endl;
	std::cout << std::endl;
	std::cout << "check" << "\t\t\t\t:" << "選んだToDoを達成済の状態にする" << std::endl;
	std::cout << "check->(ToDoの番号)" << "\t\t:(ToDoの番号)のToDoを達成済の状態にする" << std::endl;
	std::cout << "     ->all" << "\t\t\t:" << "全ての未達成ToDoを達成済の状態にする" << std::endl;
	std::cout << std::endl;
	std::cout << "delete(またはdel)" << "\t\t:" << "選んだToDoを消去する" << std::endl;
	std::cout << "delete->(ToDoの番号)" << "\t\t:" << "(ToDoの番号)のToDoを消去する" << std::endl;
	std::cout << "      ->all" << "\t\t\t:" << "全てのToDoを消去する" << std::endl;
	std::cout << "      ->checked" << "\t\t\t:" << "全ての未達成ToDoを消去する" << std::endl;
	std::cout << "      ->notchecked" << "\t\t:" << "全ての達成済みToDoを消去する" << std::endl;
	std::cout << "      ->overdeadline" << "\t\t:" << "全ての締切を過ぎた未達成ToDoを消去する" << std::endl;
	std::cout << std::endl;
	std::cout << "exit" << "\t\t\t\t:" << "プログラムを終了する" << std::endl;
	std::cout << std::endl;
	std::cout << "Enterを押して終了" << std::endl;
	std::string dammy;
	while (!std::getline(std::cin, dammy)) {}
}

void todoSort(std::vector<Todo>& allTodo)
{
	//未達成→優先度が大きい→文字列の大きさ順 で並ぶようにソート
	std::stable_sort(allTodo.begin(), allTodo.end(), [](Todo a, Todo b) {return a.getContent() > b.getContent(); });
	std::stable_sort(allTodo.begin(), allTodo.end(), [](Todo a, Todo b) {return a.getPriority() > b.getPriority(); });
	std::stable_sort(allTodo.begin(), allTodo.end(), [](Todo a, Todo b) {return !a.getIsChecked() > !b.getIsChecked(); });

	int checkedNum = 0;
	for (int i = 0; i < allTodo.size(); ++i)
	{
		if (allTodo[i].getIsChecked() == false) checkedNum++;
	}

	//未達成のToDoが締切の早い順に並ぶようにソート
	std::stable_sort(allTodo.begin(), allTodo.begin() + checkedNum, [](Todo a, Todo b)
		{
			if (a.getDay() == 0 || b.getDay() == 0) return a.getDay() > b.getDay();
			return a.getDay() < b.getDay();
		});
	std::stable_sort(allTodo.begin(), allTodo.begin() + checkedNum, [](Todo a, Todo b)
		{
			if (a.getMonth() == 0 || b.getMonth() == 0) return a.getMonth() > b.getMonth();
			return a.getMonth() < b.getMonth();
		});
	std::stable_sort(allTodo.begin(), allTodo.begin() + checkedNum, [](Todo a, Todo b)
		{
			if (a.getYear() == 0 || b.getYear() == 0) return a.getYear() > b.getYear();
			return a.getYear() < b.getYear();
		});

	//達成済のToDoが締切の早い順に並ぶようにソート
	std::stable_sort(allTodo.begin() + checkedNum, allTodo.end(), [](Todo a, Todo b)
		{
			if (a.getDay() == 0 || b.getDay() == 0) return a.getDay() > b.getDay();
			return a.getDay() < b.getDay();
		});
	std::stable_sort(allTodo.begin() + checkedNum, allTodo.end(), [](Todo a, Todo b)
		{
			if (a.getMonth() == 0 || b.getMonth() == 0) return a.getMonth() > b.getMonth();
			return a.getMonth() < b.getMonth();
		});
	std::stable_sort(allTodo.begin() + checkedNum, allTodo.end(), [](Todo a, Todo b)
		{
			if (a.getYear() == 0 || b.getYear() == 0) return a.getYear() > b.getYear();
			return a.getYear() < b.getYear();
		});
}
bool getIsOverDeadline(Todo& todo, NowTime& nowTime)
{
	bool isSameYear = todo.getYear() == nowTime.getYear();
	bool isSameMonth = todo.getMonth() == nowTime.getMonth();

	if (todo.getIsChecked()) return false;
	else if (todo.getYear() == 0) return false;
	else if (todo.getYear() > nowTime.getYear()) return false;
	else if (isSameYear && todo.getMonth() > nowTime.getMonth()) return false;
	else if (isSameYear && isSameMonth && todo.getDay() >= nowTime.getDay()) return false;
	return true;
}
int getNumberOfTodoOverDeadline(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	int ans = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (getIsOverDeadline(allTodo[i], nowTime)) ans++;
	}
	return ans;
}
void showTodo(Todo& todo, NowTime& nowTime, int maxYear, int maxPriority)
{
	//maxYear : 表示するToDoの締切年の最大値(0の場合, 締切がついたToDoは表示しないことを意味する)
	//maxPriority : 表示するToDoの優先度の最大値(0の場合, 優先度がついたToDoは表示しないことを意味する)
	if (todo.getIsChecked()) std::cout << "○" << " : ";
	else if (getIsOverDeadline(todo, nowTime)) std::cout << "×" << " : ";
	else std::cout << "　" << " : ";

	if (todo.getYear() != 0)
	{
		for (int i = 0; i < 3 - std::log10(todo.getYear()); ++i) std::cout << 0;
		std::cout << todo.getYear() << "/";
		if (todo.getMonth() < 10) std::cout << 0 << todo.getMonth() << "/";
		else std::cout << todo.getMonth() << "/";
		if (todo.getDay() < 10) std::cout << 0 << todo.getDay();
		else std::cout << todo.getDay();
		std::cout << " 締切";
	}
	//締切を持つToDoが1つ以上ある場合, 表示を整えるため, それに合わせるため空白を挿入
	else if (maxYear > 0) std::cout << std::setw(18);
	if (maxYear > 0) std::cout << " : ";

	//表示を整えるため, 最大の優先度に合わせて空白を挿入
	if (maxPriority > 0) for (int j = 0; j < maxPriority - todo.getPriority(); j++) { std::cout << "　"; }
	if (todo.getPriority() != 0) for (int j = 0; j < todo.getPriority(); j++) { std::cout << "☆"; }
	if (maxPriority > 0) std::cout << " : ";

	std::cout << todo.getContent() << std::endl;
}
void showOneTodo(Todo& todo, NowTime& nowTime)
{
	std::cout << "ToDo内容　 : " << todo.getContent() << std::endl;
	std::cout << "ToDo締切　 : ";
	if (todo.getYear() != 0) std::cout
		<< todo.getYear() << "/"
		<< todo.getMonth() << "/"
		<< todo.getDay();
	std::cout << std::endl;
	std::cout << "ToDo優先度 : ";
	for (int i = 0; i < todo.getPriority(); i++) { std::cout << "☆"; }
	std::cout << std::endl;
	std::cout << "達成状況　 : ";
	if (todo.getIsChecked()) std::cout << "達成済";
	else
	{
		std::cout << "未達成";
		if (getIsOverDeadline(todo, nowTime)) std::cout << "\n※このToDoは既に締切を過ぎています";
	}
	std::cout << std::endl;
}

void listingTodo(std::vector<Todo>& allTodo, NowTime& nowTime, int n)
{
	std::system("cls");
	int listSize = n;
	if (allTodo.size() < n) listSize = allTodo.size();

	//listSizeの桁数
	int digit = std::floor(std::log10(listSize)) + 1;

	int maxPriority = 0;
	int maxYear = 0;
	for (int i = 0; i < listSize; ++i)
	{
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		maxYear = std::max(maxYear, allTodo[i].getYear());
	}

	if (allTodo.size() > listSize)
	{
		nowTime.renew();
		std::cout << "本日は "
			<< nowTime.getYear() << "年"
			<< nowTime.getMonth() << "月"
			<< nowTime.getDay() << "日" << std::endl;

		int overDeadlineNum = getNumberOfTodoOverDeadline(allTodo, nowTime);
		if (overDeadlineNum > 0) std::cout << "締切を過ぎたToDoが " << overDeadlineNum << "件 あります" << std::endl;
		std::cout << std::endl;
	}
	std::cout << "ToDo一覧" << std::endl;
	for (int i = 0; i < listSize; i++)
	{
		//ToDo表示番号の最大桁数に合わせて空白を挿入
		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (allTodo.size() > listSize) std::cout << "その他 " << allTodo.size() - n << "件 のToDoがあります" << std::endl;
	if (allTodo.size() == 0) std::cout << "ToDoはありません" << std::endl;
}
void listingCheckedTodo(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	std::system("cls");
	int digit;
	int maxNum = 0;
	int maxPriority = 0;
	int maxYear = 0;
	int count = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (allTodo[i].getIsChecked() == false) continue;
		maxNum = std::max(maxNum, i);
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		maxYear = std::max(maxYear, allTodo[i].getYear());
		count++;
	}

	digit = std::floor(std::log10(maxNum)) + 1;

	std::cout << "達成済ToDo一覧" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//未達成の場合は飛ばす
		if (allTodo[i].getIsChecked() == false) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (count == 0) std::cout << "達成済ToDoはありません" << std::endl;
}
void listingNotCheckedTodo(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	std::system("cls");
	int digit;
	int maxNum = 0;
	int maxPriority = 0;
	int maxYear = 0;
	int count = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (allTodo[i].getIsChecked()) continue;
		maxNum = std::max(maxNum, i);
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		maxYear = std::max(maxYear, allTodo[i].getYear());
		count++;
	}

	digit = std::floor(std::log10(maxNum)) + 1;

	std::cout << "未達成ToDo一覧" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//達成済の場合は飛ばす
		if (allTodo[i].getIsChecked()) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (count == 0) std::cout << "未達成ToDoはありません" << std::endl;
}
void listingTodoWithDeadline(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	std::system("cls");
	int digit;
	int maxNum = 0;
	int maxPriority = 0;
	int count = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (allTodo[i].getYear() == 0) continue;
		maxNum = std::max(maxNum, i);
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		count++;
	}

	digit = std::floor(std::log10(maxNum)) + 1;

	std::cout << "締切付きToDo一覧" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//締切が無い場合は飛ばす
		if (allTodo[i].getYear() == 0) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, 1, maxPriority);
	}
	if (count == 0) std::cout << "締切付きToDoはありません" << std::endl;
}
void listingTodoWithoutDeadline(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	std::system("cls");
	int digit;
	int maxNum = 0;
	int maxPriority = 0;
	int count = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (allTodo[i].getYear() != 0) continue;
		maxNum = std::max(maxNum, i);
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		count++;
	}

	digit = std::floor(std::log10(maxNum)) + 1;

	std::cout << "締切なしToDo一覧" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//締切がある場合は飛ばす
		if (allTodo[i].getYear() != 0) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, 0, maxPriority);
	}
	if (count == 0) std::cout << "締切なしToDoはありません" << std::endl;
}
void listingTodoWithPriority(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	std::system("cls");
	int digit;
	int maxNum = 0;
	int maxPriority = 0;
	int maxYear = 0;
	int count = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (allTodo[i].getPriority() == 0) continue;
		maxNum = std::max(maxNum, i);
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		maxYear = std::max(maxYear, allTodo[i].getYear());
		count++;
	}

	digit = std::floor(std::log10(maxNum)) + 1;

	std::cout << "優先度付きToDo一覧" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//優先度が無い場合は飛ばす
		if (allTodo[i].getPriority() == 0) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (count == 0) std::cout << "優先度付きToDoはありません" << std::endl;
}
void listingTodoOverDeadline(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	std::system("cls");
	int digit;
	int maxNum = 0;
	int maxPriority = 0;
	int count = 0;
	for (int i = 0; i < allTodo.size(); i++)
	{
		if (getIsOverDeadline(allTodo[i], nowTime) == false) continue;
		maxNum = std::max(maxNum, i);
		maxPriority = std::max(maxPriority, allTodo[i].getPriority());
		count++;
	}

	digit = std::floor(std::log10(maxNum)) + 1;

	std::cout << "締切を過ぎたToDo一覧" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//締切を過ぎていない場合は飛ばす
		if (getIsOverDeadline(allTodo[i], nowTime) == false) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, 1, maxPriority);
	}
	if (count == 0) std::cout << "締切を過ぎたToDoはありません" << std::endl;
}

void addContentToTodo(std::vector<Todo>& allTodo)
{
	std::system("cls");
	std::cout << "追加するToDoの内容を入力してください ※戻る場合は \\back と入力してください" << std::endl;

	std::string content;
	std::getline(std::cin, content);
	if (content == "") return addContentToTodo(allTodo);
	if (content == "\\back") return;

	return addDeadlineToTodo(allTodo, content, true);
}
void addDeadlineToTodo(std::vector<Todo>& allTodo, std::string content, bool isValidDeadline)
{
	std::system("cls");
	std::cout << "ToDo内容 : " << content << std::endl;
	std::cout << "ToDoの締切を入力してください(年/月/日) ※指定しない場合はそのままEnter, 戻る場合は \\back と入力してください" << std::endl;
	if (isValidDeadline == false) std::cout << "その日付は有効ではありません" << std::endl;

	std::vector<int> deadlineVec = { 0,0,0 };

	std::string deadlineStr;
	std::getline(std::cin, deadlineStr);
	if (deadlineStr == "") return addPriorityToTodo(allTodo, content, deadlineVec, true);
	if (deadlineStr == "\\back") return addContentToTodo(allTodo);

	deadlineVec = splitInputOfDeadline(deadlineStr);
	if (deadlineVec[0] == -1) return addDeadlineToTodo(allTodo, content, false);

	return addPriorityToTodo(allTodo, content, deadlineVec, true);
}
std::vector<int> splitInputOfDeadline(std::string deadlineStr)
{
	std::vector<int> deadlineVec = { -1, -1, -1 };
	if (std::regex_match(deadlineStr, std::regex(R"(^\d{1,}/\d{1,}/\d{1,}$)")) == false)
	{
		return deadlineVec;
	}
	//文字列を / で分割する　
	std::regex slash(R"(/)");
	std::sregex_token_iterator it(deadlineStr.begin(), deadlineStr.end(), slash, -1);
	for (int i = 0; i < 3; ++i)
	{
		std::string yearOrMonthOrDay = *it++;
		if (yearOrMonthOrDay.size() <= 4 && std::all_of(yearOrMonthOrDay.begin(), yearOrMonthOrDay.end(), [](char c) { return std::isdigit(c); }))
		{
			deadlineVec[i] = std::stoi(yearOrMonthOrDay);
		}
		else
		{
			deadlineVec = { -1, -1, -1, };
			return deadlineVec;
		}
	}

	int checkYear = deadlineVec[0];
	unsigned int checkMonth = deadlineVec[1];
	unsigned int checkDay = deadlineVec[2];
	std::chrono::year_month_day date{ std::chrono::year{checkYear}, std::chrono::month{checkMonth}, std::chrono::day{checkDay} };
	//入力した日付が有効な日付かどうかを判定する
	if (date.ok() == false)
	{
		deadlineVec = { -1, -1, -1, };
		return deadlineVec;
	}

	return deadlineVec;
}
void addPriorityToTodo(std::vector<Todo>& allTodo, std::string content, std::vector<int> deadlineVec, bool isValidPriority)
{
	std::system("cls");
	std::cout << "ToDo内容　 : " << content << std::endl;
	std::cout << "ToDo締切　 : ";
	if (deadlineVec[0] != 0) std::cout
		<< deadlineVec[0] << "/"
		<< deadlineVec[1] << "/"
		<< deadlineVec[2];
	std::cout << std::endl;
	std::cout << "ToDoの優先度を入力してください(数字 最大10) ※指定しない場合はそのままEnter, 戻る場合は \\back と入力してください" << std::endl;
	if (isValidPriority == false) std::cout << "その優先度は有効ではありません" << std::endl;

	std::string priorityStr;
	std::getline(std::cin, priorityStr);
	if (priorityStr == "") return addTodo(allTodo, content, deadlineVec, 0);
	if (priorityStr == "\\back") return addDeadlineToTodo(allTodo, content, true);

	int priority;
	if (priorityStr.size() <= 2 && std::all_of(priorityStr.begin(), priorityStr.end(), [](char c) { return std::isdigit(c); }))
	{
		priority = std::stoi(priorityStr);
		if (priority > 10) return addPriorityToTodo(allTodo, content, deadlineVec, false);
	}
	else
	{
		return addPriorityToTodo(allTodo, content, deadlineVec, false);
	}

	return addTodo(allTodo, content, deadlineVec, priority);
}
void addTodo(std::vector<Todo>& allTodo, std::string content, std::vector<int> deadlineVec, int priority)
{
	std::system("cls");
	std::cout << "ToDo内容　 : " << content << std::endl;
	std::cout << "ToDo締切　 : ";
	if (deadlineVec[0] != 0) std::cout
		<< deadlineVec[0] << "/"
		<< deadlineVec[1] << "/"
		<< deadlineVec[2];
	std::cout << std::endl;
	std::cout << "ToDo優先度 : ";
	for (int i = 0; i < priority; i++) { std::cout << "☆"; }
	std::cout << std::endl;
	std::cout << "\nこのToDoを追加しますか？(y/n) 戻る場合は \\back と入力してください" << std::endl;

	std::string yesOrNo;
	std::getline(std::cin, yesOrNo);

	if (yesOrNo == "y")
	{
		allTodo.emplace_back(content, 0, deadlineVec[0], deadlineVec[1], deadlineVec[2], priority);
		return;
	}
	if (yesOrNo == "n") return;

	if (yesOrNo == "\\back") return addPriorityToTodo(allTodo, content, deadlineVec, true);

	return addTodo(allTodo, content, deadlineVec, priority);
}

void checkTodo(std::vector<Todo>& allTodo, NowTime nowTime)
{
	while (true)
	{
		std::cout << "達成済にするToDoの番号を入力してください(数字) ※戻る場合は \\back と入力してください" << std::endl;
		std::string checkStr;
		std::getline(std::cin, checkStr);

		if (checkStr == "") continue;
		if (checkStr == "\\back") return;
		if (std::all_of(checkStr.begin(), checkStr.end(), [](char c) { return std::isdigit(c); }) == false) continue;

		//ToDoの番号の最大値より桁数の大きい値は初めに除外(極端に大きい値が入力されてstoi()でバグるのを防ぐため)
		int maxDigit = std::floor(std::log10(allTodo.size())) + 1;
		if (checkStr.size() > maxDigit || std::stoi(checkStr) > allTodo.size() || std::stoi(checkStr) == 0)
		{
			std::cout << "その番号のToDoは存在しません" << std::endl;
			continue;
		}
		else if (allTodo[std::stoi(checkStr) - 1].getIsChecked())
		{
			std::cout << "その番号のToDoは既に達成済です" << std::endl;
			continue;
		}

		int checkNum = std::stoi(checkStr);
		while (true)
		{
			std::system("cls");
			showOneTodo(allTodo[checkNum - 1], nowTime);

			std::cout << "\nこのToDoを達成済にしますか？(y/n)" << std::endl;
			std::string yesOrNo;
			std::getline(std::cin, yesOrNo);

			if (yesOrNo == "y")
			{
				allTodo[checkNum - 1].setisChecked(true);
				return;
			}
			if (yesOrNo == "n") return;
		}
	}
}
void checkTodo(std::vector<Todo>& allTodo, NowTime nowTime, std::string checkStr)
{
	int checkNum;
	int maxDigit = std::floor(std::log10(allTodo.size())) + 1;

	if (checkStr.size() > maxDigit)
	{
		std::cout << "その番号のToDoは存在しません" << std::endl;
		std::cout << std::endl;
		std::cout << "Enterを押して終了" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	checkNum = std::stoi(checkStr);

	if (checkNum > allTodo.size() || checkNum == 0)
	{
		std::cout << "その番号のToDoは存在しません" << std::endl;
		std::cout << std::endl;
		std::cout << "Enterを押して終了" << std::endl;
		//Enterを押して文字列を受け取るまでループ dammyは文字列の受け取り先として用意したダミーの文字列
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}
	else if (allTodo[checkNum - 1].getIsChecked())
	{
		std::cout << "その番号のToDoは既に達成済です" << std::endl;
		std::cout << std::endl;
		std::cout << "Enterを押して終了" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	while (true)
	{
		std::system("cls");
		showOneTodo(allTodo[checkNum - 1], nowTime);

		std::cout << "\nこのToDoを達成済にしますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			allTodo[checkNum - 1].setisChecked(true);
			return;
		}
		if (yesOrNo == "n") return;
	}
}
void checkAllTodo(std::vector<Todo>& allTodo, NowTime nowTime)
{
	while (true)
	{
		std::system("cls");
		int digit;
		int maxNum = 0;
		int maxPriority = 0;
		int maxYear = 0;
		int count = 0;
		for (int i = 0; i < allTodo.size(); i++)
		{
			if (allTodo[i].getIsChecked()) continue;
			maxNum = std::max(maxNum, i);
			maxPriority = std::max(maxPriority, allTodo[i].getPriority());
			maxYear = std::max(maxYear, allTodo[i].getYear());
			count++;
		}

		digit = std::floor(std::log10(maxNum)) + 1;

		for (int i = 0; i < allTodo.size(); ++i)
		{
			if (allTodo[i].getIsChecked()) continue;

			std::cout << std::setw(digit) << i + 1 << " : ";
			showTodo(allTodo[i], nowTime, maxYear, maxPriority);
		}

		if (count == 0)
		{
			std::cout << "未達成ToDoがありません" << std::endl;
			std::cout << std::endl;
			std::cout << "Enterを押して終了" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "これら全てのToDoを達成済にしますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			for (int i = 0; i < allTodo.size(); ++i)
			{
				allTodo[i].setisChecked(true);
			}
			return;
		}
		if (yesOrNo == "n") return;
	}
}

void deleteTodo(std::vector<Todo>& allTodo, NowTime nowTime)
{
	while (true)
	{
		std::cout << "消去するToDoの番号を入力してください(数字) ※戻る場合は \\back と入力してください" << std::endl;
		std::string deleteStr;
		std::getline(std::cin, deleteStr);

		if (deleteStr == "") continue;
		if (deleteStr == "\\back") return;
		if (std::all_of(deleteStr.begin(), deleteStr.end(), [](char c) { return std::isdigit(c); }) == false) continue;

		int maxDigit = std::floor(std::log10(allTodo.size())) + 1;
		if (deleteStr.size() > maxDigit || std::stoi(deleteStr) > allTodo.size() || std::stoi(deleteStr) == 0)
		{
			std::cout << "その番号のToDoは存在しません" << std::endl;
			continue;
		}

		int deleteNum = std::stoi(deleteStr);
		while (true)
		{
			std::system("cls");
			showOneTodo(allTodo[deleteNum - 1], nowTime);

			std::cout << "\nこのToDoを消去しますか？(y/n)" << std::endl;
			std::string yesOrNo;
			std::getline(std::cin, yesOrNo);

			if (yesOrNo == "y")
			{
				allTodo.erase(allTodo.begin() + deleteNum - 1);
				return;
			}
			if (yesOrNo == "n") return;
		}

	}
}
void deleteTodo(std::vector<Todo>& allTodo, NowTime nowTime, std::string deleteStr)
{
	int deleteNum;
	int maxDigit = std::floor(std::log10(allTodo.size())) + 1;

	if (deleteStr.size() > maxDigit)
	{
		std::cout << "その番号のToDoは存在しません" << std::endl;
		std::cout << std::endl;
		std::cout << "Enterを押して終了" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	deleteNum = std::stoi(deleteStr);

	if (deleteNum > allTodo.size() || deleteNum == 0)
	{
		std::cout << "その番号のToDoは存在しません" << std::endl;
		std::cout << std::endl;
		std::cout << "Enterを押して終了" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	while (true)
	{
		std::system("cls");
		showOneTodo(allTodo[deleteNum - 1], nowTime);

		std::cout << "\nこのToDoを消去しますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			allTodo.erase(allTodo.begin() + deleteNum - 1);
			return;
		}
		if (yesOrNo == "n") return;
	}
}
void deleteAllTodo(std::vector<Todo>& allTodo)
{
	while (true)
	{
		std::system("cls");
		std::cout << "全てのToDoを消去しますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			allTodo = {};
			return;
		}
		if (yesOrNo == "n") return;
	}
}
void deleteAllCheckedTodo(std::vector<Todo>& allTodo, NowTime nowTime)
{
	while (true)
	{
		std::system("cls");
		int digit;
		int maxNum = 0;
		int maxPriority = 0;
		int maxYear = 0;
		int count = 0;
		for (int i = 0; i < allTodo.size(); i++)
		{
			if (allTodo[i].getIsChecked() == false) continue;
			maxNum = std::max(maxNum, i);
			maxPriority = std::max(maxPriority, allTodo[i].getPriority());
			maxYear = std::max(maxYear, allTodo[i].getYear());
			count++;
		}

		digit = std::floor(std::log10(maxNum)) + 1;

		for (int i = 0; i < allTodo.size(); ++i)
		{
			if (allTodo[i].getIsChecked() == false) continue;

			std::cout << std::setw(digit) << i + 1 << " : ";
			showTodo(allTodo[i], nowTime, maxYear, maxPriority);
		}
		std::cout << std::endl;

		if (count == 0)
		{
			std::cout << "達成済ToDoはありません" << std::endl;
			std::cout << std::endl;
			std::cout << "Enterを押して終了" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "これらのToDoを全て消去しますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			std::erase_if(allTodo, [](Todo x) { return x.getIsChecked(); });
			return;
		}
		if (yesOrNo == "n") return;
	}
}
void deleteAllNotCheckedTodo(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	while (true)
	{
		std::system("cls");
		int digit;
		int maxNum = 0;
		int maxPriority = 0;
		int maxYear = 0;
		int count = 0;
		for (int i = 0; i < allTodo.size(); i++)
		{
			if (allTodo[i].getIsChecked()) continue;
			maxNum = std::max(maxNum, i);
			maxPriority = std::max(maxPriority, allTodo[i].getPriority());
			maxYear = std::max(maxYear, allTodo[i].getYear());
			count++;
		}

		digit = std::floor(std::log10(maxNum)) + 1;

		for (int i = 0; i < allTodo.size(); ++i)
		{
			if (allTodo[i].getIsChecked()) continue;

			std::cout << std::setw(digit) << i + 1 << " : ";
			showTodo(allTodo[i], nowTime, maxYear, maxPriority);
		}

		if (count == 0)
		{
			std::cout << "未達成ToDoはありません" << std::endl;
			std::cout << std::endl;
			std::cout << "Enterを押して終了" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "これらのToDoを全て消去しますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			std::erase_if(allTodo, [](Todo x) { return !x.getIsChecked(); });
			return;
		}
		if (yesOrNo == "n") return;
	}
}
void deleteAllTodoOverDeadline(std::vector<Todo>& allTodo, NowTime& nowTime)
{
	while (true)
	{
		std::system("cls");
		int digit;
		int maxNum = 0;
		int maxPriority = 0;
		int maxYear = 0;
		int count = 0;
		for (int i = 0; i < allTodo.size(); i++)
		{
			if (getIsOverDeadline(allTodo[i], nowTime) == false) continue;
			maxNum = std::max(maxNum, i);
			maxPriority = std::max(maxPriority, allTodo[i].getPriority());
			maxYear = std::max(maxYear, allTodo[i].getYear());
			count++;
		}

		digit = std::floor(std::log10(maxNum)) + 1;

		for (int i = 0; i < allTodo.size(); ++i)
		{
			if (getIsOverDeadline(allTodo[i], nowTime) == false) continue;

			std::cout << std::setw(digit) << i + 1 << " : ";
			showTodo(allTodo[i], nowTime, maxYear, maxPriority);
		}

		if (count == 0)
		{
			std::cout << "締切を過ぎたToDoはありません" << std::endl;
			std::cout << std::endl;
			std::cout << "Enterを押して終了" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "これらのToDoを全て消去しますか？(y/n)" << std::endl;
		std::string yesOrNo;
		std::getline(std::cin, yesOrNo);

		if (yesOrNo == "y")
		{
			std::erase_if(allTodo, [&nowTime](Todo x) { return getIsOverDeadline(x, nowTime); });
			return;
		}
		if (yesOrNo == "n") return;
	}
}

std::vector<Todo> getFromTodo_dataCsv()
{
	std::vector<Todo> allTodo;
	std::ifstream infile("todo_data.csv");
	std::string line;
	std::regex comma(R"(,)");
	while (std::getline(infile, line))
	{
		std::sregex_token_iterator it(line.begin(), line.end(), comma, -1);
		std::sregex_token_iterator end;
		std::vector<std::string> todoData;
		while (it != end)
		{
			if (*it == "")
			{
				it++;
				continue;
			}
			todoData.push_back(*it++);
		}

		if (todoData.size() == 6) allTodo.emplace_back(todoData[0], std::stoi(todoData[1]), std::stoi(todoData[2]), std::stoi(todoData[3]), std::stoi(todoData[4]), std::stoi(todoData[5]));
		else
		{
			std::cout << "ERROR : todo_data.csv に異常があります" << std::endl;
			return allTodo;
		}
	}
	infile.close();
	return allTodo;
}
void writeToTodo_dataCsv(std::vector<Todo>& allTodo)
{
	std::ofstream outfile("todo_data.csv");
	for (int i = 0; i < allTodo.size(); ++i)
	{
		int isCheckedNum = allTodo[i].getIsChecked() ? 1 : 0;
		outfile << allTodo[i].getContent()
			<< "," << isCheckedNum
			<< "," << allTodo[i].getYear()
			<< "," << allTodo[i].getMonth()
			<< "," << allTodo[i].getDay()
			<< "," << allTodo[i].getPriority() << std::endl;
	}
	outfile.close();
}