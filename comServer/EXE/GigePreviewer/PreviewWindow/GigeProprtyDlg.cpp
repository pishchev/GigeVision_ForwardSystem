// GigeProprtyDlg.cpp: файл реализации
//

#include "pch.h"
#include "PreviewWindow.h"
#include "GigeProprtyDlg.h"
#include "afxdialogex.h"


// Диалоговое окно CGigeProprtyDlg

IMPLEMENT_DYNAMIC(CGigeProprtyDlg, CDialogEx)

CGigeProprtyDlg::CGigeProprtyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CGigeProprtyDlg, pParent)
{

}

CGigeProprtyDlg::~CGigeProprtyDlg()
{
}

void CGigeProprtyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INTERFACE_LIST, m_InterfaceList);
}


BEGIN_MESSAGE_MAP(CGigeProprtyDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CGigeProprtyDlg


BOOL CGigeProprtyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	m_InterfaceList.AddString(_T("test1"));
	m_InterfaceList.AddString(_T("test2"));
	m_InterfaceList.AddString(_T("test3"));
	m_InterfaceList.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
								// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CGigeProprtyDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialogEx::OnOK();
}
