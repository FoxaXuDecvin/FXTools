#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\GlobalVar.h"
#include"D:\CppHeader\7zipAPI.h"

using namespace std;

int main(int argc, char* argv[]) {
	SetConsoleTitle("FXTools Updater");
	if (argc < 3) {
		cout << "FXTools Updater tools, Press any key to Enter" << endl;
		cout << "Command :" << endl;
		cout << "               updater.exe <path> <fxtools file>" << endl;
		cout << "Copyright Foxaxu 2023..." << endl;
		getchar();
	}
	int alang = 0;
	alang++;
	string PATH = argv[alang];

	alang++;
	string FXMainFile = argv[alang];

	cout << "Verify Your FXTools" << endl;
	string FXNewFile = FXMainFile + "~new";

	if (_access(FXMainFile.c_str(), 0)) {
		cout << "Cannot Verify your install" << endl;
		cout << "Press Enter key to Exit" << endl;
		getchar();
		return 0;
	}

	cout << "Make sure old version is close." << endl;
	cout << "Press Enter key to Start" << endl;
	getchar();

	cout << "Connecting Server" << endl;
	
	URLDown(geturlcode("https://developer.foxaxu.com/SoftwareUpdate/FXToolAPI/FXMainFile.api"), FXNewFile);

	if (_access(FXNewFile.c_str(), 0)) {
		cout << "Download Failed ..." << endl;
		cout << "Please Check your internet, or reinstall fxtools" << endl;
		cout << "Press Enter to Exit" << endl;
		getchar();
		return 0;
	}

	cout << "Uninstall Old Version" << endl;

redeletemainfile:
	cout << endl;
	remove(FXMainFile.c_str());
	if (_access(FXMainFile.c_str(), 0)){}
	else {
		cout << "Uninstall Failed" << endl;
		cout << "Close FXTools and Try again" << endl;
		cout << "Press Enter to Try again" << endl;
		getchar();
		goto redeletemainfile;
	}
	string oldccf = PATH + "\\CCF.inis";
	remove(oldccf.c_str());
	string oldres = PATH + "\\ResFile";
	rmfolder(oldres);
	rename(FXNewFile.c_str(), FXMainFile.c_str());
	cout << "Update Complete" << endl;
	cout << "Reload FXTools" << endl;
	Sleep(1500);
	ShellExecute(0, "open", FXMainFile.c_str(), 0, 0, SW_SHOW);
	return 0;
}