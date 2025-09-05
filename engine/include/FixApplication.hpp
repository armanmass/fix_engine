#include "quickfix/Application.h"
#include "quickfix/Message.h"
#include "quickfix/Session.h"
#include <iostream>

using namespace FIX;

class FixApplication : public Application
{
  void onCreate(const SessionID& sessionID) override
  {
  }

  void onLogon(const SessionID& sessionID) override
  {
  }

  void onLogout(const SessionID& sessionID) override
  {
  }

  void toAdmin(Message&  message, const SessionID& sessionID) override
  {
  }

  void toApp(Message& message, const SessionID& sessionID) override
  {
  }

  virtual void fromAdmin(const Message &, const SessionID &) override
  {
  }
  
  void fromApp(const Message& message, const SessionID& sessionID) override
  {
    const std::string& senderCompID = sessionID.getSenderCompID().getValue();
    std::cout << "Received message from client: " << senderCompID << std::endl;
    std::cout << "Message: " << message.toString() << std::endl;
  }
};
