#include "quickfix/Application.h"

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
  }
};