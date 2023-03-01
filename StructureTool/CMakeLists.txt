# main code
# subdirectory : StructureTool

add_executable(StructureTool MinecraftTool.cpp Structure.h StructureLoader.cpp StructureLoader.h)

target_include_directories(StructureTool PUBLIC ${JSONIncludeDir})

install (TARGETS StructureTool DESTINATION bin)