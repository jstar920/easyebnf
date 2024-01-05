file (GLOB EASYEBNF_HEADERS "*.h")
message(STATUS "header files:" ${EASYEBNF_HEADERS})

source_group("headers" FILES ${EASYEBNF_HEADERS})

include_directories (.)

add_library(EASYEBNF INTERFACE)
add_custom_target(EASYEBNF_header SOURCES ${EASYEBNF_HEADERS})
target_include_directories(EASYEBNF INTERFACE  ".")

set_property(TARGET EASYEBNF_header PROPERTY FOLDER ${PRJECT_LIBRARIES_DIR})



install (TARGETS EASYEBNF
         PUBLIC_HEADER DESTINATION ${PROJECT_SOURCE_DIR}/_install/include
)
