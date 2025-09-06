import quickfix as fix
from FixMessageGen import MessageGenerator
import threading

gOrderCounter = 0
gOrderCounterLock = threading.Lock()

class FIXClient(fix.Application):
    def __init__(self, clientID: int):
        super().__init__()

        self.clientID_ = clientID
        self.sessionID_ = None
        self.loggedOn = False

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
        print(f"Client {self.clientID_}: Sending admin message")
        print(f"Message: {message}")
        
    def toApp(self, message, sessionID):
        print(f"Client {self.clientID_}: Sending app message")
        print(f"Message: {message}")

    def fromAdmin(self, message, sessionID):
        print(f"Client {self.clientID_}: Received admin message")
        print(f"Message: {message}")
        
    def fromApp(self, message, sessionID):
        print(f"Client {self.clientID_}: Received app message")
        print(f"Message: {message}")
    
    def sendNewSingleOrder(self) -> None:
        global gOrderCounter

        if not self.sessionID_:
            print(f"Client {self.clientID_}: No active session")
            return

        with gOrderCounterLock:
            currOrderID = gOrderCounter
            gOrderCounter += 1

        order = self.msgGenerator.generateNewOrderSingle(currOrderID)

        try:
            fix.Session.sendToTarget(order, self.sessionID_)
            print(f"Client {self.clientID_}: Sent order #{currOrderID}.")
        except fix.SessionNotFound:
            print(f"Client {self.clientID_}: Session not found.")
