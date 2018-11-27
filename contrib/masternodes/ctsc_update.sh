#!/bin/bash

TMP_FOLDER=$(mktemp -d)
COIN_NAME='CTSC'
COIN_PATH='/usr/local/bin/'
COIN_DAEMON='ctscd'
COIN_CLI='ctsc-cli'
COIN_TGZ='https://github.com/ctscoin/ctsc-core/releases/download/v1.1.0/CTSC-v1.1.0-linux-x86_64.tar.gz'
COIN_ZIP=$(echo $COIN_TGZ | awk -F'/' '{print $NF}')


function download_node() {
  echo -e "Preparing to download updated $COIN_NAME binaries..."
  cd $TMP_FOLDER
  wget -q $COIN_TGZ
  tar xvzf $COIN_ZIP -C /usr/local/bin/ --strip=1
  compile_error
  chmod +x $COIN_PATH$COIN_DAEMON $COIN_PATH$COIN_CLI
  cd - >/dev/null 2>&1
  rm -r $TMP_FOLDER >/dev/null 2>&1
  clear
}

##### Main #####
clear

systemctl stop $COIN_NAME.service

download_node

systemctl start $COIN_NAME.service

echo -e "${GREEN}$COIN_NAME Masternode has been updated!${NC}"
