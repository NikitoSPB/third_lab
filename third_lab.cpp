#include <iostream>
#include <string>

using namespace std;

struct Numbers
{
	string valueNumber;
	Numbers* next1 = NULL;
};
Numbers* headNumbers = NULL;

struct Signs
{
	char sign;
	int priority = 0;
	Signs* next2 = NULL;
};
Signs* headSigns = NULL;

int PriorityOperation(char POSign)
{
	switch (POSign) {
	case '(':
		return 1;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	default:
		return 0;
	}
}

void newExample(string* nExample)
{
	cout << "Enter example:\n";
	getline(cin, *nExample, '\n');
}

int correctExample(string* cExample)
{
	int lengthExample = (*cExample).length();
	int countBracket = 0, flag = 0; // 1 - number, 2 - sign, 3 - open, 4 - close
	for (int i = 0; i < lengthExample; i++)
	{
		if ((i < lengthExample - 1) && ((*cExample)[i] == '/' && (*cExample)[i + 1] == '0'))
			return 0;
		if ((*cExample)[i] == ' ') //spaces
		{
			(*cExample).erase(i, 1);
			i--;
			lengthExample--;
			continue;
		}
		if (((*cExample)[i] >= 'A' && (*cExample)[i] <= 'Z') || ((*cExample)[i] >= 'a' && (*cExample)[i] <= 'z')) //variables
		{
			if (flag == 1 || flag == 4)
				return 0;
			string nameVariable, valueVariable;
			int cEi = 1;
			while ((i + cEi < lengthExample) && (((*cExample)[i + cEi] >= 'A' && (*cExample)[i + cEi] <= 'Z') || ((*cExample)[i + cEi] >= 'a' && (*cExample)[i + cEi] <= 'z')))
				cEi++;
			nameVariable = (*cExample).substr(i, cEi);
			cout << "Input value of variable\n" << nameVariable << " = ";
			cin >> valueVariable;
			(*cExample).erase(i, cEi);
			(*cExample).insert(i, valueVariable);
			(*cExample).insert(i + valueVariable.length(), " ");
			lengthExample = lengthExample - cEi + valueVariable.length() + 1;
			i--;
			continue;
		}
		if ((*cExample)[i] >= '0' && (*cExample)[i] <= '9') //numbers
		{
			if (flag == 1 || flag == 4)
				return 0;
			i++;
			while ((i < lengthExample) && (*cExample)[i] >= '0' && (*cExample)[i] <= '9')
				i++;
			flag = 1;
			i--;
			continue;
		}
		if ((*cExample)[i] == '+' || (*cExample)[i] == '-' || (*cExample)[i] == '*' || (*cExample)[i] == '/') //signs
		{
			if (flag != 1 && flag != 4)
				return 0;
			flag = 2;
			continue;
		}
		if ((*cExample)[i] == '(') // open brackets
		{
			if (flag == 1 || flag == 4)
				return 0;
			countBracket++;
			flag = 3;
			continue;
		}
		if ((*cExample)[i] == ')') // close brackets
		{
			countBracket--;
			if ((flag != 1 && flag != 3 && flag != 4) || countBracket < 0)
				return 0;
			flag = 4;
			continue;
		}
		return 0;
	}
	for (int i = 0; i < lengthExample; i++)
	{
		if ((*cExample)[i] == '(' && (*cExample)[i + 1] == ')')
		{
			if (i == 0 || (*cExample)[i - 1] == '(')
			{
				(*cExample).erase(i, 2);
				i--;
				lengthExample -= 2;
			}
			else
			{
				(*cExample).erase(i - 1, 3);
				i -= 2;
				lengthExample -= 3;
			}
		}
	}
	if ((flag != 1 && flag != 4) || countBracket != 0)
		return 0;
	return 1;
}

void addNum(string addNumber)
{
	Numbers* newNumber = new Numbers;
	newNumber->valueNumber = addNumber;
	if (headNumbers != NULL)
		newNumber->next1 = headNumbers;
	headNumbers = newNumber;
}

void addSig(char addSign, int addPriority)
{
	Signs* newSign = new Signs;
	newSign->sign = addSign;
	newSign->priority = addPriority;
	if (headSigns != NULL)
		newSign->next2 = headSigns;
	headSigns = newSign;
}

string popNum()
{
	if (headNumbers == NULL)
	{
		cout << "Error. Numbers is over\n";
		system("Pause");
		return "Error";
	}
	string popNumber = headNumbers->valueNumber;
	Numbers* temp = headNumbers->next1;
	headNumbers->next1 = NULL;
	delete headNumbers;
	headNumbers = temp;
	return popNumber;
}

char popSig()
{
	if (headSigns == NULL)
	{
		cout << "Error. Signs is over\n";
		system("Pause");
		return 'E';
	}
	char popSign = headSigns->sign;
	Signs* temp = headSigns->next2;
	headSigns->next2 = NULL;
	delete headSigns;
	headSigns = temp;
	return popSign;
}

string createPPN(string* cPPNExample)
{
	string cPPN;
	int cLengthExample = (*cPPNExample).length();
	int priority2 = 0, prioritySum = 0, prioritySign = 0;
	for (int i = cLengthExample - 1; i >= 0; i--)
	{
		if ((i >= 0) && (*cPPNExample)[i] == ')')
			priority2 += PriorityOperation((*cPPNExample)[i]);
		else if ((i >= 0) &&(*cPPNExample)[i] == '(')
			priority2 -= PriorityOperation((*cPPNExample)[i]);
		else if ((i >= 0) && (*cPPNExample)[i] >= '0' && (*cPPNExample)[i] <= '9')
		{
			int j = 1;
			string stringNumber;
			stringNumber = (*cPPNExample)[i];
			i--;
			while (i >= 0 && (*cPPNExample)[i] >= '0' && (*cPPNExample)[i] <= '9')
			{
				stringNumber = (*cPPNExample)[i] + stringNumber;
				i--;
				j++;
			}
			addNum(stringNumber);
			cout << "Number " << stringNumber << " put in Notation.\n";
			i++;
		}
		else if ((*cPPNExample)[i] == '+' || (*cPPNExample)[i] == '-' || (*cPPNExample)[i] == '*' || (*cPPNExample)[i] == '/')
		{
			prioritySign = PriorityOperation((*cPPNExample)[i]);
			prioritySum = priority2 + prioritySign;
			if (headSigns == NULL || prioritySum >= headSigns->priority)
			{
				addSig((*cPPNExample)[i], prioritySum);
			}
			else
			{
				while (headSigns != NULL && prioritySum < headSigns->priority)
				{
					string s1;
					s1 = popSig();
					addNum(s1);
					cout << "Priority " << '"' << s1 << '"' << " qreater or equal than that. Put in Notation.\n";
				}
				addSig((*cPPNExample)[i], prioritySum);
			}
		}
	}
	while (headSigns != NULL)
	{
		string s1;
		s1 = popSig();
		addNum(s1);
		cout << "Put " << '"' << s1 << '"' << " in Notation\n";
	}
	while (headNumbers != NULL)
		cPPN += popNum();
	return cPPN;
}

string createPPN2(string* cPPN2Example)
{
	string cPPN;
	int cLengthExample = (*cPPN2Example).length();
	int priority2 = 0, prioritySum = 0, prioritySign = 0;
	for (int i = cLengthExample - 1; i >= 0; i--)
	{
		if ((i >= 0) && (*cPPN2Example)[i] == ')')
			priority2 += PriorityOperation((*cPPN2Example)[i]);
		else if ((i >= 0) && (*cPPN2Example)[i] == '(')
			priority2 -= PriorityOperation((*cPPN2Example)[i]);
		else if ((i >= 0) && (*cPPN2Example)[i] >= '0' && (*cPPN2Example)[i] <= '9')
		{
			int j = 1;
			string stringNumber;
			stringNumber = (*cPPN2Example)[i];
			i--;
			while (i >= 0 && (*cPPN2Example)[i] >= '0' && (*cPPN2Example)[i] <= '9')
			{
				stringNumber = (*cPPN2Example)[i] + stringNumber;
				i--;
				j++;
			}
			addNum(stringNumber);
			i++;
		}
		else if ((*cPPN2Example)[i] == '+' || (*cPPN2Example)[i] == '-' || (*cPPN2Example)[i] == '*' || (*cPPN2Example)[i] == '/')
		{
			prioritySign = PriorityOperation((*cPPN2Example)[i]);
			prioritySum = priority2 + prioritySign;
			if (headSigns == NULL || prioritySum >= headSigns->priority)
				addSig((*cPPN2Example)[i], prioritySum);
			else
			{
				while (headSigns != NULL && prioritySum < headSigns->priority)
				{
					string s1;
					s1 = popSig();
					addNum(s1);
				}
				addSig((*cPPN2Example)[i], prioritySum);
			}
		}
	}
	while (headSigns != NULL)
	{
		string s1;
		s1 = popSig();
		addNum(s1);
	}
	while (headNumbers != NULL)
		cPPN += popNum();
	return cPPN;
}

string createOPN(string* cOPNExample)
{
	string cOPN;
	int cLengthExample = (*cOPNExample).length();
	int priority2 = 0, prioritySum = 0, prioritySign = 0;
	for (int i = 0; i < cLengthExample; i++)
	{
		if ((*cOPNExample)[i] == ')')
		{
			priority2 -= PriorityOperation((*cOPNExample)[i]);
		}
		else if ((*cOPNExample)[i] == '(')
		{
			priority2 += PriorityOperation((*cOPNExample)[i]);
		}
		else if ((*cOPNExample)[i] >= '0' && (*cOPNExample)[i] <= '9')
		{
			int j = 1;
			string stringNumber;
			stringNumber = (*cOPNExample)[i];
			i++;
			while ((i < cLengthExample) && (*cOPNExample)[i] >= '0' && (*cOPNExample)[i] <= '9')
			{
				stringNumber += (*cOPNExample)[i];
				i++;
				j++;
			}
			cout << "Number " << stringNumber << " put in Notation.\n";
			cOPN += stringNumber;
			i--;
		}
		else if ((*cOPNExample)[i] == '+' || (*cOPNExample)[i] == '-' || (*cOPNExample)[i] == '*' || (*cOPNExample)[i] == '/')
		{
			prioritySign = PriorityOperation((*cOPNExample)[i]);
			prioritySum = priority2 + prioritySign;
			if (headSigns == NULL || prioritySum > headSigns->priority)
				addSig((*cOPNExample)[i], prioritySum);
			else
			{
				while (headSigns != NULL && prioritySum <= headSigns->priority)
				{
					string s1;
					s1 = popSig();
					cOPN += s1;
					cout << "Priority " << '"' << s1 << '"' << " qreater than that. Put in Notation.\n";
				}
				addSig((*cOPNExample)[i], prioritySum);
			}
		}
	}
	while (headSigns != NULL)
	{
		string s1;
		s1 = popSig();
		cOPN += s1;
		cout << "Put " << '"' << s1 << '"' << " in Notation\n";
	}
	return cOPN;
}

string createOPN2(string* cOPN2Example)
{
	string cOPN;
	int cLengthExample = (*cOPN2Example).length();
	int priority2 = 0, prioritySum = 0, prioritySign = 0;
	for (int i = 0; i < cLengthExample; i++)
	{
		if ((*cOPN2Example)[i] == ')')
		{
			priority2 -= PriorityOperation((*cOPN2Example)[i]);
		}
		else if ((*cOPN2Example)[i] == '(')
		{
			priority2 += PriorityOperation((*cOPN2Example)[i]);
		}
		else if ((*cOPN2Example)[i] >= '0' && (*cOPN2Example)[i] <= '9')
		{
			int j = 1;
			string stringNumber;
			stringNumber = (*cOPN2Example)[i];
			i++;
			while ((i < cLengthExample) && (*cOPN2Example)[i] >= '0' && (*cOPN2Example)[i] <= '9')
			{
				stringNumber += (*cOPN2Example)[i];
				i++;
				j++;
			}
			addNum(stringNumber);
			cOPN += stringNumber;
			i--;
		}
		else if ((*cOPN2Example)[i] == '+' || (*cOPN2Example)[i] == '-' || (*cOPN2Example)[i] == '*' || (*cOPN2Example)[i] == '/')
		{
			prioritySign = PriorityOperation((*cOPN2Example)[i]);
			prioritySum = priority2 + prioritySign;
			if (headSigns == NULL || prioritySum > headSigns->priority)
				addSig((*cOPN2Example)[i], prioritySum);
			else
			{
				while (headSigns != NULL && prioritySum <= headSigns->priority)
				{
					string s1;
					s1 = popSig();
					cOPN += s1;
				}
				addSig((*cOPN2Example)[i], prioritySum);
			}
		}
	}
	while (headSigns != NULL)
	{
		string s1;
		s1 = popSig();
		cOPN += s1;
	}
	return cOPN;
}

double resPPN(string* rPPN)
{
	double resultPPN = 0;
	int rLengthPPN = (*rPPN).length();
	for (int i = rLengthPPN - 1; i >= 0; i--)
	{
		if ((*rPPN)[i] >= '0' && (*rPPN)[i] <= '9')
		{
			string s4;
			s4 = (*rPPN)[i];
			addNum(s4);
		}
		else if ((*rPPN)[i] == '+' || (*rPPN)[i] == '-' || (*rPPN)[i] == '*' || (*rPPN)[i] == '/')
		{
			double number1 = 0, number2 = 0;
			string s1 = popNum();
			number1 = stod(s1);
			string s2 = popNum();
			number2 = stod(s2);
			switch ((*rPPN)[i])
			{
			case '+':
			{
				cout << number1 << ' ' << (*rPPN)[i] << ' ' << number2 << " = " << number1 + number2 << '\n';
				addNum(to_string(number1 + number2));
				break;
			}
			case '-':
			{
				cout << number1 << ' ' << (*rPPN)[i] << ' ' << number2 << " = " << number1 - number2 << '\n';
				addNum(to_string(number1 - number2));
				break;
			}
			case '/':
			{
				cout << number1 << ' ' << (*rPPN)[i] << ' ' << number2 << " = " << number1 / number2 << '\n';
				addNum(to_string(number1 / number2));
				break;
			}
			case '*':
			{
				cout << number1 << ' ' << (*rPPN)[i] << ' ' << number2 << " = " << number1 * number2 << '\n';
				addNum(to_string(number1 * number2));
				break;
			}
			}
		}
	}
	string s3 = popNum();
	resultPPN = stod(s3);
	return resultPPN;
}

double resOPN(string* rOPN)
{
	double resultOPN = 0;
	int rLengthOPN = (*rOPN).length();
	for (int i = 0; i < rLengthOPN; i++)
	{
		if ((*rOPN)[i] >= '0' && (*rOPN)[i] <= '9')
		{
			string s4;
			s4 = (*rOPN)[i];
			addNum(s4);
		}
		else if ((*rOPN)[i] == '+' || (*rOPN)[i] == '-' || (*rOPN)[i] == '*' || (*rOPN)[i] == '/')
		{
			double number1 = 0, number2 = 0;
			string s1 = popNum();
			number1 = stod(s1);
			string s2 = popNum();
			number2 = stod(s2);
			switch ((*rOPN)[i])
			{
			case '+':
			{
				cout << number2 << ' ' << (*rOPN)[i] << ' ' << number1 << " = " << number2 + number1 << '\n';
				addNum(to_string(number2 + number1));
				break;
			}
			case '-':
			{
				cout << number2 << ' ' << (*rOPN)[i] << ' ' << number1 << " = " << number2 - number1 << '\n';
				addNum(to_string(number2 - number1));
				break;
			}
			case '/':
			{
				cout << number2 << ' ' << (*rOPN)[i] << ' ' << number1 << " = " << number2 / number1 << '\n';
				addNum(to_string(number2 / number1));
				break;
			}
			case '*':
			{
				cout << number2 << ' ' << (*rOPN)[i] << ' ' << number1 << " = " << number2 * number1 << '\n';
				addNum(to_string(number2 * number1));
				break;
			}
			}
		}
	}
	string s3 = popNum();
	resultOPN = stod(s3);
	return resultOPN;
}

void menu(string* mExample, string* mPPN, string* mOPN)
{
	system("cls");
	string polPPN, polOPN;
	double resultatPPN = 0, resultatOPN = 0;
	int punktMenu;
	cout << "Which action with you want to do? Choose the number\n"
		<< "1 - Create PPN\n"
		<< "2 - Create OPN\n"
		<< "3 - Check PPN\n"
		<< "4 - Check OPN\n"
		<< "5 - Calculate PPN\n"
		<< "6 - Calculate OPN\n"
		<< "0 - Exit\n\n";
	cin >> punktMenu;
	system("cls");
	switch (punktMenu)
	{
	case 1:
		system("cls");
		cout << "Example: " << *mExample << "\n\n";
		(*mPPN) = createPPN(mExample);
		cout << "\n\nPPN: " << (*mPPN) << '\n';
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	case 2:
		system("cls");
		cout << "Example: " << *mExample << "\n\n";
		(*mOPN) = createOPN(mExample);
		cout << "\n\nOPN: " << (*mOPN) << '\n';
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	case 3:
		system("cls");
		cout << "Example: " << *mExample << "\n\n";
		cout << "Input your PPN: ";
		cin.ignore();
		getline(cin, polPPN);
		(*mPPN) = createPPN2(mExample);
		cout << "\nCorrect PPN: " << (*mPPN) << "\n\n";
		if (polPPN == (*mPPN))
			cout << "Correct!\n";
		else
			cout << "Incorrect!\n";
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	case 4:
		system("cls");
		cout << "Example: " << *mExample << "\n\n";
		cout << "Input your OPN: ";
		cin.ignore();
		getline(cin, polOPN);
		(*mOPN) = createOPN2(mExample);
		cout << "\nCorrect OPN: " << (*mOPN) << "\n\n";
		if (polPPN == (*mOPN))
			cout << "Correct!\n";
		else
			cout << "Incorrect!\n";
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	case 5:
		system("cls");
		if ((*mPPN) == "P")
		{
			cout << "PPN not created.\n";
			system("Pause");
			menu(mExample, mPPN, mOPN);
			break;
		}
		cout << "PPN: " << (*mPPN) << "\n\n";
		resultatPPN = resPPN(mPPN);
		cout << "\n\nResult of PPN: " << resultatPPN << '\n';
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	case 6:
		system("cls");
		if ((*mOPN) == "O")
		{
			cout << "OPN not created.\n";
			system("Pause");
			menu(mExample, mPPN, mOPN);
			break;
		}
		cout << "OPN: " << (*mOPN) << "\n\n";
		resultatOPN = resOPN(mOPN);
		cout << "\n\nResult of OPN: " << resultatOPN << '\n';
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	case 0:
		break;
	default:
		cout << "Error! Repeat, please.\n\n";
		system("Pause");
		menu(mExample, mPPN, mOPN);
		break;
	}
}

int main()
{
	string example, PPN = "P", OPN = "O";
	double resultatPPN, resultatOPN;
	do
	{
		newExample(&example);
		if (!correctExample(&example))
		{
			cout << "\nError of example. Repeat\n";
			system("Pause");
			system("cls");
		}
	} while (!correctExample(&example));
	menu(&example, &PPN, &OPN);
	return 0;
}