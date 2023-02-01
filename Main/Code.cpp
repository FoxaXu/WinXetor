//Copyright Foxaxu (C) 2023
// WinXetor Tool Code
// More info Please visit https://www.foxaxu.com/winxetor/developer


#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<urlmon.h>
#include<Psapi.h>
#include<TlHelp32.h>
#include<tchar.h>
#include<io.h>
#include<tlhelp32.h>
#pragma comment(lib,"URlmon.lib")

#undef UNICODE
#undef _UNICODE

using namespace std;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

void Wchar_tToString(string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText;
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;
	delete[]psText;
}

LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

int main(int argc, char* argv[]) {

	string VerCode = "1.0.1-rev";

	string DMFileSwitch = ".debugmark";
	bool DebugMode = isFileExists_ifstream(DMFileSwitch);

	int line = 0;
	line < argc;

	errno_t	err = 0;
	char	FileName[100] = { 0 };
	char    FilePath[_MAX_PATH] = { 0 };
	char    ProcessName[0x40] = { 0 };
	DWORD   ProcessPID = 0;
	char* tmp1 = NULL;
	char* tmp2 = NULL;

	ProcessPID= GetCurrentProcessId();
	GetModuleFileNameA(NULL, FilePath, _MAX_PATH);

	tmp1 = strrchr((char*)FilePath, '\\');
	tmp2 = strrchr((char*)FilePath, '.');
	memcpy(ProcessName , tmp1 + 1, min(tmp2 - tmp1 - 1, 0x40));

	if (DebugMode){
		cout << endl;
	    cout << "WinXetor Tool  " << VerCode << "  File Name:" << FileName << "  " << FilePath << "  " << ProcessName << ".exe" << endl;
	    cout << "Debug Mode: " << DebugMode << "  PID:  " << ProcessPID << endl;
	    cout << "Argc Line:  " << argc << endl;
	    cout << endl;
	}

	if (argc == 1) {
		//Default UI

		return 0;
	}
	if (argc == 2) {
		//Command For use
		line++;
		string $AddCode1 = argv[line];

		//Notice
		if ($AddCode1 == "-version") {
			cout << endl;
			cout << "WinXetor Windows Tool " << " Version X64:  " << VerCode << endl;
			cout << "Copyright FoxaXu(C) All Code on Github" << endl;
			cout << "Developer Team https://www.foxaxu.com/WinXetor/developer" << endl;
			cout << "Program will auto found new version" << endl;
			cout << endl;
			return 0;
		}
		if ($AddCode1 == "-dl") {
			cout << endl;
			cout << "Help -taskdl" << endl;
			cout << "Format:  " << endl;
			cout << endl;
			cout << "               winxetor -taskdl %URL% %SAVEPATH%" << endl;
			cout << "      %URL% = Download Link. like:  https://www.foxaxu.com/a.exe" << endl;
			cout << "      %SAVEPATH%  = File Save path. Like:  C:\\a.exe" << endl;
			cout << " Use Windows API Download , maybe cannot running on Windows PE" << endl;
			cout << " Process Exit" << endl;
			return 0;
		}
		if ($AddCode1 == "-mkdir") {
			cout << endl;
			cout << "creat dir command" << endl;
			cout << "Format :  " << endl << endl;
			cout << "              winxetor -mkdir %NAME% " << endl;
			cout << "     %NAME% = Folder name" << endl;
			cout << "Process Exit" << endl;
			return 0;
		}
		if ($AddCode1 == "-rmdir") {
			cout << endl;
			cout << "remove dir command" << endl;
			cout << "Format :  " << endl << endl;
			cout << "              winxetor -rmdir %NAME% " << endl;
			cout << "     %NAME% = Folder name" << endl;
			cout << "Process Exit" << endl;
			return 0;
		}
		if ($AddCode1 == "-runas") {
			cout << endl;
			cout << "Help -runas" << endl;
			cout << "Format :  " << endl;
			cout << endl;
			cout << "                winxetor -runas %Program% %Parameter%  " << endl;
			cout << "           %Program% = Program file. like C:\\Windows\\Notepad.exe " << endl;
			cout << "           %Parameter% = Program run Parameter. like cmd.exe /c time" << endl;
			cout << " Use Administrator Run" << endl;
			cout << "Process Exit" << endl;
			return 0;
		}
		if ($AddCode1 == "-nogui") {
			cout << endl;
			cout << "Help -nogui" << endl;
			cout << "Format :  " << endl;
			cout << endl;
			cout << "                winxetor -nogui  %Program% %Parameter%" << endl;
			cout << "           %Program% = Program file. like C:\\Windows\\Notepad.exe " << endl;
			cout << "           %Parameter% = Program run Parameter. like cmd.exe /c time" << endl;
			cout << " Run Program Hide GUI. Notice some program unsupport hide GUI" << endl;
			cout << "Process Exit" << endl;
			return 0;
		}

		//Command
		if ($AddCode1 == "-help") {
			cout << endl;
			cout << "Help Center" << endl;
			cout << " WinXetor Tools Help Center" << endl;
			cout << endl;
			cout << "     WinXetor" << endl;
			cout << "                      -dl  Download" << endl;
			cout << "                      -mkdir  Create Folder" << endl;
			cout << "                      -rmdir   Remove Folder" << endl;
			cout << "                      -runas   Run as Administrator" << endl;
			cout << "                      -nogui  Run but no GUI" << endl;
			cout << "                      -version   detail version info " << endl;
			cout << "                      -help     Get Help" << endl;
			cout << "         More info please visit   https://www.foxaxu.com/WinXetor" << endl;
			cout << "          Copyright FoxaXu (C) 2023       PRODUCT INFO: Preview" << endl;
			cout << endl;
			return 0;
		}

		goto UnknownCommand;
	}
	if (argc == 3) {
		//Command Line 3
		line++;
		string $AddCode1 = argv[line];
		line++;
		string $AddCode2 = argv[line];

		//Notice
		if ($AddCode1 == "-dl") {
			cout << endl;
			cout << "Help -taskdl" << endl;
			cout << "Format:  " << endl;
			cout << endl;
			cout << "               winxetor -taskdl %URL% %SAVEPATH%" << endl;
			cout << "      %URL% = Download Link. like:  https://www.foxaxu.com/a.exe" << endl;
			cout << "      %SAVEPATH%  = File Save path. Like:  C:\\a.exe" << endl;
			cout << " Use Windows API Download , maybe cannot running on Windows PE" << endl;
			cout << " Process Exit" << endl;
			return 0;
		}

		//Command
		if ($AddCode1 == "-rmdir") {
			ofstream taskscript;
			taskscript.open("task~rmdir.bat");
			taskscript << "rd /s /q " << $AddCode2 << endl;
			taskscript << "del task~rmdir.bat" << endl;
			taskscript << "exit" << endl;
			taskscript.close();
			ShellExecute(0, "open", "task~rmdir.bat", 0, 0, SW_HIDE);
			return 0;
		}
		if ($AddCode1 == "-mkdir") {
			ofstream taskscript;
			taskscript.open("task~mkdir.bat");
			taskscript << "md " << $AddCode2 << endl;
			taskscript << "del task~mkdir.bat" << endl;
			taskscript << "exit" << endl;
			taskscript.close();
			ShellExecute(0, "open", "task~mkdir.bat", 0, 0, SW_HIDE);
			return 0;
		}
		if ($AddCode1 == "-runas") {

			bool retFileCheckEXIST = isFileExists_ifstream($AddCode2);
			if (retFileCheckEXIST) {
            LPCSTR AdminRun = $AddCode2.c_str();
			ShellExecute(0, "runas", AdminRun, 0, 0, SW_SHOW);
			return 0;
			}
			else {
				cout << "File not exist " << endl;
				return 0;
			}
			
		}
		if ($AddCode1 == "-nogui") {
			bool hidefilecheck = isFileExists_ifstream($AddCode2);
			if (hidefilecheck) {
				LPCSTR runhide = $AddCode2.c_str();
				ShellExecute(0, "open", runhide, 0, 0, SW_HIDE);
				return 0;
			}
			else {
				cout << "File Not Exist" << endl;
				return 0;
			}
		}

		goto UnknownCommand;
	}
	if (argc == 4) {
		//Line 4 Command
		line++;
		string $AddCode1 = argv[line];
		line++;
		string $AddCode2 = argv[line];
		line++;
		string $AddCode3 = argv[line];

		if ($AddCode1 == "-dl") {
			cout << "Starting Download Service" << endl;
			string DownloadURL = $AddCode2;
			string SavePath = $AddCode3;

			char delmark[20];
			strcpy_s(delmark, SavePath.c_str());
			
			cout << "Download URL :   " << DownloadURL << endl;
			cout << "Save Path :   " << SavePath << endl;
			cout << "Downloading...  " << endl;
			cout << endl <<endl;

			bool retcheckA = isFileExists_ifstream(SavePath);
			if (retcheckA) {
				remove(delmark);
			}

			LPCWSTR Durl = stringToLPCWSTR(DownloadURL);
			LPCWSTR Dsp = stringToLPCWSTR(SavePath);

			HRESULT applydownload = URLDownloadToFileW(
				nullptr,
				Durl,
				Dsp,
				0,
				nullptr
			);
			bool retdown = isFileExists_ifstream(SavePath);
			if (retdown) {
				cout << "Download Successfully" << endl;
				cout << "File is save from :  " << SavePath << endl;
				cout << "Process Exit" << endl;
				return 0;
			}
			else
			{
				cout << "Download Failed" << endl;
				cout << "Please try again or check your download link" << endl;
				cout << "Process Exit" << endl;
			}
		}
		if ($AddCode1 == "-runas") {

			bool retFileCheckEXIST = isFileExists_ifstream($AddCode2);
			if (retFileCheckEXIST) {
            LPCSTR AdminRun = $AddCode2.c_str();
			LPCSTR RunAdd = $AddCode3.c_str();
			ShellExecute(0, "runas", AdminRun, RunAdd, 0, SW_SHOW);
			return 0;
			}
			else {
				cout << "File not exist " << endl;
				return 0;
			}
			
		}
		if ($AddCode1 == "-nogui") {
			bool hidefilecheck = isFileExists_ifstream($AddCode2);
			if (hidefilecheck) {
				LPCSTR runhide = $AddCode2.c_str();
				LPCSTR runaddcode = $AddCode3.c_str();
				ShellExecute(0, "open", runhide, runaddcode, 0, SW_HIDE);
				return 0;
			}
			else {
				cout << "File Not Exist" << endl;
				return 0;
			}
		}

		goto UnknownCommand;
	}
	
	goto MarkforOut;
UnknownCommand:
	cout << "Unknown Command. " << endl;
	cout << "Please use -help to next" << endl;
	return 0;
	
	MarkforOut:
	MessageBox(0, "Code over support", "WinXetor", MB_OK);
	return 0;
}