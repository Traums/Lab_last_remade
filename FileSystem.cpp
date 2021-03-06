//---------------------------------------------------------------------------

#pragma hdrstop

#include "Main.h"
#include "FileSystem.h"
#include "windows.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
AbstractFS::AbstractFS(const wchar_t* disk_name){
	DiskHandle = CreateFileW(disk_name,
							 GENERIC_READ,
							 FILE_SHARE_READ | FILE_SHARE_WRITE,
							 NULL,
							 OPEN_EXISTING,
							 0,
							 NULL);

	if (DiskHandle == INVALID_HANDLE_VALUE)
	{
		Form1->Label4->Caption = getError();
	}
}
FAT32::FAT32(const wchar_t* disk_name) : AbstractFS(disk_name){
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;
	bool ReadSector;
	unsigned long SectorBegin = SetFilePointer(DiskHandle,
											   offset.LowPart,
											   &offset.HighPart,
											   FILE_BEGIN);
	if (SectorBegin != offset.LowPart) {
	   Form1->Label4->Caption = "?????? ????????? ???????";
	   CloseHandle(DiskHandle);
	}

	if(!ReadFile(DiskHandle,
		Block,
		bytes,
		&bytesRead,
		NULL))
	{
		Form1->Label4->Caption = "?????? ?????? ?????";
		CloseHandle(DiskHandle);
	}

	FAT32_BootRecord *ptrFAT32_BootRecord = (FAT32_BootRecord*)Block;
	BytesPerSector = ptrFAT32_BootRecord -> BytesPerSector;
	SectorsPerCluster = ptrFAT32_BootRecord -> SectorsPerCluster;
	BytesPerCluster =  BytesPerSector*SectorsPerCluster;

	OEM = L"FAT32";

	if (ptrFAT32_BootRecord->LargeSectors != 0)
	{
		 TotalClusters = (ptrFAT32_BootRecord->LargeSectors)/SectorsPerCluster;
	}
	else
	{
		 TotalClusters = (ptrFAT32_BootRecord->SmallSectors)/SectorsPerCluster;
	}
}

NTFS::NTFS(const wchar_t* disk_name) :AbstractFS(disk_name){
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;
	unsigned long SectorBegin = SetFilePointer(DiskHandle,
		offset.LowPart,
		&offset.HighPart,
		FILE_BEGIN);
	if (SectorBegin != offset.LowPart) {
	   Form1->Label4->Caption = "?????? ????????? ???????";
	   CloseHandle(DiskHandle);
	}

	bool ReadSector;
	if(!ReadFile(DiskHandle,
				 Block,
				 bytes,
				 &bytesRead,
				 NULL))
	{
		Form1->Label4->Caption = "?????? ?????????? ??????";
		CloseHandle(DiskHandle);
	}

	NTFS_BootRecord *ptrNTFS_BootRecord = (NTFS_BootRecord*)Block;
	BytesPerSector = ptrNTFS_BootRecord -> BytesPerSector;
	SectorsPerCluster = ptrNTFS_BootRecord -> SectorsPerCluster;
	BytesPerCluster =  BytesPerSector*SectorsPerCluster;
	OEM = L"NTFS";
	TotalClusters = (ptrNTFS_BootRecord -> TotalSectors)/SectorsPerCluster;
}
HANDLE AbstractFS::GetDiskHandle()
{
	return DiskHandle;
}
unsigned long AbstractFS::GetBytesPerSector()
{
	return BytesPerSector;
}
unsigned long AbstractFS::GetBytesPerCluster()
{
	return BytesPerCluster;
}
unsigned long AbstractFS::GetSectorsPerCluster()
{
	return SectorsPerCluster;
}
unsigned long AbstractFS::GetTotalClusters()
{
	return TotalClusters;
}
const wchar_t* AbstractFS::GetOEM()
{
	return OEM;
}
byte* AbstractFS::ReadCluster(unsigned long long number, BYTE *dataBuffer){

	//BytesPerCluster * number;

	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = number * BytesPerSector;
	unsigned long long currentPosition  =  SetFilePointer(DiskHandle,
															offset.LowPart,
															&offset.HighPart,
															FILE_BEGIN);
	if (currentPosition  != offset.LowPart) {
	   Form1->Label4->Caption = getError();
	   //Form1->Label4->Caption = "?????? ????????? ???????";
	   //CloseHandle(DiskHandle);
	}

	bool ReadSector;
	if(!ReadFile(DiskHandle,
				 dataBuffer,
				 bytes,
				 &bytesRead,
				 NULL))

	{
		char errMsg[65];
		DWORD dw = GetLastError();
		FormatMessageA(
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					dw,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPSTR)&errMsg,
					sizeof(errMsg), NULL );
					//return *errMsg;
		String Error = getError();
		Form1->Label4->Caption = getError();
		//CloseHandle(DiskHandle);
	};
	/*Byte* ptrBlock = Block;
	dataBuffer = ptrBlock*/

	return dataBuffer ;
	//return true;
}
AbstractFS* FactoryFS(const wchar_t* disk_name){
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;
	AbstractFS* FS;
	HANDLE DiskHandle;
	bool ReadSector;

	if((DiskHandle = CreateFileW(disk_name,
								GENERIC_READ,
								FILE_SHARE_READ | FILE_SHARE_WRITE,
								NULL,
	                          	OPEN_EXISTING,
								0,
								NULL)) == INVALID_HANDLE_VALUE)
	{
	   Form1->Label3->Caption = getError();

	   CloseHandle(DiskHandle);
	   Form1->Label4->Caption = "?????? ??????????? ?????";
	}
	unsigned long SectorBegin = SetFilePointer(DiskHandle,
											   offset.LowPart,
											   &offset.HighPart,
											   FILE_BEGIN);
	if (SectorBegin != offset.LowPart) {
	   Form1->Label4->Caption = "?????? ????????? ???????";
	   CloseHandle(DiskHandle);
	}

	if(!ReadFile(DiskHandle,
			 Block,
			 bytes,
			 &bytesRead,
			 NULL))
	{
		Form1->Label4->Caption = "?????? ?????????? ??????";
		CloseHandle(DiskHandle);
	}

	Abstract_FS *ptrAbstract_FS = (Abstract_FS*)Block;
	CloseHandle(DiskHandle);

	if (strstr(ptrAbstract_FS->OEM,"NTFS")) {
	   FS = new NTFS(disk_name);
	}else if (strstr(ptrAbstract_FS -> OEM,"MSDOS5.0")) {
	   FS = new FAT32(disk_name);
	}else {
	   Form1->Label4->Caption = "?????? ??????????? ???????? ???????";
	}
    return FS;
}
char getError(){
	char errMsg[65];
	DWORD dw = GetLastError();
	FormatMessageA(
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPSTR)&errMsg,
				sizeof(errMsg), NULL );
				return *errMsg;
}
