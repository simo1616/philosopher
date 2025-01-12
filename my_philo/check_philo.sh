#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m'

# Counter for tests
TOTAL_TESTS=0
PASSED_TESTS=0

# Function to print test result
print_result() {
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[OK]${NC} $2"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}[KO]${NC} $2"
    fi
}

# Function to check program output
check_output() {
    local output=$1
    local expected=$2
    if [[ "$output" == *"$expected"* ]]; then
        return 0
    fi
    return 1
}

echo -e "${BLUE}Starting Philosophers Checker...${NC}\n"

# Check if program compiles
echo -e "${YELLOW}Checking compilation...${NC}"
make re > /dev/null 2>&1
print_result $? "Program compilation"

# Arguments format test
echo -e "\n${YELLOW}Running argument format tests...${NC}"

# Test with insufficient arguments
output=$(./philo 5 2>&1)
check_output "$output" "Usage: ./philo [# Philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([nb_eat])"
print_result $? "Correct usage message for insufficient arguments"

# Test with invalid number of philosophers
output=$(./philo 0 800 200 200 2>&1)
check_output "$output" "Usage: ./philo [# Philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([nb_eat])"
print_result $? "Invalid number of philosophers"

# Test with negative time
output=$(./philo 4 -400 200 200 2>&1)
check_output "$output" "Usage: ./philo [# Philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([nb_eat])"
print_result $? "Negative time value"

# Basic execution tests
echo -e "\n${YELLOW}Running basic execution tests...${NC}"

# Test with valid arguments
timeout 2 ./philo 4 800 200 200 > /dev/null 2>&1
print_result $? "Valid execution with 4 philosophers"

# Test with valid arguments and number of meals
timeout 2 ./philo 4 800 200 200 5 > /dev/null 2>&1
print_result $? "Valid execution with specified meals"

# Memory test
echo -e "\n${YELLOW}Running memory test...${NC}"

if command -v valgrind &> /dev/null; then
    timeout 5 valgrind --leak-check=full --error-exitcode=1 \
    ./philo 4 800 200 200 5 >/dev/null 2>&1
    print_result $? "Memory leak check"
else
    echo "Valgrind not installed - skipping memory leak test"
fi

# Death timing test
echo -e "\n${YELLOW}Running death timing test...${NC}"

output=$(timeout 1 ./philo 1 800 200 200 2>&1)
if [[ "$output" == *"has taken a fork"* ]]; then
    print_result 0 "Single philosopher test"
else
    print_result 1 "Single philosopher test"
fi

# Final results
echo -e "\n${BLUE}Test Results:${NC}"
echo -e "Total tests: $TOTAL_TESTS"
echo -e "Passed tests: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed tests: ${RED}$((TOTAL_TESTS - PASSED_TESTS))${NC}"

if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
    echo -e "\n${GREEN}All tests passed! 🎉${NC}"
else
    echo -e "\n${RED}Some tests failed! 😕${NC}"
fi