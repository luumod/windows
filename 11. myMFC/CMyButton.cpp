// CMyButton.cpp: 实现文件
//

#include "pch.h"
#include "11. myMFC.h"
#include "CMyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CMyButton::OnBnClicked)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyButton 消息处理程序




void CMyButton::OnBnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBoxW(L"控件处理消息");
}


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//1. 获取父窗口区域
	CRect ParRect{ 0 };
	GetParent()->GetClientRect(ParRect);
	//2. 获取按钮区域
	CRect ButRect{ 0 };
	GetClientRect(ButRect);
	//3. 获取随机坐标
	UINT x = rand() % (ParRect.Width() - ButRect.Width());
	UINT y = rand() % (ParRect.Height() - ButRect.Height());
	ButRect.MoveToXY(x, y);
	MoveWindow(ButRect);

	CButton::OnMouseMove(nFlags, point);
}
