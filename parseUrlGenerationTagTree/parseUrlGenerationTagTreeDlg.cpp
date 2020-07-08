
// parseUrlGenerationTagTreeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "parseUrlGenerationTagTree.h"
#include "parseUrlGenerationTagTreeDlg.h"
#include "afxdialogex.h"
#include<stack>
#include<fstream>
#include<afxinet.h> 
#include<set>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CparseUrlGenerationTagTreeDlg 对话框



CparseUrlGenerationTagTreeDlg::CparseUrlGenerationTagTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PARSEURLGENERATIONTAGTREE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CparseUrlGenerationTagTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CparseUrlGenerationTagTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CparseUrlGenerationTagTreeDlg::OnBnClickedButton1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CparseUrlGenerationTagTreeDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CparseUrlGenerationTagTreeDlg 消息处理程序

BOOL CparseUrlGenerationTagTreeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CparseUrlGenerationTagTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CparseUrlGenerationTagTreeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CparseUrlGenerationTagTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CparseUrlGenerationTagTreeDlg::IsHtmlLable(CString label)
{
	std::set<CString>labels
	{
		//HTML页面结构
		L"html",
		L"head",
		L"body",
		L"title",
		//常用标签
		L"h1",L"h2",L"h3",L"h4",L"h5",L"h6",//子标题
		L"p",//段落
		L"a",//锚(超链接)
		L"font",//字体
		L"br",//换行
		L"hr",//水平线
		L"img",//图像
		//格式化标签
		L"b",//粗体
		L"big",//大号字
		L"small",//小号字
		L"i",//斜体
		L"strong",//加重语气
		L"sub",//下标
		L"sup",//上标
		L"u",//下划线
		//列表标签
		L"u1",//无序列表，块标签
		L"o1",//有序列表，块标签
		L"li",//列表项目，块标签
		L"d1",//定义列表，块标签
		L"dt",//定义标题，块标签
		L"dd",//定义描述，块标签
		//表格相关
		L"table",//表格
		L"tr",//表行
		L"td",//单元格
		L"caption",//标题
		L"thread",//表头部分
		L"tbody",//主题部分
		L"tfoot",//定义表格的页脚（脚注或表注）
		//表单相关
		L"form",//表单
		L"input",//表单元素（输入框）
		L"select",//选择下拉框
		L"option",//选项（下拉列表项）
		L"textarea",//文本域
		//框架相关
		L"frameset",//框架集
		L"frame",//框架
		L"iframe",//内嵌框架
		//容器
		L"div",//分割（容器标签（块））
		L"span",//跨度（容器标签（行内））
			
		L"style",
		L"center",
		L"script",
		//单标签(自关闭的标签)
		L"meta",//head子标签，设置页面元信息的
		L"base",//设置网页所有链接的相对目录(如根目录)的
		L"col",//在表格table中定义一个或多个列的属性
		L"frame",//定义框架的一个窗口（已遗弃）
		L"link",//定义文档与外部资源的关系的链接
		L"area",//标签定义图像映射内部的区域（图像映射指的是带有可点击区域的图像）
		L"param",//元素允许您为插入 XHTML 文档的对象规定 run-time 设置，也就是说，此标签可为包含它的
		L"object",//标签提供参数
		L"applet",//标签提供参数
		L"embed",//HTML5 中新增的,标签定义了一个容器，用来嵌入外部应用或者互动程序（插件）
		L"keygen",//该对象提供了一个安全的方式来验证用户
		L"source",//为媒体元素（比如 和 ）定义媒体资源
		L"marquee",//普通卷动 
		L"ins",//底线(表示插入文字)
		L"nav"//标签定义导航链接的部分
	};
	if (labels.find(label) != labels.end())
		return true;
	else
		return false;
}

bool CparseUrlGenerationTagTreeDlg::IsSelfClosingLable(CString label)
{
	std::set<CString>selfClosingLable
	{   L"meta",//head子标签，设置页面元信息的
	    L"base",//设置网页所有链接的相对目录(如根目录)的
		L"br",//换行
		L"hr",//水平线
		L"img",//图像
		L"input",//表单元素
		L"col",//在表格table中定义一个或多个列的属性
		L"frame",//定义框架的一个窗口（已遗弃）
		L"link",//定义文档与外部资源的关系的链接
		L"area",//标签定义图像映射内部的区域（图像映射指的是带有可点击区域的图像）
		L"param",//元素允许您为插入 XHTML 文档的对象规定 run-time 设置，也就是说，此标签可为包含它的
		L"object",//标签提供参数
		L"applet",//
		L"embed",//HTML5 中新增的,标签定义了一个容器，用来嵌入外部应用或者互动程序（插件）
		L"keygen",//该对象提供了一个安全的方式来验证用户
		L"source",//为媒体元素（比如 和 ）定义媒体资源
		L"nav"//标签定义导航链接的部分
	};
	if (selfClosingLable.find(label) != selfClosingLable.end())
		return true;
	else
		return false;
}

bool CparseUrlGenerationTagTreeDlg::IsLabelAttribute(CString attributes)
{
	std::set<CString>LabelAttributes
	{   
		//meta属性
		L"content",
		L"http-equiv",
		L"name",
		L"scheme",
		//link属性
		L"href",//URL,超文本引用
		L"hreflang",
		L"rel",
		L"type",
		L"sizes",
		L"media",
		// 标签定义超链接，用于从一张页面链接到另一张页面,元素最重要的属性是 href 属性，它指示链接的目标

		L"src",//
		L"border",//
		L"size",//
		L"width",//
		L"height",//
		L"bgcolor",//
		L"background",//
		L"list-style",//
		L"list-style-image",//
		L"line-height",//
		L"text-align",//
		L"letter-spacing",//
		L"text-decoration",//
		L"marge-top",L"marge-right",L"marge-bottom",L"marge-left",
		L"display",//
		L"position",//
		L"float",
		L"clear",
		L"type",
		L"align"
		L"method",
		L"alt",
		L"cellpadding",
		L"cellsapcing",

		L"target",
		L"colspan",
		L"rowspan",
		L"readonly",
		L"value",
		L"maxlenght",
		L"scrolldelay",//滚动延时
		L"direction",//方向（滚动方向）
		L"http-equiv",
        //鼠标事件
		//L"onclick",//当单击鼠标时运行脚本
		//L"ondblclick",//当双击鼠标时运行脚本
		//L"onmousedown",
		//L"onmousemove",
		//L"onmouseout"
    };
	if (LabelAttributes.find(attributes) != LabelAttributes.end())
		return true;
	else
		return false;

}



void CparseUrlGenerationTagTreeDlg::parseUrlToHtml(CString  strUrl, CString urlFilePath)
{
	CInternetSession mySession(NULL, 0);
	CHttpFile* myHttpFile = NULL;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str是要打开的地址
	CString myData;
	CString  m_csHtmlContent;
	while (myHttpFile->ReadString(myData))
	{
		m_csHtmlContent += myData;
	}
	mySession.Close();
	myHttpFile->Close();
	delete myHttpFile;
	myHttpFile = NULL;

	CFile w_file;
	//如果文件事先不存在的话，需要CFile::modeCreate，否则就不需要。
	w_file.Open(urlFilePath, CFile::modeCreate | CFile::modeWrite);
	w_file.Write(m_csHtmlContent, m_csHtmlContent.GetLength());
	w_file.Flush();
	w_file.Close();
	return;

}

void CparseUrlGenerationTagTreeDlg::urlGenerationTagTree(CString urlFilePath)
{
	std::stack<HTREEITEM> tree_node_htreeitem;
	std::stack<CString> tree_node_lable;
	CString lable;
	HTREEITEM child_node = NULL;
	char pos;
	std::ifstream read_file(urlFilePath);
	read_file >> std::noskipws;//不忽略空格
	while (!read_file.eof())
	{
		lable = L"";
		read_file >> pos;//每次读取一个字符
		if (pos == '<')
		{
			read_file >> pos;
			//this is not lable
			if (pos == '!') 
			{
				char pos_add_one;
				char pos_add_two;
				read_file >> pos_add_one;
				read_file >> pos_add_two;
				if (pos_add_one == '-' && pos_add_two == '-')
				{
					while (!((pos == '-') && (pos_add_one == '-') && (pos_add_two == '>')))
					{
						pos = pos_add_one;
						pos_add_one = pos_add_two;
						read_file >> pos_add_two;
					}
				}
				else 
					continue;
			}
			else if (pos == '/')
			{
				//get close lable
				read_file >> pos;
				while (pos != '>')
				{
					lable = lable + pos;
					read_file >> pos;
				}
				if (IsHtmlLable(lable) && (!tree_node_lable.empty()))
				{
					if ((tree_node_lable.top() == lable) && (!tree_node_htreeitem.empty()))
					{
						tree_node_lable.pop();
						tree_node_htreeitem.pop();
					}
				}
			}
			else
			{
				while (pos != ' ' && pos != '>')
				{
					lable = lable + pos;
					read_file >> pos;
				}
				if (IsHtmlLable(lable))
				{
					if (tree_node_htreeitem.empty())
					{
						tree_node_htreeitem.push(m_tree.InsertItem(lable, 0, 0, NULL));
						tree_node_lable.push(lable);
					}
					else
					{
						child_node = m_tree.InsertItem(lable, 0, 0, tree_node_htreeitem.top());
						if (!IsSelfClosingLable(lable))
						{
							tree_node_htreeitem.push(child_node);
							tree_node_lable.push(lable);
						}
					}
				}
				else
					continue;
			}
		}
	}
	read_file.close();
	return;
}

void CparseUrlGenerationTagTreeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUrl = L"https://www.csdn.net/";
	CString urlFilePath = L"csdn.txt";
	//CString strUrl = L"https://www.baidu.com/";//URL地址
	//CString urlFilePath = L"..\\baidu.txt";//保存HTML文件路径

	parseUrlToHtml(strUrl, urlFilePath);//解析URL获取HTML内容并保存到urlFilePath中
	urlGenerationTagTree(urlFilePath);//读取HTML内容生成标签树

	return;
}





void CparseUrlGenerationTagTreeDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
