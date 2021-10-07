cmake_minimum_required(VERSION 3.10)
project(PackageTest CXX)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(split split-test.cpp)
add_executable(to_int to_int_test.cpp)
add_executable(comparator comparator_test.cpp)
add_executable(ip_comparator ip_comparator_test.cpp)
add_executable(reverse_sort reverse_sort_test.cpp)
add_executable(filters filter_test.cpp)

set_target_properties(split to_int comparator ip_comparator reverse_sort filters PROPERTIES
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(split PRIVATE "..")
target_include_directories(to_int PRIVATE "..")
target_include_directories(comparator PRIVATE "..")
target_include_directories(ip_comparator PRIVATE "..")
target_include_directories(reverse_sort PRIVATE "..")
target_include_directories(filters PRIVATE "..")

target_link_libraries(split
    ${Boost_LIBRARIES}
    helper_library
)
target_link_libraries(to_int
    ${Boost_LIBRARIES}
    helper_library
)
target_link_libraries(comparator
    ${Boost_LIBRARIES}
    helper_library
)
target_link_libraries(ip_comparator
    ${Boost_LIBRARIES}
    helper_library
)
target_link_libraries(reverse_sort
    ${Boost_LIBRARIES}
    helper_library
)
target_link_libraries(filters
    ${Boost_LIBRARIES}
    helper_library
)

add_test(split "${CMAKE_BINARY_DIR}/tests/split")
add_test(to_int "${CMAKE_BINARY_DIR}/tests/to_int")
add_test(comparator "${CMAKE_BINARY_DIR}/tests/comparator")
add_test(ip_comparator "${CMAKE_BINARY_DIR}/tests/ip_comparator")
add_test(reverse_sort "${CMAKE_BINARY_DIR}/tests/reverse_sort")
add_test(filters "${CMAKE_BINARY_DIR}/tests/filters")