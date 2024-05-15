#!/bin/sh

[ ! -d "./compile" ] && mkdir compile

if [ -f "*.stackdump" ]
then
    rm "*.stackdump"
fi

problem=$1
flag=$2
input=$3
copied=false
if [ "$flag" = "-a" ]
then
    if [ ! -f "./code/$problem.cpp" ]
    then
        echo "no such file to archive. give a valid file to archive."
        exit 1
    fi
    mv "./code/$problem.cpp" "./archive/$problem.cpp"
    exit
fi

if [ ! -f "./code/$problem.cpp" ]
then
    if [ ! -f "./archive/$problem.cpp" ]
    then
        echo "no such file to execute. give a valid file to execute.\n"
        exit 1
    fi
    cp "./archive/$problem.cpp" "./code/$problem.cpp"
    copied=true
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
else
    echo "program executing...\n"
    "./compile/$problem.exe"
fi

if [ "$copied" = true ]
then
    rm "./code/$problem.cpp"
fi