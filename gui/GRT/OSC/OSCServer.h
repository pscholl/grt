#ifndef OSCSERVER_H
#define OSCSERVER_H

#include <QObject>
#include <QDebug>

#define BOOST_THREAD_USE_LIB

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#if _MSC_VER >= 1600
    #include "OSCMessage.h"
#else
    #include "OSC/OSCMessage.h"
#endif
#include <queue>

#define STRING_TO_QSTRING(x) QString(x)

class OSCServer : public osc::OscPacketListener {

public:
    OSCServer(unsigned int listenerPort=5000,bool verbose=true);
    virtual ~OSCServer();

    bool start();

    bool stop();

    bool addMessaage( const OSCMessagePtr msg );

    bool getServerRunning();

    bool getNewMessagesReceived();

    unsigned int getNumMessages();

    OSCMessagePtr getNextMessage();

    bool setVerbose(bool verbose);
    bool setIncomingDataPort(unsigned int listenerPort);

protected:
    void mainThread();
    virtual void ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName &remoteEndpoint );
    bool clearMessages();

    bool serverRunning;
    bool verbose;
    unsigned int listenerPort;
    boost::mutex mutex;
    boost::thread *serverThread;
    UdpListeningReceiveSocket *oscSocket;
    std::queue< OSCMessagePtr > messages;

};

#endif // OSCSERVER_H
