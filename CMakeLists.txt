cmake_minimum_required(VERSION 3.16)
project(Locadex VERSION 0.2.0 LANGUAGES C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(LOCADEX_BUILD_TESTS "Build Locadex validation tests" OFF)
option(LOCADEX_BUILD_EXAMPLES "Build Locadex examples" OFF)
option(LOCADEX_STRICT_WARNINGS "Treat supported compiler warnings as errors" ON)

function(locadex_apply_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
        if(LOCADEX_STRICT_WARNINGS)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
        if(LOCADEX_STRICT_WARNINGS)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()

add_library(locadex STATIC
    src/locadex_grid_direction8_i32.c
    src/locadex_morton3_decode_u32.c
    src/locadex_morton3_encode_u32.c
    src/locadex_voxel_coords_3d_u32.c
    src/locadex_voxel_index_3d_u32.c
)
add_library(Locadex::Locadex ALIAS locadex)
target_compile_features(locadex PUBLIC c_std_99)
set_target_properties(locadex PROPERTIES
    C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO EXPORT_NAME Locadex)
target_include_directories(locadex PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
locadex_apply_warnings(locadex)

if(LOCADEX_BUILD_EXAMPLES)
    add_executable(locadex_example_minimal examples/minimal.c)
    target_link_libraries(locadex_example_minimal PRIVATE Locadex::Locadex)
    target_compile_features(locadex_example_minimal PRIVATE c_std_99)
    set_target_properties(locadex_example_minimal PROPERTIES
        C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    locadex_apply_warnings(locadex_example_minimal)
endif()

if(LOCADEX_BUILD_TESTS)
    enable_testing()
    enable_language(CXX)
    set(LOCADEX_TESTS api_audit morton voxel)
    foreach(test_name IN LISTS LOCADEX_TESTS)
        add_executable(locadex_test_${test_name} tests/test_${test_name}.c)
        target_link_libraries(locadex_test_${test_name} PRIVATE Locadex::Locadex)
        target_compile_features(locadex_test_${test_name} PRIVATE c_std_99)
        set_target_properties(locadex_test_${test_name} PROPERTIES
            C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
        locadex_apply_warnings(locadex_test_${test_name})
        if(test_name STREQUAL "api_audit" AND NOT MSVC)
            target_link_libraries(locadex_test_${test_name} PRIVATE m)
        endif()
        add_test(NAME locadex.${test_name} COMMAND locadex_test_${test_name})
    endforeach()

    set(LOCADEX_PUBLIC_HEADERS
        grid_direction8_i32.h
        morton3_decode_u32.h
        morton3_encode_u32.h
        voxel_coords_3d_u32.h
        voxel_index_3d_u32.h
    )
    foreach(header IN LISTS LOCADEX_PUBLIC_HEADERS)
        string(REPLACE ".h" "" header_test_name "${header}")
        set(header_smoke_source "${CMAKE_CURRENT_BINARY_DIR}/header_${header_test_name}.c")
        file(WRITE "${header_smoke_source}" "#include <locadex/spatial/${header}>\nint main(void) { return 0; }\n")
        add_executable(locadex_header_${header_test_name} "${header_smoke_source}")
        target_link_libraries(locadex_header_${header_test_name} PRIVATE Locadex::Locadex)
        target_compile_features(locadex_header_${header_test_name} PRIVATE c_std_99)
        set_target_properties(locadex_header_${header_test_name} PROPERTIES
            C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
        locadex_apply_warnings(locadex_header_${header_test_name})
        add_test(NAME locadex.header.${header_test_name}
            COMMAND locadex_header_${header_test_name})
    endforeach()

    set(LOCADEX_CPP_SMOKE "")
    foreach(header IN LISTS LOCADEX_PUBLIC_HEADERS)
        string(APPEND LOCADEX_CPP_SMOKE "#include <locadex/spatial/${header}>\n")
    endforeach()
    string(APPEND LOCADEX_CPP_SMOKE
        "int main() { uint32_t code=0; return locadex_morton3_encode_u32(1u,2u,3u,&code) && code==53u ? 0 : 1; }\n")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/headers_cpp.cpp" "${LOCADEX_CPP_SMOKE}")
    add_executable(locadex_headers_cpp "${CMAKE_CURRENT_BINARY_DIR}/headers_cpp.cpp")
    target_link_libraries(locadex_headers_cpp PRIVATE Locadex::Locadex)
    locadex_apply_warnings(locadex_headers_cpp)
    add_test(NAME locadex.headers_cpp COMMAND locadex_headers_cpp)
endif()

install(TARGETS locadex EXPORT LocadexTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT LocadexTargets FILE LocadexTargets.cmake NAMESPACE Locadex::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Locadex)
configure_package_config_file(cmake/LocadexConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/LocadexConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Locadex)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/LocadexConfigVersion.cmake
    VERSION ${PROJECT_VERSION} COMPATIBILITY SameMinorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LocadexConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/LocadexConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Locadex)
