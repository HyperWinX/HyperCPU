#!/bin/bash

# Setup variables
HEADER="src/version.hpp"
STR=$(cat $HEADER)
LEN=${#STR}

# Split version using custom delimiter
IFS='.' read -r VMAJOR VMINOR VPATCH <<< $(echo $STR | awk '{print $6}' | cut -b 2-$((LEN - 41)) -)

# Increment minor version, resetting patch
VMINOR=$((VMINOR + 1))
VPATCH=0

# Build string and write it back
STR="static constexpr char HCPU_VERSION[] = \"$VMAJOR.$VMINOR.$VPATCH\";"
echo "$STR" > "$HEADER"

# Update version in README
sed -i 's/    <img src="https:\/\/img.shields.io\/badge\/version-[^"]*"/    <img src="https:\/\/img.shields.io\/badge\/version-'"$VMAJOR.$VMINOR.$VPATCH"'-red"/' README.md
