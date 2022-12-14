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

//#include <qregexp.h>
#include <QList>
#include <QFrame>
#include <QTimer>
#include <QListView>
#include <QListWidget> // code update
#include <QListWidgetItem> // code update
#include <QDateTime>
#include <QComboBox>
#include <QPushButton>
#include <QFile>
#include <QTextEdit>
//#include <QMultiLineEdit> // deprecated
#include <QHBoxLayout>
#include <QLineEdit> //code updates
#include <QPalette>  //code updates
#include <QTableWidget> //
#include <QTreeWidget>

#include "pcrproto.h"

QListWidget *mlistView;

class MonitorItem : public QListWidget
{
public:
  MonitorItem(QListWidget * parent);

  //QTreeWidget mlistView;

  // painting
  void paintCell( QPainter *, const QPalette::ColorGroup &, int, int, int);
  void paintFocus ( QPainter *, const QPalette::ColorGroup & , const QRect & );

  // channel info
  void getBookmark( struct bookmark_t * );
  void setBookmark( struct bookmark_t * );

  enum CmdType {Start, On, Off, Stop};

  // shell execute info
  void setCmd( CmdType, const QString & );
  QString getCmd( CmdType );
  void setCmdPID( CmdType, int);
  int  getCmdPID( CmdType );

  int getElapseTime();
  void setElapseTime(int);

private:
  int elapseTime;
  bookmark_t bm;
  int CmdStartPID;
  int CmdStopPID;
  int CmdOnPID;
  int CmdOffPID;
  QString CmdStart;
  QString CmdOn;
  QString CmdOff; 
  QString CmdStop;  
};

/*
class MonitorFile
{
public:
  MonitorFile();
  void Load(QListView *);
  void Save(QListView *);

private:
  QFile dataFile;

  void ReadEntry();
  void ReadCycle();
  void WriteCycle();
  void WriteEntry();
};

*/

class Preset
{
public:
 Preset( QString Alias, QString CmdStart, QString CmdOn, QString CmdOff, QString CmdStop, int e)
 { alias = Alias; on = CmdOn; off = CmdOff; start = CmdStart; stop = CmdStop; elapseTime = e; }

 QString Alias()    const { return alias; }
 QString CmdOn()    const { return on; } 
 QString CmdOff()   const { return off; }
 QString CmdStart() const { return start; }
 QString CmdStop()  const { return stop; }
 int ElapseTime()   const { return elapseTime; }
 //QTreeWidget *mlistView;

private:
 QString alias;
 QString on;
 QString off;
 QString start;
 QString stop;
 int elapseTime;
};

class MonitorDialog : public QFrame
{
 Q_OBJECT
public:
  MonitorDialog( QWidget * parent=0, const char * name=0);
  ~MonitorDialog();

  //QTreeWidget mlistView;

signals:
  // connect these to pcrproxy
  void gotoBookmark( struct bookmark_t * );
  void getBookmark( struct bookmark_t * );

public slots:
  // connect these to pcrproxy
  void sigStrengthUpdate( unsigned char );
  void squelchOnUpdate( bool );
  void toMonitorSlot( struct bookmark_t * );

private slots:
  void StartSlot();
  void StopSlot();
  void AddSlot();
  void DeleteSlot();
  void LoadSlot();
  void SaveSlot();
  void UpdateSlot();
  void OptionSlot( bool );
  void PresetSlot( const QString & );
  void AddPreset();
  void DelPreset();
  void ExecuteStop();

  void DoubleClickedSlot(QListWidgetItem *); // QListView
  void SelectionChangedSlot(QListWidgetItem *); // QListView
  void TimeToChangeChannel();
  void RecordTimeout();

private:
  QList<Preset>  presetList;
  struct bookmark_t bm;
  bool           squelchOn;
  bool           monitoring;
  int            timeStepMsec;
  QTimer         timeStep;
  QTimer         elapseTimer;
  MonitorItem    *currentItem;
  QListWidgetItem   *mlistWidget; // QListView
  QLineEdit      *cmdStartEdit;
  QLineEdit      *cmdOnEdit;
  QLineEdit      *cmdOffEdit;
  QLineEdit      *cmdStopEdit;
  QLineEdit      *elapseEdit;
  QLineEdit      *timeStepEdit;
  QPushButton    *startButton;
  QPushButton    *stopButton;
  QPushButton    *updateButton;
  QPushButton    *optionButton;
  QPushButton    *addButton;
  QPushButton    *deleteButton;
  QPushButton    *loadButton;
  QPushButton    *saveButton;
  QPushButton    *addPresetButton;
  QPushButton    *delPresetButton;
  QLineEdit      *console;
  QComboBox      *presetCombo;

  void ExecuteCmd( MonitorItem::CmdType, QString );
};
