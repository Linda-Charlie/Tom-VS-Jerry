#include "pch.h"
#include "CInfoFoLe.h"

CInfoFoLe::CInfoFoLe()
{

}
CInfoFoLe::~CInfoFoLe()
{

}


void CInfoFoLe::ReadLogin(CString& name, CString& pwd)
{
	std::ifstream ifs;//创建文件输入对象
	ifs.open(_F_LOGIN);//打开文件

	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));//读取第一行
	name = CString(buf);

	memset(buf, 0, sizeof(buf));//清空buf
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close();
}


void CInfoFoLe::WritePwd(char* name, char* pwd)
{
	std::ofstream ofs;//创建文件输出对象
	ofs.open(_F_LOGIN);//打开文件

	ofs << name << std::endl;//将name写入文件并换行
	ofs << pwd << std::endl;//将pwd写入文件并换行

	ofs.close();//关闭文件

}
