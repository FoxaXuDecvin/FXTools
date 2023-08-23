//Mode: 
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\CppHeader\7zipAPI.h"

int main(int argc, char* argv[]) {
	string selfadr = getselfinfo();
	cout << "Loading ..." << endl;

	string osroot = getwinenv("systemroot");
	string Sys32 = "\"" + osroot + "\\System32" + "\"";
	string bcmd;

	if (argc == 2) {
		int alang = 0;
		alang < argc;
		alang++;
		string paraA = argv[alang];
		if (paraA == "-os") {
			cout << "Windows Check & Repair, Script  --Version 1.01" << endl;
			cout << "Command: Dism Sfc Chkdsk" << endl;
			cout << "Program is running on Normal Mode" << endl;
			cout << "This Software support running on PE Mode" << endl;
			cout << "Press Enter to Start" << endl;
			getchar();
			cout << "Ready?";
			getchar();
			cout << "Dism Restorehealth" << endl;
			bcmd = Sys32 + "\\dism.exe /online /cleanup-image /restorehealth";
			system(bcmd.c_str());
			cout << endl;
			cout << "Sfc Scannow" << endl;
			bcmd = Sys32 + "\\sfc.exe /scannow";
			system(bcmd.c_str());
			cout << "Chkdsk Disk Volume C:" << endl;

			ShellExecute(0, "runas","chkdsk.exe", "C: /f",Sys32.c_str(), SW_SHOW);
			bcmd = Sys32 + "\\chkdsk.exe C: / f";
			system(bcmd.c_str());

			cout << endl;
			cout << "Command Complete, you can close this window" <<endl;
			cout << "other disk check : Select other disk volume:  C: / D: / E: " << endl;
			string diskvolume;
			string dtempse;
		BackSelDiskVol:
			cout << endl;
			cout << "localdisk ~ $ ";
			getline(cin, diskvolume);
			bool testvolume = testAdmin(diskvolume);
			if (testvolume) {
				bcmd = Sys32 + "\\chkdsk.exe " + diskvolume + " /f";
				system(bcmd.c_str());
				goto BackSelDiskVol;
			}
			else {
				cout << "Error Cannot set disk,Access Denied or not exist" << endl;
				goto BackSelDiskVol;
			}
		}
		if (paraA == "-pe") {
			system("cls");
			cout << "Windows Check & Repair, Script  --Version 1.01" << endl;
			cout << "Command: Dism Sfc Chkdsk" << endl;
			cout << "Program is running on PE Mode" << endl;
			cout << "OS System32 Path :  " << Sys32 << endl;
			cout << "Press Enter to Start" << endl;
			getchar();
		MainStart:
			system("cls");
			cout << "Use Code to select Function" << endl;
			cout << "disabled               fixboot              -Fix Windows Boot Manager" << endl;
			cout << "disabled               fixbootuefi         -Fix UEFI Windows Boot Manager" << endl;
			cout << "                       quickchkdsk       -Use Windows Command Check disk" << endl;
			cout << "disabled               applyimage        - Use Dism Tools Install Windows" << endl;
			cout << "                            Coming Soon  .   .   ." << endl;
			cout << "Copyright FoxaXu 2023" << endl;
			cout << "If you have some recommand. Please Contact us" << endl;

			string UserShell;
		BackSelectPETool:
			cout << "OSCheck Tools ~   $ ";
			getline(cin, UserShell);
			if (UserShell == "fixboot") {
				cout << "This Function is Lock" << endl;
				cout << "Press Enter to Exit" << endl;
				getchar();
				goto MainStart;

				cout << "Select OS Volume:  " << endl;
				string osvol;
			BackOSVS:
				cout << "OS Volume   $";
				getline(cin, osvol);
				bool testOSV = testAdmin(osvol);
				//系统盘
				if (testOSV) {
					//系统文件夹
					string OSFolder = osvol + "\\Windows";
					bool testOSVF = testAdmin(OSFolder);
					if (testOSVF) {
						//存在-询问启动分区
						cout << "Select Boot Volume Frist disk volume.size about 100mb" << endl;
						string osbv;
					BackOSBVS:
						cout << "Boot Partition   ~ $ ";
						getline(cin, osbv);
						bool testOSBVR = testAdmin(osbv);
						if (testOSBVR) {
							//最后确认
							cout << "Please Make sure this info: " << endl;
							cout << " OS PATH :  " << OSFolder << " .  Boot Partition :  " << osbv << endl;
							cout << "Boot Mode : Legacy(Not UEFI) Default Language" << endl;
							string userselect;
							cout << "Type \"y\" to start Repair Boot  ~ $ ";
							getline(cin, userselect);
							if (userselect == "y") {
								cout << "Start Repair... " << endl;
								bcmd = Sys32 + "\\Bcdboot.exe " + OSFolder + " /s " + osbv;
								system(bcmd.c_str());

								cout << endl;
								cout << "Press Enter to Back" << endl;
								getchar();
							}
							cout << endl << "User Cancel" << endl;
							cout << "Press Enter to Back" << endl;
							getchar();
						}
						else {
							cout << endl;
							cout << "We Cannot to set disk :  " << osbv << " .Try to Format or select other boot partition" << endl;
							cout << "Press Enter to Back" << endl;
							getchar();
						}

					}
					cout << "Windows is not Available on this partition" << endl;
					cout << "Pease select other volume" << endl;
					goto MainStart;
				}
				else {
					cout << "Access is Denied, Check your Select" << endl;
					cout << "Press any key to Back" << endl;
					getchar();
					goto BackSelectPETool;
				}
			}
			if (UserShell == "fixbootuefi") {
				cout << "This Function is Lock" << endl;
				cout << "Press Enter to Exit" << endl;
				getchar();
				goto MainStart;

				//UEFI修复
				cout << "Select UEFI OS Volume:  " << endl;
				string osvol;
				cout << "OS Volume   $";
				getline(cin, osvol);
				bool testOSV = testAdmin(osvol);
				//系统盘
				if (testOSV) {
					//系统文件夹
					string OSFolder = osvol + "\\Windows";
					bool testOSVF = testAdmin(OSFolder);
					if (testOSVF) {
						//存在-询问启动分区
						cout << "Select Boot Volume Frist disk volume(EFI).size about 100 ~ 300mb" << endl;
						string osbv;
						cout << "Boot Partition (EFI Partition)   ~ $ ";
						getline(cin, osbv);
						bool testOSBVR = testAdmin(osbv);
						if (testOSBVR) {
							//最后确认
							cout << "Please Make sure this info: " << endl;
							cout << " OS PATH :  " << OSFolder << " .  Boot Partition :  " << osbv << endl;
							cout << "Boot Mode : UEFI Boot . Default Language" << endl;
							string userselect;
							cout << "Type \"y\" to start Repair Boot  ~ $ ";
							getline(cin, userselect);
							if (userselect == "y") {
								cout << "Start Repair... " << endl;
								bcmd = Sys32 + "\\Bcdboot.exe " + OSFolder + " /s " + osbv + " /f UEFI";
								system(bcmd.c_str());
								cout << endl;
								cout << "Press Enter to Back" << endl;
								getchar();
							}
							cout << endl << "User Cancel" << endl;
							cout << "Press Enter to Back" << endl;
							getchar();
						}
						else {
							cout << endl;
							cout << "We Cannot to set disk :  " << osbv << " .Try to Format or select other boot partition" << endl;
							cout << "Press Enter to Back" << endl;
							getchar();
						}

					}
					cout << "Windows is not Available on this partition" << endl;
					cout << "Pease select other volume" << endl;
					goto MainStart;
				}
				else {
					cout << "Access is Denied, Check your Select" << endl;
					cout << "Press any key to Back" << endl;
					getchar();
					goto BackSelectPETool;
				}
			}
			if (UserShell == "quickchkdsk") {
				//Quick Check Disk
				cout << "Select Disk to Check or Repair :  C: D: E:" << endl;
				string VolumeSet;
			BackSLCHD:
				getline(cin, VolumeSet);
				bool VSCheck = testAdmin(VolumeSet);
				if (VSCheck) {
					//磁盘存在，开始扫描
					cout << "Start Run CHKDSK" << endl;
					cout << "Please wait" << endl;
					bcmd = Sys32 + "\\chkdsk.exe " + VolumeSet + " /f";
					system(bcmd.c_str());
					cout << endl;
					cout << "Press Enter key to back" << endl;
					getchar();
					goto MainStart;
				}
				cout << "Cannot Find Disk Volume :  " << VolumeSet << endl;
				cout << "Press Enter key to back" << endl;
				getchar();
				goto MainStart;
			}
			if (UserShell == "applyimage") {
				cout << "This Function is Lock" << endl;
				cout << "Press Enter to Exit" << endl;
				getchar();
				goto MainStart;

				cout << "Select Image (ESD/WIM) File" << endl;
				string imgsel;
			rsIMG:
				cout << "select file   ~ $ ";
				getline(cin, imgsel);
				if (_access(imgsel.c_str(), 0)) {
					cout << "File not Exist" << endl;
					cout << "Press Enter to Back" << endl;
					getchar();
					goto MainStart;
				}
				cout << "Select Save Path" << endl;
				string savepathIMG;
			NoAuthSIMG:
				cout << endl;
				cout << "Save Path:  C: D: E:    ~ $ ";
				getline(cin, savepathIMG);
				bool retspg = testAdmin(savepathIMG);
				//检查路径
				if (retspg) {}
				else
				{
					//无法直接读写，尝试创建
					CreateDirectory(savepathIMG.c_str(), 0);
					bool retspg2 = testAdmin(savepathIMG);
					if (retspg2) {}
					else {
						//错误的路径
						cout << "File Cannot Save in this path:  " << savepathIMG << endl;
						cout << "Please Select other path" << endl;
						goto NoAuthSIMG;
					}
				}
				cout << "Start Dism Command" << endl;
				bcmd = Sys32 + "\\Dism.exe  " + "/apply-image /imagefile:\"" + imgsel + "\" /indexdir:1 /ApplyDir:\"" + savepathIMG + "\"";
				system(bcmd.c_str());
				cout << endl;
				cout << "Complete. Press Enter to Back" << endl;
				getchar();
				goto MainStart;
			}
			if (UserShell == "debug") {
				string pathprocs = getwinenv("cd");
				cout << "Process Path %CD%" << pathprocs << endl;
				string pathinfo = getwinenv("path");
				cout << "PATH : %PATH%  ~ " << pathinfo << endl;
				cout << "End Debug" << endl;
				cout << "Test Command " << endl;
				system("sfc");
				system("X:\\Windows\\System32\\sfc.exe");
				system("dism");
				system("X:\\Windows\\System32\\dism.exe");
				system("\"X:\\Windows\\System32\\sfc.exe\"");
				system("\"X:\\Windows\\System32\\dism.exe\"");
				system("\"X:\\Windows\\System32\\bcdboot.exe\"");
				cmdshell("X:\\Windows\\System32\\dism.exe", "\\", "ncode");
				cmdshell("X:\\Windows\\System32\\sfc.exe", "\\", "ncode");
				getchar();
				goto MainStart;
			}


			cout << "Unknown Command :  " << UserShell << endl;
			cout << endl;
			goto BackSelectPETool;

		}
		MessageBox(0, "Parameter Error", "OSCheck", MB_OK);
	}
	
	system("cls");
	cout << "Please select mode" << endl;
	cout << "   oscheck.exe -pe / -os" << endl;
	getchar();
	return 0;
}