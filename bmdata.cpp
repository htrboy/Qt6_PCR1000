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

#include "bmdata.h"
#include <QInputDialog>
#include <QPainter>

//#include <qinputdialog.h>

///////////////////////////////////////////////////////
////////  CLASS BookmarkItem                 //////////
///////////////////////////////////////////////////////


/////////////////////////////////////
////   Constructor sets          ////
/////////////////////////////////////
BookmarkItem::BookmarkItem (QListWidget *parent)
  : QListWidget( parent )
{  SetDefault(); }

BookmarkItem::BookmarkItem (QListWidget *parent, QListWidgetItem *after)
  : QListWidget( parent )
{  SetDefault(); }

//BookmarkItem::BookmarkItem (QListViewItem *parent)
//  : QListViewItem( parent )
//{  SetDefault(); }

//BookmarkItem::BookmarkItem (QListViewItem *parent, BookmarkItem *after)
//  : QListViewItem( parent, after )
//{  SetDefault(); }


////////////////////////////////////////////
/// Return true if the item is  a folder ///
////////////////////////////////////////////
bool BookmarkItem::isFolderBegin(){ return folderBegin; }



////////////////////////////////////////////
/// Set folder flag        /////////////////
////////////////////////////////////////////
void BookmarkItem::setIsFolderBegin( bool flag ){ folderBegin = flag;}



/////////////////////////////////////////////
/////  Set variables to default values   ////
/////////////////////////////////////////////
void BookmarkItem::SetDefault(){
    memset(&bm, 0, sizeof(bm));
  //bzero(&bm, sizeof(bm));
  bm.freq    = DEFAULT_FREQ;
  bm.mode    = DEFAULT_MODE;
  bm.filter  = DEFAULT_FILTER;
  bm.ifshift = DEFAULT_IFSHIFT;
  bm.vol     = 0;
  bm.squelch = 0;
  bm.ATT     = 0;
  bm.AGC     = 0;
  bm.NB      = 0;
  bm.VSC     = 0;
  bm.AFC     = 0;
  bm.alias[0]   = '\0';
  bm.info[0]    = '\0';
  folderBegin   = false;
}



///////////////////////////////////////////////
////  Set channel data (e.g. freq, mode)    ///
////  If "flag" is true, it also update     ///
////  column that is displayed on QListView ///
///////////////////////////////////////////////
void BookmarkItem::setBookmark( struct bookmark_t *src, bool flag)
{
  memcpy(&bm,src,sizeof(struct bookmark_t));
  if(flag)
    fillColumnText();
}



//////////////////////////////////////////////
/// Return current channel data stored  //////
//////////////////////////////////////////////
void BookmarkItem::getBookmark(struct bookmark_t *dst)
{
  memcpy(dst, &bm,sizeof(struct bookmark_t));
}



////////////////////////////////////
////  Fill in appropriate column ///
////  to be displayed            ///
////////////////////////////////////
void BookmarkItem::fillColumnText()
{
  QString freqstr;

  // frequency (1st col)
  freqstr.setNum(bm.freq);

  insertItem(0,freqstr);
  
  // mode (2nd col)
  switch(bm.mode){
  case MODE_NFM: freqstr = "NFM"; break;
  case MODE_WFM: freqstr = "WFM"; break;
  case MODE_USB: freqstr = "USB"; break;
  case MODE_LSB: freqstr = "LSB"; break;
  case MODE_AM:  freqstr = "AM" ; break;
  default: freqstr = "ERROR";
  }
  insertItem(1, freqstr);

  // alias (3rd col)
  insertItem(2, bm.alias);
}


////////////////////////////////////////
///// Overwrite paint focus. No paint //
////////////////////////////////////////
void BookmarkItem::paintFocus ( QPainter *, const QPalette & cg, const QRect & r )
{
}



/////////////////////////
// Sorting            ///
/////////////////////////
QString BookmarkItem::key ( int col, bool ) const
{
  if( col == 0 )
      return item(0); //->toString();
    //return item(0)->rightJustify(10, '0');
  else
    return item(col);
}




////////////////////////////////////////
///// Overwrite paint subroutine     ///
///// to us more flexibily to adjust ///
///// color and style                ///
////////////////////////////////////////
void BookmarkItem::paintCell ( QPainter * p, const QPalette & cg,
			       int column, int width, int align )
{
  QPalette _cg(cg);
  bool isFolder = false;
  QString str = bm.alias;

  // check if it is a folder
  if(isFolderBegin()){
     isFolder = true;
     
     // keep left
     align = Qt::AlignLeft;
  }

  if(p->isActive() && !isFolder){
     _cg.setColor (QPalette::HighlightedText, Qt::red );
     _cg.setColor (QPalette::Text, Qt::red );
     _cg.setColor (QPalette::Highlight, Qt::green);
     _cg.setColor (QPalette::Window, Qt::green);
  }

  paintCell (p, _cg, column, width, align);
}



////////////////////////////////////////////////////////////////////
///////////        CLASS BookmarkData                       ////////
////////////////////////////////////////////////////////////////////


////////////////////////////
//// Constructor         ///
////////////////////////////
BookmarkData::BookmarkData()
{
  // set filename to null
  dataFile.rename( QString() );
}


///////////////////////////////////////////
/////  Load database from file         ////
///////////////////////////////////////////
bool BookmarkData::Load(QListView *bmList)
{
  QString fname;

  this->bmList = bmList;

  // open file dialog and set filename
  fname = QFileDialog::getOpenFileName();
  if(fname.isEmpty()) return false;
  dataFile.rename( fname );

  // open file
  if(!dataFile.open(QIODevice::ReadOnly))
    return false;

  // fill data
  while( !dataFile.atEnd() ){
     if(!ReadCycle(0, 1)){
        dataFile.close();
        return false;
     }
  }

  dataFile.close();
  return false;
}



////////////////////////////////////
////  Read each channel from file //
////////////////////////////////////
bool BookmarkData::ReadCycle( BookmarkItem *parent, int childCount){

  bookmark_t data;
  BookmarkItem *bmItem;
  QString str;
  int i;

  for(i = 0; i < childCount; i++){
     if(!ReadEntry( &data )) 
        return false;
    
     if( parent ) 
        bmItem = new BookmarkItem( parent );
     else
        bmItem = new BookmarkItem( bmList );

     // if beginning new folder then recursive deeper
     str = data.alias;
     if(str.contains("FOLDER BEGIN:")){

        bmItem->setBookmark( &data, false );
        bmItem->setText(0, str.remove(0,13));
        bmItem->setIsFolderBegin( true );

        if(!ReadCycle( bmItem, data.freq ))
           return false;
     }else
        bmItem->setBookmark( &data, true );
  }

  return true;
}



/////////////////////////////////////////////
/////       Save database to file        ////
/////////////////////////////////////////////
bool BookmarkData::Save(QListView *bmList){
  QString fname;

  this->bmList = bmList;

  fname = QFileDialog::getSaveFileName();

  if(fname.isEmpty()) return false;
  dataFile.rename( fname );
  

  if(!dataFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
      return false;
  }

  if(WriteCycle()){

    dataFile.flush();
    dataFile.close();
    
    return true;
  }else{
    dataFile.close();
    return false;
  }
}



////////////////////////////////////
//// Proxy subroutine to read //////
//// an entry from file       //////
////////////////////////////////////
bool BookmarkData::ReadEntry(struct bookmark_t *data)
{
  char buf[1024];
  char *ptr;
  char numbuf[64];
  QString str;
  int i;

  memset(buf, 0, 1024);
  //bzero(buf,1024); // deprecated

  i = dataFile.readLine( buf, 1024 );

  // strip new line
  for( i--; i >= 0; i--)
    if( buf[i]=='\r' || buf[i]=='\n')
       buf[i] = 0;
    else
       break; 
    
  str = buf;
  ptr = buf;

  // alias
  i = str.indexOf(",",0);
  if(i < 0) return false;
  buf[i] = '\0';
  strncpy_s(data->alias,ptr,ALIASSIZE);
  ptr = buf+i+1;

  // freq
  i = str.indexOf(",",i+1);
  if(i < 0) return false;
  buf[i] = '\0';
  strncpy_s(numbuf,ptr,64);
  ptr = buf+i+1;
  data->freq = QString(numbuf).toULong();

  // ts
  i = str.indexOf(",",i+1);
  if(i < 0) return false;
  buf[i] = '\0';
  strncpy_s(numbuf,ptr,64);
  ptr = buf+i+1;
  data->ts = QString(numbuf).toULong();

  // the rest of numbers
#define PARSE_INT(val) i = str.indexOf(",",i+1);  \
                       if(i < 0) return false; \
                       buf[i] = '\0';          \
                       strncpy_s(numbuf,ptr,64); \
                       ptr = buf+i+1;          \
                       val = QString(numbuf).toUShort() 
  
  PARSE_INT(data->mode);
  PARSE_INT(data->filter);
  PARSE_INT(data->vol);
  PARSE_INT(data->squelch);
  PARSE_INT(data->ifshift);
  PARSE_INT(data->ATT);
  PARSE_INT(data->AGC);
  PARSE_INT(data->NB);
  PARSE_INT(data->VSC);
  PARSE_INT(data->AFC);
  PARSE_INT(data->CTCSS);
  PARSE_INT(data->scope);
  
  // info
  buf[str.length()] = '\0';
  strncpy_s(data->info, ptr, INFOSIZE);
  
  str = data->info;

  // replace \r with CR(13)
  str.replace("\\\\r", "\r");

  // replace \n with LF(10)
  str.replace("\\\\n", "\n");

  strncpy_s(data->info, str.toUtf8(), INFOSIZE);

#ifdef  DEBUG_VER_
  fprintf(stderr,"%s,"
	  "%lu,%lu,%d,%d,"
	  "%s\n",
	  data->alias,
	  data->freq,data->ts,data->vol,data->scope,
	  data->info);
#endif // DEBUG_VER_

  return true;
}


////////////////////////////////////
//// Proxy subroutine to write /////
//// an entry into fil         /////
////////////////////////////////////
bool BookmarkData::WriteEntry(struct bookmark_t *data)
{
  QString alias;
  QString info;
  QString buf;
  // field separated by comma and record is end-of-line
    
  ///////////////
  /// alias  ////
  ///////////////
  alias = data->alias;

  // strip whitespace
  alias.simplified();

  // strip comma from alias
  alias.replace(",", " ");

  ///////////////
  /// info    ///
  ///////////////
  info = data->info;

  // replace CR(13) with \r
  info.replace("\r","\\r");

  // replace LF(10) with \n
  info.replace("\n","\\n");

  buf.asprintf(
	  ","      // alias
	  "%lu,"   // freq
	  "%lu,"   // ts
	  "%d,"    // mode
	  "%d,"    // filter
	  "%d,"    // vol
	  "%d,"    // squelch
	  "%d,"    // ifshift
	  "%d,"    // ATT
	  "%d,"    // AGC
	  "%d,"    // NB
	  "%d,"    // VSC
	  "%d,"    // AFC
	  "%d,"    // CTCSS
	  "%d,",   // scope
	  data->freq,
	  data->ts,
	  data->mode,
	  data->filter,
	  data->vol,
	  data->squelch,
	  data->ifshift,
	  data->ATT,
	  data->AGC,
	  data->NB,
	  data->VSC,
	  data->AFC,
	  data->CTCSS,
	  data->scope);
  buf.append(info);
  buf.append("\r\n");
  buf.prepend(alias);

  dataFile.write(buf.toUtf8(),buf.length());

  return true;
}



////////////////////////////////////
//// Write each channel to file  ///
////////////////////////////////////
bool BookmarkData::WriteCycle()
{
  BookmarkItem *bm;
  bookmark_t data;
  QListWidget it ( bmList );
  //QListViewItemIterator it ( bmList );
    int h=it.count();
  // iterate through all items in the list
  //for( int i=0 ; it.item(i); ++i){
    for (int i=0; i<h; ++i) {
        it.item(i);

        bm = (BookmarkItem *)it.currentItem();

        bm->getBookmark( &data );
     
        // add number of child in case of folder
        if(bm->isFolderBegin()){
            data.freq = bm->count();
        }

        WriteEntry( &data );

    }

  return true;
}
