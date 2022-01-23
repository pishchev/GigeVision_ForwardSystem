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
	, _configurator(_T(""))
{

}

CGigeProprtyDlg::~CGigeProprtyDlg()
{
}

void CGigeProprtyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _configurator);
}


BEGIN_MESSAGE_MAP(CGigeProprtyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CGigeProprtyDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CGigeProprtyDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Обработчики сообщений CGigeProprtyDlg


BOOL CGigeProprtyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
								// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CGigeProprtyDlg::OnOK()
{	
	CT2A cnvtr(_configurator, CP_UTF8);
	useConfig(_prev, std::string(cnvtr));
	*_isSet = true;
	CDialogEx::OnOK();
}

void CGigeProprtyDlg::OnBnClickedButton2()
{

}

void CGigeProprtyDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	GetDlgItemText(IDC_EDIT1, _configurator);
}
