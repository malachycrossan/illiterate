#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Create results directory
mkdir -p test_results

# Function to compile and test C++ files
test_cpp_file() {
    local source_file=$1
    local base_name=$(basename "$source_file" .cpp)
    local dir_name=$(dirname "$source_file")
    
    # Create results subfolder for this source file
    local result_dir="test_results/${dir_name}"
    mkdir -p "$result_dir"
    
    echo -e "${YELLOW}Testing C++ file: $source_file${NC}"
    
    # Compile
    g++ -std=c++17 -Wall -o "${result_dir}/${base_name}" "$source_file" 2> "${result_dir}/${base_name}_compile.log"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Compilation failed for $source_file${NC}"
        cat "${result_dir}/${base_name}_compile.log"
        return 1
    fi
    
    echo -e "${GREEN}✓ Compilation successful${NC}"
    
    # Run tests
    run_tests "${result_dir}/${base_name}" "$dir_name" "$base_name" "$result_dir"
}

# Function to compile and test C files
test_c_file() {
    local source_file=$1
    local base_name=$(basename "$source_file" .c)
    local dir_name=$(dirname "$source_file")
    
    # Create results subfolder for this source file
    local result_dir="test_results/${dir_name}"
    mkdir -p "$result_dir"
    
    echo -e "${YELLOW}Testing C file: $source_file${NC}"
    
    # Compile
    gcc -std=c11 -Wall -o "${result_dir}/${base_name}" "$source_file" 2> "${result_dir}/${base_name}_compile.log"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Compilation failed for $source_file${NC}"
        cat "${result_dir}/${base_name}_compile.log"
        return 1
    fi
    
    echo -e "${GREEN}✓ Compilation successful${NC}"
    
    # Run tests
    run_tests "${result_dir}/${base_name}" "$dir_name" "$base_name" "$result_dir"
}

# Function to compile and test Java files
test_java_file() {
    local source_file=$1
    local base_name=$(basename "$source_file" .java)
    local dir_name=$(dirname "$source_file")
    
    # Create results subfolder for this source file
    local result_dir="test_results/${dir_name}"
    mkdir -p "$result_dir"
    
    echo -e "${YELLOW}Testing Java file: $source_file${NC}"
    
    # Compile
    javac "$source_file" -d "$result_dir" 2> "${result_dir}/${base_name}_compile.log"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Compilation failed for $source_file${NC}"
        cat "${result_dir}/${base_name}_compile.log"
        return 1
    fi
    
    echo -e "${GREEN}✓ Compilation successful${NC}"
    
    # Run tests (Java needs different execution)
    run_java_tests "$base_name" "$dir_name" "$result_dir"
}

# Function to run tests for compiled binaries (C/C++)
run_tests() {
    local executable=$1
    local dir_name=$2
    local base_name=$3
    local result_dir=$4
    
    # Look for test files in tests directory
    local test_dir="${dir_name}/tests"
    
    if [ ! -d "$test_dir" ]; then
        echo -e "${YELLOW}! No tests directory found at $test_dir${NC}"
        return 0
    fi
    
    # Find all input files
    local input_files=$(find "$test_dir" -name "${base_name}_*.in" -o -name "test_*.in" | sort)
    
    if [ -z "$input_files" ]; then
        echo -e "${YELLOW}! No test input files found${NC}"
        return 0
    fi
    
    # Run each test
    for input_file in $input_files; do
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        
        # Determine expected output file
        local test_name=$(basename "$input_file" .in)
        local expected_file="${test_dir}/${test_name}.out"
        
        if [ ! -f "$expected_file" ]; then
            echo -e "${RED}✗ Expected output file not found: $expected_file${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            continue
        fi
        
        echo "  Running test: $test_name"
        
        # Run the program with input
        timeout 5s "$executable" < "$input_file" > "${result_dir}/${base_name}_${test_name}_actual.out" 2> "${result_dir}/${base_name}_${test_name}_error.log"
        local exit_code=$?
        
        if [ $exit_code -eq 124 ]; then
            echo -e "${RED}  ✗ Test timed out (>5s)${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            continue
        fi
        
        if [ $exit_code -ne 0 ]; then
            echo -e "${RED}  ✗ Program crashed (exit code: $exit_code)${NC}"
            cat "${result_dir}/${base_name}_${test_name}_error.log"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            continue
        fi
        
        # Compare output
        if diff -w "$expected_file" "${result_dir}/${base_name}_${test_name}_actual.out" > "${result_dir}/${base_name}_${test_name}_diff.txt" 2>&1; then
            echo -e "${GREEN}  ✓ Test passed${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}  ✗ Test failed - output mismatch${NC}"
            echo "  Expected output:"
            head -5 "$expected_file"
            echo "  Actual output:"
            head -5 "${result_dir}/${base_name}_${test_name}_actual.out"
            echo "  Diff saved to: ${result_dir}/${base_name}_${test_name}_diff.txt"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    done
}

# Function to run tests for Java files
run_java_tests() {
    local base_name=$1
    local dir_name=$2
    local result_dir=$3
    
    # Look for test files in tests directory
    local test_dir="${dir_name}/tests"
    
    if [ ! -d "$test_dir" ]; then
        echo -e "${YELLOW}! No tests directory found at $test_dir${NC}"
        return 0
    fi
    
    # Find all input files
    local input_files=$(find "$test_dir" -name "${base_name}_*.in" -o -name "test_*.in" | sort)
    
    if [ -z "$input_files" ]; then
        echo -e "${YELLOW}! No test input files found${NC}"
        return 0
    fi
    
    # Run each test
    for input_file in $input_files; do
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        
        # Determine expected output file
        local test_name=$(basename "$input_file" .in)
        local expected_file="${test_dir}/${test_name}.out"
        
        if [ ! -f "$expected_file" ]; then
            echo -e "${RED}✗ Expected output file not found: $expected_file${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            continue
        fi
        
        echo "  Running test: $test_name"
        
        # Run the Java program with input
        timeout 5s java -cp "$result_dir" "$base_name" < "$input_file" > "${result_dir}/${base_name}_${test_name}_actual.out" 2> "${result_dir}/${base_name}_${test_name}_error.log"
        local exit_code=$?
        
        if [ $exit_code -eq 124 ]; then
            echo -e "${RED}  ✗ Test timed out (>5s)${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            continue
        fi
        
        if [ $exit_code -ne 0 ]; then
            echo -e "${RED}  ✗ Program crashed (exit code: $exit_code)${NC}"
            cat "${result_dir}/${base_name}_${test_name}_error.log"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            continue
        fi
        
        # Compare output
        if diff -w "$expected_file" "${result_dir}/${base_name}_${test_name}_actual.out" > "${result_dir}/${base_name}_${test_name}_diff.txt" 2>&1; then
            echo -e "${GREEN}  ✓ Test passed${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}  ✗ Test failed - output mismatch${NC}"
            echo "  Expected output:"
            head -5 "$expected_file"
            echo "  Actual output:"
            head -5 "${result_dir}/${base_name}_${test_name}_actual.out"
            echo "  Diff saved to: ${result_dir}/${base_name}_${test_name}_diff.txt"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    done
}

# Main execution
echo "========================================"
echo "Starting Automated Testing"
echo "========================================"

# Read modified files
if [ -f "filtered_files.txt" ]; then
    while IFS= read -r file; do
        if [ ! -f "$file" ]; then
            echo -e "${YELLOW}Skipping deleted file: $file${NC}"
            continue
        fi
        
        echo ""
        echo "----------------------------------------"
        
        # Determine file type and run appropriate test
        if [[ $file == *.cpp ]] || [[ $file == *.cc ]] || [[ $file == *.cxx ]]; then
            test_cpp_file "$file"
        elif [[ $file == *.c ]]; then
            test_c_file "$file"
        elif [[ $file == *.java ]]; then
            test_java_file "$file"
        fi
    done < filtered_files.txt
fi

# Print summary
echo ""
echo "========================================"
echo "Test Summary"
echo "========================================"
echo -e "Total tests:  $TOTAL_TESTS"
echo -e "${GREEN}Passed:       $PASSED_TESTS${NC}"
echo -e "${RED}Failed:       $FAILED_TESTS${NC}"
echo "========================================"

# Save summary to file
cat > test_results/summary.txt << EOF
Test Summary
============
Total tests:  $TOTAL_TESTS
Passed:       $PASSED_TESTS
Failed:       $FAILED_TESTS

Status: $([ $FAILED_TESTS -eq 0 ] && echo "SUCCESS" || echo "FAILURE")
EOF

# Exit with appropriate code
if [ $FAILED_TESTS -gt 0 ]; then
    exit 1
else
    exit 0
fi
