#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
using namespace std;
//抽象基类
class Employee
{
	public:
		Employee(string);
		virtual ~Employee();
		string getName();   //姓名
		void   setName(string);
		int    getNum();    //编号
		virtual double getSalary(); //薪水
		int    getClass();  //等级
		int    getFlag();
		virtual void promote()=0;//
		virtual void save(ofstream &out)=0;
		static int max_num;
		void show();
		friend ostream &operator<<(ostream& out,Employee &p)
		{
			out<<p._class<<" "
				<<p._name<<" "
				<<p._salary<<" "
				<<p._num<<endl;
			return out;
		}
	protected:
		string _name;
		int    _num;
		double _salary;
		int    _class;
		int    _flag;
};
int Employee::max_num = 1000;
Employee::Employee(string name="null")
{
	_name = name;
	max_num++;
	_num  = max_num;
	_salary = 0;
	_class = 1;
}
Employee::~Employee()
{
//	max_num--;
	delete this;
}
string Employee::getName()
{
	return _name;
}
void Employee::setName(string name)
{
	_name = name;
}
int Employee::getNum()
{
	return _num;
}
double Employee::getSalary()
{
	return _salary;
}
int Employee::getClass()
{
	return _class;
}
int Employee::getFlag()
{
	return _flag;
}
void Employee::show()
{
	cout<<"name: "<<_name<<" num: "<<_num<<" class: "<<_class<<" salary: "<<_salary<<endl;
}

//经理类
class Manager:virtual public Employee
{
	public:
		Manager(string);
		~Manager();
		virtual void promote();
		virtual double getSalary();
		void save(ofstream &out)
		{
			out<<_flag<<" "
				<<_class<<" "
				<<_name<<" "
				<<_salary<<" "
				<<_num<<" "
				<<_payPermonth<<endl;
		}
		friend istream &operator>>(istream& in,Manager &p)
		{
			in>>p._class;
			in>>p._name;
			in>>p._salary;
			in>>p._num;
			in>>p._payPermonth;
			if(p._num > max_num)
				max_num = p._num;
			return in;
		}
	protected:
		int _payPermonth;
};
void Manager::promote()
{
	_class = 4;
}
Manager::Manager(string name="null"):Employee(name)
{
	_payPermonth = 8000;
	promote();
	_flag = 4;
}
Manager::~Manager()
{
//	max_num--;
	delete this;
}
double Manager::getSalary()
{
	return _payPermonth;
}

//兼职销售类
class Salesman:virtual public Employee
{
	public:
		Salesman(string);
		~Salesman();
		virtual void promote();
		virtual double getSalary();
		void setSalesment(double);
		virtual void save(ofstream& out);
		friend istream &operator>>(istream& in,Salesman &p)
		{
			in>>p._class;
			in>>p._name;
			in>>p._salary;
			in>>p._num;
			in>>p._salesment;
			in>>p._percent;
			if(p._num > max_num)
				max_num = p._num;
			return in;
		}
	protected:
		double _salesment;
		double _percent;
};
Salesman::Salesman(string name="null2"):Employee(name)
{
	_salesment = 0;
	_percent   = 0.04;
	promote();
	_flag = 1;
}
Salesman::~Salesman()
{
//	max_num--;
	delete this;
}
void Salesman::save(ofstream& out)
{
	out<<_flag<<" "
		<<_class<<" "
		<<_name<<" "
		<<_salary<<" "
		<<_num<<" "
		<<_salesment<<" "
		<<_percent<<endl;
}
void Salesman::promote()
{
	_class = 2;
}
double Salesman::getSalary()
{
	return _percent*_salesment;
}
void Salesman::setSalesment(double salesment)
{
	_salesment = salesment;
}


//兼职技术
class Technicial:virtual public Employee
{
	public:
		Technicial(string);
		~Technicial();
		virtual void promote();
		virtual double getSalary();
		//		void setPerhour();
		void setHours(int);
		virtual void save(ofstream& out)
		{
			out<<_flag<<" "
				<<_class<<" "
				<<_name<<" "
				<<_salary<<" "
				<<_num<<" "
				<<_payPerhour<<" "
				<<_hours<<endl;
		}
		friend istream &operator>>(istream& in,Technicial &p)
		{
			in>>p._class;
			in>>p._name;
			in>>p._salary;
			in>>p._num;
			in>>p._payPerhour;
			in>>p._hours;
			if(p._num > max_num)
				max_num = p._num;
			return in;
		}
	private:
		double _payPerhour;
		int    _hours;
};
Technicial::Technicial(string name="null3"):Employee(name)
{
	_payPerhour = 100;
	_hours      = 0;
	promote();
	_flag = 2;
}
Technicial::~Technicial()
{
//	max_num--;
	delete this;
}
void Technicial::promote()
{
	_class = 3;
}
double Technicial::getSalary()
{
	return _hours*_payPerhour;
}
void Technicial::setHours(int hours)
{
	_hours = hours;
}

class SalesManager:public Salesman,public Manager
{
	public:
		SalesManager(string);
		~SalesManager();
		virtual void promote();
		virtual double getSalary();
		virtual void save(ofstream& out)
		{
			out<<_flag<<" "
				<<_class<<" "
				<<_name<<" "
				<<_salary<<" "
				<<_num<<" "
				<<_salesment<<" "
				<<_percent<<" "
				<<_payPermonth<<endl;
		}
		friend istream &operator>>(istream& in,SalesManager &p)
		{
			in>>p._class;
			in>>p._name;
			in>>p._salary;
			in>>p._num;
			in>>p._salesment;
			in>>p._percent;
			in>>p._payPermonth;
			if(p._num > max_num)
				max_num = p._num;
			return in;
		}
};

//销售经理
SalesManager::SalesManager(string name="null4"):Employee(name)
{
	_salesment = 0;
	_percent   = 0.05;
	_payPermonth = 5000;
	promote();
	_flag = 3;
}
SalesManager::~SalesManager()
{
	delete this;
}
void SalesManager::promote()
{
	_class = 3;
}
double SalesManager::getSalary()
{
	return _payPermonth+_percent*_salesment;
}

//hanshu
void menu();
void saveTofile(list<Employee*> l);
list<Employee*> creatFromfile();


int main()
{
	list<Employee*> l;
	string name;
	char ch;
	list<Employee*>::iterator it;
	l=creatFromfile();
	while(1)
	{
		menu();
		cin.get(ch).get();
		switch(ch)//cin.get(ch).get())
		{
			case '0':cout<<"是否保存:y?";
					 if(cin.get()=='y')
						 saveTofile(l);
					 return 0;
			case '1':cout<<"请输入姓名：";
					 getline(cin,name);
					 cout<<"请选择人员职位:"<<endl
						 <<"1--兼职销售"<<endl
						 <<"2--兼职技术"<<endl
						 <<"3--经理"<<endl
						 <<"4--销售经理"<<endl;
					 cin.get(ch).get();
					 switch(ch)//cin.get(ch).get())
					 {
						 case '1'://Salesman s(name);
							 l.push_back(new Salesman(name));
							 break;
						 case '2'://Technicial t(name);
							 l.push_back(new Technicial(name));
							 break;
						 case '3'://Manager m(name);
							 l.push_back(new Manager(name));
							 break;
						 case '4'://SalesManager s(name);
							 l.push_back(new SalesManager(name));
							 break;
					 }
					 break;
			case '2':cout<<"请输入姓名：";
					 getline(cin,name);
					 for(it=l.begin();it!=l.end();it++)
					 {
						 if((*it)->getName()==name)
						 {
							 l.erase(it);
							 cout<<"删除成功"<<endl;
							 break;
						 }
					 }
					 if(it == l.end())
						 cout<<"未找到相关信息"<<endl;
					 cin.get();
					 break;
			case '3':for(it=l.begin();it!=l.end();it++)
					 {
						 (*it)->show();
					 }
					 cin.get();
					 break;
			case '4':cout<<"请输入姓名：";
					 getline(cin,name);
					 for(it=l.begin();it!=l.end();it++)
					 {
						 if((*it)->getName()==name)
						 {
							 (*it)->show();
							 break;
						 }
					 }
					 if(it == l.end())
						 cout<<"未找到相关信息"<<endl;
					 cin.get();
					 break;
			case '5':saveTofile(l);
					 break;
		}
	}
}

void menu()
{
	system("clear");
	cout<<"*****************************************"<<endl
		<<"************公司人员管理系统*************"<<endl
		<<"*****************************************"<<endl
		<<"**********made by jhonny with c++********"<<endl
		<<"*****************************************"<<endl;
	cout<<endl<<endl<<endl;
	cout<<"****1 ------- 增加****"<<endl
		<<"****2 ------- 删除****"<<endl
		<<"****3 ------- 显示****"<<endl
		<<"****4 ------- 查找****"<<endl
		<<"****5 ------- 保存****"<<endl
		<<"****0 ------- 退出****"<<endl
		<<"请输入选择：";
}

void saveTofile(list<Employee*> l)
{
	//	l.sort();
	ofstream out("data.txt");
	for(list<Employee*>::iterator it=l.begin();it!=l.end();it++)
	{
		(*it)->save(out);
	}
}

list<Employee*> creatFromfile()
{
	list<Employee*> l;
	int tflag;
	ifstream in("data.txt");
	while(!in.eof())
	{
		in>>tflag;
		switch(tflag)
		{
			case 1:
				{
					tflag = 0;
					Salesman* s = new Salesman();
					in>>*s;
					l.push_back(s);
					break;
				}
			case 2:
				{
					tflag = 0;
					Technicial* t = new Technicial();
					in>>*t;
					l.push_back(t);
					break;
				}
			case 3:
				{
					tflag = 0;
					SalesManager* p = new SalesManager();
					in>>*p;
					l.push_back(p);
					break;
				}
			case 4:
				{
					tflag = 0;
					Manager* p = new Manager();
					in>>*p;
					l.push_back(p);
					break;
				}
		}
	}
	return l;
}
