import random
import datetime

import quickfix as fix
import quickfix50sp2 as fix50


class MessageGenerator:
    """Artificial message generation"""
    
    def __init__(self):
        self.symbols_     = ["AAPL", "MSFT", "GOOGL", "AMZN", "TSLA", "NVDA", "META", "NFLX"]
        self.sides_       = [fix.Side_BUY, fix.Side_SELL]
        self.orderTypes_  = [fix.OrdType_MARKET, fix.OrdType_LIMIT, fix.OrdType_STOP]
        self.timeInForce_ = [fix.TimeInForce_DAY, fix.TimeInForce_GOOD_TILL_CANCEL, fix.TimeInForce_IMMEDIATE_OR_CANCEL]
        
    def randomPrice(self) -> float:
        return round(random.uniform(100.0, 200.0), 2)
        
    def randomQuantity(self) -> int:
        return random.randint(100, 500)

    def randomSymbol(self) -> str:
        return random.choice(self.symbols_)

    def randomSide(self) -> fix.Side:
        return random.choice(self.sides_)
        
    def randomOrderType(self) -> fix.OrdType:
        return random.choice(self.orderTypes_)
        
    def randomTimeInForce(self) -> fix.TimeInForce:
        return random.choice(self.timeInForce_)
    
    def generateNewOrderSingle(self, clientOrderID: int) -> fix50.NewOrderSingle:
        ordType = self.randomOrderType()

        order = fix50.NewOrderSingle()

        order.setField(fix.ClOrdID(str(clientOrderID)))
        order.setField(fix.HandlInst(fix.HandlInst_AUTOMATED_EXECUTION_ORDER_PRIVATE_NO_BROKER_INTERVENTION))
        order.setField(fix.Symbol(self.randomSymbol()))
        order.setField(fix.Side(self.randomSide()))
        order.setField(fix.TransactTime())
        order.setField(fix.OrdType(ordType))

        order.setField(fix.OrderQty(self.randomQuantity()))
        order.setField(fix.TimeInForce(self.randomTimeInForce()))

        if ordType in [fix.OrdType_LIMIT, fix.OrdType_STOP]:
            order.setField(fix.Price(self.randomPrice()))

        return order