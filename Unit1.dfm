object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 351
  ClientWidth = 495
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 384
    Top = 8
    Width = 62
    Height = 16
    Caption = #1046#1080#1079#1085#1077#1081': 3'
  end
  object Label2: TLabel
    Left = 384
    Top = 96
    Width = 69
    Height = 16
    Caption = #1059#1088#1086#1074#1077#1085#1100' : 1'
  end
  object Timer1: TTimer
    Interval = 20
    OnTimer = Timer1Timer
    Left = 296
    Top = 16
  end
end
