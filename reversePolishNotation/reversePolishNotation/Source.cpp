#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>
#include<stdlib.h>
using namespace std;
class symbol
{
protected:
	vector<double> v1;
	int op1, op2, count;
	string tp, st, m1, m2;
	string space = "space", variable = "", var = "";
	double X1, Y1;
public:
	string match_var(string var)
	{
		if (var == "p" || var == "P" || var == "o" || var == "O" || var == "w" || var == "W" || var == "*" || var == "/" || var == "%" || var == "-" || var == "+" || var == "." || (var >= "0" && var <= "9"))
		{
			variable = var;
		}
		else
		{
			variable = space;
		}
		return variable;
		variable = "";
	}
};
class operand : public symbol
{
public:
	double intValue(string number)
	{
		double num = stod(number);
		v1.push_back(num);
		return num;
	}
	void removeSpace()
	{
		X1 = v1[v1.size() - 2];
		Y1 = v1[v1.size() - 1];
		v1.pop_back();
		v1.pop_back();
	}
	int getSize()
	{
		return v1.size();
	}
	void pushValue(double val)
	{
		v1.push_back(val);
	}
	double opt()
	{
		return v1[0];
	}
	void Empty()
	{
		v1.clear();
	}
	double X()
	{
		return X1;
	}
	double Y()
	{
		return Y1;
	}
};
class Operator : public symbol
{
protected:
	string element;
public:
	string check(string st)
	{
		var = st;
		return var;
		var = "";
	}
	string getOperationType(char ch)
	{
		var = ch;
		return var;
		var = "";
	}
	virtual double operation(double d1, double d2)
	{
		X1 = d1;
		Y1 = d2;
		return 0;
	}
	bool vaidate_size(vector<string> &v2, string input)
	{
		unsigned int i;
		op1 = 0, op2 = 0, count = 0, i = 0, tp = "", st = "", m1 = "", m2 = "";
		while (i < input.length())
		{
			m2 = input.at(i);
			m1 = match_var(m2);
			st = input.at(i);
			m2 = "";
			if (m1 != st)
			{
				if (st == "\t" || st == " ")
				{
					if (tp != "")
					{
						if (tp.length() == 1 && tp.at(0) == '.')
						{
							return false;
						}
						else if (tp.at(tp.length() - 1) == '.')
						{
							tp += '0';
						}
						else if (tp.at(0) == '.')
						{
							tp += '0';
						}
						if (count > 1)
						{
							return false;
						}
						v2.push_back(tp);
						count = 0;
						tp = "";
						op1++;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				st = "";
				if ((input.at(i) >= '0' && input.at(i) <= '9') || input.at(i) == '.')
				{
					st = check(m1);
					tp = tp + st;
					st = "";
					m1 = "";
					if (input.at(i) == '.')
					{
						count++;
					}
				}
				else if (input.at(i) == '+' || input.at(i) == '-' || input.at(i) == '*' || input.at(i) == '/' || input.at(i) == '%' || input.at(i) == 'p' || input.at(i) == 'P')
				{
					if (tp != "")
					{
						if (tp.length() == 1 && tp.at(0) == '.')
						{
							return false;
						}
						else if (tp.at(tp.length() - 1) == '.')
						{
							tp += '0';
						}
						else if (tp.at(0) == '.')
						{
							tp += '0';
						}
						if (count > 1)
						{
							return false;
						}
						v2.push_back(tp);
						op1++;
						count = 0;
						tp = "";
					}
					if (input.at(i) == 'p' || input.at(i) == 'P')
					{
						if (((i + 2) < input.length()) && (input.at(i + 1) == 'o' || input.at(i + 1) == 'O') && (input.at(i + 2) == 'W' || input.at(i + 2) == 'w'))
						{
							v2.push_back("pow");
							op2++;
							i += 2;
						}
						else
						{
							return false;
						}
					}
					else
					{
						st = getOperationType(input.at(i));
						v2.push_back(st);
						op2++;
						st = "";
					}
				}
				else
				{
					return false;
				}
			}
			if (i == input.length() - 1)
			{
				if (tp != "")
				{
					if (tp.length() == 1 && tp.at(0) == '.')
					{
						return false;
					}
					else if (tp.at(tp.length() - 1) == '.')
					{
						tp += '0';
					}
					else if (tp.at(0) == '.')
					{
						tp += '0';
					}
					if (count > 1)
					{
						return false;
					}
					v2.push_back(tp);
					op1++;
					count = 0;
					tp = "";
				}
			}
			i++;
		}
		int T = v2.size() - 1;
		if (v2.size() <= 1)
		{
			return true;
		}
		if (v2.size() > 0 && !(v2[T] == "+" || v2[T] == "-" || v2[T] == "*" || v2[T] == "/" || v2[T] == "%" || v2[T] == "pow"))
		{
			return false;
		}
		else if (v2.size() > 0 && (v2[0] == "+" || v2[0] == "-" || v2[0] == "*" || v2[0] == "/" || v2[0] == "%" || v2[0] == "pow"))
		{
			return false;
		}
		else if (op1 != (op2 + 1))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
class add : public Operator
{
public:
	void getOperationType(string name)
	{
		element = name;
	}
	double operation(double num1, double num2)
	{
		return (num1 + num2);
	}
};
class subtract : public Operator
{
public:
	void getOperationType(string name)
	{
		element = name;
	}
	double operation(double num1, double num2)
	{
		return (num1 - num2);
	}
};
class division : public Operator
{
public:
	void getOperationType(string name)
	{
		element = name;
	}
	double operation(double num1, double num2)
	{
		return (num1 / num2);
	}
};
class modulus : public Operator
{
public:
	void getOperationType(string name)
	{
		element = name;
	}
	double operation(double num1, double num2)
	{
		return fmod(num1, num2);
	}
};
class power : public Operator
{
public:
	void getOperationType(string name)
	{
		element = name;
	}
	double operation(double num1, double num2)
	{
		return pow(num1, num2);
	}
};
class multiply : public Operator
{
public:
	void getOperationType(string name)
	{
		element = name;
	}
	double operation(double num1, double num2)
	{
		return (num1 * num2);
	}
};
int main()
{
	symbol newSysmbol;
	operand newOperand;
	Operator newop;
	string fileName;
	string syError = "";
Start:
	cout << "Enter the file name or Path:";
	cin >> fileName;
	ifstream file(fileName);
	if (file.is_open())
	{
		string input;
		vector<string> row;
		int i = 1;
		while (getline(file, input))
		{
			bool T1 = newop.vaidate_size(row, input);
			if (T1 == true)
			{
				if (row.size() == 0)
				{
					cout << endl;
					goto End;
				}
				unsigned int i = 0;
				while (i < row.size())
				{
					if (row[i] == "+" || row[i] == "-" || row[i] == "*" || row[i] == "/" || row[i] == "%" || row[i] == "pow")
					{
						if (newOperand.getSize() >= 2)
						{
							newOperand.removeSpace();
							double p1 = newOperand.X();
							double p2 = newOperand.Y();
							if (row[i] == "+")
							{
								add a;
								Operator &newop = a;
								a.getOperationType("+");
								newOperand.pushValue(newop.operation(p1, p2));
							}
							else if (row[i] == "-")
							{
								subtract s;
								Operator &newop = s;
								s.getOperationType("-");
								newOperand.pushValue(newop.operation(p1, p2));
							}
							else if (row[i] == "*")
							{
								multiply m;
								Operator &newop = m;
								m.getOperationType("*");
								newOperand.pushValue(newop.operation(p1, p2));
							}
							else if (row[i] == "/")
							{
								division d;
								Operator &newop = d;
								if (p2 == 0)
								{
									syError = "SYNTAX ERROR";
									newOperand.pushValue(1);
								}
								else
									d.getOperationType("/");
								newOperand.pushValue(newop.operation(p1, p2));
							}
							else if (row[i] == "%")
							{
								modulus mo;
								Operator &newop = mo;
								mo.getOperationType("%");
								newOperand.pushValue(newop.operation(p1, p2));
							}
							else if (row[i] == "pow")
							{
								power po;
								Operator &newop = po;
								po.getOperationType("");
								newOperand.pushValue(newop.operation(p1, p2));
							}
						}
						else
						{
							cout << "SYNTAX ERROR" << endl;
							syError = "";
							i++;
							goto End;
						}
					}
					else
					{
						newOperand.intValue(row[i]);
					}
					i++;
				}
				if (newOperand.getSize() == 1)
				{
					if (syError != "")
						cout << syError << endl;
					else
						cout << newOperand.opt() << endl;
					syError = "";
					i++;
				}
				else
				{
					cout << "SYNTAX ERROR" << endl;
					syError = "";
					i++;
				}
			}
			else
			{
				cout << "SYNTAX ERROR" << endl;
				i++;
			}
		End:
			row.clear();
			newOperand.Empty();
			T1 = false;
		}
	}
	else
	{
		cout << "File does not exist." << endl;
		goto Start;
	}
	return 0;
}


