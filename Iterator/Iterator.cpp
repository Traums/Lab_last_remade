//---------------------------------------------------------------------------

#pragma hdrstop

#include "Iterator.h"
#include "FileSystem.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
Iterator::Iterator(AbstractFS* FS) :ClusterNumber(0), ClustersTotal(FS->GetTotalClusters()), Done(false), FS(FS)
{
	byte* dataBuffer = new BYTE[FS->GetBytesPerCluster()];
}
void Iterator::First(){
	ClusterNumber = 1;
}
void Iterator::Last(){
	ClusterNumber = ClustersTotal;
}
void Iterator::Next(){
	ClusterNumber++;
}
int Iterator::Current(){
	return ClusterNumber;
}
bool Iterator::IsDone(){
	return (ClusterNumber < ClustersTotal && Done == false);
}
unsigned long Iterator::GetClusterNumber(){
	return ClusterNumber;
}
void Iterator::Stop(){
	Done = true;
}
byte* Iterator::GetDataOnCluster( byte *dataBuffer){
	//dataBuffer = FS->ReadCluster(ClusterNumber, dataBuffer);
	return FS->ReadCluster(ClusterNumber, dataBuffer);//dataBuffer;
}


