object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 588
  ClientWidth = 944
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 528
    Top = 72
    Width = 150
    Height = 28
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1076#1080#1089#1082':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 528
    Top = 106
    Width = 143
    Height = 28
    Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label3: TLabel
    Left = 399
    Top = 443
    Width = 13
    Height = 28
    Caption = '1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 8
    Top = 542
    Width = 83
    Height = 28
    Caption = #1054#1096#1080#1073#1082#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 443
    Width = 378
    Height = 28
    Caption = #1058#1077#1082#1091#1097#1080#1081' '#1086#1073#1088#1072#1073#1072#1090#1099#1074#1072#1077#1084#1099#1081' '#1082#1083#1072#1089#1090#1077#1088':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 72
    Width = 497
    Height = 353
    Header.AutoSizeIndex = 0
    TabOrder = 0
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = #1057#1080#1075#1085#1072#1090#1091#1088#1072
      end
      item
        Position = 1
        Text = #1050#1083#1072#1089#1090#1077#1088
      end>
  end
  object Edit1: TEdit
    Left = 684
    Top = 68
    Width = 37
    Height = 36
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = 'C'
  end
  object Button1: TButton
    Left = 736
    Top = 68
    Width = 97
    Height = 36
    Caption = #1054#1087#1088#1077#1076#1077#1083#1080#1090#1100
    TabOrder = 2
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 528
    Top = 288
    Width = 265
    Height = 25
    Caption = #1048#1075#1085#1086#1088#1080#1088#1086#1074#1072#1090#1100' '#1087#1091#1089#1090#1099#1077' '#1082#1083#1072#1089#1090#1077#1088#1099
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 3
  end
  object Button2: TButton
    Left = 519
    Top = 248
    Width = 258
    Height = 34
    Caption = #1055#1086#1080#1089#1082' '#1089#1080#1075#1085#1072#1090#1091#1088
    TabOrder = 4
    OnClick = Button2Click
  end
  object CheckBox2: TCheckBox
    Left = 528
    Top = 328
    Width = 265
    Height = 17
    Caption = #1057#1095#1080#1090#1072#1090#1100' '#1087#1077#1088#1074#1099#1077' 15000 '#1082#1083#1072#1089#1090#1077#1088#1086#1074
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 5
  end
  object Button3: TButton
    Left = 528
    Top = 368
    Width = 105
    Height = 57
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 6
    OnClick = Button3Click
    OnExit = Button3Exit
  end
  object Button4: TButton
    Left = 639
    Top = 368
    Width = 170
    Height = 57
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1091#1102' '#1079#1072#1087#1080#1089#1100
    TabOrder = 7
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 736
    Top = 456
    Width = 105
    Height = 61
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086#1090#1086#1082
    TabOrder = 8
    OnClick = Button5Click
  end
end