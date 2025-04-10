#pragma once
#include"Shell.h"

class Enemy :
    public Shell
{
public:
    Enemy();
    ~Enemy();

    void Show(CDC* pDC);

    CString strImgPathName = GetExePath() + L"sourse\\enemy1.png";
    CImage m_imgenemy;

    //CString pattern[3] = { L"difficult",L"middle",L"easy" };
};

