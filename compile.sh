#!/bin/sh

[ ! -d "./compile" ] && mkdir compile

problem=$1
flag=$2
input=$3
if [ ! -f "./code/$problem.cpp" ]
then
    echo "no such file. give a valid file\n"
    exit 1
fi

if [ "$flag" = "-c" ] 
then
    g++ "./code/$problem.cpp" -o "./compile/$problem.exe" -O2 -Wall -lm -static -std=gnu++17 -DONLINE_JUDGE -DBO  
fi

if [ ! -f "./compile/$problem.exe" ]
then
    echo "code not compiled. first compile your code\n"
    exit 1
fi

if [ "$input" = "-i" ]
then
    if [ ! -f "./input/$problem.txt" ]
    then
        echo "no input file. make a valid input file\n"
        exit 1
    fi
    echo "compile done. program executing...\n"
    "./compile/$problem.exe" < "./input/$problem.txt"
    exit
fi

echo "program executing...\n"
"./compile/$problem.exe"
