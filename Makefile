#To build with a make file...
#need tab after dependency list
#target: list of dependencies
#	command to build target from dependencies
#touch filename.c to rebuild

Map2Map: Map2Map.c
	gcc Map2Map.c -o Map2Map -Wall -Werror
