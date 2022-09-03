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

#ifndef PCRIO_H_
#define PCRIO_H_

//////////////////////////////////////////////////////////////////
// PcrIO is responsible for sending and receiving messages with
// PCR1000. Once recieve a message, it sends signal via Qt.
//////////////////////////////////////////////////////////////////

#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QDebug>

#define PCRIO_BUFFERSIZE 64

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class PcrIO : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString msg READ msg WRITE setMsg NOTIFY msgChanged);

signals:
    void dataToPcChanged( const QString& m_dataToPc, int len );
    void connected();
    void closed();
    void disconnected();
    void radioMessage( const char *mesg, int len );
    void messageSent();

public:
    explicit PcrIO( QSerialPort *serialPort, QObject *parent = nullptr );
    void pcToRadio( QString messageToRadio );
    //bool serialDeviceOpen( const char *device, QSerialPort::BaudRate baudrate );
    bool serialDeviceClose( );
    bool powerState( QString lastMsg );
    bool highPriority () const;
    bool Close();

    QString m_dataToPc;
    QString lastMessage;
    bool startUp = false;


    // INIT MESSAGES
    QString onMsg    = "H101";  //power on
    QString offMsg   = "H100";  //power off
    QString query    = "H1?";   //radio status
    QString diag     = "G300";  // set diagnostic mode (not fast mode)
    QString initBaud = "G103";  // 9600
    QString fastBaud = "G105";  // 38400

public slots:
    Q_INVOKABLE void write(const char* _messageToRadio, int msg);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    void displayMessage(QByteArray dataFromRadio);
    void radioToPc( QByteArray dataFromRadio, int len );
    void _init_();
    void startRadio();
    void stopRadio();

protected:
    bool isTokenComplete( const char* data, int len, int* first, int* tokenLen );


};


/*
//#include <unistd.h> //unix standards
//#include <time.h>
//#include <termios.h>  //unix io
//#include <sys/time.h>
//#include <sys/ioctl.h>
//#include <stdio.h>
//#include <errno.h>
//#include <fcntl.h>

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDateTime>    //modernize
#include <QString>      //  "
#include <QFile>        //  "

#define PCRIO_BUFFERSIZE 64

class PcrIO : public QObject
{
  Q_OBJECT

  QSerialPort* serialPort;

  QSerialPort::BaudRate baudrate = QSerialPort::Baud9600;

public:
  PcrIO( QObject *parent=0, const char *name=0 );
  ~PcrIO();
  
  bool highPriority () const;
  bool Open( const char *device, QSerialPort::BaudRate baudrate );
  bool Close();

public slots:
  void sendMessageSlot( const char *mesg, int len );

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

signals:
  void connected();
  void closed();
  void disconnected();
  void radioMessage( const char *mesg, int len );
  void messageSent();

protected:
  void timerEvent( QTimerEvent * );
  bool ReadWrite();
  bool IsTokenComplete( const char *data, int len, int *first, int *tokenlen );

private:
    QSerialPort *m_serialPort = nullptr;
  struct termios {
      int tio=0;
      int oldtio=0;
  }termios;

  int    fd;
  //fd_set rset, wset;
  //struct termios tio, oldtio;

  int  timerId;
  int  bytesToWrite;
  char bufferRead[PCRIO_BUFFERSIZE];
  char bufferWrite[PCRIO_BUFFERSIZE];
  char mesg[PCRIO_BUFFERSIZE];
  int  bufferReadLen;

#ifdef DEBUG_VER_
  time_t t;
#endif // DEBUG_VER_
};
*/
#endif // PCRIO_H_

