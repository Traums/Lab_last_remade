//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "sqlite3.h"
#include "FileSystem.h"
#include "Thread.h"
#include <string>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
sqlite3* Database;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	int openResult = sqlite3_open16(L".\\Database.sqlite", &Database);
	AbstractFS* FS;

    VirtualStringTree1 -> NodeDataSize = sizeof(TreeNodeStruct);
	sqlite3_stmt *pStatement;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	AbstractFS* FS;
	UnicodeString FSInfo;
	wchar_t Path[64];
	UnicodeString deviceName = Form1->Edit1->Text;
	wchar_t EditText = deviceName.w_str()[0];
	swprintf(Path,L"\\\\.\\%c:",EditText);

	FS = FactoryFS(Path);
	FSInfo += "??? ??:";FSInfo += UnicodeString(FS->GetOEM());
	FSInfo += "\n???? ?? ??????:";FSInfo += UnicodeString(FS->GetBytesPerSector());
	FSInfo += "\n???????? ? ????????:";FSInfo += UnicodeString(FS->GetSectorsPerCluster());
	FSInfo += "\n???? ? ???????? ";FSInfo += UnicodeString(FS->GetBytesPerCluster());
	FSInfo += "\n?????????? ?????????:";FSInfo += UnicodeString(FS->GetTotalClusters());

	Label2->Caption = FSInfo;
	Label2->Visible = True;
    Form1->Button2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	AbstractFS* FS;
	wchar_t Path[64];
	UnicodeString deviceName = Form1->Edit1->Text;
	wchar_t EditText = deviceName.w_str()[0];
	swprintf(Path,L"\\\\.\\%c:",EditText);

	FS = FactoryFS(Path);
	ReadThreadPtr = new ReadThread(false, FS, Database);

	int openResult = sqlite3_open16(L".\\Database.sqlite", &Database);
	const char *errmsg;
	if( openResult != SQLITE_OK)
	{
		errmsg = sqlite3_errmsg(Database);
	}
	else
	{
		errmsg = "DONE";
	};

	sqlite3_stmt *pStatement;
	int result = sqlite3_prepare16_v2(Database, L"SELECT * FROM Signatures;", -1, &pStatement, NULL);
	while (true) {
		result = sqlite3_step(pStatement);
		if (result == SQLITE_ROW)
		{
			PVirtualNode entryNode = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(entryNode);

			nodeData -> ID = sqlite3_column_int(pStatement,0);
			nodeData -> ClusterNumber = sqlite3_column_int(pStatement,1);
			nodeData -> Signature = (UnicodeString)(char*)sqlite3_column_text(pStatement,2);
		}
	   if(result == SQLITE_DONE) break;
	}
	sqlite3_finalize(pStatement);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	VirtualStringTree1->DeleteNode(selectedNode);

	int selectedNodeIndex = selectedNode->Index;
	int delIndex;
	sqlite3* DataBase;
	sqlite3_stmt *pStatement;
	const char *errmsg;

	char* sqlStr;
	selectedNodeIndex = selectedNodeIndex + 1;

	std::string tmp = "DELETE FROM Signatures WHERE ID = " + std::to_string(selectedNodeIndex) + ";";
	char const *res = tmp.c_str();

	int deleteRes =  sqlite3_exec(Database, res,NULL, NULL ,NULL);
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   VirtualStringTree1->Clear();

   char sqlStr [] = "DELETE FROM Signatures;";
   int deleteRes =  sqlite3_exec(Database, sqlStr,NULL, NULL ,NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Exit(TObject *Sender)
{
	sqlite3_close(Database);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	if(!Node) return;
    TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(Node);
		switch (Column) {
			case 0:
			{
				CellText = UnicodeString(nodeData -> ID);  break;
			}
			case 1:
			{
				CellText = UnicodeString(nodeData -> ClusterNumber);  break;
			}
			case 2:
			{
				CellText = nodeData -> Signature; break;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	if(ReadThreadPtr!=NULL)
		ReadThreadPtr->Terminate();
}
//---------------------------------------------------------------------------

