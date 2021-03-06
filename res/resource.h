//stamp:107c8902138473f5
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				XML_page = _T("LAYOUT:XML_page");
				XML_MyDevice = _T("LAYOUT:XML_MyDevice");
				XML_MyDevice_Info = _T("LAYOUT:XML_MyDevice_Info");
			}
			const TCHAR * XML_MAINWND;
			const TCHAR * XML_page;
			const TCHAR * XML_MyDevice;
			const TCHAR * XML_MyDevice_Info;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _IMG{
			public:
			_IMG(){
				traymenu_icons = _T("IMG:traymenu_icons");
				png_tab_main = _T("IMG:png_tab_main");
				png_page_icons = _T("IMG:png_page_icons");
				png_logo = _T("IMG:png_logo");
				png_mydevice = _T("IMG:png_mydevice");
				png_bell = _T("IMG:png_bell");
				png_skinbtn = _T("IMG:png_skinbtn");
				png_connect_dev = _T("IMG:png_connect_dev");
				png_pro_pc_apps = _T("IMG:png_pro_pc_apps");
			}
			const TCHAR * traymenu_icons;
			const TCHAR * png_tab_main;
			const TCHAR * png_page_icons;
			const TCHAR * png_logo;
			const TCHAR * png_mydevice;
			const TCHAR * png_bell;
			const TCHAR * png_skinbtn;
			const TCHAR * png_connect_dev;
			const TCHAR * png_pro_pc_apps;
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _SMENU{
			public:
			_SMENU(){
				menu_skin = _T("SMENU:menu_skin");
				menu_tray = _T("SMENU:menu_tray");
			}
			const TCHAR * menu_skin;
			const TCHAR * menu_tray;
		}SMENU;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"Txt_Tip",65549},
		{L"_name_start",65535},
		{L"btn_close",65544},
		{L"btn_max",65542},
		{L"btn_min",65541},
		{L"btn_mydevice",65536},
		{L"btn_restore",65543},
		{L"btn_skin",65540},
		{L"face",65548},
		{L"name",65547},
		{L"tab2",65537},
		{L"tab3",65538},
		{L"tab4",65539},
		{L"tab_main",65545},
		{L"tv_ios",65546}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			Txt_Tip = namedXmlID[0].strName;
			_name_start = namedXmlID[1].strName;
			btn_close = namedXmlID[2].strName;
			btn_max = namedXmlID[3].strName;
			btn_min = namedXmlID[4].strName;
			btn_mydevice = namedXmlID[5].strName;
			btn_restore = namedXmlID[6].strName;
			btn_skin = namedXmlID[7].strName;
			face = namedXmlID[8].strName;
			name = namedXmlID[9].strName;
			tab2 = namedXmlID[10].strName;
			tab3 = namedXmlID[11].strName;
			tab4 = namedXmlID[12].strName;
			tab_main = namedXmlID[13].strName;
			tv_ios = namedXmlID[14].strName;
		}
		 const wchar_t * Txt_Tip;
		 const wchar_t * _name_start;
		 const wchar_t * btn_close;
		 const wchar_t * btn_max;
		 const wchar_t * btn_min;
		 const wchar_t * btn_mydevice;
		 const wchar_t * btn_restore;
		 const wchar_t * btn_skin;
		 const wchar_t * face;
		 const wchar_t * name;
		 const wchar_t * tab2;
		 const wchar_t * tab3;
		 const wchar_t * tab4;
		 const wchar_t * tab_main;
		 const wchar_t * tv_ios;
		}name;

		class _id{
		public:
		const static int Txt_Tip	=	65549;
		const static int _name_start	=	65535;
		const static int btn_close	=	65544;
		const static int btn_max	=	65542;
		const static int btn_min	=	65541;
		const static int btn_mydevice	=	65536;
		const static int btn_restore	=	65543;
		const static int btn_skin	=	65540;
		const static int face	=	65548;
		const static int name	=	65547;
		const static int tab2	=	65537;
		const static int tab3	=	65538;
		const static int tab4	=	65539;
		const static int tab_main	=	65545;
		const static int tv_ios	=	65546;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int infotabbk	=	3;
		const static int mainbk	=	4;
		const static int red	=	5;
		const static int white	=	6;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
