// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string> 
#include <shlobj.h>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <locale> 
#include <codecvt>
#include <windows.h>
#include <Lmcons.h>

namespace fs = std::filesystem;

using namespace std;


int main(void)
{
	
	//trouvage du nom
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	cout << "salut mon bo " << username << endl;

	//trouvage du chemin
	TCHAR mcdir[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL,
		CSIDL_APPDATA | CSIDL_FLAG_CREATE,
		NULL,
		0,
		mcdir)))
	{
		std::cout << "dossier Appdata trouve" << endl;
	}
	
	//formatage du chemin
	string mcdi = mcdir;
	std::cout << mcdi.c_str() << endl;
	mcdi += "\\.minecraft";
	std::cout << mcdi.c_str() << endl;

	//conversion de l'adresse en string
	TCHAR* bob = mcdir;
	string s_mcdir = bob;
	
	//moddifcation de prof.json
	string prof = mcdi += "\\launcher_profiles.json";
	std::cout << prof << endl;

	string line;
	ifstream myfile(prof);
	ostringstream o_prof;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			o_prof << line << '\n';
			if (line.find("\"profiles\" : {") == 2) {
				o_prof << "    \"59efa1743311ab816385ef945539c77b\" : {" << endl
					<< "	  \"created\" : \"2020-01-23T16:18:06.380Z\", " << endl
					<< "	  \"gameDir\" : \"C:\\\\Users\\\\" << username <<"\\\\AppData\\\\Roaming\\\\.modpack" << endl
					<< "      \"icon\" : \"Cake\", " << endl
					<< "      \"javaArgs\" : \"-Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M\"," << endl
					<< "      \"lastUsed\" : \"2020-01-21T01:48:52.398Z\"," << endl
					<< "      \"lastVersionId\" : \"1.12.2-forge1.12.2-14.23.5.2847\"," << endl
					<< "      \"name\" : \"Le meilllllllleur serveur\"," << endl
					<< "      \"type\" : \"custom\"" << endl
					<< "	}," << endl;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	ofstream newprof;
	newprof.open(prof.c_str());
	if(newprof.is_open()) {
		newprof << o_prof.str();
		newprof.close();
		puts("File successfully created");
	}
	else
		puts("Error creating file");
	
	

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


/*
"59efa1743311ab816385ef945539c77b" : {
	  "created" : "2020-01-23T16:18:06.380Z",
	  "gameDir" : "C:\\Users\\mimas\\AppData\\Roaming\\le_meilleur_serveur",
	  "icon" : "Cake",
	  "javaArgs" : "-Xmx4G -XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=32M",
	  "lastUsed" : "2020-01-21T01:48:52.398Z",
	  "lastVersionId" : "1.12.2-forge1.12.2-14.23.5.2847",
	  "name" : "Le meilllllllleur serv\u00e9",
	  "type" : "custom"
	},
*/