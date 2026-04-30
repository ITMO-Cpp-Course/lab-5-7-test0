add_library(resource_core STATIC
    src/document.cpp
    src/documentBuilder.cpp
    src/invertedIndex.cpp
)

target_compile_features(resource_core PUBLIC cxx_std_20)

target_include_directories(resource_core
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(resource_core PRIVATE project_warnings)

if (TARGET project_sanitizers)
    target_link_libraries(resource_core PRIVATE project_sanitizers)
endif()