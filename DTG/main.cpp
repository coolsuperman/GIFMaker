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
		if ( msg.sType == _T ("click") ) {//��갴����Ϣ��
			CDuiString strControlName = msg.pSender->GetName ();
			if ( strControlName == _T ("Load") ) {//��ȡ�ռ�����
				LoadFile ();
			}
			else if ( strControlName == _T ("Cut") ) {
				Cut ();
			}
			else if ( strControlName == _T ("SCGIF") ) {
				GenerateGifWithPic ();
			}
			else
				OnClick (msg);//��С�� ���//�رյ�Ĭ��ʵ�֣�
		}
		else if ( msg.sType == _T ("windowinit") ) {//���ڳ�ʼ����Ϣ
			//MessageBox (NULL , _T ("��ʼ��") , _T ("GIF") , IDOK);
			m_pEditStart =(CEditUI*) m_PaintManager.FindControl (_T ("WBK2"));//��ȡ��ʼ
			m_pEditStart->SetMaxChar (8);//��ȡ�ַ���������
			m_pEditEnd = (CEditUI*)m_PaintManager.FindControl (_T ("WBK3"));//��ȡ��ֹ
			m_pEditEnd->SetMaxChar (8);//��ȡ�ַ���������
		}
	}
	void LoadFile () {
		//MessageBox (NULL , _T ("����") , _T ("������") , IDOK);
		OPENFILENAME ofn;//�˽�ṹ��
		TCHAR FileName [MAX_PATH];//���ַ�
		memset (&ofn , 0 , sizeof (OPENFILENAME));
		memset (FileName , 0 , sizeof (char)*MAX_PATH);
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.lpstrFilter = _T ("��Ƶ\0*.rmvb; *.flv;*.avi;*.mp4\0");
		ofn.lpstrFile = FileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		//bool once= true;
		if ( GetOpenFileName (&ofn) )//FileName�õ��û���ѡ���ļ���·�� 
		{
			//MessageBox (NULL , FileName , NULL , NULL);
			CEditUI* pPathEdit = (CEditUI*)m_PaintManager.FindControl (_T ("WBK1"));
			pPathEdit->SetText (FileName);
			//once = false;
		}
	}
	void Cut () {
		MessageBox (NULL , _T("��ȡ��Ƶ") , _T("����") , IDOK);
	}
	void GenerateGifWithPic () {
		CDuiString strFFmepgPath = CPaintManagerUI::GetInstancePath ()+_T ("ffmpeg\\ffmpeg");//��ȡ����Ŀ¼��
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
		//�������
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