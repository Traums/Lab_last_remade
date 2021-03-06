//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit1;
	TButton *Button1;
	TCheckBox *CheckBox1;
	TButton *Button2;
	TCheckBox *CheckBox2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button3Exit(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall Button5Click(TObject *Sender);


private:	// User declarations
    class ReadThread* ReadThreadPtr;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};

typedef struct
{
        int ID;
		UnicodeString Signature;
		int ClusterNumber;
} TreeNodeStruct;
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
