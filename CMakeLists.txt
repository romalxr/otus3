cmake_minimum_required(VERSION 3.2.2)

if (NOT "$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(allocator allocator.cpp)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cowwwboy@ya.ru)
include(CPack)