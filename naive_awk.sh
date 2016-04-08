#!/bin/bash

SIZE=$1

awk '{s[$2]+=$1}END{for(i in s){print s[i],i}}' | sort -n | tail -$SIZE
