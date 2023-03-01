# main build
# directory /

cmake_minimum_required(VERSION 3.26)

project (StructureToolProject)
add_subdirectory(Vendor/rapidjson/include)
add_subdirectory(StructureTool)

message(STATUS "include directory: ${PROJECT_SOURCE_DIR}")


# include (InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "$ LOCATION")
# set(CPACK_PACKAGE_VERSION_MAJOR "0")
# set(CPACK_PACKAGE_VERSION_MINOR "1")
# set(CPACK_GENERATOR_NSIS)
# set(CPACK_NSIS_MODIFY_PATH ON)

# include(CPACK)
