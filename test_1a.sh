#!/bin/bash

# Define required functions and variables
print_ok() {
    echo "Test passed"
}

print_ko() {
    echo "Test failed"
}

SHELL="./hsh"
OUTPUTFILE="checker_output_standalone"
LTRACE=`which ltrace`
LTRACEOUTPUTFILE="checker_ltrace_output_standalone"
SLEEP=`which sleep`
SLEEPSECONDS=1

# Test description
echo "Testing if getline function was used by using ltrace"

# Test: check if the getline function was used by using ltrace
command="/bin/ls
/bin/ls
/bin/ls"

# Remove temporary file (if it exists)
rm -f $tmp_file

# Send commands
echo "Starting test..."
echo "$command" | $LTRACE -bc -o $LTRACEOUTPUTFILE $SHELL > $OUTPUTFILE 2> /dev/null &
echo "Contents of LTRACEOUTPUTFILE:"
cat $LTRACEOUTPUTFILE

# Wait a little bit
$SLEEP $SLEEPSECONDS

# Check the result
nmatch=`cat $LTRACEOUTPUTFILE | grep getline | wc -l`
if [ $nmatch -eq 1 ]; then
    print_ko
else
    print_ok
fi

# Clean up
echo "Test finished, cleaning up..."
rm -f $tmp_file
rm -f $OUTPUTFILE
rm -f $LTRACEOUTPUTFILE