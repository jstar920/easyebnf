file (GLOB TESTS_HEADERS "*.h")
file (GLOB TESTS_SOURCES "*.cpp")

message(STATUS "header files:" ${TESTS_HEADERS})
message(STATUS "source files:" ${TESTS_SOURCES})

source_group("headers" FILES ${TESTS_HEADERS})
source_group("sources" FILES ${TESTS_SOURCES})

include_directories (.)

#add_library(tests SHARED ${TESTS_HEADERS} ${TESTS_SOURCES})
add_executable(easyebnf_tests ${TESTS_HEADERS} ${TESTS_SOURCES})
target_link_libraries(easyebnf_tests PRIVATE easyebnf_static)
target_include_directories(easyebnf_tests PRIVATE ${CMAKE_SRC_ROOT_DIRECTORY}/easyebnf) 

set_property(TARGET easyebnf_tests PROPERTY FOLDER ${PRJECT_LIBRARIES_DIR}/test)

#set_target_properties(easyebnf PROPERTIES RUNTIME_OUTPUT_DIRECTORY %{PROJECT_BINARY_DIR}/bin)

