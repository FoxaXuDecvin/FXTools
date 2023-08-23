#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\CppHeader\7zipAPI.h"

using namespace std;

string CleanFolderA(string folder) {
	rmfolder(folder);
	Sleep(1000);
	mdfolder(folder);
	string BCode = "OK";
	return BCode;
}

string FileDeleteA(string file) {
	remove(file.c_str());
	string BCode = "OK";
	return BCode;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << " OS Clean Tools," << endl;
		cout << "Copyright FoxaXu 2023" << endl;
		cout << "Command :   " << endl;
		cout << "   osclean.exe <OSDRIVE> <USERNAME>" << endl;
		cout << "Version 1.01" << endl;
		getchar();
		return 0;
	}

	int alang = 0;
	alang < argc;

	alang++;
	string pathset = argv[alang];
	alang++;
	string userselect = argv[alang];
	cout << endl;
	cout << "Ready?" << endl;
	cout << "We will delete these file:" << endl;
	cout << " %HOMEDRIVE%\\Windows\\Temp" << endl;
	cout << " %HOMEDRIVE%\\Windows\\SystemTemp" << endl;
	cout << " %HOMEDRIVE%\\Windows\\SoftwareDistribution" << endl;
	cout << " %HOMEDRIVE%\\Users\\%UserName%\\AppData\\Local\\Temp" << endl;
	cout << " %HOMEDRIVE%\\Users\\%UserName%\\AppData\\Roaming\\Temp" << endl;
	cout << "If you have some recommand please contacts us" << endl;
	cout << "Press Enter to Start " << endl;
	getchar();
	cout << "Warning. Please running on PE Mode, some file maybe lock" << endl;
	
	string pubtin;

	cout << "CLEAN %HOMEDRIVE%\\Windows\\Temp" << endl;
	pubtin = pathset + "\\Windows\\Temp";
	CleanFolderA(pubtin);

	cout << "CLEAN %HOMEDRIVE%\\Windows\\SystemTemp" << endl;
	pubtin = pathset + "\\Windows\\SystemTemp";
	CleanFolderA(pubtin);

	cout << "CLEAN %HOMEDRIVE%\\Windows\\SoftwareDistribution" << endl;
	pubtin = pathset + "\\Windows\\SoftwareDistribution";
	CleanFolderA(pubtin);

	cout << "CLEAN %HOMEDRIVE%\\Users\\%UserName%\\AppData\\Local\\Temp" << endl;
	pubtin = pathset + "\\Users\\" + userselect + "\\AppData\\Local\\Temp";
	CleanFolderA(pubtin);

	cout << "CLEAN %HOMEDRIVE%\\Users\\%UserName%\\AppData\\Roaming\\Temp" << endl;
	pubtin = pathset + "\\Users\\" + userselect + "\\AppData\\Roaming\\Temp";
	CleanFolderA(pubtin);

	cout << endl << "Do you want Clean Explorer Data,(Warning, We will clean Quick Access Bar)" << endl;
	string selectline;
	cout << "Warning:  off your caps lock:  y/n $";
	getline(cin, selectline);

	if (selectline == "y") {
		cout << "Restart Windows Explorer" << endl;
		cout << "Press Enter key to Start" << endl;
		getchar();
		ShellExecute(0, "runas", "taskkill", "/f /im explorer.exe", 0, SW_HIDE);
		cout << "CLEAN %HOMEDRIVE%\\Users\\%UserName%\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\AutomaticDestinations" << endl;
		pubtin = pathset + "\\Users\\" + userselect + "\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\AutomaticDestinations";
		CleanFolderA(pubtin);
		Sleep(3000);
		ShellExecute(0, "runas", "userinit.exe", 0, 0, SW_SHOW);
	}

	cout << "Next Delete : pagefile.sys hiberfil.sys DumpStack.log.tmp bootTel.dat swapfile.sys" << endl;
	
	pubtin = pathset + "\\pagefile.sys";
	FileDeleteA(pubtin);

	pubtin = pathset + "\\hiberfil.sys";
	FileDeleteA(pubtin);

	pubtin = pathset + "\\DumpStack.log.tmp";
	FileDeleteA(pubtin);

	pubtin = pathset + "\\bootTel.dat";
	FileDeleteA(pubtin);

	pubtin = pathset + "\\swapfile.sys";
	FileDeleteA(pubtin);

	cout << endl << "Complete, if file is not delete,please use PE Mode to run,or report for us" << endl;
	cout << "Press any key to Exit" << endl;
	getchar();
	return 0;
}