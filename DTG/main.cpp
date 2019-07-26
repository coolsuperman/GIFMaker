#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include <tchar.h>
#include"Head.h"


class CDuiFrameWnd : public WindowImplBase {
	private:
	CEditUI* m_pEditStart;
	CEditUI* m_pEditEnd;
	public:
	virtual LPCTSTR    GetWindowClassName () const { 
		return _T ("DUIMainFrame");
	}
	virtual CDuiString GetSkinFile () { 
		return _T ("duilib.xml");
	}
	virtual CDuiString GetSkinFolder () { 
		return _T (""); 
	}
	virtual void Notify (TNotifyUI& msg) {
		if ( msg.sType == _T ("click") ) {//鼠标按键消息；
			CDuiString strControlName = msg.pSender->GetName ();
			if ( strControlName == _T ("Load") ) {//获取空间名字
				LoadFile ();
			}
			else if ( strControlName == _T ("Cut") ) {
				Cut ();
			}
			else if ( strControlName == _T ("SCGIF") ) {
				GenerateGifWithPic ();
			}
			else
				OnClick (msg);//最小化 最大化//关闭的默认实现；
		}
		else if ( msg.sType == _T ("windowinit") ) {//窗口初始化消息
			//MessageBox (NULL , _T ("初始化") , _T ("GIF") , IDOK);
			m_pEditStart =(CEditUI*) m_PaintManager.FindControl (_T ("WBK2"));//获取起始
			m_pEditStart->SetMaxChar (8);//摄取字符最大个数；
			m_pEditEnd = (CEditUI*)m_PaintManager.FindControl (_T ("WBK3"));//获取终止
			m_pEditEnd->SetMaxChar (8);//摄取字符最大个数；
		}
	}
	void LoadFile () {
		//MessageBox (NULL , _T ("测试") , _T ("标题栏") , IDOK);
		OPENFILENAME ofn;//了解结构体
		TCHAR FileName [MAX_PATH];//宽字符
		memset (&ofn , 0 , sizeof (OPENFILENAME));
		memset (FileName , 0 , sizeof (char)*MAX_PATH);
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.lpstrFilter = _T ("视频\0*.rmvb; *.flv;*.avi;*.mp4\0");
		ofn.lpstrFile = FileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		//bool once= true;
		if ( GetOpenFileName (&ofn) )//FileName得到用户所选择文件的路径 
		{
			//MessageBox (NULL , FileName , NULL , NULL);
			CEditUI* pPathEdit = (CEditUI*)m_PaintManager.FindControl (_T ("WBK1"));
			pPathEdit->SetText (FileName);
			//once = false;
		}
	}
	void Cut () {
		MessageBox (NULL , _T("截取视频") , _T("测试") , IDOK);
	}
	void GenerateGifWithPic () {
		CDuiString strFFmepgPath = CPaintManagerUI::GetInstancePath ()+_T ("ffmpeg\\ffmpeg");//获取工程目录；
		SHELLEXECUTEINFO strSEInfo;
		memset (&strSEInfo ,0, sizeof (SHELLEXECUTEINFO));
		strSEInfo.cbSize = sizeof (SHELLEXECUTEINFO);
		strSEInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		strSEInfo.lpFile = _T ("C:/Windows/System32/cmd.exe");
		CDuiString strPictruePath = CPaintManagerUI::GetInstancePath () + _T ("ffmpeg\\Pictrue\\%d.jpg ");
		CDuiString strOutPath = CPaintManagerUI::GetInstancePath () + _T ("ffmpeg\\Pictrue\\out.gif");
		CDuiString strCMD (_T ("/c"));
		strCMD += strFFmepgPath + _T (" -r 1 -i ") + strPictruePath + strOutPath;
		strSEInfo.lpParameters = strCMD;
		strSEInfo.nShow = SW_HIDE;
		//发送命令；
		ShellExecuteEx(&strSEInfo);
		WaitForSingleObject (strSEInfo.hProcess , INFINITE);
	}
	void GenersteGifWithView () {

	}
};

int APIENTRY _tWinMain (HINSTANCE hInstance , HINSTANCE hPrevInstance , LPTSTR lpCmdLine , int nCmdShow) {
	CPaintManagerUI::SetInstance (hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create (NULL , _T ("DUIWnd") , UI_WNDSTYLE_FRAME , WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow ();
	duiFrame.ShowModal ();
	return 0;
}