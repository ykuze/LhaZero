object MsgForm: TMsgForm
  Left = 0
  Top = 0
  Caption = 'LhaZero'
  ClientHeight = 81
  ClientWidth = 496
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object MsgOldLb: TLabel
    Left = 8
    Top = 8
    Width = 52
    Height = 14
    Caption = 'MsgOldLb'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object MsgLb: TLabel
    Left = 8
    Top = 29
    Width = 34
    Height = 14
    Caption = 'MsgLb'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object CntLb: TLabel
    Left = 8
    Top = 50
    Width = 45
    Height = 14
    Caption = 'Count : '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
end
