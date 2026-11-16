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
    src/core/Permission.cpp
    src/core/Role.cpp
    src/core/Department.cpp
    src/core/User.cpp
    src/core/AccessController.cpp
    src/documents/Tag.cpp
    src/documents/Attachment.cpp
    src/documents/DocumentMetadata.cpp
    src/documents/DocumentVersion.cpp
    src/documents/Document.cpp
    src/documents/DocumentTemplate.cpp
    src/documents/ContractDocument.cpp
    src/documents/InvoiceDocument.cpp
    src/documents/OrderDocument.cpp
    src/documents/ReportDocument.cpp
    src/documents/MemoDocument.cpp
    src/workflow/ApprovalStep.cpp
    src/workflow/EscalationRule.cpp
    src/workflow/ApprovalRoute.cpp
    src/workflow/WorkflowState.cpp
    src/workflow/WorkflowManager.cpp
    src/signatures/CryptoHasher.cpp
    src/signatures/Certificate.cpp
    src/signatures/DigitalSignature.cpp
    src/signatures/OfficialStamp.cpp
    src/signatures/SignatureService.cpp
    src/storage/StorageLocation.cpp
    src/storage/Folder.cpp
    src/storage/ArchivePolicy.cpp
    src/storage/ArchiveRecord.cpp
    src/storage/DocumentRepository.cpp
    src/storage/BackupManager.cpp
    src/search/SearchFilter.cpp
    src/search/IndexEntry.cpp
    src/search/TagRegistry.cpp
    src/search/DocumentSorter.cpp
    src/search/SearchEngine.cpp
    src/notifications/NotificationChannel.cpp
    src/notifications/Notification.cpp
    src/notifications/Subscription.cpp
    src/notifications/Reminder.cpp
    src/notifications/NotificationService.cpp
    src/audit/AuditEntry.cpp
    src/audit/AuditLogger.cpp
    src/audit/ComplianceRule.cpp
    src/audit/SecurityIncident.cpp
    src/audit/ComplianceChecker.cpp
    src/analytics/WorkflowMetrics.cpp
    src/analytics/DepartmentStats.cpp
    src/analytics/SlaMonitor.cpp
    src/analytics/AnalyticsReporter.cpp
    src/analytics/DocumentFlowSystem.cpp
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
