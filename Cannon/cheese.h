#pragma once
#include "Shell.h"
class cheese :
    public Shell
{
public:
    cheese();
    ~cheese();

    void Show(CDC* pDC);

    CString strImgPathName = GetExePath() + L"sourse\\cheese.png";
    CImage m_imgcheese;
};

