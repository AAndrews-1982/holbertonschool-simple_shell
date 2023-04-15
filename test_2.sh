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
SLEEP=`which sleep`
SLEEPSECONDS=1

# Test: run /bin/ls many times, with a lot of spaces everywhere
command="/bin/ls
     /bin/ls
/bin/ls     
  /bin/ls     "
tmp_file="checker_tmp_file_$RANDOM"

# Remove temporary file (if it exists)
rm -f $tmp_file

# Create a pseudo random file
touch $tmp_file

# Send commands
echo "$command" | $SHELL > $OUTPUTFILE 2> /dev/null &

# Wait a little bit
$SLEEP $SLEEPSECONDS

# Check the result
nmatch=`cat $OUTPUTFILE | grep -c "$tmp_file"`
if [ $nmatch -eq 4 ]; then
    print_ok
else
    print_ko
fi

# Clean up
rm -f $tmp_file
rm -f $OUTPUTFILE