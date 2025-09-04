import quickfix as fix
from fixmessagegen import MessageGenerator

class FIXClient(fix.Application):
    def __init__(self, clientID: int):
        super().__init__()

        self.clientID_ = clientID
        self.sessionID_ = None
        self.loggedOn = False

        self.orderCounter_ = 0
        self.msgGenerator = MessageGenerator()

    def onCreate(self, sessionID):
        self.sessionID_ = sessionID
        print(f"Client {self.clientID_}: Session created - {sessionID}")
        
    def onLogon(self, sessionID):
        print(f"Client {self.clientID_}: Logged on - {sessionID}")
        self.loggedOn = True
        
    def onLogout(self, sessionID):
        print(f"Client {self.clientID_}: Logged out - {sessionID}")
        self.loggedOn = False
        
    def toAdmin(self, message, sessionID):
        print(f"Client {self.clientID_}: Sending admin message - {message}")
        
    def toApp(self, message, sessionID):
        print(f"Client {self.clientID_}: Sending app message - {message}")

    def fromAdmin(self, message, sessionID):
        print(f"Client {self.clientID_}: Received admin message - {message}")
        
    def fromApp(self, message, sessionID):
        print(f"Client {self.clientID_}: Received app message - {message}")
    
    def sendNewSingleOrder(self) -> None:
        if not self.sessionID_:
            print(f"Client {self.clientID_}: No active session")
            return

        order = self.msgGenerator.generateNewOrderSingle(self.orderCounter_)

        try:
            fix.Session.sendToTarget(order, self.sessionID_)
            print(f"Client {self.clientID_}: Sent order #{self.orderCounter_}.")
        except fix.SessionNotFound:
            print(f"Client {self.clientID_}: Session not found.")

        self.orderCounter_ += 1