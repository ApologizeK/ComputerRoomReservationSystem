#include"orderFile.h"


void makemap(string str, map<string, string>& m)
{
	string key;
	string value;
	int pos = str.find(":");
	if (pos != -1)
	{
		key = str.substr(0, pos);
		value = str.substr(pos + 1, str.size() - pos - 1);
		m.insert(pair<string, string>(key, value));
	}
}

OrderFile::OrderFile()
{
	ifstream ifs(ORDER_FILE, ios::in);
	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	this->m_size = 0;

	while (ifs >> date && ifs >> interval && ifs 
		>> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//cout << date << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl;
		//cout << status << endl;

		//string key;
		//string value;
		//map<string, string>m;
		////interval:111
		//int pos = date.find(":");
		//if (pos != -1)
		//{
		//	key = date.substr(0, pos);
		//	value = date.substr(pos + 1, date.size() - pos - 1);
		//	m.insert(pair<string, string>(key, value));
		//}

		//pos = interval.find(":");
		//if (pos != -1)
		//{
		//	key = interval.substr(0, pos);
		//	value = interval.substr(pos + 1, interval.size() - pos - 1);
		//	m.insert(pair<string, string>(key, value));
		//}


		//pos = interval.find(":");
		//if (pos != -1)
		//{
		//	key = interval.substr(0, pos);
		//	value = interval.substr(pos + 1, interval.size() - pos - 1);
		//	m.insert(pair<string, string>(key, value));
		//}

		map<string, string>m;
		makemap(date, m);
		makemap(interval, m);
		makemap(stuId, m);
		makemap(stuName, m);
		makemap(roomId, m);
		makemap(status, m);
		this->m_orderData.insert(pair<int, map<string, string>>(this->m_size, m));
		this->m_size++;
	}
	ifs.close();

	//for (map<int, map<string, string>>::iterator it = this->m_orderData.begin();
	//	it != this->m_orderData.end(); it++)
	//{
	//	cout << "条数 " << it->first << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin();
	//		mit != (*it).second.end(); mit++)
	//	{
	//		cout << " key = " << (*mit).first << " value = " << (*mit).second << " ";
	//	}
	//	cout << endl;
	//}
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out|ios::trunc);
	for (int i = 0; i < this->m_size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
}