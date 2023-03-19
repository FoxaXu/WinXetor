// WinXetor
// Copyright FoxaXu

#include<Windows.h>
#include"D:\CppHeader\winapicore.h"

using namespace std;

int main(int argc, char* argv[]) {

	string PFName = getselfinfo("processfullname");
	int PPIDx = getpid();
	string PPID = to_string(PPIDx);

	ofstream logs;
	ofstream runlock;
	logs.open("winxetor.log");
	string SSLockName = "wx~" + PPID + "~session.lock";
	runlock.open(SSLockName);

	reloadmark:
	SetConsoleTitle("WinXetor Loading");

	logs << "Start Load WinXetor" << endl;

	string $String = "Lang";
	bool retlang = existfolder($String);
	if (retlang){}
	else {
		logs << "ERROR: Lang Folder is missing" << endl;
		MessageBox(0, "Language file is missing. WinXetor Cannot Launch", "Launch Error", MB_OK);
		return 1;
	}
	$String = "config.ini";
	bool retconfig = existcheck($String);
	if (retconfig) {}
	else
	{
		logs << "ERROR: CONFIG.INI is missing" << endl;
		MessageBox(0, "Configure file is missing in .\\config.ini", "Launch Error", MB_OK);
		return 1;
	}
	string langname = readini(".\\config.ini", "Settings", "DefaultLanguage");
	string DevFun = readini(".\\config.ini", "Settings", "DeveloperFunction");
	string langformat = readini(".\\config.ini", "ConfigHeader", "LangFormat");
	string wxversion = readini(".\\config.ini", "ConfigHeader", "Version");
	logs << "Language File: " + langname << endl;
	logs << "WinXetor Version: " + wxversion << endl;

	cout << "Developer Function switch mode :  " << DevFun << endl;

	string $Langfile = "Lang\\" + langname;
	bool retlangfile = existcheck($Langfile);
	if (retlangfile) {}
	else {
		$String = "Cannot read language file  " + $Langfile;
		logs << "ERROR: " + $String << endl;
		MessageBox(0, $String.c_str(), "Launch Error", MB_OK);
		writeini(".\\config.ini", "Settings", "DefaultLanguage", "en-us.lang");
		goto reloadmark;
	}
	
	string langfileformat = readini($Langfile, "Head", "LangFormat");
	if (langfileformat == langformat) {}
	else {
		int a = 0;
		string langmob = "This Language maybe cannot running in this WinXetor Version. Lang Ver:  " + langfileformat + "  Your WinXetor Version:  " + langformat + "  Do you want load this language?";
		a = MessageBox(0, langmob.c_str(), "Support Warning", MB_YESNO);
		if (a == 6) {}
		else {
			writeini(".\\config.ini", "Settings", "DefaultLanguage","en-us.lang");
			goto reloadmark;
		}
	}

	// Start Load
	string langtitlebar = readini($Langfile, "LangUI", "titlebar");
	SetConsoleTitle(langtitlebar.c_str());
	logs << "Loading Files ..." << endl;

	string langmsg = readini($Langfile, "LangUI", "langmsg");
	string wxmsg = readini($Langfile, "LangUI", "wxmsg");
	string langerror = readini($Langfile, "LangUI", "langerror");
	string langgetnotice = readini($Langfile, "LangUI", "langgetnotice");

	//out version info
	cout << langmsg << endl;
	cout << wxmsg << " " << wxversion << endl;

	$String = "wxcore.exe";
	bool retwxcore = existcheck($String);
	if (retwxcore) {}
	else {
		logs << "ERROR: Core file missing.  wxcore.exe" << endl;
		cout << langerror << "CORE_FILE_MISSING";
		MessageBox(0, "Core file is missing .\\wxcore.exe", "Launch Error", MB_OK);
		return 0;
	}

	$String = "dl.exe";
	bool retdlcore = existcheck($String);
	if (retdlcore) {
		logs << "dl.exe is ready" << endl;
	}
	else {
		logs << "Download File : DL.exe" << endl;
		logs << "URL: https://developer.foxaxu.com/download/cppcore/dl.exe" << endl;
		URLDown("https://developer.foxaxu.com/download/cppcore/dl.exe", "dl.exe");
	}

	$String = "anticrash.exe";
	bool retace = existcheck($String);
	if (retace) {
		logs << "anticrash.exe is ready" << endl;
	}
	else {
		logs << "Download File : DL.exe" << endl;
		logs << "URL: https://developer.foxaxu.com/WinXetor/download/anticrash.exe" << endl;
		URLDown("https://developer.foxaxu.com/WinXetor/download/anticrash.exe", "anticrash.exe");
	}

	ShellExecute(0, "open", "anticrash.exe", SSLockName.c_str(), 0, SW_HIDE);

	cout << langgetnotice << endl;

	bool retnotice = URLDown("https://api.foxaxu.com/public/notice.txt", "notice.txt");
	if (retnotice) {}
	else {
		ofstream write;
		write.open("notice.txt");
		write << "Connect Server Failed" << endl;
		write.close();
	}

	system("cls");
	system("type notice.txt");

	string ShellTitle = readini($Langfile, "ShellUI", "Title");
	string ShellTitleHelps = readini($Langfile, "ShellUI", "ShellHelp");

	//Print Shell
	cout << endl;
	cout << ShellTitle << endl;
	cout << ShellTitleHelps << endl;

	string shellkey;
	string markfile = ".\\workcheck.mark";
BackShell:
	remove(markfile.c_str());
	cout << endl;
	cout << "WinXetor " + wxversion + " Shell  $";
	getline(cin, shellkey);
	logs << "Enter command :  " + shellkey << endl;

	cmarkfile(markfile, "markrun");

	if (shellkey == "update") {
		ShellExecute(0, "open", "wxcore.exe", "update", 0, SW_SHOW);
		goto BackShell;
	}
	if (shellkey == "refreshlang") {
		ShellExecute(0, "open", "wxcore.exe", "refreshlang", 0, SW_SHOW);
		goto BackShell;
	}
	if (shellkey == "version") {
		string LINFO = readini($Langfile, "Head", "LangINFO");
		cout << "WinXetor Windows Tool" << endl;
		cout << "Version  : " + wxversion << endl;
		cout << "Language :  " + LINFO << endl;

		if (DevFun == "enabled") {
			cout << "Process Full Name :  " + PFName << endl;
			cout << "Process PID :  " + PPID << endl;
			cout << "Developer Function is Enabled" << endl;
			cout << "use offdebugmode command off" << endl;
		}
		goto BackShell;
	}
	if (shellkey == "reload") {
		goto reloadmark;
	}
	if (shellkey == "help") {
		cout << "WinXetor Windows Tool" << endl;
		cout << "    update   -Check update" << endl;
		cout << "    refreshlang   -refresh language" << endl;
		cout << "    version   -List version" << endl;
		cout << "    help   -list help" << endl;
		cout << "    reload   -Reload WinXetor" << endl;
		cout << "    setlang   -Set New Language for WinXetor from Lang Folder" << endl;
		cout << endl << "Copyright FoxaXu" << endl;
		goto BackShell;
	}
	if (shellkey == "setlang") {
		cout << "select your language" << endl;
		cout << "Do not add:  .lang" << endl;
		string langselect;
		BackSLang:
		cout << endl;
		cout << "Lang\\File.lang   $";
		getline(cin, langselect);
		string charccc = "Lang\\" + langselect + ".lang";
		bool retslang = existcheck(charccc);
		if (retslang) {
			string LINFO = readini(charccc, "Head", "LangINFO");
			cout << "Do you want use this language:  " + LINFO + "  ?" << endl;
			cout << "If you select this language we will reload WinXetor Now" << endl;
			cout << "<y/n>   $";
			string xlangselect;
			getline(cin, xlangselect);
			if (xlangselect == "y") {
				string SETLANGINI = langselect + ".lang";
				writeini(".\\config.ini", "Settings", "DefaultLanguage",SETLANGINI);
				goto reloadmark;
			}
			goto BackShell;
		}
		else {
			cout << "This language " + langselect + " is not exist on Lang Folder" << endl;
			cout << "Maybe this language WinXetor unsupport.  You can try to DIY lang file" << endl;
			goto BackSLang;
		}
	}
	if (shellkey == "web") {
		ShellExecute(0, "open", "https://developer.foxaxu.com/WinXetor", 0, 0, SW_SHOW);
		goto BackShell;
	}

	//OpenOffDebug
	if (shellkey == "opendebugmode") {
		writeini(".\\config.ini", "Settings", "DeveloperFunction", "enabled");
		cout << "complete" << endl;
		goto BackShell;
	}
	if (shellkey == "offdebugmode") {
		writeini(".\\config.ini", "Settings", "DeveloperFunction", "disabled");
		cout << "complete" << endl;
		goto BackShell;
	}

	//Hide CMD
	if (DevFun == "enabled") {
        if (shellkey == "testcrash") {
		return 0;
	}
		if (shellkey == "debuglang") {
			writeini(".\\config.ini", "Settings", "DefaultLanguage", "test.lang");
			goto reloadmark;
		}
	}
	

	string UCMD = readini($Langfile, "ShellUI", "UnknownCMD");
	string UCMDHelp = readini($Langfile, "ShellUI", "UnknownCMDHelp");
	cout << UCMD << shellkey << endl;
	cout << UCMDHelp << endl;
	goto BackShell;
}