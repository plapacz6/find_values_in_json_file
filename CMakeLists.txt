cmake_minimum_required(VERSION 3.18)
project(app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(find_field_in_json_file,
    src/solution.cpp
    src/main.cpp    
)
include_directories(include)

enable_testing()

# does the application run
add_test(NAME Runs COMMAND ../build/find_field_in_json_file  -f file.json -c 6 -o field2occurrenceCount)

# does the usage message work?
add_test(NAME Usage COMMAND ../build/find_field_in_json_file)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Using:.*>"
  )

# does the application run
add_test(NAME Demonstration COMMAND ../test/test.sh)


