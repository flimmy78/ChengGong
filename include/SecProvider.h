// SecProvider.h: interface for the SecProvider class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECPROVIDER_H__09D80750_B862_4138_8233_DB7523D0BD51__INCLUDED_)
#define AFX_SECPROVIDER_H__09D80750_B862_4138_8233_DB7523D0BD51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����ģ�������ļ�
BOOL WINAPI ImpModelData(LPCSTR lpPath);

//����ģ�������ļ�
BOOL WINAPI ExpModelData(LPCSTR lpDB,LPCSTR lpPath);

//��������
BOOL WINAPI ImpSection(LPCSTR lpPath);

//���������
BOOL WINAPI ExpSection(LPCSTR lpPath);

#endif // !defined(AFX_SECPROVIDER_H__09D80750_B862_4138_8233_DB7523D0BD51__INCLUDED_)
