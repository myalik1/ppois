cmake_minimum_required(VERSION 3.16)
project(DocumentWorkflowLab2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(DOMAIN_SOURCES
    src/exceptions/WorkflowExceptions.cpp
    src/core/IdentityAndAccess.cpp
    src/documents/DocumentCore.cpp
    src/documents/SpecializedDocuments.cpp
    src/workflow/WorkflowEngine.cpp
    src/signatures/DigitalSignatures.cpp
    src/storage/StorageAndArchive.cpp
    src/search/SearchAndIndexing.cpp
    src/notifications/NotificationSystem.cpp
    src/audit/AuditAndCompliance.cpp
    src/analytics/AnalyticsAndSystem.cpp
)

add_library(docflow_domain STATIC ${DOMAIN_SOURCES})

add_executable(docflow_cli
    src/main.cpp
    cli/ConsoleMenu.cpp
)
target_link_libraries(docflow_cli PRIVATE docflow_domain)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(docflow_tests
    tests/ExceptionsTest.cpp
    tests/IdentityAndAccessTest.cpp
    tests/DocumentCoreTest.cpp
    tests/SpecializedDocumentsTest.cpp
    tests/WorkflowEngineTest.cpp
    tests/DigitalSignaturesTest.cpp
    tests/StorageAndArchiveTest.cpp
    tests/SearchAndIndexingTest.cpp
    tests/NotificationSystemTest.cpp
    tests/AuditAndComplianceTest.cpp
    tests/AnalyticsAndSystemTest.cpp
)
target_link_libraries(docflow_tests PRIVATE docflow_domain GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(docflow_tests)
