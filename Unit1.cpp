//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Graphics::TBitmap*Back;
Graphics::TBitmap*GoodImage;
Graphics::TBitmap*BadImage;
TPoint GoodPos;
int o, x0, j, i, speed=1,NewX,NewY,N;
bool IsIntersect;
TPoint BadPos[25];  //Положения x,y каждого плохиша
int Lifes;
int p;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
randomize();
Back=new Graphics::TBitmap();
Back->Width =300;
Back->Height=300;
GoodImage=new Graphics::TBitmap();
GoodImage->LoadFromFile("good.bmp");
BadImage=new Graphics::TBitmap();
BadImage->LoadFromFile("bad.bmp");
BadImage->Transparent=true;
Lifes=3;
N=15;
p=1;
}
//---------------------------------------------------------------------------
TForm1::FlipOnForm()
{
		Canvas->Draw(0,0,Back);
}
TForm1::CreateCoord()
{
	for (int r=0; r<N; r++)
	{
		int Counter=0;
		while (1)
		{
			Counter++;
			if (Counter>500000)
				return false;
			NewX=random(300);
			NewY=random(5)*30+60;
			 IsIntersect=false;
			for (int i=0; i<N; i++)
			{
				if (BadPos[i].x<-50) continue;
				if (NewY==BadPos[i].y && NewX>BadPos[i].x-50 && NewX<BadPos[i].x+50)
				{
					IsIntersect=true;
					break;
				}
			}
			if (!IsIntersect) break;
		}
		BadPos[r].x=NewX;
		BadPos[r].y=NewY;
	}
	return true;
	/*for (int row=0; row<5; row++)
	{
		for (int i=0; i<3; i++)
		{
			while (1)
			{
				NewX=random(300);
				IsIntersect=false;
				for (int j=0; j<3; j++)
				{

				}
			}
		}
	} */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
MoveBad();
Back->Canvas->Brush->Color=RGB(192,192,192);
 for(int j=0;j<25;j++)
 for(int i=0;i<25;i++)
 {
Back->Canvas->FillRect(Rect(i*30,j*30,i*30+30,j*30+30));
Back->Canvas->Draw(GoodPos.x*30,GoodPos.y*30,GoodImage);
 }
DrawBad();
FlipOnForm();
if(IfAll())
		{
		Timer1->Enabled=false;
		ShowMessage("Переход на следующий уровень\n+1 жизнь");
		Lifes++;
		speed++;
		p++;
        Label2->Caption="Уровень: "+IntToStr(p);
		Label1->Caption="Жизней:"+IntToStr(Lifes);
		GoodPos=Point(0,0);
		for(int i=0;i<N;i++)BadPos[i].x=666;
		//MoveBad();
		Timer1->Enabled=true;
		}
if(TestEnd())
		{
		Timer1->Enabled=false;
		ShowMessage("Вас сбили");
		if(Lifes>0)
		{
		Lifes--;
		Label1->Caption="Жизней: "+IntToStr(Lifes);
		GoodPos=Point(0,0);
		for(int i=0;i<N;i++)BadPos[i].x=666;
		//MoveBad();
		Timer1->Enabled=true;
		}else
				{
				ShowMessage("Вам придётся начинать сначала");
				Lifes=3;
				speed=1;
				p=1;
				Label2->Caption="Уровень: "+IntToStr(p);
				Label1->Caption="Жизней: "+IntToStr(Lifes);
				GoodPos=Point(0,0);
				for(int i=0;i<N;i++)BadPos[i].x=666;
				//MoveBad();
				Timer1->Enabled=true;
				}
		}
}

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
if(Key==VK_LEFT)
		{
		GoodPos.x--;
		}
if(Key==VK_RIGHT)
		{
		GoodPos.x++;
		}
if(Key==VK_UP)
		{
		GoodPos.y--;
		}
if(Key==VK_DOWN)
		{
		GoodPos.y++;
		}
if(GoodPos.x>9)GoodPos.x=9;
if(GoodPos.x<0)GoodPos.x=0;
if(GoodPos.y>9)GoodPos.y=9;
if(GoodPos.y<0)GoodPos.y=0;
}


//---------------------------------------------------------------------------
TForm1::MoveBad()
{
  if (BadPos[0].x==666)
  {
		CreateCoord();
		return 0;
  }

  for (int r = 0; r < N; r++) // вместо этой штуки
  {
	if (BadPos[r] .x<-50)
	{
		while (1)
		{
			NewX=300;
			NewY=random(5)*30+60;
			IsIntersect=false;
			for (int i=0; i<N; i++)
			{
				if (BadPos[i].x<-50) continue;
				if (BadPos[i].y==NewY && NewX>BadPos[i].x-50 && NewX<BadPos[i].x+50)
				{
					IsIntersect=true;
					break;
				}
			}
			if (!IsIntersect) break;
		}
		BadPos[r].x=NewX;
		BadPos[r].y=NewY;
	}
   //BadPos[r] .x=random (300);
   //BadPos[r] .y=random (5)*30 +50;
   }
   /*int cellWidth =  300 / 8; int currentBadGuy = 0;
   for(int i = 0; i <  5; i++)
   {for(int j = 0; j <  8; j++)
   {if (i == 0 && j == 0) continue;
   BadPos[currentBadGuy].x=j * cellWidth + random(cellWidth);
   BadPos[currentBadGuy].y=i;currentBadGuy++;}} */
   for (int i = 0; i < N; i++)
   {
	  BadPos[i] .x-=speed;
   }
}


TForm1::DrawBad()
{
	   for(int i=0;i<N;i++)
	   {
	   Back->Canvas->Draw(BadPos[i].x,BadPos[i].y,BadImage);
	   }
}

bool __fastcall TForm1::TestEnd()
{
for(int j=0;j<N;j++)
{
RECT Rect1=Rect(GoodPos.x*30+3,GoodPos.y*30,GoodPos.x*30+27,GoodPos.y*30+27);
RECT Rect3=Rect(0,0,0,0);
RECT Rect2=Rect(BadPos[j].x+5,BadPos[j].y+5,BadPos[j].x+25,BadPos[j].y+25);
if(IntersectRect(&Rect3,&Rect1,&Rect2))
{
return true;
}
}
return false;
}

bool TForm1::IfAll()
{
if (GoodPos .y>7)
{
 return true;
}
else
return false;
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  for(int i=0;i<N;i++)BadPos[i].x=666;
}
//---------------------------------------------------------------------------


