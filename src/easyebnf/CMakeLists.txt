file (GLOB EASYEBNF_HEADERS "*.h")
file (GLOB EASYEBNF_CPPs "*.cpp")
message(STATUS "header files:" ${EASYEBNF_HEADERS})
message(STATUS "cpp files:" ${EASYEBNF_CPPs})

source_group("headers" FILES ${EASYEBNF_HEADERS})
source_group("sources" FILES ${EASYEBNF_CPPs})

include_directories (.)

add_library(EASYEBNF INTERFACE)
add_custom_target(EASYEBNF_header SOURCES ${EASYEBNF_HEADERS} ${EASYEBNF_CPPs})
target_include_directories(EASYEBNF INTERFACE  ".")

set_property(TARGET EASYEBNF_header PROPERTY FOLDER ${PRJECT_LIBRARIES_DIR})



install (TARGETS EASYEBNF
         PUBLIC_HEADER DESTINATION ${PROJECT_SOURCE_DIR}/_install/include
)
