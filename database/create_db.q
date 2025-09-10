tradesdb:([] 
    time:`timestamp$();
    sym:`symbol$();
    price:`float$();
    quantity:`int$()
 )

`:database/tradesdb set tradesdb
show meta tradesdb
show "New trades database created at: database/tradesdb"
\\

