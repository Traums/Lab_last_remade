//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop
#include "Main.h"
#include "Thread.h"
#include "sqlite3.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#pragma package(smart_init)
int count;
__fastcall ReadThread::ReadThread(bool CreateSuspended, AbstractFS* FS, sqlite3* Database)
	: TThread(CreateSuspended), FS(FS), Database(Database)
{
	 FreeOnTerminate = true;
	 Iterator_inst = new  Iterator(FS);
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
	 count = 1;
	 int SignFound = 0 ;
	 sqlite3_stmt *pStatement;
	 int openDB = sqlite3_open16(L".\\Database.sqlite",&Database);

	 if (openDB != SQLITE_OK)
	 {
		Form1->Label4->Caption = "?????? ???????? ??";
	 }

	 for( Iterator_inst->First();Iterator_inst->IsDone() == true;Iterator_inst->Next())
	 {
		if(Terminated){
			break;
		}
		if(Form1->CheckBox2->Checked && (int)Iterator_inst->Current() == 15001){
			Iterator_inst->Stop();
            continue;
		}

		int dummmy = Iterator_inst->Current();
		//BYTE* dataBuffer;
		//BYTE dataBuffer = FS->GetBytesPerSector();
		//BYTE * dataBuffer[512] = new byte[FS->GetBytesPerSector()];

        BYTE* dataBuffer = new byte[FS->GetBytesPerSector()];
		dataBuffer = Iterator_inst->GetDataOnCluster(dataBuffer);
		UpdateLabel();


		if(Form1->CheckBox1->Enabled){
			if (Check_Cluster(dataBuffer))continue;
		}

		std::wstring DetectedSign = CheckSignature(dataBuffer);
		if(!compare_wstr(DetectedSign,L"Not Found"))
		{
			std::wstring sql = L"INSERT INTO Signatures (ID, Cluster, Signature) Values (" + std::to_wstring(SignFound+1) + L","
			+ std::to_wstring(Iterator_inst->Current())	+ L", \"" + DetectedSign + L"\");";

			const wchar_t* sql_statement = sql.c_str();
			int result = sqlite3_prepare16_v2(Database, sql_statement, -1, &pStatement, NULL);

			if (result == SQLITE_OK){
				sqlite3_step(pStatement);
				sqlite3_finalize(pStatement);
				SignFound++;
			}else {
				char const *errmsg = sqlite3_errmsg(Database);
				Form1->Label4->Caption = sqlite3_errmsg(Database);
			}
		}
		else
		{
		  continue;
		}

	 }
	 Form1->Label7->Caption = SignFound;

	 sqlite3_close(Database);
}
bool compare_wstr(std::wstring stringA , std::wstring stringB)
{
	transform(stringA.begin(), stringA.end(), stringA.begin(), toupper);
	transform(stringB.begin(), stringB.end(), stringB.begin(), toupper);

    return (stringA == stringB);
}
bool Check_Cluster(BYTE* Flow){
	if (Flow != NULL )
		return (Flow[0] == 0x00);
	else
		return false;
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::UpdateLabel()
{
  Form1->Label3->Caption = count++;
}

BYTE jpeg[]={0xFF,0xD8,0xFF,0xE0};
BYTE png[]={0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
BYTE zip[]={0x50,0x4B,0x03,0x04};
BYTE rar[]={0x52,0x61,0x72,0x21,0x1A,0x07,0x01};
BYTE zip7[]={0x37,0x7A,0xBC,0xAF,0x27};
BYTE *Signatures[]={jpeg,png,zip,rar,zip7};
std::wstring Signatures_name[5] = { L"jpeg", L"png", L"zip", L"rar", L"zip7"};

std::wstring CheckSignature(BYTE* ByteFlow){
	if (ByteFlow != NULL)
	for(int i = 0; i < 5;i++){
		for(int j=1; j < sizeof(Signatures[i]) ;j++)
		{
			if(ByteFlow[j]==Signatures[i][j]){
				if(j == sizeof(Signatures[i])-1)
				{
					return Signatures_name[i];
				}
				else{
					break;
                }
			}
		}
	}
return L"Not Found";
}
