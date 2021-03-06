//---------------------------------------------------------------------------

#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Main.h"
#include "FileSystem.h"
#include "Iterator.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
std::wstring CheckSignature(BYTE* ByteFlow);

class ReadThread : public TThread
{
private:
    void __fastcall UpdateLabel();
protected:
	AbstractFS* FS;
	bool EnableDec;
	Iterator* Iterator_inst;
	void __fastcall Execute();
	BYTE* Content;
    sqlite3* Database;
public:
	AbstractFS* GetFS();
	bool GetEnableDec();
	__fastcall ReadThread(bool CreateSuspended, AbstractFS* FS, sqlite3* Database);
};
bool Check_Cluster(BYTE* Flow);
bool compare_wstr(std::wstring stringA , std::wstring stringB);
//---------------------------------------------------------------------------
#endif
