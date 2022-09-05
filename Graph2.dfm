object FormSizeVer: TFormSizeVer
  Left = 0
  Top = 0
  Caption = 'Size between vertex'
  ClientHeight = 237
  ClientWidth = 272
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LabelEnterSize: TLabel
    Left = 56
    Top = 40
    Width = 172
    Height = 17
    Caption = 'Enter size between vertex'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelNumSize: TLabel
    Left = 56
    Top = 168
    Width = 153
    Height = 17
    Caption = 'Enter numbers in fields'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object EditSizeVer: TEdit
    Left = 72
    Top = 71
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '1'
    OnKeyPress = EditSizeVerKeyPress
  end
  object ButtonOkClose: TButton
    Left = 94
    Top = 120
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 1
    OnClick = ButtonOkCloseClick
  end
end
