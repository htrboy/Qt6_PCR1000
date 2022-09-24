/*
 *
 * QtPcr is a PCR-1000 controls.
 * 
 * Copyright (C) 2001
 *
 *     Teepanis Chachiyo  <teepanis@physics.purdue.edu>
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

#include <QString>

#include "freqdisplay.h"
#include "mainwindow.h"


FreqDisplay::FreqDisplay(QWidget *parent, const char *name)
    : QLCDNumber()
{
	setMode( Dec );
	setSegmentStyle( Filled );
    setDigitCount( 13 );
	setFrameStyle( 0x00 );
	setPalette( QPalette( Qt::green, Qt::black ) );
	
	currentFreq = DEFAULT_FREQ;

	displayFreq( currentFreq );	
}



void FreqDisplay::displayFreq(const pcrfreq_t freq)
{
    QString fTemp;
	int i;

	currentFreq = freq;

    fTemp = QString::number(freq);
    i = fTemp.length();
    fTemp.insert(i-3,QString("."));

	if(i>6)
        fTemp.insert(i-6,QString("."));

}



void FreqDisplay::displayReset()
{
	displayFreq( currentFreq );
}



void FreqDisplay::displayTemp( const QString *str)
{
	display(*str);
}
