#!/bin/sh
# this gives you a primitive interactive client for slopchat

NICK="x64x2"
ADDRESS="170.100.431.12"
IFS=""

while true; do 
  clear
  clear
  
#  ./slopchat $ADDRESS # retrieve messages
  ./slopchat $ADDRESS | grep --color -E "^| $NICK " # this adds color

  echo "------------------"

  echo -n "message (empty to refresh): "
  read MESSAGE

  if test -n "$MESSAGE"; then
    ./slopchat "$ADDRESS" "$NICK" "$MESSAGE" # send message
  fi
done

