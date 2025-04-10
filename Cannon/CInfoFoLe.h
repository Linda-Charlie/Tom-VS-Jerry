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

	//读取登录信息
	void ReadLogin(CString& name, CString& pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);
};

