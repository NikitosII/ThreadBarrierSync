#!/bin/bash

SOURCE_FILE="ThreadBarrierSync.c"
EXECUTABLE="ThreadBarrierSync"

gcc -o $EXECUTABLE $SOURCE_FILE -pthread

if [ $? -ne 0 ]; then
    echo "Ошибка компиляции."
    exit 1
fi

./$EXECUTABLE
