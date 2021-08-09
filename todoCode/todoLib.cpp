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
	std::cout << "�R�}���h�ꗗ ���啶���������͋�ʂ��Ȃ�, ->�́u �v(���p�X�y�[�X)�ő�p��" << std::endl;
	std::cout << "list" << "\t\t\t\t:" << "ToDo���X�g���̑S�Ă�ToDo��\������" << std::endl;
	std::cout << "list->checked" << "\t\t\t:" << "ToDo���X�g���̑S�Ă̒B����ToDo��\������" << std::endl;
	std::cout << "    ->notchecked" << "\t\t:" << "ToDo���X�g���̑S�Ă̖��B��ToDo��\������" << std::endl;
	std::cout << "    ->deadline" << "\t\t\t:" << "ToDo���X�g���̑S�Ă̒��ؕt��ToDo��\������" << std::endl;
	std::cout << "    ->nodeadline" << "\t\t:" << "ToDo���X�g���̑S�Ă̒��؂Ȃ�ToDo��\������" << std::endl;
	std::cout << "    ->priority" << "\t\t\t:" << "ToDo���X�g���̑S�Ă̗D��x(���}�[�N)�t��ToDo��\������" << std::endl;
	std::cout << "    ->overdeadline(�܂���over)" << "\t:" << "ToDo���X�g���̑S�Ă̒��؂��߂������B��ToDo��\������" << std::endl;
	std::cout << std::endl;
	std::cout << "add" << "\t\t\t\t:" << "ToDo���X�g��ToDo��ǉ�����" << std::endl;
	std::cout << std::endl;
	std::cout << "check" << "\t\t\t\t:" << "�I��ToDo��B���ς̏�Ԃɂ���" << std::endl;
	std::cout << "check->(ToDo�̔ԍ�)" << "\t\t:(ToDo�̔ԍ�)��ToDo��B���ς̏�Ԃɂ���" << std::endl;
	std::cout << "     ->all" << "\t\t\t:" << "�S�Ă̖��B��ToDo��B���ς̏�Ԃɂ���" << std::endl;
	std::cout << std::endl;
	std::cout << "delete(�܂���del)" << "\t\t:" << "�I��ToDo����������" << std::endl;
	std::cout << "delete->(ToDo�̔ԍ�)" << "\t\t:" << "(ToDo�̔ԍ�)��ToDo����������" << std::endl;
	std::cout << "      ->all" << "\t\t\t:" << "�S�Ă�ToDo����������" << std::endl;
	std::cout << "      ->checked" << "\t\t\t:" << "�S�Ă̖��B��ToDo����������" << std::endl;
	std::cout << "      ->notchecked" << "\t\t:" << "�S�Ă̒B���ς�ToDo����������" << std::endl;
	std::cout << "      ->overdeadline" << "\t\t:" << "�S�Ă̒��؂��߂������B��ToDo����������" << std::endl;
	std::cout << std::endl;
	std::cout << "exit" << "\t\t\t\t:" << "�v���O�������I������" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter�������ďI��" << std::endl;
	std::string dammy;
	while (!std::getline(std::cin, dammy)) {}
}

void todoSort(std::vector<Todo>& allTodo)
{
	//���B�����D��x���傫����������̑傫���� �ŕ��Ԃ悤�Ƀ\�[�g
	std::stable_sort(allTodo.begin(), allTodo.end(), [](Todo a, Todo b) {return a.getContent() > b.getContent(); });
	std::stable_sort(allTodo.begin(), allTodo.end(), [](Todo a, Todo b) {return a.getPriority() > b.getPriority(); });
	std::stable_sort(allTodo.begin(), allTodo.end(), [](Todo a, Todo b) {return !a.getIsChecked() > !b.getIsChecked(); });

	int checkedNum = 0;
	for (int i = 0; i < allTodo.size(); ++i)
	{
		if (allTodo[i].getIsChecked() == false) checkedNum++;
	}

	//���B����ToDo�����؂̑������ɕ��Ԃ悤�Ƀ\�[�g
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

	//�B���ς�ToDo�����؂̑������ɕ��Ԃ悤�Ƀ\�[�g
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
	//maxYear : �\������ToDo�̒��ؔN�̍ő�l(0�̏ꍇ, ���؂�����ToDo�͕\�����Ȃ����Ƃ��Ӗ�����)
	//maxPriority : �\������ToDo�̗D��x�̍ő�l(0�̏ꍇ, �D��x������ToDo�͕\�����Ȃ����Ƃ��Ӗ�����)
	if (todo.getIsChecked()) std::cout << "��" << " : ";
	else if (getIsOverDeadline(todo, nowTime)) std::cout << "�~" << " : ";
	else std::cout << "�@" << " : ";

	if (todo.getYear() != 0)
	{
		for (int i = 0; i < 3 - std::log10(todo.getYear()); ++i) std::cout << 0;
		std::cout << todo.getYear() << "/";
		if (todo.getMonth() < 10) std::cout << 0 << todo.getMonth() << "/";
		else std::cout << todo.getMonth() << "/";
		if (todo.getDay() < 10) std::cout << 0 << todo.getDay();
		else std::cout << todo.getDay();
		std::cout << " ����";
	}
	//���؂�����ToDo��1�ȏ゠��ꍇ, �\���𐮂��邽��, ����ɍ��킹�邽�ߋ󔒂�}��
	else if (maxYear > 0) std::cout << std::setw(18);
	if (maxYear > 0) std::cout << " : ";

	//�\���𐮂��邽��, �ő�̗D��x�ɍ��킹�ċ󔒂�}��
	if (maxPriority > 0) for (int j = 0; j < maxPriority - todo.getPriority(); j++) { std::cout << "�@"; }
	if (todo.getPriority() != 0) for (int j = 0; j < todo.getPriority(); j++) { std::cout << "��"; }
	if (maxPriority > 0) std::cout << " : ";

	std::cout << todo.getContent() << std::endl;
}
void showOneTodo(Todo& todo, NowTime& nowTime)
{
	std::cout << "ToDo���e�@ : " << todo.getContent() << std::endl;
	std::cout << "ToDo���؁@ : ";
	if (todo.getYear() != 0) std::cout
		<< todo.getYear() << "/"
		<< todo.getMonth() << "/"
		<< todo.getDay();
	std::cout << std::endl;
	std::cout << "ToDo�D��x : ";
	for (int i = 0; i < todo.getPriority(); i++) { std::cout << "��"; }
	std::cout << std::endl;
	std::cout << "�B���󋵁@ : ";
	if (todo.getIsChecked()) std::cout << "�B����";
	else
	{
		std::cout << "���B��";
		if (getIsOverDeadline(todo, nowTime)) std::cout << "\n������ToDo�͊��ɒ��؂��߂��Ă��܂�";
	}
	std::cout << std::endl;
}

void listingTodo(std::vector<Todo>& allTodo, NowTime& nowTime, int n)
{
	std::system("cls");
	int listSize = n;
	if (allTodo.size() < n) listSize = allTodo.size();

	//listSize�̌���
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
		std::cout << "�{���� "
			<< nowTime.getYear() << "�N"
			<< nowTime.getMonth() << "��"
			<< nowTime.getDay() << "��" << std::endl;

		int overDeadlineNum = getNumberOfTodoOverDeadline(allTodo, nowTime);
		if (overDeadlineNum > 0) std::cout << "���؂��߂���ToDo�� " << overDeadlineNum << "�� ����܂�" << std::endl;
		std::cout << std::endl;
	}
	std::cout << "ToDo�ꗗ" << std::endl;
	for (int i = 0; i < listSize; i++)
	{
		//ToDo�\���ԍ��̍ő包���ɍ��킹�ċ󔒂�}��
		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (allTodo.size() > listSize) std::cout << "���̑� " << allTodo.size() - n << "�� ��ToDo������܂�" << std::endl;
	if (allTodo.size() == 0) std::cout << "ToDo�͂���܂���" << std::endl;
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

	std::cout << "�B����ToDo�ꗗ" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//���B���̏ꍇ�͔�΂�
		if (allTodo[i].getIsChecked() == false) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (count == 0) std::cout << "�B����ToDo�͂���܂���" << std::endl;
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

	std::cout << "���B��ToDo�ꗗ" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//�B���ς̏ꍇ�͔�΂�
		if (allTodo[i].getIsChecked()) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (count == 0) std::cout << "���B��ToDo�͂���܂���" << std::endl;
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

	std::cout << "���ؕt��ToDo�ꗗ" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//���؂������ꍇ�͔�΂�
		if (allTodo[i].getYear() == 0) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, 1, maxPriority);
	}
	if (count == 0) std::cout << "���ؕt��ToDo�͂���܂���" << std::endl;
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

	std::cout << "���؂Ȃ�ToDo�ꗗ" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//���؂�����ꍇ�͔�΂�
		if (allTodo[i].getYear() != 0) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, 0, maxPriority);
	}
	if (count == 0) std::cout << "���؂Ȃ�ToDo�͂���܂���" << std::endl;
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

	std::cout << "�D��x�t��ToDo�ꗗ" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//�D��x�������ꍇ�͔�΂�
		if (allTodo[i].getPriority() == 0) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, maxYear, maxPriority);
	}
	if (count == 0) std::cout << "�D��x�t��ToDo�͂���܂���" << std::endl;
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

	std::cout << "���؂��߂���ToDo�ꗗ" << std::endl;
	for (int i = 0; i < allTodo.size(); i++)
	{
		//���؂��߂��Ă��Ȃ��ꍇ�͔�΂�
		if (getIsOverDeadline(allTodo[i], nowTime) == false) continue;

		std::cout << std::setw(digit) << i + 1 << " : ";
		showTodo(allTodo[i], nowTime, 1, maxPriority);
	}
	if (count == 0) std::cout << "���؂��߂���ToDo�͂���܂���" << std::endl;
}

void addContentToTodo(std::vector<Todo>& allTodo)
{
	std::system("cls");
	std::cout << "�ǉ�����ToDo�̓��e����͂��Ă������� ���߂�ꍇ�� \\back �Ɠ��͂��Ă�������" << std::endl;

	std::string content;
	std::getline(std::cin, content);
	if (content == "") return addContentToTodo(allTodo);
	if (content == "\\back") return;

	return addDeadlineToTodo(allTodo, content, true);
}
void addDeadlineToTodo(std::vector<Todo>& allTodo, std::string content, bool isValidDeadline)
{
	std::system("cls");
	std::cout << "ToDo���e : " << content << std::endl;
	std::cout << "ToDo�̒��؂���͂��Ă�������(�N/��/��) ���w�肵�Ȃ��ꍇ�͂��̂܂�Enter, �߂�ꍇ�� \\back �Ɠ��͂��Ă�������" << std::endl;
	if (isValidDeadline == false) std::cout << "���̓��t�͗L���ł͂���܂���" << std::endl;

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
	//������� / �ŕ�������@
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
	//���͂������t���L���ȓ��t���ǂ����𔻒肷��
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
	std::cout << "ToDo���e�@ : " << content << std::endl;
	std::cout << "ToDo���؁@ : ";
	if (deadlineVec[0] != 0) std::cout
		<< deadlineVec[0] << "/"
		<< deadlineVec[1] << "/"
		<< deadlineVec[2];
	std::cout << std::endl;
	std::cout << "ToDo�̗D��x����͂��Ă�������(���� �ő�10) ���w�肵�Ȃ��ꍇ�͂��̂܂�Enter, �߂�ꍇ�� \\back �Ɠ��͂��Ă�������" << std::endl;
	if (isValidPriority == false) std::cout << "���̗D��x�͗L���ł͂���܂���" << std::endl;

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
	std::cout << "ToDo���e�@ : " << content << std::endl;
	std::cout << "ToDo���؁@ : ";
	if (deadlineVec[0] != 0) std::cout
		<< deadlineVec[0] << "/"
		<< deadlineVec[1] << "/"
		<< deadlineVec[2];
	std::cout << std::endl;
	std::cout << "ToDo�D��x : ";
	for (int i = 0; i < priority; i++) { std::cout << "��"; }
	std::cout << std::endl;
	std::cout << "\n����ToDo��ǉ����܂����H(y/n) �߂�ꍇ�� \\back �Ɠ��͂��Ă�������" << std::endl;

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
		std::cout << "�B���ςɂ���ToDo�̔ԍ�����͂��Ă�������(����) ���߂�ꍇ�� \\back �Ɠ��͂��Ă�������" << std::endl;
		std::string checkStr;
		std::getline(std::cin, checkStr);

		if (checkStr == "") continue;
		if (checkStr == "\\back") return;
		if (std::all_of(checkStr.begin(), checkStr.end(), [](char c) { return std::isdigit(c); }) == false) continue;

		//ToDo�̔ԍ��̍ő�l��茅���̑傫���l�͏��߂ɏ��O(�ɒ[�ɑ傫���l�����͂����stoi()�Ńo�O��̂�h������)
		int maxDigit = std::floor(std::log10(allTodo.size())) + 1;
		if (checkStr.size() > maxDigit || std::stoi(checkStr) > allTodo.size() || std::stoi(checkStr) == 0)
		{
			std::cout << "���̔ԍ���ToDo�͑��݂��܂���" << std::endl;
			continue;
		}
		else if (allTodo[std::stoi(checkStr) - 1].getIsChecked())
		{
			std::cout << "���̔ԍ���ToDo�͊��ɒB���ςł�" << std::endl;
			continue;
		}

		int checkNum = std::stoi(checkStr);
		while (true)
		{
			std::system("cls");
			showOneTodo(allTodo[checkNum - 1], nowTime);

			std::cout << "\n����ToDo��B���ςɂ��܂����H(y/n)" << std::endl;
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
		std::cout << "���̔ԍ���ToDo�͑��݂��܂���" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter�������ďI��" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	checkNum = std::stoi(checkStr);

	if (checkNum > allTodo.size() || checkNum == 0)
	{
		std::cout << "���̔ԍ���ToDo�͑��݂��܂���" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter�������ďI��" << std::endl;
		//Enter�������ĕ�������󂯎��܂Ń��[�v dammy�͕�����̎󂯎���Ƃ��ėp�ӂ����_�~�[�̕�����
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}
	else if (allTodo[checkNum - 1].getIsChecked())
	{
		std::cout << "���̔ԍ���ToDo�͊��ɒB���ςł�" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter�������ďI��" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	while (true)
	{
		std::system("cls");
		showOneTodo(allTodo[checkNum - 1], nowTime);

		std::cout << "\n����ToDo��B���ςɂ��܂����H(y/n)" << std::endl;
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
			std::cout << "���B��ToDo������܂���" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter�������ďI��" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "�����S�Ă�ToDo��B���ςɂ��܂����H(y/n)" << std::endl;
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
		std::cout << "��������ToDo�̔ԍ�����͂��Ă�������(����) ���߂�ꍇ�� \\back �Ɠ��͂��Ă�������" << std::endl;
		std::string deleteStr;
		std::getline(std::cin, deleteStr);

		if (deleteStr == "") continue;
		if (deleteStr == "\\back") return;
		if (std::all_of(deleteStr.begin(), deleteStr.end(), [](char c) { return std::isdigit(c); }) == false) continue;

		int maxDigit = std::floor(std::log10(allTodo.size())) + 1;
		if (deleteStr.size() > maxDigit || std::stoi(deleteStr) > allTodo.size() || std::stoi(deleteStr) == 0)
		{
			std::cout << "���̔ԍ���ToDo�͑��݂��܂���" << std::endl;
			continue;
		}

		int deleteNum = std::stoi(deleteStr);
		while (true)
		{
			std::system("cls");
			showOneTodo(allTodo[deleteNum - 1], nowTime);

			std::cout << "\n����ToDo���������܂����H(y/n)" << std::endl;
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
		std::cout << "���̔ԍ���ToDo�͑��݂��܂���" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter�������ďI��" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	deleteNum = std::stoi(deleteStr);

	if (deleteNum > allTodo.size() || deleteNum == 0)
	{
		std::cout << "���̔ԍ���ToDo�͑��݂��܂���" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter�������ďI��" << std::endl;
		std::string dammy;
		while (!std::getline(std::cin, dammy)) {}
		return;
	}

	while (true)
	{
		std::system("cls");
		showOneTodo(allTodo[deleteNum - 1], nowTime);

		std::cout << "\n����ToDo���������܂����H(y/n)" << std::endl;
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
		std::cout << "�S�Ă�ToDo���������܂����H(y/n)" << std::endl;
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
			std::cout << "�B����ToDo�͂���܂���" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter�������ďI��" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "������ToDo��S�ď������܂����H(y/n)" << std::endl;
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
			std::cout << "���B��ToDo�͂���܂���" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter�������ďI��" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "������ToDo��S�ď������܂����H(y/n)" << std::endl;
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
			std::cout << "���؂��߂���ToDo�͂���܂���" << std::endl;
			std::cout << std::endl;
			std::cout << "Enter�������ďI��" << std::endl;
			std::string dammy;
			while (!std::getline(std::cin, dammy)) {}
			return;
		}

		std::cout << std::endl;
		std::cout << "������ToDo��S�ď������܂����H(y/n)" << std::endl;
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
			std::cout << "ERROR : todo_data.csv �Ɉُ킪����܂�" << std::endl;
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