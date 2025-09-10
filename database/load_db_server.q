\p 9788
\p

save_trades:{
    if[(`tradesdb in tables `.) and (count tradesdb) > 0;
        `:database/tradesdb set tradesdb;
        show "tradesdb saved at ", .z.p
    ];
 }

.z.ts: save_trades
\t 60000

\l database/tradesdb
show "Trades database loaded."
tradesdb
