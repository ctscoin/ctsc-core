#!/bin/bash

CONFIGFOLDER='/root/.ctsc'
COIN_NAME='ctsc'
COIN_PATH='/usr/local/bin/'
COIN_DAEMON='ctscd'
COIN_CLI='ctsc-cli'

# color codes
RED='\033[0;91m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

##### Main #####
clear

echo -e "${RED}Stopping $COIN_DAEMON...${NC}"
systemctl stop ${COIN_NAME^^}.service
# $COIN_CLI stop

echo -e "${RED}Sleeping for 20 seconds...${NC}";
sleep 20

cd $CONFIGFOLDER

echo -e "${YELLOW}Clearing existing files...${NC}"
mv wallet{.dat,.keep}
mv $COIN_NAME{.conf,.keep}

rm -rf *.conf *.dat *.log blocks chainstate backups database sporks .lock -r

mv wallet{.keep,.dat}
mv $COIN_NAME{.keep,.conf}

ls -al

sleep 5

echo -e "${YELLOW}Starting $COIN_DAEMON...${NC}"
systemctl start ${COIN_NAME^^}.service
#$COIN_DAEMON -daemon -reindex

echo -e "${GREEN}${COIN_NAME^^} Masternode refreshed!${NC}"
