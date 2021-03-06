// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include "CDataCenter.h"

#include "iOsDeviceLib/iOSUtils.h"

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

void LoadSkinFormXml(SDemoSkin* skin, SkinType* skinType, SkinLoadInf* skininf)
{
	SStringT strSkinConfigPath = SApplication::getSingleton().GetAppDir() + _T("\\themes\\skin_config.xml");

	pugi::xml_document docLoad;
	pugi::xml_parse_result result = docLoad.load_file(strSkinConfigPath);
	if (result)
	{
		pugi::xml_node skinInf = docLoad.child(L"DEMO_SKIN_CONFIG").child(L"skinInf");
		*skinType = (SkinType)skinInf.attribute(L"type").as_int();
		switch (*skinType)
		{
			//纯色只有SkinSaveInf的color有效
		case color:
			skininf->color = skinInf.attribute(L"color").as_int();
			break;
			//此处为系统皮肤，只需要给文件路径和margin
		case sys:
			skininf->filepath = skinInf.attribute(L"skin_path").as_string();
			int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
			swscanf(skinInf.attribute(L"skin_margin").as_string(), L"%d,%d,%d,%d", &v1, &v2, &v3, &v4);
			skininf->margin.left = v1;
			skininf->margin.top = v2;
			skininf->margin.right = v3;
			skininf->margin.bottom = v4;
			break;
		}
	}
}

bool CMainDlg::LoadSkin()
{
	SDemoSkin* skin = (SDemoSkin*)GETSKIN(L"skin_bk", GetScale());
	if (skin)
	{
		SkinLoadInf loadInf;
		SkinType type;
		LoadSkinFormXml(skin, &type, &loadInf);

		if (type == SkinType::color)
		{
			SStringW bkColor;
			bkColor.Format(L"#%02x%02x%02x%02x",
				GetRValue(loadInf.color),
				GetGValue(loadInf.color),
				GetBValue(loadInf.color),
				GetAValue(loadInf.color));
			FindChildByID(R.id.Txt_Tip)->SetAttribute(L"colorText", bkColor);
		}

		skin->SetHander(this);
		return skin->LoadSkin(type, loadInf);
	}
	return false;
}

void CMainDlg::ShowToolTip(LPCTSTR tipMsg)
{
	SShellNotifyIcon* notify = FindChildByID2<SShellNotifyIcon>(110);
	notify->ShowNotify(L"idou", tipMsg);
}

void CMainDlg::OnSkin()
{
	SWindow* pWnd = FindChildByID(R.id.btn_skin);
	if (pWnd)
	{
		CRect rcWnd = pWnd->GetWindowRect();
		ClientToScreen(&rcWnd);
		SMenuEx menu;
		menu.LoadMenu(_T("SMENU:menu_skin"));
		menu.TrackPopupMenu(0, rcWnd.left - 182, rcWnd.bottom + 4, m_hWnd);
	}
}

void CMainDlg::OnSetSkin(int id)
{
	LPCTSTR skinColor[] = { _T("#236ee7"), _T("#3baca2"),_T("#e79481") ,
		_T("#e1839f"), _T("#e97474"), _T("#8eae48"),
		_T("#7f74d1"), _T("#d59d66"), _T("#9f887a") };
	COLORREF color;
	if (SColorParser::ParseValue(skinColor[id - 600], color))
	{
		SDemoSkin* skin = (SDemoSkin*)GETSKIN(L"skin_bk", GetScale());
		if (skin)
		{
			skin->SetColor(color);
			FindChildByID(R.id.Txt_Tip)->SetAttribute(L"colorText", skinColor[id - 600]);
			SWindow::Invalidate();
		}
	}
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	//SShellNotifyIcon *notify = FindChildByID2<SShellNotifyIcon>(110);
	//notify->ShowNotify(L"Hello SOUI",L"这可能是一个提示");

	m_mainTabBinder.BindHost(FindChildByID2<STabCtrl>(R.id.tab_main));
	m_mainTabBinder.Bind(FindChildByID(R.id.btn_mydevice), 0);
	m_mainTabBinder.Bind(FindChildByID(R.id.tab2), 1);
	m_mainTabBinder.Bind(FindChildByID(R.id.tab3), 2);
	m_mainTabBinder.Bind(FindChildByID(R.id.tab4), 3);

	STreeView* pTreeView = FindChildByName2<STreeView>("tv_ios");
	if (pTreeView)
	{
		m_pTreeViewAdapter.Attach(new CiOSDeviceTreeViewAdapter(this));

		CDataCenter::getSingleton().AddDevGUID("000-00-00-00-00", m_pTreeViewAdapter);
		CDataCenter::getSingleton().AddDevGUID("000-00-00-00-01", m_pTreeViewAdapter);

		pTreeView->SetAdapter(m_pTreeViewAdapter);
	}

	CiOSDevice::SetCallBack(this);

	LoadSkin();
	return 0;
}
bool CMainDlg::SaveSkin(SkinType skinType, SkinSaveInf & skinSaveInf)
{
	pugi::xml_document docSave;
	pugi::xml_node rootNode = docSave.append_child(L"DEMO_SKIN_CONFIG");
	pugi::xml_node childSkinType = rootNode.append_child(L"skinInf");
	childSkinType.append_attribute(L"type") = skinType;
	SStringT strSkinConfigPath = SApplication::getSingleton().GetAppDir() + _T("\\themes\\skin_config.xml");
	switch (skinType)
	{
	case color://纯色只有SkinSaveInf的color有效
		childSkinType.append_attribute(L"color") = (int)skinSaveInf.color;
		break;
	case sys://此处为系统皮肤，只需要给文件路径和margin
	{
		childSkinType.append_attribute(L"skin_path") = skinSaveInf.filepath;
		SStringW margin;
		margin.Format(L"%d,%d,%d,%d", skinSaveInf.margin.left, skinSaveInf.margin.top, skinSaveInf.margin.right, skinSaveInf.margin.bottom);
		childSkinType.append_attribute(L"skin_margin") = margin;
	}
	break;
	case builtin:
	default:
		break;
	}
	return docSave.save_file(strSkinConfigPath);
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
	SDemoSkin* skin = (SDemoSkin*)GETSKIN(L"skin_bk", GetScale());
	if (skin)
	{
		skin->SaveSkin();
	}
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	//SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	ShowWindow(SW_HIDE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;

	SWindow* pBtnMax = FindChildByName(L"btn_max");
	SWindow* pBtnRestore = FindChildByName(L"btn_restore");
	if (!pBtnMax || !pBtnRestore) return;

	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}


//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}


void CMainDlg::ChildMenuItemClick(int nGID)
{

}

void CMainDlg::ChildMenuItemDBClick(int nGID)
{

}

void CMainDlg::ChildMenuItemRClick(int nGID)
{

}

void CMainDlg::idevice_event_cb_t(const idevice_event_t * event)
{
	//conn_type没什么用始终为1，
	//event 
	//IDEVICE_DEVICE_ADD = 1,添加
	//IDEVICE_DEVICE_REMOVE,拔出
	//IDEVICE_DEVICE_PAIRED 配对，一个新设备，会先收到添加，如果在手机点击信任电脑会收到配对
	switch (event->event)
	{
	case IDEVICE_DEVICE_ADD:
	{
		SStringT udid = S_CA2T(event->udid, CP_UTF8);
		
		if (CiOSDevice::IsPair(event->udid))
		{
			CiOSDevice mydev;
			if (mydev.OpenDevice(event->udid))
			{
				int battery;
				mydev.GetBattery(batteryKey[0], battery);
				
				SMessageBox(NULL, SStringT().Format(L"插入设备：%s----%s\n电池电量:%d", udid,  L"已配对",battery), L"", MB_OK);
			}
			else
			{
				SMessageBox(NULL, SStringT().Format(L"插入设备：%s----%s", udid, L"已配对但无法连接设备，可能已被其它应用占用"), L"", MB_OK);
			}
			
		}
		else
		{
			SMessageBox(NULL, SStringT().Format(L"插入设备：%s----%s", udid, L"未配对"), L"", MB_OK);
		}

	}break;
	case IDEVICE_DEVICE_REMOVE: {
		SStringT udid = S_CA2T(event->udid, CP_UTF8);
		SMessageBox(NULL, SStringT().Format(L"%s：%s", L"拔出设备", udid), L"", MB_OK);
	}break;
	case IDEVICE_DEVICE_PAIRED: {
		SStringT udid = S_CA2T(event->udid, CP_UTF8);
		SMessageBox(NULL, SStringT().Format(L"%s：%s", L"配对设备", udid), L"", MB_OK);
	}break;
	}
}
