#To build with a make file...
#need tab after dependency list
#target: list of dependencies
#	command to build target from dependencies
#touch filename.c to rebuild

TerrainGeneration: TerrainGeneration.c
	gcc TerrainGeneration.c -o TerrainGeneration -Wall -Werror
