#!/bin/sh

EXEC=./ScalarConverter

while IFS= read -r line || [ -n "$line" ]; do
    echo "===== INPUT: \"$line\" ====="
    $EXEC "$line"
    echo ""
done < tests.txt