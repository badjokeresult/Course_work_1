#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
#define Clear cin.clear(), cin.ignore(32767, '\n')
#define Pause system("pause"), system("cls")
using namespace std;
bool CheckString(string a)
{
	int len = 0;
	const char alp[] = " АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < strlen(alp); j++)
		{
			if (a[i] == alp[j]) len++;
		}
	}
	if (len == a.size()) return true;
	else
	{
		cout << "Данная строка должна содержать только буквы русского алфавита и пробелы\n";
		return false;
	}
}
class Subject
{
protected:
	string subject;
	int mark;
public:
	Subject()
	{
		subject = "";
		mark = NULL;
	}
	string GetSubject()
	{
		return subject;
	}
	void SetData()
	{
		do
		{
			Clear;
			cout << "Название предмета: ";
			getline(cin, subject, '\n');
		} while (CheckString(subject) == false);
		cout << "Оценка за предмет (2 - 5) \"" << subject << "\": ";
		cin >> mark;
		while ((mark < 2 || mark > 5) || cin.fail())
		{
			Clear;
			cout << "Оценка за предмет \"" << subject << "\": ";
			cin >> mark;
		}
	}
	double GetMark()
	{
		return mark;
	}
	void PrintData()
	{
		cout << "Предмет: " << subject << endl;
		cout << "Оценка за предмет \"" << subject << "\": " << mark << endl;
	}
};
class Session : public Subject
{
protected:
	int amountOfSubjects;
	Subject* subjectsData;
public:
	Session()
	{
		amountOfSubjects = NULL;
		subjectsData = new Subject;
	}
	bool CheckSub(string s, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (subjectsData[i].GetSubject() == s)
			{
				cout << "В одной сессии не может быть двух одинаковых предметов\n";
				return false;
			}
		}
		return true;
	}
	double GetMark()
	{
		double res = 0.0;
		for (int i = 0; i < amountOfSubjects; i++)
		{
			res += subjectsData[i].GetMark();
		}
		return res;
	}
	void SetData()
	{
		do
		{
			Clear;
			cout << "Кол - во предметов (1 - 10): ";
			cin >> amountOfSubjects;
		} while ((amountOfSubjects < 1 || amountOfSubjects > 10) || cin.fail());
		subjectsData = new Subject[amountOfSubjects];
		for (int i = 0; i < amountOfSubjects; i++)
		{
			do
			{
				subjectsData[i].SetData();
			} while (CheckSub(subjectsData[i].GetSubject(), i) == false);
		}
	}
	void PrintData()
	{
		cout << "Кол - во предметов: " << amountOfSubjects << endl;
		for (int i = 0; i < amountOfSubjects; i++)
		{
			subjectsData[i].PrintData();
		}
	}
	int GetAmountOfSubjects()
	{
		return amountOfSubjects;
	}
};
class Student : public Session
{
	string surname;
	string name;
	string patronym;
	int day, month, year;
	int enterYear;
	string faculty, department;
	string group;
	char sex;
	string id;
	int amountOfSessions;
	Session* sessions;
	double middleMark;
public:
	static int count;
	Student()
	{
		surname = "";
		name = "";
		patronym = "";
		day = 0;
		month = 0;
		year = 0;
		enterYear = 0;
		faculty = "";
		department = "";
		group = "";
		sex = 'M';
		id = "";
		amountOfSessions = NULL;
		sessions = new Session;
		middleMark = 0.0;
	}
	int GetAmountOfSubjects()
	{
		int res = 0;
		for (int i = 0; i < amountOfSessions; i++)
		{
			res += sessions[i].GetAmountOfSubjects();
		}
		return res;
	}
	double GetMark()
	{
		double res = 0.0;
		for (int i = 0; i < amountOfSessions; i++)
		{
			res += sessions[i].GetMark();
		}
		return res;
	}
	bool CheckBirthDate(int d, int m, int y)
	{
		if (y >= 1940 && y <= 2004)
		{
			if (m >= 1 && m <= 12)
			{
				switch (m)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if (d >= 1 && d <= 31) return true;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					if (d >= 1 && d <= 30) return true;
					break;
				case 2:
					if (y % 4 == 0 || y % 100 == 0 || y % 400 == 0)
					{
						if (d >= 1 && d <= 29) return true;
					}
					else
					{
						if (d >= 1 && d <= 28) return true;
					}
					break;
				default:
					cout << "Введена неверная дата\n";
				}
			}
			else cout << "Месяц должен быть от 1 до 12!\n";
		}
		else cout << "Год должен быть от 1940 до 2004\n";
		return false;
	}
	bool CheckId(string iden)
	{
		for (int i = 0; i < count; i++)
		{
			if (this[i].id == iden)
			{
				cout << "Студент с таким номером зачётной книжки уже существует\n";
				return false;
			}
		}
		return true;
	}
	void SetData(int c)
	{
		int local_cnt = count;
		for (int i = local_cnt; i < c + local_cnt; i++)
		{
			cin.ignore();
			cout << "Фамилия: ";
			getline(cin, this[i].surname, '\n');
			while (CheckString(this[i].surname) == false)
			{
				cout << "Повторите ввод: ";
				Clear;
				getline(cin, this[i].surname, '\n');
			}
			cout << "Имя: ";
			getline(cin, this[i].name, '\n');
			while (CheckString(this[i].name) == false)
			{
				cout << "Повторите ввод: ";
				Clear;
				getline(cin, this[i].name, '\n');
			}
			cout << "Отчество: ";
			getline(cin, this[i].patronym, '\n');
			while (CheckString(this[i].patronym) == false)
			{
				cout << "Повторите ввод: ";
				Clear;
				getline(cin, this[i].patronym, '\n');
			}
			do
			{
				cin.ignore(32767, '\n');
				cout << "Пол (М - мужской, Ж - женский): ";
				cin >> this[i].sex;
			} while ((this[i].sex != 'М' && this[i].sex != 'Ж') || cin.fail());
			do
			{
				Clear;
				cout << "Дата рождения (ДД.ММ.ГГГГ) (1940 - 2004): ";
				char sep;
				cin >> this[i].day >> sep >> this[i].month >> sep >> this[i].year;
			} while ((CheckBirthDate(this[i].day, this[i].month, this[i].year) == false) || cin.fail());
			do
			{
				Clear;
				cout << "Год поступления (2000 - 2020): ";
				cin >> this[i].enterYear;
			} while (cin.fail() || (this[i].enterYear < 2000 || this[i].enterYear > 2020) || ((this[i].enterYear - this[i].year) < 15));
			cout << "Факультет: ";
			cin.ignore();
			getline(cin, this[i].faculty, '\n');
			cout << "Кафедра: ";
			getline(cin, this[i].department, '\n');
			do
			{
				cout << "Группа (10 символов): ";
				cin >> this[i].group;
			} while (this[i].group.size() != 10);
			do
			{
				cout << "Номер зачётной книжки (7 символов): ";
				cin >> this[i].id;
			} while (this[i].id.size() != 7 || this->CheckId(this[i].id) == false);
			do
			{
				Clear;
				cout << "Кол - во сессий (1 - 9): ";
				cin >> this[i].amountOfSessions;
			} while ((this[i].amountOfSessions < 1 || this[i].amountOfSessions > 9) || cin.fail());
			this[i].sessions = new Session[this[i].amountOfSessions];
			for (int j = 0; j < this[i].amountOfSessions; j++)
			{
				cout << "Данные о сессии " << j + 1 << ": \n";
				this[i].sessions[j].SetData();
			}
			this[i].middleMark = this[i].GetMark() / this[i].GetAmountOfSubjects();
			count++;
			if (i != c - 1 + local_cnt)
			{
				int actionChoice;
				do
				{
					Clear;
					cout << "Желаете продожить ввод (1 - Да, 2 - Нет): ";
					cin >> actionChoice;
				} while (cin.fail() || (actionChoice != 1 && actionChoice != 2));
				if (actionChoice == 2) break;
			}
		}
	}
	void ChangeData()
	{
		if (count == 0) cout << "База данных пуста\n";
		else
		{
			string iden;
			do
			{
				cout << "Введите номер зачётной книжки студента (7 символов): ";
				Clear;
				cin >> iden;
			} while (cin.fail() || iden.size() != 7);
			int choice;
			bool state = false;
			for (int i = 0; i < count; i++)
			{
				if (this[i].id == iden)
				{
					state = true;
					for (; 1;)
					{
						cout << "Выберите информацию для изменения:\n1. Фамилия\n2. Имя\n3. Отчество\n4. Дата рождения\n5. Пол\n6. Группа\n7. Факультет\n8. Кафедра\n9. Данные о сессиях\n10. Номер зачётной книжки\n11. Год поступления\n12. Выход из меню изменения данных\n";
						do
						{
							Clear;
							cin >> choice;
						} while (cin.fail());
						switch (choice)
						{
						case 1:
							do
							{
								Clear;
								cout << "Фамилия: ";
								cin >> this[i].surname;
							} while (cin.fail() || CheckString(this[i].surname) == false);
							break;
						case 2:
							do
							{
								Clear;
								cout << "Имя: ";
								cin >> this[i].name;
							} while (cin.fail() || CheckString(this[i].name) == false);
							break;
						case 3:
							do
							{
								Clear;
								cout << "Отчество: ";
								cin >> this[i].patronym;
							} while (cin.fail() || CheckString(this[i].patronym) == false);
							break;
						case 4:
							do
							{
								Clear;
								cout << "Дата рождения (ДД.ММ.ГГГГ) (Год рождения не раньше 1940 и не позже 2004): ";
								char sep;
								cin >> this[i].day >> sep >> this[i].month >> sep >> this[i].year;
							} while ((CheckBirthDate(this[i].day, this[i].month, this[i].year) == false) || (cin.fail()) || (this[i].enterYear - this[i].year) < 15);
							break;
						case 5:
							do
							{
								Clear;
								cout << "Пол (М - мужской, Ж - женский): ";
								cin >> this[i].sex;
							} while ((this[i].sex != 'М' && this[i].sex != 'Ж') || cin.fail());
							break;
						case 6:
							do
							{
								Clear;
								cout << "Группа (10 символов): ";
								cin >> this[i].group;
							} while (this[i].group.size() != 10);
							break;
						case 7:
							cin.ignore();
							cout << "Факультет: ";
							getline(cin, this[i].faculty, '\n');
							break;
						case 8:
							cin.ignore();
							cout << "Кафедра: ";
							getline(cin, this[i].department, '\n');
							break;
						case 9:
							do
							{
								Clear;
								cout << "Введите новые данные о сессиях:\nВведите кол - во сессий (1 - 9): ";
								cin >> this[i].amountOfSessions;
							} while (this[i].amountOfSessions < 1 || this[i].amountOfSessions > 9 || cin.fail());
							for (int j = 0; j < this[i].amountOfSessions; j++)
							{
								cout << "Сессия " << j + 1 << ":\n";
								this[i].sessions[j].SetData();
							}
							this[i].middleMark = this[i].GetMark() / this[i].GetAmountOfSubjects();
							break;
						case 10:
							do
							{
								Clear;
								cout << "Введите номер зачётной книжки (7 символов): ";
								cin >> this[i].id;
							} while (this[i].id.size() != 7 || cin.fail());
							break;
						case 11:
							cout << "Год поступления (2000 - 2020): ";
							cin >> this[i].enterYear;
							while ((this[i].enterYear < 2000 || this[i].enterYear > 2020) || cin.fail() || (this[i].enterYear - this[i].year) < 15)
							{
								Clear;
								cout << "Повторите ввод: ";
								cin >> this[i].enterYear;
							}
							break;
						case 12:
							return;
						default:
							cout << "Введите корректный пункт меню!\n";
						}
					}
				}
			}
			if (state == false) cout << "Не найдено студента с данным номером зачётной книжки\n";
		}
	}
	Student* DeleteData()
	{
		if (count == 0)
		{
			cout << "База данных пуста\n";
			return this;
		}
		else
		{
			Student* arr = new Student[count - 1];
			string iden;
			do
			{
				cin.ignore();
				cout << "Введите номер зачётной книжки студента (7 символов): ";
				cin >> iden;
			} while (iden.size() != 7);
			for (int i = 0; i < count; i++)
			{
				if (this[i].id == iden)
				{
					for (int j = i; j + 1 < count; j++)
					{
						this[j] = this[j + 1];
					}
				}
			}
			count--;
			cout << "Данные для студента с номером зачётной книжки " << iden << " удалены\n";
			for (int i = 0; i < count; i++)
			{
				arr[i] = this[i];
			}
			return arr;
		}
	}
	void CourseVariant()
	{
		if (count == 0)
		{
			cout << "База данных пуста\n";
			Pause;
		}
		else
		{
			double general_middle = 0.0;
			int local_cnt = 0;
			char gen;
			do
			{
				Clear;
				cout << "Введите пол (М - мужской, Ж - женский): ";
				cin >> gen;
			} while (gen != 'М' && gen != 'Ж');
			int best_cnt = 0; int worst_cnt = 0;
			for (int i = 0; i < count; i++)
			{
				if (this[i].sex == gen)
				{
					local_cnt++;
					general_middle += this[i].middleMark;
				}
			}
			if (local_cnt == 0)
			{
				cout << "В базе данных отсутствуют студенты с выбранным полом\n";
				return;
			}
			Student* best = new Student[local_cnt];
			Student* worst = new Student[local_cnt];
			general_middle /= local_cnt;
			for (int i = 0; i < count; i++)
			{
				if (this[i].sex == gen)
				{
					if (this[i].middleMark >= general_middle)
					{
						best[best_cnt] = this[i];
						best_cnt++;
					}
					else if (this[i].middleMark < general_middle)
					{
						worst[worst_cnt] = this[i];
						worst_cnt++;
					}
				}
			}
			if (best_cnt == 0 && worst_cnt == 0) cout << "Не найдено студентов!\n";
			else
			{
				if (best_cnt != 0)
				{
					cout << endl << "Наиболее успевающие студенты:" << endl;
					for (int i = 0; i < best_cnt; i++)
					{
						cout << i + 1 << ". ";
						best->PrintData(best[i].id);
						cout << "Средний балл за все сессии: " << best[i].middleMark << endl;
						cout << endl;
					}
				}
				else cout << "Не найдено наиболее успевающих студентов, принадлежащих полу " << gen << endl;
				if (worst_cnt != 0)
				{
					cout << endl << "Наименее успевающие студенты:" << endl;
					for (int i = 0; i < worst_cnt; i++)
					{
						cout << i + 1 << ". ";
						worst->PrintData(worst[i].id);
						cout << "Средний балл за все сессии: " << worst[i].middleMark << endl;
						cout << endl;
					}
				}
				else cout << "Не найдено наименее успевающих студентов, принадлежащих полу " << gen << endl;
				cout << endl;
				system("pause");
				delete[]best;
				delete[]worst;
				system("cls");
			}
		}
	}
	void PrintData(string iden = "")
	{
		if (count == 0) cout << "База данных пуста\n";
		else
		{
			if (iden == "")
			{
				cout << endl;
				for (int i = 0; i < count; i++)
				{
					cout << "ФИО: " << this[i].surname << " " << this[i].name << " " << this[i].patronym << endl;
					cout << "Пол: " << this[i].sex << endl;
					cout << "Дата рождения: " << this[i].day << "." << this[i].month << "." << this[i].year << endl;
					cout << "Год поступления: " << this[i].enterYear << endl;
					cout << "Факультет: " << this[i].faculty << endl;
					cout << "Кафедра: " << this[i].department << endl;
					cout << "Группа: " << this[i].group << endl;
					cout << "Номер зачётной книжки: " << this[i].id << endl;
					cout << "Кол - во сессий: " << this[i].amountOfSessions << endl;
					for (int j = 0; j < this[i].amountOfSessions; j++)
					{
						cout << "Данные о сессии " << j + 1 << ":\n";
						this[i].sessions[j].PrintData();
					}
					cout << endl;
				}
			}
			else
			{
				bool state = false;
				for (int i = 0; i < count; i++)
				{
					if (this[i].id == iden)
					{
						state = true;
						cout << "ФИО: " << this[i].surname << " " << this[i].name << " " << this[i].patronym << endl;
						cout << "Пол: " << this[i].sex << endl;
						cout << "Дата рождения: " << this[i].day << "." << this[i].month << "." << this[i].year << endl;
						cout << "Год поступления: " << this[i].enterYear << endl;
						cout << "Факультет: " << this[i].faculty << endl;
						cout << "Кафедра: " << this[i].department << endl;
						cout << "Группа: " << this[i].group << endl;
						cout << "Номер зачётной книжки: " << this[i].id << endl;
						cout << "Кол - во сессий: " << this[i].amountOfSessions << endl;
						for (int j = 0; j < this[i].amountOfSessions; j++)
						{
							cout << "Данные о сессии " << j + 1 << ":\n";
							this[i].sessions[j].PrintData();
						}
						cout << endl;
					}
				}
				if (state == false) cout << "Студента с введённым номером зачётной книжки не найдено\n";
			}
		}
	}
	Student* AddMemory(int b)
	{
		Student* arr = new Student[count + b];
		for (int i = 0; i < count; i++)
		{
			arr[i] = this[i];
		}
		return arr;
	}
	~Student()
	{
		if (surname != "") cout << "Данные для студента \"" << surname << " " << name << " " << patronym << "\" удалены\n";
	}
	string GetId()
	{
		return id;
	}
};
int Student::count = 0;
char m1[] = { "1. Добавление данных о студентах\n" };
char m2[] = { "2. Изменение данных о студенте по номеру зачётной книжки\n" };
char m3[] = { "3. Удаление данных о студенте по номеру зачётной книжки\n" };
char m4[] = { "4. Вывод наиболее и наименее успевающих студентов с поиском по полу\n" };
char m5[] = { "5. Вывод на печать данных обо всех студентах\n" };
char m6[] = { "6. Вывод на печать данных об одном студенте по номеру зачётной книжки\n" };
char m7[] = { "7. Выход из программы\n" };
char* menu[] = { m1,m2,m3,m4,m5,m6, m7 };
int func_menu(char* a[])
{
	int q;
	for (int i = 0; i < 7; i++)
	{
		cout << a[i];
	}
	cout << "Введите цифру от 1 до 7: ";
	cin >> q;
	while (cin.fail() || q < 1 || q > 7)
	{
		Clear;
		cout << "Повторите ввод: ";
		cin >> q;
	}
	return q;
}
int main()
{
	system("chcp 1251>nul");
	Student* students = new Student[1];
	ofstream inputFile;
	ifstream outputFile;
	string iden;
	for (; 1;)
	{
		switch (func_menu(menu))
		{
		case 1:
			int amountOfStudents;
			cout << "Введите кол - во студентов для заполнения: ";
			cin >> amountOfStudents;
			while (cin.fail() || amountOfStudents < 1)
			{
				Clear;
				cin >> amountOfStudents;
			}
			students = students->AddMemory(amountOfStudents);
			students->SetData(amountOfStudents);
			Pause;
			inputFile.open("DataBase.bin", ios::trunc | ios::binary);
			inputFile.write((char*)&students, sizeof(students));
			inputFile.close();
			break;
		case 2:
			students->ChangeData();
			Pause;
			inputFile.open("DataBase.bin", ios::trunc | ios::binary);
			inputFile.write((char*)&students, sizeof(students));
			inputFile.close();
			break;
		case 3:
			students = students->DeleteData();
			Pause;
			inputFile.open("DataBase.bin", ios::trunc | ios::binary);
			inputFile.write((char*)&students, sizeof(students));
			inputFile.close();
			break;
		case 4:
			outputFile.open("DataBase.bin", ios::binary);
			outputFile.read((char*)&students, sizeof(students));
			outputFile.close();
			students->CourseVariant();
			break;
		case 5:
			outputFile.open("DataBase.bin", ios::binary);
			outputFile.read((char*)&students, sizeof(students));
			outputFile.close();
			students->PrintData();
			Pause;
			break;
		case 6:
			outputFile.open("DataBase.bin", ios::binary);
			outputFile.read((char*)&students, sizeof(students));
			outputFile.close();
			if (students->count == 0) cout << "База данных пуста\n";
			else
			{
				do
				{
					cin.ignore();
					cout << "Введите номер зачётной книжки студента (7 символов): ";
					cin >> iden;
				} while (iden.size() != 7);
				students->PrintData(iden);
			}
			Pause;
			break;
		case 7:
			delete[]students;
			cout << "Программа завершается...\n";
			system("pause");
			exit(1);
		default:
			cout << "Повторите ввод!\n";
		}
	}
}
