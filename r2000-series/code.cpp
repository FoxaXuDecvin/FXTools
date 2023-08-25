//Developer Code:
// Build  --Build Version, not release.  - B1101
// Preview  --Developer Preview Version, Ready to Release.  --P1104
// Release  --Release Version, Public Version.  --R1109

#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\CppHeader\7zipAPI.h"

using namespace std;

string GETRES(string block,string title) {
	string file = "CCF.inis";
	string PATH = getselfpath();
	string ResFile = PATH + "\\" + file;
	
	return readini(ResFile, block, title);
}

string TestConnectServer(){
	string RETURNCODE;

	string SWITCHTEST = GETRES("Net", "Switch");
	if (SWITCHTEST == "off") {
		RETURNCODE = "DISABLED";
		return RETURNCODE;
	}
	string URLS = GETRES("Net", "TestURL");
	string URLV = GETRES("Net", "TestURLCode");

	string GETCODEX = geturlcode(URLS);
	WriteGlobal("ServerReturnDefault", GETCODEX);
	if (URLV == GETCODEX) {
		RETURNCODE = "TRUE";
		return RETURNCODE;
	}
	else {
		RETURNCODE = "FALSE";
		return RETURNCODE;
	}
}

string UpdateNow() {
	string CODES;

	string ServerTestX = GetGlobal("TCS");
	if (ServerTestX == "true") {}
	else {
		CODES = "FAILED";
		return CODES;
	}

	string GETURLUPDATEAPI = GETRES("NET", "UpdateAPI");
	string LVersion = geturlcode(GETURLUPDATEAPI);

	string CVersion = GETRES("Current", "VCODE");
	
	if (LVersion == CVersion) {
		CODES = "NOUPDATE";
		return CODES;
	}
	else {
		CODES = "NEW";
		return CODES;
	}
}

int main() {
	FXReloadAPI:

	cout << "FXTools. By FoxaXu" << endl;

	string VCODE = "R2115";
	string selfadr = getselfinfo();
	string file = "CCF.inis";
	string PATH = getselfpath();
	string ResFile = PATH + "\\" + file;

	int PPID = getpid();

	//日志API

	string logfile = PATH + "\\" + "Latest.log";

	ofstream OutputLog;
	OutputLog.open(logfile);

	string DATEINFO = getwinenv("date");
	string TIMEINFO = getwinenv("time");

	OutputLog << "[Start Time] " << DATEINFO << " / " << TIMEINFO << endl;
	OutputLog << "Start to Record Log" << endl;
	OutputLog << "FXTools VCODE :  " <<VCODE << endl;

	//Launch Test

	OutputLog << "Loading Resources" << endl;
	if (_access(ResFile.c_str(), 0)) {
		//install Mode
		OutputLog << "Install Resources File" << endl;
		cout << "Prepare install Resources File CCF.inis" << endl;
		URLDown("https://developer.foxaxu.com/SoftwareUpdate/FXToolAPI/defaultconfig.inis", ResFile);
		if (_access(ResFile.c_str(), 0)) {
			cout << "Download CCF.inis Failed. Try to use other version to run" << endl;
			cout << "Press any key to Exit" << endl;
			getchar();
			return 0;
		}
		cout << "Check Res Version" << endl;
		string ResFVCODE = readini(ResFile, "Current","VCODE");
		if (ResFVCODE == VCODE) {}
		else {
			cout << "Warning, The Res File Version is not support your version,please use Version: " << ResFVCODE << " ,to install this tool" << endl;
			cout << "Current Version : _ " << VCODE << "_ .ResFile Support Version :  _" << ResFVCODE << "_" << endl;
			cout << "Press Enter to Try Run" << endl;
			getchar();
		}
		ShellExecute(0, "open", selfadr.c_str(), 0, 0, SW_SHOW);
		return 0;
	}

	string ConsoleTitle = GETRES("mainUI", "ConsoleTitle");
	OutputLog << "Set Console Title :   " << ConsoleTitle << endl;
	SetConsoleTitle(ConsoleTitle.c_str());

	//检查运行目录是否存在空格
	string checkfilePAUSE = PATH + "\\CCF.inis";
	if (_access(checkfilePAUSE.c_str(), 0)) {
		cout << "Warning: Your Path The run path does not support spaces" << endl;
		cout << "Press any key to Exit" << endl;
		getchar();
		return 0;
	}

	//连接服务器
	cout << "Launching FoxaXu Tools..." << endl;
	cout << "Please wait..      Loading Files" << endl;
	string CMD;
	string AllowEula;
	string EFile = PATH + "\\AllowEula";

	//尝试对接服务器
	string URLGG = GETRES("Net", "TestURL");
	OutputLog << "Try to Connect Server" << endl;
	OutputLog << "Server CDS :   " << URLGG << endl;
	string cx = TestConnectServer();
	if (cx == "DISABLED") {
		OutputLog << "Connect Server is Disabled" << endl;
	}
	string SerVT = GetGlobal("ServerReturnDefault");

	OutputLog << "Server Return Data :   " << SerVT << endl;

	if (cx == "TRUE") {
		OutputLog << "Connect Server Succeed" << endl;
		WriteGlobal("TCS", "true");
	}
	else {
		OutputLog << "Connect Server Failed" << endl;
		WriteGlobal("TCS", "false");
	}

	string ServerTest = GetGlobal("TCS");

	system("cls");

	//检查 7zip模块
	OutputLog << "Check 7Zip Plugin Support" << endl;
	string fdinfo = PATH + "\\7zip";
	string n7zFilePathN = PATH + "\\7zip\\7z.exe";
	bool fdtest = existfolder(fdinfo);
	if (fdtest) {}
	else {
		cout << "Installing Extend 7zip" << endl;
		cout << "Please wait" << endl;
		if (ServerTest == "false") {
			cout << endl;
			cout << "[ERROR] Cannot Connect.Check your internet.or config had set Net Switch off" << endl;
			cout << "TCS Code is :  " << ServerTest << endl;
			cout << "Press Enter to Exit" << endl;
			getchar();
			return 0;
		}
		else {
			cout << "GET URL" << endl;
			string n7zexe = geturlcode(GETRES("Net", "7zInstallEXEAPI"));
			string n7zdll = geturlcode(GETRES("Net", "7zInstallDLLAPI"));
			cout << "Start Download.." << endl;
			cout << "Download 7z.exe" << endl;
			clearfolder(fdinfo);
			Sleep(800);
			string dsfpath = fdinfo + "\\7z.exe";
		ReDownload7z:
			URLDown(n7zexe, dsfpath);
			if (_access(dsfpath.c_str(), 0)) {
				cout << "7z.exe Download Failed" << endl;
				cout << "Try again" << endl;
				cout << endl;
				goto ReDownload7z;
			}

			cout << "Download 7z.dll" << endl;
			dsfpath = fdinfo + "\\7z.dll";
		ReDownload7zdll:
			URLDown(n7zdll, dsfpath);
			if (_access(dsfpath.c_str(), 0)) {
				cout << "7z.dll Download Failed" << endl;
				cout << "Try again" << endl;
				cout << endl;
				goto ReDownload7zdll;
			}
			cout << "Prep 7z Complete" << endl;
			Sleep(1000);
		}
	}

	system("cls");

	//自动获取数字证书
	string FXCert = PATH + "\\FoxaXu-Root-CA.cer";
	if (_access(FXCert.c_str(), 0)) {
		cout << "Check Cert File" << endl;
		cout << "Download Cert" << endl;
		string URLDs = geturlcode(GETRES("FoxaXu", "certfile"));
		URLDown(URLDs, FXCert);
		if (_access(FXCert.c_str(), 0)) {
			cout << "Get Cert File Failed" << endl;
		}
		cout << "OK" << endl;
		Sleep(1000);
		system("cls");
	}

	//检查 ResFile
	string ResFileFD = PATH + "\\ResFile";
	bool resfile = existfolder(ResFileFD);
	if (resfile) {}
	else {
		cout << "Prepare Resources Pack" << endl;
		cout << "make Folder" << endl;
		mdfolder(ResFileFD);

		string URLD = geturlcode(GETRES("Net", "resfilepackAPI"));
		string DSV = PATH + "\\temp~resfile.zip";
	ReDownloadRSP:

		cout << "Download File" << endl;
		URLDown(URLD, DSV);

		cout << "Check Download" << endl;
		Sleep(500);
		if (_access(DSV.c_str(), 0)) {
			cout << "Download Res Pack Failed" << endl;
			cout << "Try Again.. Please wait" << endl;
			goto ReDownloadRSP;
		}

		cout << "Unzip the file" << endl;
		n7zUNZIP(n7zFilePathN, DSV, ResFileFD, "0");
		cout << "Complete" << endl;
		Sleep(2000);
		remove(DSV.c_str());
	}

	//分界线

	//检查Extend
	string extendfolder = PATH + "\\Extend";
	bool retfdex = existfolder(extendfolder);
	if (retfdex){}
	else {
		mdfolder(extendfolder);
		cmarkfile(extendfolder + "\\.fxmark", "Copyright-FoxaXu");
	}

	//安装MSVC插件
	system("cls");
	string MSVCChekFile = PATH + "\\msvcp140.dll";
	if (_access(MSVCChekFile.c_str(), 0)) {
		cout << "Check Microsoft Visual C++ Runtime Pack" << endl;
		//下载安装MSVC包
		cout << "Start Download Microsoft Visual C++ Runtime Pack" << endl;
		Sleep(1000);
		string DURLsMS = geturlcode(GETRES("Net", "MsvcpAPI"));
		string Dtemp = PATH + "\\$temp~msvcp.zip";
	ReDownloadMSVCP:
		cout << "Connecting to SoftwareUpdate Cloud Disk Service..." << endl;
		URLDown(DURLsMS, Dtemp);
		if (_access(Dtemp.c_str(), 0)) {
			cout << "Failed to Download Microsoft Visual C++ Runtime Pack." << endl;
			cout << "Install MSVCP Pack Failed. " << endl;
			cout << "Press any key to Try again" << endl;
			getchar();
			goto ReDownloadMSVCP;
		}
		cout << "Unzip MSVCP Pack File" << endl;
		n7zUNZIP(n7zFilePathN, Dtemp, PATH, "0");
		cout << "Complete to prepare msvcp" << endl;
		Sleep(1500);
		remove(Dtemp.c_str());
		system("cls");
	}
	//安装UpdateCore
	string UpdateCoreFile = PATH + "\\Updater.exe";
	if (_access(UpdateCoreFile.c_str(), 0)) {
		cout << "Install Update Core..." << endl;
		string UCFURL = geturlcode(GETRES("Net", "UpdateCoreAPI"));
		URLDown(UCFURL, UpdateCoreFile);
		cout << "Downloading Core File ..." << endl;
		Sleep(1500);
		system("cls");
		if (_access(UpdateCoreFile.c_str(), 0)) {
			cout << endl;
			cout << "Download Update Core Failed" << endl;
			cout << "Press Enter to Skip Download Update" << endl;
			getchar();
			system("cls");
		}

	}


	//加载EULA
	if (_access(EFile.c_str(), 0)) {}
	else {
		goto SkipEula;
	}
	Sleep(1000);

	CMD = "type \"" + PATH + "\\ResFile\\Text\\EULA.txt\"";
	system("cls");
	system(CMD.c_str());

	cout << endl << " allow. if else please close this window. $";
	getline(cin, AllowEula);
	if (AllowEula == "allow") {
		ofstream MarkAllowEula;
		MarkAllowEula.open(EFile);
		MarkAllowEula << "allow" << endl;
		MarkAllowEula.close();
		ShellExecute(0, "open", selfadr.c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	else {
		system("cls");
		cout << "You are Disallow this eula" << endl;
		getchar();
		return 0;
	}

SkipEula:

	//输出标题
	CMD = "type \"" + PATH + "\\ResFile\\Text\\LaunchTitle.txt\"";
	system(CMD.c_str());
	cout << endl;
	if (ServerTest == "true") {
		OutputLog << "FXTools is running on [Online] Mode" << endl;
		cout << "Online" << endl;
	}
	else {
		OutputLog << "FXTools is running on [Offline] Mode" << endl;
		cout << "Offline" << endl;
	}

	string LINECHAT;
	
	string ConsoleShell = GETRES("mainUI", "ConsoleShell");
	string RVCODE = GETRES("Current", "VCODE");
	if (RVCODE == VCODE) {}
	else {
		cout << "Warning. FX Tools, Running on Uncompatible Mode,Please Update your version or reinstall fxtools" << endl;
	}
	OutputLog << "Console Shell Text :   " << ConsoleShell << endl;
	cout << "FoxaXu Tools Version :  _" << VCODE << "_ , Copyright FoxaXu 2023,FoxaXu Developer World" << endl;
	cout << "Use command Help to start" << endl;
BackShellAPI:
	cout << endl << ConsoleShell << " ";
	getline(cin, LINECHAT);
	OutputLog << "---------------------------------------------------------------------------" << endl;

	OutputLog << "User Type :  [" << LINECHAT << "].  Time :  " << getwinenv("time") << endl;
	cout << endl;

	bool testpathrun = existfolder(PATH);
	if (testpathrun) {}
	else {
		MessageBox(0, "Error.FXTools seems has problem,Running Path is Null,Maybe you should check your disk.", "FXTools Crash Report", MB_OK);
		return 0;
	}

	//额外
	if (LINECHAT == "eula") {
		OutputLog << "Open Eula Documect" << endl;
		string EulaFilePath = "\"" + PATH + "\\ResFile\\Text\\EULA.txt\"";
		ShellExecute(0, "open", "notepad", EulaFilePath.c_str(), 0, SW_SHOW);
		goto BackShellAPI;
	}
	if (LINECHAT == "update") {
		OutputLog << "Check Update" << endl;
		cout << "Checking Version" << endl;
		cout << "Please wait" << endl;;
		cout << "Current Version :  _" << VCODE << "_ , FXTools Version Code." << endl;
		cout << endl;

		string backdata = UpdateNow();
		if (backdata == "NEW") {
			string $GETURLUPDATEAPI = GETRES("NET", "UpdateAPI");
			OutputLog << "New Update" << endl;
			OutputLog << "Update API :  " << $GETURLUPDATEAPI << endl;
			string $NewVersion = geturlcode($GETURLUPDATEAPI);
			if ($NewVersion == "geturlfailed") {
				MessageBox(0, "Error,Geturlcode Plugin Run Error: Geturlfailed.Try to rerun this Program", "GetUrlCode Error", MB_OK);
				goto BackShellAPI;
			}
			OutputLog << "New Version CODE :  " << $NewVersion << endl;
			cout << "New Update Version :  _"<< $NewVersion <<"_  "<< endl;
			cout << "Do you want update ? " << endl;
			string USelectUpdate;
			cout << endl << "_y/n_ off caps lock  _ $ ";
			getline(cin, USelectUpdate);
			if (USelectUpdate == "y") {
				if (_access(UpdateCoreFile.c_str(), 0)) {
					cout << "Update Core not install successfully" << endl;
					cout << "Please try to reinstall fxtools" << endl;
					cout << endl << "Press Enter to Back" << endl;
					getchar();
					goto BackShellAPI;
				}
				string parameterupdate = PATH + " " + selfadr;
				ShellExecute(0, "open", UpdateCoreFile.c_str(), parameterupdate.c_str(), 0, SW_SHOW);
				cout << "Now, You can close this window" << endl;
				cout << "Press Enter to Exit this window" << endl;
				getchar();
				return 0;
			}
			goto BackShellAPI;
		}
		if (backdata == "NOUPDATE") {
			OutputLog << "No Update" << endl;
			cout << "You are using Latest Version of FXTools,You can visit https://www.foxaxu.com/dev/fxtools get more info" << endl;
			cout << "Thanks your using" << endl;
			goto BackShellAPI;
		}
		OutputLog << "Failed to Connect Server Check Update" << endl;
		cout << "Check Update Failed :  Internet Error, Please visit https://www.foxaxu.com/dev/fxtools get more info / Download." << endl;
		cout << "Thanks your using." << endl;
		goto BackShellAPI;
	}
	if (LINECHAT == "openfolder") {
		OutputLog << "OpenFolder :  " << PATH << endl;
		ShellExecute(0, "open", "explorer", PATH.c_str(), 0, SW_SHOW);
		goto BackShellAPI;
	}
	if (LINECHAT == "openccf") {
		OutputLog << "User Select Edit CCF.inis File" << endl;
		//编辑CCF
		int userselecteccf;
		userselecteccf = MessageBox(0, "Warning: CCF is FXTools Core File, if you edit this file,The Tools maybe broken,Please make sure,select yes or no", "Edit CCF File", MB_YESNO);
		if (userselecteccf == 6) {
			OutputLog << "User Click Yes to Edit File" << endl;
			OutputLog << "Note pad Open file :  " << ResFile << endl;
			ShellExecute(0, "open", "notepad", ResFile.c_str(), 0, SW_SHOW);
			goto BackShellAPI;
		}
		OutputLog << "User Click Cancel to Edit File" << endl;
		goto BackShellAPI;
	}
	if (LINECHAT == "openlog") {
		OutputLog << "User Open Log File" << endl;
		//打开日志
		OutputLog << "Note pad Open file :  " << logfile << endl;
		ShellExecute(0, "open", "notepad", logfile.c_str(), 0, SW_SHOW);
		goto BackShellAPI;
	}
	if (LINECHAT == "ver") {
		OutputLog << "Version List" << endl;
		cout << endl;
		cout << "FoxaXu Tools Release" << endl;
		cout << "By FoxaXu Developer ,Copyright FoxaXu 2023" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "Core Version :  " << VCODE << endl;
		string FCode = GETRES("Current", "VCODE");
		cout << "CCF Version :   " << FCode << endl;

		OutputLog << "Core Version :  [" << VCODE <<"].  CCF Version :  [" << FCode << "]." << endl;

		string CDNAME = GETRES("Current", "CodeName");
		cout << "FXTools Code Name : " << CDNAME << endl;
		string VINFOS = GETRES("Current", "Version");
		cout << "Version Info :  " << VINFOS << endl;
		string VerHELP = GETRES("Current", "VerHead");
		cout << "Version Help Info :  " << VerHELP << endl;

		OutputLog << "Code Name :  [" << CDNAME << "]. Version Info :  [" << VINFOS << "]. Version Help info :  [" << VerHELP <<"]." << endl;

		cout << endl;
		cout << "Program Running on: " << endl;
		cout << "               " << PATH << endl;
		cout << "               " << selfadr << endl;
		cout << " Process PID :  " << endl;
		cout << "             " << PPID << endl;
		
		OutputLog << "Program Running on :  [" << PATH << "]." << endl;
		OutputLog << "Program File :  [" << selfadr << "]. Process PID :  [" << PPID << "]." << endl;

		if (RVCODE == VCODE) {}
		else {
			OutputLog << "Version Warning :  [FXTools Running on unsupport CCF Core Version]" << endl;
			cout << endl;
			cout << "Warning: FXTools Running on unsupport CCF Core Version" << endl;
		}
		cout << "------------------------------------------------------------------------" << endl;
		cout << "            Copyright FoxaXu 2022 -2023. FoxaXu Developer" << endl;
		cout << endl;
		goto BackShellAPI;
 	}
	if (LINECHAT == "help") {
		OutputLog << "Open Help Document" << endl;
		string HelpDoc = PATH + "\\ResFile\\Text\\HelpCenter.txt";
		string newaddress = PATH + "\\HelpDoc.txt";
		
		CopyFile(HelpDoc.c_str(), newaddress.c_str(), 0);
		ShellExecute(0, "open", "notepad", newaddress.c_str(), 0, SW_SHOW);
		goto BackShellAPI;
	}

	//TOOLS工具
	if (LINECHAT == "osclean") {
		OutputLog << "Run OSClean Tools" << endl;
		string CoreFile = PATH + "\\extend\\osclean.exe";
		if (_access(CoreFile.c_str(), 0)) {
			cout << "Download OS Clean Tools" << endl;
			cout << "Please wait.connecting server" << endl;
			string OSCDown = geturlcode(GETRES("ExtendDownload", "osclean"));
			cout << "Start Download" << endl;
			Sleep(1000);
			URLDown(OSCDown, CoreFile);
			if (_access(CoreFile.c_str(), 0)) {
				cout << "Check your internet, we cannot connect server,download failed" << endl;
				goto BackShellAPI;
			}
			cout << "Complete" << endl;
		}
		Sleep(1000);
		cout << endl;
		cout << "We recommand running on PE Mode is better" << endl;
		cout << "Select OS Drive to Start" << endl;
		cout << "like:  C: D: E:" << endl;

		//选择框
		string TYPEALine;

		BACKSOSPT:
		cout << endl << "OSClean- $";
		getline(cin, TYPEALine);
		string CHECKPOINT = TYPEALine + "\\Windows\\notepad.exe";
		if (_access(CHECKPOINT.c_str(), 0)) {
			cout << "OS PATH is Null, Vailed check failed" << endl;
			goto BACKSOSPT;
		}

		OutputLog << "User Select :  " << TYPEALine << endl;

		string SelectUser;
		BackSLUM:
		cout << "Select User Name in OS PATH\\Users\\%UserName% - $";
		getline(cin, SelectUser);
		string UserFolder = TYPEALine + "\\Users\\" + SelectUser;
		bool retusfd = existfolder(UserFolder);
		if (retusfd) {}
		else {
			cout << "Null User Type Please check your \"Users\" folder" << endl;
			goto BackSLUM;
		}
		string parameter = TYPEALine + " " + SelectUser;
		bool PETest = existfolder("X:\\Windows");
		if (PETest) {
			ShellExecute(0, "open", CoreFile.c_str(), parameter.c_str(), 0, SW_SHOW);
			cout << endl << "Start Run Command" << endl;
			goto BackShellAPI;
		}
		OutputLog << "User Select User Name :  " << SelectUser << endl;
		ShellExecute(0, "runas", CoreFile.c_str(), parameter.c_str(), 0, SW_SHOW);
		cout << endl << "Start Run Command" << endl;
		goto BackShellAPI;
	}
	if (LINECHAT == "oscheck") {
		OutputLog << "Run OSCheck Tool" << endl;
		string CoreFile = PATH + "\\extend\\oscheck.exe";
		if (_access(CoreFile.c_str(), 0)) {
			cout << "Download OS Check Tools" << endl;
			cout << "Please wait ....   connecting server" << endl;
			string OSCDown = geturlcode(GETRES("ExtendDownload", "oscheck"));
			cout << "Start Download" << endl;
			Sleep(1000);
			URLDown(OSCDown, CoreFile);
			if (_access(CoreFile.c_str(), 0)) {
				cout << "Check your internet, we cannot connect server,download failed" << endl;
				goto BackShellAPI;
			}
			cout << "Complete" << endl;
		}
		Sleep(1000);
		cout << endl;
		cout << "We recommand running on PE Mode is better" << endl;
		cout << "Select Run Mode ( \"os\" or \"pe\" mode)" << endl;
		
		string ckrun;
	ReSelectCKRUN:
		cout << "OS Check Tools    ~ $ ";
		getline(cin, ckrun);
		//判断代码是否有效果
		if (ckrun == "os") {
			bool PETest = existfolder("X:\\Windows");
			if (PETest) {
				OutputLog << "OSCheck Mode :   OS / PE" << endl;
				ShellExecute(0, "open", CoreFile.c_str(), "-os", PATH.c_str(), SW_SHOW);
				goto BackShellAPI;
			}
			else {
				OutputLog << "OSCheck Mode :   OS" << endl;
				ShellExecute(0, "runas", CoreFile.c_str(), "-os", PATH.c_str(), SW_SHOW);
				goto BackShellAPI;
			}
		}
		if (ckrun == "pe") {
			bool PETest = existfolder("X:\\Windows");
			if (PETest) {
				OutputLog << "OSCheck Mode :   PE / PEMode" << endl;
				ShellExecute(0, "open", CoreFile.c_str(), "-pe", PATH.c_str(), SW_SHOW);
				goto BackShellAPI;
			}
			else {
				OutputLog << "OSCheck Mode :   PE" << endl;
				cout << "You are not running on PE Mode, some Function maybe missing" << endl;
				ShellExecute(0, "runas", CoreFile.c_str(), "-pe", PATH.c_str(), SW_SHOW);
				goto BackShellAPI;
			}
		}
		cout << "Null Set" << endl;
		goto ReSelectCKRUN;
	}

	//关闭/重置窗口
	if (LINECHAT == "uninstall") {
		//卸载FXTools
		cout << "Warning, Do you want uninstall FXTools?" << endl;
		cout << "If you install FXTools on root path. Its not support" << endl;
		cout << "The uninstall program will delete all folder" << endl;
		cout << "Press Enter to Start Uninstall" << endl;
		getchar();
		system("cls");
		cout << "Uninstall FXTools" << endl;
		cout << "Please wait" << endl;

		Sleep(2000);
		
		ofstream UninstallScript;
		string USPath = getwinenv("temp") + "\\fx~uninstall.bat";
		UninstallScript.open(USPath);
		UninstallScript << "@echo off" << endl;
		UninstallScript << "echo= Delete " << "\"" << PATH << "\"" << endl;
		UninstallScript << "echo= Please wait ..." << endl;
		UninstallScript << "ping 127.0.0.1 -n 3 >nul" << endl;
		UninstallScript << "rd /s /q " << "\"" << PATH << "\"" << endl;
		UninstallScript << "cls" << endl;
		UninstallScript << "echo= Thanks Your Using" << endl;
		UninstallScript << "echo= FXTools is Uninstall Successfully" << endl;
		UninstallScript << "echo= If you have some problem please contact us https://www.foxaxu.com/contact" << endl;
		UninstallScript << "echo= Thank You" << endl;
		UninstallScript << "echo= " << endl;
		UninstallScript << "echo=                        Don`t close this window. Press any key to delete this script" << endl;
		UninstallScript << "pause" << endl;
		UninstallScript << "del " + USPath << endl;
		UninstallScript << "exit" << endl;
		UninstallScript.close();

		ShellExecute(0, "open", USPath.c_str(), 0, 0, SW_SHOW);
		return 0;
	}
	if (LINECHAT == "reload") {
		OutputLog << "FXTools Reload" << endl;
		OutputLog << "----------------------------------------------------------------------------------------------------" << endl;
		goto FXReloadAPI;
	}
	if (LINECHAT == "close") {
		OutputLog << "FXTools :  End Task" << endl;
		OutputLog << "close window" << endl;
		CMD = "type \"" + PATH + "\\ResFile\\Text\\EndType.txt\"";
		system(CMD.c_str());
		return 0;
	}
	if (LINECHAT == "exit") {
		OutputLog << "FXTools :  End Task" << endl;
		OutputLog << "close window" << endl;
		CMD = "type \"" + PATH + "\\ResFile\\Text\\EndType.txt\"";
		system(CMD.c_str());
		return 0;
	}

	OutputLog << "Unknown Command :  [" << LINECHAT <<"]." << endl;
	CMD = "type \"" + PATH + "\\ResFile\\Text\\ErrorType.txt\"";
	system(CMD.c_str());
	cout << endl;
	goto BackShellAPI;
}