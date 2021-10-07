cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ENV{GITHUB_RUN_NUMBER})
    set(ENV{GITHUB_RUN_NUMBER} 1)
endif()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

project(ip_filter VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
include(conan.cmake)
conan_cmake_configure(REQUIRES boost/1.77.0
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})


add_library(helper_library helper_library.cpp)
add_executable(ip_filter ip_filter.cpp)

enable_testing()
add_subdirectory(tests)

set_target_properties(ip_filter helper_library PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE
    helper_library
)

if (MSVC)
    target_compile_options(helper_library PRIVAT-E
        /W4
    )
    target_compile_options(ip_filter PRIVAT-E
        /W4
    )
else ()
    target_compile_options(helper_library PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT max-in-3d@ngs.ru)

include(CPack)


