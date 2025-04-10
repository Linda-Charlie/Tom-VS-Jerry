#pragma once
#include "Enemy.h"
class Enemy2 :
    public Enemy
{
public:
    Enemy2();
    ~Enemy2();

    void Show(CDC* pDC);

    CString strImgPathName = GetExePath() + L"sourse\\enemy2.png";
    CImage m_imgenemy2;
};

