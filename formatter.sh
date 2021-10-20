#!/bin/bash

if [ -p /dev/stdin ]; then
    cat - | awk '
            func center_align(s) {
                return sprintf("%-9s", s)
            }

            {
                if (NR==1){
                    word = center_align("");
                    bar  = center_align("|");
                    pos  = center_align("START");
                }
                if (NR!=1){
                    word = word center_align($1);
                    bar  = bar  center_align("|");
                    pos  = pos  center_align($2);
                }
                print word;
                print bar;
                print pos;
                print "";
            }'
fi
