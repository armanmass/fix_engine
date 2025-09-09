trades:([] 
    timestamp:`datetime$();
    symbol:`symbol$();
    price:`real$();
    quantity:`int$()
 )

`:database/tradesdb set trades
show meta trades
show "New trades database created at: database/tradesdb"
\\

