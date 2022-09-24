/*
 *
 * QtPcr is a PCR-1000 controls.
 * 
 * Copyright (C) 2001
 *
 *     Teepanis Chachiyo   <teepanis@physics.purdue.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.     
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.              
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software   
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

/*
 * code updates
 * changes to QTimer calls
 * and QString callss
*/

#include "keypad.h"

bool ok;

KeyPad::KeyPad( QWidget *parent, const char *name)
    : QWidget( parent )
{

  button0 	= 	new QPushButton("0", this );
  button1 	= 	new QPushButton("1", this );
  button2 	= 	new QPushButton("2", this );
  button3 	= 	new QPushButton("3", this );
  button4 	= 	new QPushButton("4", this );
  button5 	= 	new QPushButton("5", this );
  button6 	= 	new QPushButton("6", this );
  button7 	= 	new QPushButton("7", this );
  button8 	= 	new QPushButton("8", this );
  button9 	= 	new QPushButton("9", this );
  buttonDot     = 	new QPushButton(".", this );
  buttonEnter   =	new QPushButton("E", this );
  
  button0->setFocusPolicy( Qt::NoFocus );
  button1->setFocusPolicy( Qt::NoFocus );
  button2->setFocusPolicy( Qt::NoFocus );
  button3->setFocusPolicy( Qt::NoFocus );
  button4->setFocusPolicy( Qt::NoFocus );
  button5->setFocusPolicy( Qt::NoFocus );
  button6->setFocusPolicy( Qt::NoFocus );
  button7->setFocusPolicy( Qt::NoFocus );
  button8->setFocusPolicy( Qt::NoFocus );
  button9->setFocusPolicy( Qt::NoFocus );
  buttonDot->setFocusPolicy( Qt::NoFocus );
  buttonEnter->setFocusPolicy( Qt::NoFocus );

  connect( button0, SIGNAL(clicked()), this, SLOT(clicked0()) );
  connect( button1, SIGNAL(clicked()), this, SLOT(clicked1()) );
  connect( button2, SIGNAL(clicked()), this, SLOT(clicked2()) );
  connect( button3, SIGNAL(clicked()), this, SLOT(clicked3()) );
  connect( button4, SIGNAL(clicked()), this, SLOT(clicked4()) );
  connect( button5, SIGNAL(clicked()), this, SLOT(clicked5()) );
  connect( button6, SIGNAL(clicked()), this, SLOT(clicked6()) );
  connect( button7, SIGNAL(clicked()), this, SLOT(clicked7()) );
  connect( button8, SIGNAL(clicked()), this, SLOT(clicked8()) );
  connect( button9, SIGNAL(clicked()), this, SLOT(clicked9()) );
  connect( buttonDot,   SIGNAL(clicked()), this, SLOT(clickedDot()) );
  connect( buttonEnter, SIGNAL(clicked()), this, SLOT(clickedEnter()) );
  
  tempFreq = "";
  tictoc   = new QTimer;
  
  connect( tictoc, SIGNAL(timeout()),
	   this, SLOT(timeOut()) );
  
  setFocusPolicy( Qt::StrongFocus );
  setFocus();
}



KeyPad::~KeyPad()
{

  delete button0;
  delete button1;
  delete button2;
  delete button3;
  delete button4;
  delete button5;
  delete button6;
  delete button7;
  delete button8;
  delete button9;
  delete buttonDot;
  delete buttonEnter;
  
  delete tictoc;
  
}


//
// keyReleaseEvent grabs keyboard input frequency
//
void KeyPad::keyPressEvent( QKeyEvent *e )
{
    switch(e->text().toInt(&ok, 10)) {
    //switch(e->ascii()){ // code update
		case '\r': clickedEnter(); break;
		case '.':  clickedDot(); break;
		case '0':  clicked0(); break;
		case '1':  clicked1(); break;
		case '2':  clicked2(); break;
		case '3':  clicked3(); break;
		case '4':  clicked4(); break;
		case '5':  clicked5(); break;
		case '6':  clicked6(); break;
		case '7':  clicked7(); break;
		case '8':  clicked8(); break;
		case '9':  clicked9(); break;
	}
}



//
// resizeEvent recomputes size and positon of each keyboard
// to fit the whole screen
//
void KeyPad::resizeEvent( QResizeEvent *e )
{
	int w, h;

	w = e->size().width()/3;
	h = e->size().height()/4;
	button1->setGeometry(   0, 0, w, h);
	button2->setGeometry(   w, 0, w, h);
	button3->setGeometry( 2*w, 0, w, h);

    button4->setGeometry(   0, h, w, h);
    button5->setGeometry(   w, h, w, h);
    button6->setGeometry( 2*w, h, w, h);

    button7->setGeometry(   0, h*2, w, h);
    button8->setGeometry(   w, h*2, w, h);
    button9->setGeometry( 2*w, h*2, w, h);

    buttonDot->setGeometry(     0, h*3, w, h);
    button0->setGeometry(       w, h*3, w, h);
    buttonEnter->setGeometry( 2*w, h*3, w, h);

}



//
// timeOut occurs when entering freqency session
// has expired
//
void KeyPad::timeOut()
{
    tempFreq = "";
	emit displayReset();
}



//
// clickedNumber handles event when user clicked
// numbering buttons
//
void KeyPad::clickedNumber(const char *str)
{
    tictoc->start( 5000 );
    //tictoc->start( 5000, true ); // code update

	if(tempFreq.length() >= 11)
		return;

	tempFreq.append(str);
	emit displayTemp( &tempFreq );	
}

void KeyPad::clicked0(){ clickedNumber("0"); }
void KeyPad::clicked1(){ clickedNumber("1"); }
void KeyPad::clicked2(){ clickedNumber("2"); }
void KeyPad::clicked3(){ clickedNumber("3"); }
void KeyPad::clicked4(){ clickedNumber("4"); }
void KeyPad::clicked5(){ clickedNumber("5"); }
void KeyPad::clicked6(){ clickedNumber("6"); }
void KeyPad::clicked7(){ clickedNumber("7"); }
void KeyPad::clicked8(){ clickedNumber("8"); }
void KeyPad::clicked9(){ clickedNumber("9"); }

void KeyPad::clickedDot()
{
    tictoc->start( 5000 );
 
	if(tempFreq.length() >= 11)
		return;

	if(tempFreq.contains(".")==0 && tempFreq.length()<=4){
		tempFreq.append(".");
		emit displayTemp( &tempFreq );
	}else
		return;
	
}

void KeyPad::clickedEnter()
{
	int dot;
	int npadzero;
 
    tictoc->start( 500 );

	if(tempFreq.length() >= 11)
		return;
    dot = tempFreq.contains("."); // code update
    //dot = tempFreq.find(".");

	if(dot >= 0){
		npadzero = 7-tempFreq.length()+dot;
		tempFreq.remove(dot,1);
	}else
		npadzero = 6;

	for(int i = 0; i < npadzero; i++)
		tempFreq.append("0");

	pcrfreq_t freq = tempFreq.toULong();

	emit setFreq( freq ); 

	tictoc->stop();
	timeOut();
    tempFreq = "";

	return;
}
