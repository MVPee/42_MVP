#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

dir=$(find . -maxdepth 1 -type d | tail -n 1 | cut -c 3-)

echo -e "${RED}Project: $dir${NC}"

cc _bin_/file/*.c -o tester

if [ "$dir" == "pushswap" ]; then
    cd "pushswap"
    make
    cd ..
    ./tester "pushswap"
else
    echo -e "${YELLOW}No project detected...${NC}"
fi

rm tester