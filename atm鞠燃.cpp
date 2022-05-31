#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<Windows.h>
using namespace std;
class User;
//��̬����
static bool login = false;
//�ͻ���Ϣ�����Ĵ���
vector<User> Usr;
vector<User>::iterator it = Usr.begin();
//������
class Assist
{
public:
	void Save(User u);//�洢���ݵ�����
	bool JudgeID(string s);//�ж����֤�������Ƿ�Ϸ�
	bool JudgePass(string s);//�ж����������Ƿ�Ϸ�
	bool IDIsReg(string s);//�ж����֤���Ƿ��Ѿ���ע��
	bool JudgeAcc(string s);//�ж��ʺ������Ƿ�Ϸ�
	bool AccIsReg(string s);//�ж��ʺ��Ƿ��Ѿ���ע��
};
class User
{
	friend class Assist;
	friend User Login(Assist a);
	friend void Change();
	friend string itos(int i);
public:
	User();
	void Read(string a, string b, string c, string d, int e, string f);//�ӱ��ض�ȡ�û���Ϣ
	void Register(Assist a);//����
	void ShowInform();//��ʾ�ͻ���Ϣ
	void ShowBalance();//��ѯ���
	void Transfer();//ת��
	void TakeCash();//ȡ��
	void SaveCash();//���
	void ChangePass(Assist a);//�޸�����
private:
	string acc;//�˻�
	string name;//����
	string ID;//���֤
	string pass;//����
	string record;//��ȡ���¼
	int money;//���
};
//ȫ�ֺ���:
void Change()//������ı��浽����
{
	fstream os;
	os.open("D:\\UserList.txt", ios::out);
	for (vector<User>::iterator out = Usr.begin(); out != Usr.end(); out++)
	{
		os << out->name << " " << out->ID << " " << out->acc << " " << out->pass << " " << out->money <<" "<< out->record << endl;
	}
	os.close();
}
User Login(Assist a)//��¼
{
	User u;
	ifstream input, judgein;
	input.open("D:\\UserList.txt", ios::in);
	judgein.open("D:\\Frozen.txt", ios::in);
	cout << "----------------------------�忨:������������Ϣ--------------------------" << endl;
	string InAcc, InPass;
	string temp;
	string read;
	cout << setiosflags(ios::left);
	cout << setw(52) << "�����������ʺ�:"; cin >> InAcc;
	while (getline(input, read))//�����ص����ݶ�ȡ��Usr������
	{
		string name, id, acc, pass, num, record;
		stringstream strin(read);
		strin >> name >> id >> acc >> pass >> num>> record;
		int money = stoi(num);
		u.Read(name, id, acc, pass, money, record);
		Usr.push_back(u);
	}
	while (getline(judgein, temp))
	{
		if (temp == InAcc)
		{
			cout << "�����˻��ѱ��������޷���¼" << endl << "��������������" << endl;
			Sleep(1000);
			login = false;
			it = Usr.begin();
			return *it;
		}
	}
	for (it = Usr.begin(); it != Usr.end(); it++)//���������ҳ����ʺ�
	{
		if ((*it).acc == InAcc)
		{
			cout << setw(52) << "��������������:"; cin >> InPass;
			if ((*it).pass == InPass)
			{
				cout << "��½�ɹ�" << endl;
				login = true;
				return *it;
			}
			else
			{
				cout << setw(52) << "�������!������2���������:"; cin >> InPass;
				if ((*it).pass == InPass)
				{
					cout << "��½�ɹ�" << endl;
					login = true;
					return *it;
				}
				else
				{
					cout << setw(52) << "�������!������1���������:"; cin >> InPass;
					if ((*it).pass == InPass)
					{
						cout << "��½�ɹ�" << endl;
						login = true;
						return *it;
					}
					else
					{
						cout << "��������������룬�����˻��ѱ�����" << endl << "����������ҳ��" << endl;
						Sleep(1000);
						ofstream output;
						output.open("D:\\Frozen.txt", ios::app);
						output << InAcc << endl;
						login = false;
						return *it;
					}
				}
			}
		}
	}
	cout << "!����!�����ڴ��ʺ�" << endl << "����������ҳ��" << endl;
	Sleep(1000);
	input.close();
	it = Usr.begin();
	return *it;
}
string itos(int i)//������תΪ�ַ���
{
	stringstream s;
	s << i;
	return s.str();
}
//��Assist�ĳ�Ա����:
bool Assist::JudgeID(string s)
{
	int t = 0;
	for (int i = 0; i < s.length()-1; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			t++;
		}
	}
	if ((s[s.length()-1] >= '0' && s[s.length()-1] <= '9') || s[s.length()-1] == 'X')//���ǵ����֤����X��β
	{
		t++;
	}
	if (t == 18) { return true; }
	else { return false; }
}
bool Assist::JudgeAcc(string s)
{
	if (s.length() != 19) { return false; }
	else
	{
		for (int i = 0; i < 19; i++)
		{
			if (s[i] < '0' || s[i]>'9') { return false; }
		}
		return true;
	}
}
bool Assist::JudgePass(string s)
{
	int t=0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			t++;
		}
	}
	if (t == 6) { return true; }
	else { return false; }
}
bool Assist::IDIsReg(string s)
{
	ifstream input;
	input.open("D:\\UserList.txt", ios::in);
	string temp;
	while (getline(input, temp))
	{
		stringstream ss(temp);
		string temp1, temp2, temp3;
		ss >> temp1 >> temp2 >> temp3;
		if (temp2 == s)
		{
			return false;
		}
	}
	return true;
}
bool Assist::AccIsReg(string s)
{
	{
		ifstream input;
		input.open("D:\\UserList.txt", ios::in);
		string temp;
		while (getline(input, temp))
		{
			stringstream ss(temp);
			string temp1, temp2, temp3;
			ss >> temp1 >> temp2 >> temp3;
			if (temp3 == s)
			{
				return false;
			}
		}
		return true;
	}
}
void Assist::Save(User u)
{
	fstream outFile;
	outFile.open("D:\\UserList.txt",ios::app);
	outFile << u.name<<" "<< u.ID <<" "<< u.acc << " " << u.pass << " " << u.money << endl;
	outFile.close();
}
//��User�ĳ�Ա����:
void User::Register(Assist a)
{
	string InAcc, InName, InID, InPass1, InPass2;
	cout << "----------------------------��ӭʹ�ÿ�������----------------------------" << endl;
	cout << setiosflags(ios::left);
	cout << "�밴��ʾ������Ϣ" << endl;
	cout << setw(52) << "��������������:";
	cin >> InName;
	name = InName;
	while (1)//�������֤��
	{
		cout << setw(52) << "�������������֤��(18λ������X��ʹ�ô�д):";
		while (1)
		{
			cin >> InID;
			if (a.JudgeID(InID))
			{
				break;
			}
			else
			{
				cout << setw(52) << "!����������Ϸ������֤��(18λ������X��ʹ�ô�д)��";
			}
		}
		if (a.IDIsReg(InID))//ȷ���û��ṩ�����֤δ��ʹ��
		{
			ID = InID;
			break;
		}
		else
		{
			cout << "!����!�����֤�ѱ�ע��" << endl;
		}
	}
	cout << setw(52) << "�����������ʺţ�Ϊ19λ����";
	while (1)
	{
		cin >> InAcc;
		if (!a.JudgeAcc(InAcc))
		{
			cout << "!����!��ȷ���˻�Ϊ19λ����";
		}
		else
		{
			if (a.AccIsReg(InAcc))
			{
				acc = InAcc;
				break;
			}
			else
			{
				cout << setw(52) << "!����!���ʺ��Ѿ���ע��,����������:";
			}
		}
	}
	Flag2:
	cout << setw(52) << "�������������룬Ϊ6λ����:";
	while (1)//�趨����
	{
		cin >> InPass1;
		if (a.JudgePass(InPass1))
		{
			cout << setw(52) << "���ٴ�������������:";
			while (1)
			{
				cin >> InPass2;
				if (a.JudgePass(InPass2) && InPass2 == InPass1)
				{
					pass = InPass2;
					break;
				}
				else
				{
					cout << setw(52) << "������!����:1.�����Ƿ�Ϊ6λ���֡�2.�������������Ƿ���ͬ��" << endl;
					cout << setw(52) << "���ٴ�������������:" << endl;
					goto Flag2;
				}
			}
			break;
		}
		else
		{
			cout << setw(52) << "!����!�������ʽ����Ҫ���6λ��������:";
		}
	}
	cout << "�����ɹ�!���ṩ����Ϣ����:" << endl;
	this->ShowInform();
	a.Save(*this);
	cout << "������Ϣ�ѱ�����������" << endl << "�����������˵�" << endl;
	Sleep(1000);
}
User::User()
{
	money = 10000;
}
void User::Read(string a, string b, string c, string d, int e,string f)
{
	name = a;
	ID = b;
	acc = c;
	pass = d;
	money = e;
	record = f;
}
void User::ShowInform()
{
	cout << setiosflags(ios::left) << endl;
	cout << setw(10) << "����:" <<  name << endl;
	cout << setw(10) << "���֤��:" << ID << endl;
	cout << setw(10) << "�˻�:" << acc << endl;
}
void User::ShowBalance()
{
	cout << "---------------------------------����ѯ--------------------------------" << endl;
	cout << "��Ŀǰ�����Ϊ:" << this->money << endl << "�����������˵�"<<endl;
	Sleep(2000);
}
void User::TakeCash()
{
	ofstream ofr;
	ofr.open("D:\\UserList.txt", ios::out);
	cout << "------------------------------------ȡ��-----------------------------------" << endl;
	int num = 0;
	while (1)
	{
		cout << setw(52) << "����������ȡ����(�����ο�ȡ��100000Ԫ):"; 
		cin >> num;
		if (num < 100 || num % 100 != 0)
		{
			cout << "!����!ȡ���ֻ��Ϊ100��������" << endl;
		}
		else
		{
			if ((money - num) < 0)
			{
				cout << "����!" << endl;
			}
			else
			{
				if (num > 100000)
				{
					cout << "��һ��ֻ��ȡ��100000Ԫ" << endl;
				}
				else
				{
					money -= num;
					it->money -= num;
					string temp1 = itos(num);
					string temp2 = "-" + temp1;
					it->record += temp2;
					cout << "ȡ��ɹ�!" << endl << "����ǰ�����Ϊ:" << this->money << "Ԫ" << endl;
					cout << "����������ҳ��";
					ofr.close();
					Sleep(1000);
					break;
				}
			}
		}
	}
}
void User::SaveCash()
{
	ofstream ofr;
	ofr.open("D:\\UserList.txt", ios::out);
	int num;
	cout << "------------------------------------���-----------------------------------" << endl;
	while (1)
	{
		cout << setw(52) << "���������Ĵ����(�����οɴ��100000Ԫ):"; cin >> num;
		if (num < 100 || num % 100 != 0)
		{
			cout << "!����!����ֻ��Ϊ100��������" << endl;
		}
		else if (num > 100000)
		{
			cout << "��һ��ֻ�ɴ��100000Ԫ" << endl;
		}
		else
		{
			money += num;
			it->money += num;
			string temp1 = itos(num);
			string temp2 = "+" + temp1;
			it->record += temp2;
			cout << "���ɹ�!" << endl << "����ǰ�����Ϊ:" << this->money << "Ԫ" << endl;
			cout << "����������ҳ��";
			Sleep(1000);
			ofr.close();
			break;
		}
	}
}
void User::Transfer()
{
	string InAcc1, InAcc2, temp; int num; bool out = false;
	cout << "------------------------------------ת��-----------------------------------" << endl;
	ifstream input;
	input.open("D:\\UserList.txt", ios::in);
	cout << setw(52)<<"��������Ҫת����ʺ�:";
	cin >> InAcc1;
	for (it=Usr.begin(); it != Usr.end(); it++)
	{
		if (this->acc == InAcc1)
		{
			out = true;
			cout << "!����!�������Ը��Լ�ת��" << endl << "����������ҳ��";
			Sleep(1000);
			break;
		}
		else
		{
			if (it->acc == InAcc1)
			{
				out = true;
				cout << setw(52) << "���ٴ�������Ҫת����ʺ�:";
				while (1)
				{
					cin >> InAcc2;
					if (InAcc1 == InAcc2)
					{
						cout << setw(52) << "����������ת�˽��(�����ο�ת��100000Ԫ):"; cin >> num;
						if ((money - num) < 0)
						{
							cout << "����!" << endl;
							goto Flag;
						}
						else if (num > 100000)
						{
							cout << "��һ��ֻ��ȡ��100000Ԫ" << endl;
							goto Flag;
						}
						else
						{
							money -= num;
							it->money += num;
							string temp1 = itos(num);
							it->record += "+" + temp1;
							cout << "ת�˳ɹ�!" << endl << "����ǰ�����Ϊ:" << this->money << "Ԫ" << endl;
							cout << "����������ҳ��";
							Sleep(1000);
							for (it = Usr.begin(); it != Usr.end(); it++)
							{
								if (it->acc == this->acc)
								{
									it->money -= num;
									it->record = it->record+"-" + temp1;
								}
							}
							goto Flag;
						}
					}
					else
					{
						cout << setw(52) << "!����!�������������ʺ��Ƿ�һ��";
					}
				}
			}
		}
	}
	Flag:
	if (out == false)
	{
		cout << "û�д��ʺ�" << endl << "��������������" << endl;
		Sleep(1000);
	}
}
void User::ChangePass(Assist a)
{
	string cPass1,cPass2;
	cout << setiosflags(ios::left);
	cout << "----------------------------------�޸�����---------------------------------" << endl;
	cout << setw(52) << "�������޸ĺ������,Ϊ6λ����:";
	while (1)
	{
		cin >> cPass1;
		if (a.JudgePass(cPass1))
		{
			cout << setw(52) << "���ٴ�������������:";
			while (1)
			{
				cin >> cPass2;
				if (a.JudgePass(cPass2) && cPass2== cPass1)
				{
					pass = cPass1;
					it->pass = cPass1;
					break;
				}
				else
				{
					cout << setw(52) << "������!����:1.�����Ƿ�Ϊ6λ���֡�2.�������������Ƿ���ͬ��" << endl;
					cout << setw(52) << "���ٴ�������������:";
				}
			}
			break;
		}
		else
		{
			cout << setw(52) << "!����!�������ʽ����Ҫ���6λ��������:";
		}
	}
	cout << "�޸ĳɹ�" << endl << "����������ҳ��" << endl;
	Sleep(1000);
}
//�����������幦��
int main()
{
	User usr;
	Assist a;
	string c, d, e;
	while (1)
	{
		cout << setiosflags(ios::left);
		cout << "-----------------��ӭʹ������ATM������ѡ�����ķ���--------------------" << endl;
		cout << "    " << "1.����" << endl
			<< "    " << "2.�忨" << endl
			<< "    " << "3.��������" << endl;
		cout << setw(52)<<"���ڴ���������ѡ��:";
		cin >> d;
		if (d != "1" && d != "2" && d != "3")//�����쳣����
		{
			cout << "��������Чѡ��";
			Sleep(1000);
			system("cls");
		}
		else
		{
			system("cls");
			if (d == "1")
			{
				usr.Register(a);
				system("cls");
			}
			else if (d == "2")
			{
				User ulogin = Login(a);
				system("cls");
				if (login)
				{
					while (1)
					{
						cout << "--------------��ӭʹ������ATM�����������в˵���ѡ�����ķ���----------" << endl;
						cout << "    " << "1.��ѯ���" << endl
							<< "    " << "2.��ȡ��" << endl
							<< "    " << "3.ת��" << endl
							<< "    " << "4.�޸�����" << endl
							<< "    " << "5.�˿�" << endl
							<< setw(52)<<"���ڴ���������ѡ��:";
						cin >> c;
						system("cls");
						if (c != "1" && c != "2" && c != "3" && c != "4"&&c!="5")
						{
							cout << "��������Чѡ��";
							Sleep(1000);
							system("cls");
						}
						if (c == "1")
						{
							ulogin.ShowBalance();
							system("cls");
						}
						else if (c == "2")
						{
                            cout << "----------------------------------��ȡ��----------------------------------" << endl;
							cout << "��ѡ��:" << endl;
							cout << "    1.���" << endl << "    2.ȡ��" << endl;
							cout << setw(52) << "����������ѡ��:"; cin >> e;
							if (e != "1" && e != "2")
							{
								cout << "��������Чѡ��";
								Sleep(1000);
								system("cls");
							}
							else if (e == "1")
							{
								system("cls");
								ulogin.SaveCash();
								Change();
							}
							else
							{
								system("cls");
								ulogin.TakeCash();
								Change();
							}
							Change();
							system("cls");
						}
						else if (c == "3")
						{
							ulogin.Transfer();
							Change();
							system("cls");
						}
						else if (c == "4")
						{
							ulogin.ChangePass(a);
							Change();
							system("cls");
						}
						else if (c == "5")
						{
							cout << "�˿��ɹ�" << endl;
							break;
						}
					}
				}
			}
			else if (d == "3")
			{
				system("cls");
				cout << "��л����ʹ��" << endl;
				break;
			}
		}
	}
	return 0;
}
