#!/bin/bash
# script to backup the directory /home/lu/data. if data is a dir, backup the whole dir

# back up and compression the data dir, save to backup/data_date, ensuring not
# cover prev date data
# tar is the unix system command for packup and back up comamnd
# -c: create a new backup file; -z: gzip compression; -f: followed by back doc name (path)
tar -czf /home/lu/backup/data_$(date +%Y%m%d).tar.gz /home/lu/data

# following is the command line to set up routine execution of this shell script
# chmod -x backup.sh
# crontab -e  //open crontab file 
# 0 0 * * * /home/lu/greenpear/OSlearn/backup.sh  // noting not the back data but this script
# // 0 0 represwent execute at 0min 0h.
# // * * * represent execute at every day of a month (1-31), every month of a year 
# // and every day of a week (1-7)

# verifying we set up crontab task successfully
# crontab -l  // list all your crontab work
# grep CRON /var/log/syslog  // check the system sys log to see if the cron job is
# being executed.  (this step might vary depending on your system's configuration)

# case
# 42 22 * * * /home/lu/greenpear/OSlearn/backup.sh
# grep CRON /var/log/syslog
#Apr 30 22:41:01 lu-t3610 CRON[27661]: (lu) CMD (/home/lu/greenpear/OSlearn/backup.sh)
#Apr 30 22:41:01 lu-t3610 CRON[27660]: (CRON) info (No MTA installed, discarding output)
# means already execute the cron task but MTA has not been established. so we cannot see log message.