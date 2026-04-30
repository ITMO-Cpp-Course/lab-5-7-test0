add_library(resource_core STATIC
    src/documentBuilder.cpp
    src/document.cpp
    src/invertedIndex.cpp
)

target_link_libraries(resource_core PRIVATE project_warnings)

if (TARGET project_sanitizers)
    target_link_libraries(resource_core PRIVATE project_sanitizers)
endif ()

target_include_directories(resource_core
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)