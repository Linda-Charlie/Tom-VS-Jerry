#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include "pch.h"

#define _F_LOGIN "./login.int"

struct pattern
{
	int speed;
	int num;
};

class CInfoFoLe
{
public:
	CInfoFoLe();
	~CInfoFoLe();

	//��ȡ��¼��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);
};

