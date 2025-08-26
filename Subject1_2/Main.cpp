#pragma comment(lib, "Winmm.lib")
#include "Vector.h"
#include <iostream>
#include <stdlib.h>
#include <memory>
class CardInfo
{
public:
	CardInfo()
	{

	}
	void SetId(int id) { _id = id; }
	void SetName(char* name) { 
		if (_name != nullptr)
		{
			delete[]_name;
		}
		_name = std::move(name); name = nullptr; }
	void SetType(char* type) { 
		if (_type != nullptr)
		{
			delete[]_type;
		}
		_type = std::move(type); type = nullptr; }
	void SetCost(int cost) { _cost = cost; }
	void SetRarity(int rarity) { _rarity = rarity; }
	
	CardInfo(int id, const char* name, const char* type, int cost, int rarity)
		: _id(id), _cost(cost), _rarity(rarity)
	{
		int size = strlen(name) + 1;
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, size, name);

		size = strlen(type) + 1;
		_type = new char[strlen(type) + 1];
		strcpy_s(_type, size, type);
	}

	CardInfo(CardInfo&& rhs)
		: _id(rhs._id), _cost(rhs._cost), _rarity(rhs._rarity)
	{
		_name = std::move(rhs._name);
		_type = std::move(rhs._type);
		rhs._type = nullptr;
		rhs._name = nullptr;
		
	}

	friend std::ostream& operator<<(std::ostream& os, CardInfo& ci)
	{
		return os << "아이디 번호: " << ci._id << "\n"
			"이름: " << ci._name << "\n"
			"타입: " << ci._type << "\n"
			"비용: " << ci._cost << "\n"
			"특수성: " << ci._rarity << "\n";
	}
	~CardInfo()
	{
		delete[] _name;
		delete[] _type;
	}

private:
	int _id = 0;
	char* _name = nullptr;
	char* _type = nullptr;
	int _cost = 0;;
	int _rarity = 0;
};
TVector<CardInfo*> v;

char buffer[65536];
#include <string>
#include <Windows.h>
void FileIo()
{
	FILE* fp;
	fopen_s(&fp, "CardDatabase.csv", "rt");
	if (fp == nullptr) {
		DebugBreak();
		return ;
	}
	size_t ret = fread(buffer, sizeof(char), 65536, fp);
	buffer[ret] = 0;

	std::string str;
	int fileIdx = 0;
	while (true) {
		CardInfo tmpCard;
		int idx = 0;
		bool flag = true;
		while (true)
		{
			if (buffer[fileIdx] == '\n' || buffer[fileIdx] == ',' || buffer[fileIdx] == '\0')
			{
				if (idx == 0)
				{
					int value;
					try
					{
						value = std::stoi(str.c_str());
						tmpCard.SetId(value);
					}
					catch (const std::exception&)
					{
						flag = false;
					}
					idx++;

				}
				else if (idx == 1)
				{
					char* tempName = new char[str.size() + 1];
					strcpy_s(tempName, str.size() + 1, str.data());
					tmpCard.SetName(tempName); idx++;
				}
				else if (idx == 2)
				{
					char* tempName = new char[str.size() + 1];
					strcpy_s(tempName, str.size() + 1, str.data());
					tmpCard.SetType(tempName); idx++;
				}
				else if (idx == 3)
				{
					int value;
					try
					{
						value = std::stoi(str.c_str());
						tmpCard.SetCost(value);
					}
					catch (const std::exception&)
					{
						flag = false;
					}
					idx++;
				}
				else if (idx == 4)
				{
					int value;
					try
					{
						value = std::stoi(str.c_str());
						tmpCard.SetRarity(value);
					}
					catch (const std::exception&)
					{
						flag = false;
					}
					if (flag == true)
					{
						v.PushBack(new CardInfo(std::move(tmpCard)));
					}
					flag = true;
					idx = 0;
				}

				str.clear();
				if (buffer[fileIdx] == '\0')
					return;
			}
			else
			{
				str.push_back(buffer[fileIdx]);
			}
			fileIdx = fileIdx + 1;

			
		}

	}
}
int keyDown[255];

bool GetKeyDownUndo()
{
	return keyDown[VK_OEM_COMMA];
}
bool GetKeyDownRedo()
{
	return keyDown[VK_OEM_PERIOD];
}

int main()
{

	FileIo();

	for (int i = 0; i < v.Size(); ++i)
	{
		std::cout << *v[i] << '\n';
	}

	int a = 0;

	int remainTime = 200;
	DWORD lastTime = timeGetTime();
	while (true)
	{
		for (int i = 0; i < 255; ++i) {
			SHORT result = GetAsyncKeyState(i);
			if (result & 0x8000) {
				keyDown[i] = true;
			}
		}
		if (GetKeyDownUndo()) {
			CardInfo* cur;
			v.PopFront(cur);
			v.PushBack(cur);
			v.Front(cur);
			std::cout << *cur << '\n';

		}
		if (GetKeyDownRedo()) {
			CardInfo* cur;
			v.PopBack(cur);
			v.PushFront(cur);
			v.Front(cur);
			std::cout << *cur << '\n';
		}
		// Clear
		for (int i = 0; i < 255; ++i) {
			keyDown[i] = 0;
		}
		Sleep(10);
	}
}