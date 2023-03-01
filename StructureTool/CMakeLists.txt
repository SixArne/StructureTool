# main code
# subdirectory : StructureTool

add_executable(StructureTool MinecraftTool.cpp Structure.h StructureLoader.cpp StructureLoader.h)

target_include_directories(StructureTool PUBLIC ${JSONIncludeDir})

configure_file(Data/structure.json ${CMAKE_CURRENT_BINARY_DIR}/Data)

install (TARGETS StructureTool DESTINATION bin)