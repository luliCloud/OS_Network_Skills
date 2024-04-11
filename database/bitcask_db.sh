#!/bin/bash
db_set() {
    echo "$1,$2" >> database
}

db_get () {
    grep "^$1," database | sed -e "s/^$1,//" | tail -n 1
}

# using db_set and db_get funciton
db_set 123456 '{"name":"London","attractions":["Big Ben","London Eye"]}'

db_set 42 '{"name":"San Francisco","attractions":["Golden Gate Bridge"]}'

db_get 42

# use instruction: 
# $ chmod +x bitcask_db.sh // a file named database will apear
# $ source bitcask_db.sh
# $ db_set 35 '{"name":"San Jose","attractions":["Nvidia","Roku"]}' // write this key-value to database
# $ db_get 35
# '{"name":"San Jose","attractions":["Nvidia","Roku"]}'