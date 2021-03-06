//---------------------------------------------------------------------------

#ifndef IteratorH
#define IteratorH
#include "FileSystem.h"
#include "Main.h"
//---------------------------------------------------------------------------

class Iterator
{
	protected:
	   unsigned long ClusterNumber;
	   //BYTE* dataBuffer;
	   unsigned long ClustersTotal;
	   bool Done;
	   AbstractFS* FS;
	public:
		Iterator(AbstractFS* FS);
		unsigned long GetClusterNumber();
		bool IsDone();
		void First();
		void Last();
		void Next();
		int Current();
        void Stop();
		byte* Iterator::GetDataOnCluster( byte *dataBuffer);
};

#endif
