include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")

include_directories(${DOCTEST_INCLUDE_DIR})

################################################################

set(CMAKE_CROSSCOMPILING_EMULATOR "${CMAKE_SOURCE_DIR}/run-qemu.sh" CACHE FILEPATH "Path to the emulator for the target system.")


################################################################

add_executable(tests Buffer_tests.cpp)
add_dependencies(tests doctest)

target_compile_definitions(tests PRIVATE
    DOCTEST_CONFIG_NO_MULTITHREADING
    DOCTEST_CONFIG_NO_POSIX_SIGNALS
)

# Make sure doctest headers are available
target_include_directories(tests PRIVATE ${DOCTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)

# add_test(NAME all_tests COMMAND tests --nographic)
add_test(NAME all_tests COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:tests> -nographic)


################################################################

set_target_properties(tests PROPERTIES
    SUFFIX .elf
    LINK_DEPENDS "${LINKER_SCRIPTS}"
)

target_link_options(tests PRIVATE
  -T${CMAKE_SOURCE_DIR}/ldscripts/mem.ld
  -T${CMAKE_SOURCE_DIR}/ldscripts/sections.ld
  LINKER:--print-memory-usage
  LINKER:--sort-section=name
  LINKER:--cref
  LINKER:-Map,${CMAKE_CURRENT_BINARY_DIR}/tests.map
)

target_link_libraries(tests PRIVATE system)

