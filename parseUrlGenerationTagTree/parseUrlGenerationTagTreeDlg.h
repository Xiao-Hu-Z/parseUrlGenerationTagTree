
// parseUrlGenerationTagTreeDlg.h: 头文件
//

#pragma once


// CparseUrlGenerationTagTreeDlg 对话框
class CparseUrlGenerationTagTreeDlg : public CDialogEx
{
// 构造
public:
	CparseUrlGenerationTagTreeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARSEURLGENERATIONTAGTREE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl m_tree;
public:
	bool IsHtmlLable(CString label);
	bool IsSelfClosingLable(CString label);
	bool IsLabelAttribute(CString attributes);
	void parseUrlToHtml(CString  strUrl, CString filePath);
	void urlGenerationTagTree(CString urlFilePath);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
