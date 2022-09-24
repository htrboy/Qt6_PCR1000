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

#include "aliasdisplay.h"
#include <stdio.h>

InfoLabel::InfoLabel(QWidget * parent, const char * name)
    : QLabel( ){}

void InfoLabel::mouseReleaseEvent ( QMouseEvent * e)
{
    emit mouseReleased();
}

InfoDisplay::InfoDisplay(QWidget * parent, const char * name)
    : QWidget( )
{
    //QColorGroup cg(colorGroup());

    QPalette cg;


    cg.setColor(QPalette::WindowText, Qt::cyan);
    cg.setColor(QPalette::Dark, Qt::black);
    cg.setColor(QPalette::Window, Qt::black);

    //setPalette( QPalette(cg, cg, cg) );


    info = "";

    infoLine = new InfoLabel( sb->viewport() );
    tictoc = new QTimer;
    speed = 50;
    editing = false;

    //setFrameStyle( InfoLabel::NoFrame );
    infoLine->setFrameStyle( InfoLabel::NoFrame );
    infoLine->setPalette( cg );
    sb->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    sb->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    sb->setViewport(infoLine);
    connect( tictoc, SIGNAL(timeout()),
             this, SLOT(timeToScroll()) );

    connect( infoLine, SIGNAL(mouseReleased()),
             this, SLOT(infoMouseReleasedSlot()) );

    infoUpdate("");
}

QString InfoDisplay::text()
{ return info; }

void InfoDisplay::infoUpdate(const char *str){
    QString temp;

    //QColorGroup cg(colorGroup());
    //QPalette cg;

    info = str;
    if(info.isEmpty()){
        tictoc->stop();
    }

    tictoc->start( speed );
    //temp = info.simplifyWhiteSpace();
    temp = info.trimmed();
    temp.prepend("                                       ");
    temp.append ("                                       ");

    infoLine->setText(temp);
}

void InfoDisplay::setRunning(bool flag)
{
    if(flag){
        tictoc->start( speed  );
    }else
        tictoc->stop();
}

void InfoDisplay::setSpeed( int speed )
{
    this->speed = speed;
    if(tictoc->isActive())
        tictoc->start( speed );
}

void InfoDisplay::timeToScroll()
{
    int x;

    //x = contentsX();
    x = sb->height();
    sb->scroll( 1 , 0 );

    if(x == sb->height())
        scroll( -1024, 0);

}


void InfoDisplay::infoMouseReleasedSlot() 
{
    editing = !editing;
    emit editingMode( editing );
    if(editing)
        infoUpdate("Click HERE again after you done editing");
}


AliasDisplay::AliasDisplay(QWidget * parent, const char * name)
    : QLineEdit( )
{
    QPalette cg;

    cg.setColor(QPalette::Text, Qt::cyan);
    cg.setColor(QPalette::Dark, Qt::black);
    cg.setColor(QPalette::Window, Qt::black);

    //setPalette( QPalette(cg, cg, cg) );

    memset(alias, 0, ALIASSIZE);
    setMaxLength( ALIASSIZE );
    setReadOnly( true );
    setFrame( false );
    setFocusPolicy( Qt::ClickFocus );
    connect( this, SIGNAL(returnPressed()),
             this, SLOT(returnPressedSlot()));
}


void AliasDisplay::aliasUpdate(const char *alias )
{
    strncpy_s( this->alias, alias, ALIASSIZE);
    setText(alias);
}

void AliasDisplay::mouseReleaseEvent ( QMouseEvent * e)
{
    QPalette cg;

    if(isReadOnly()){

        cg.setColor(QPalette::Text, Qt::yellow);
        cg.setColor(QPalette::Dark, Qt::darkGreen);
        cg.setColor(QPalette::Window, Qt::darkGreen);
        //setPalette( QPalette(cg, cg, cg) );
        repaint();

        setReadOnly( false );
    }else{
        returnPressedSlot();
    }
}


void AliasDisplay::returnPressedSlot()
{
    QString str;
    QPalette cg;

    setReadOnly( true );
    if(isModified()){
        strncpy_s(alias, (const char *)text().toLatin1(), ALIASSIZE);
        emit setAlias(alias);
    }

    cg.setColor(QPalette::Text, Qt::cyan);
    cg.setColor(QPalette::Dark, Qt::black);
    cg.setColor(QPalette::Window, Qt::black);

    //setPalette( QPalette(cg, cg, cg) );
    repaint();

    focusNextPrevChild( false );
}

