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
	std::ifstream ifs;//�����ļ��������
	ifs.open(_F_LOGIN);//���ļ�

	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));//��ȡ��һ��
	name = CString(buf);

	memset(buf, 0, sizeof(buf));//���buf
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close();
}


void CInfoFoLe::WritePwd(char* name, char* pwd)
{
	std::ofstream ofs;//�����ļ��������
	ofs.open(_F_LOGIN);//���ļ�

	ofs << name << std::endl;//��nameд���ļ�������
	ofs << pwd << std::endl;//��pwdд���ļ�������

	ofs.close();//�ر��ļ�

}
