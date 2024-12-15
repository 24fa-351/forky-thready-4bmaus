
#!/bin/bash

# Clear the results.txt file if it exists
> results.txt

# Array of test cases (min, max, pattern)
declare -a tests=(
    "1 10 1"
    "1 10 2"
    "10 50 1"
    "10 50 2"
    "20 30 1"
    "20 30 2"
    "50 100 1"
    "50 100 2"
    "100 110 1"
    "100 110 2"
    "200 210 1"
    "200 210 2"
    "1 256 1"  # Test large number of processes (max range)
    "1 256 2"  # Test large number of processes (max range, sequential)
)

# Loop through the test cases
for test in "${tests[@]}"
do
  # Echo the command being run to results.txt
  echo "command line: ./main $test" >> results.txt
  
  # Run the program with the test case and append output to results.txt
  ./main $test >> results.txt
  
  # Add a blank line for readability
  echo "" >> results.txt
done

# Display the results
cat results.txt
