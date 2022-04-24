#!/bin/bash

EXEC_TYPE="UNKNOWN"

#Detect OS for appropriate compilation
case $OSTYPE in
        "linux-gnu")
            EXEC_TYPE="a.out"
            ;;
        "cygwin")
            EXEC_TYPE="a.out"
            ;;
        "msys")
            EXEC_TYPE="a.exe"
esac

#Compile source for appropriate OS
echo "Preparing to compile and link source..."
if g++ main.cpp algo.cpp -I../include
then
    echo "Executable created for $OSTYPE, preparing to execute..."
else    
    echo "Exectuable failed to create, exiting!!!"
    exit 1
fi

./$EXEC_TYPE