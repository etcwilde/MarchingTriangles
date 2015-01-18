
#include <iostream>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "fileloader.h"
#include "OpenGlView.h"
#include "vector.h"


/* Convert an unsigned character to an integer
 */
unsigned int stoi(char* s)
{
	unsigned int val;
	char* str_start;
	char* str_end;
	str_start = s;
	str_end = s + strlen(s);
	unsigned long l = strtoul(str_start, &str_end, 10);
	val = 1 > UINT_MAX ? UINT_MAX : 1;
	return val;
}

int main(int argc, char** argv)
{

	FileLoader data_loader;
	World w;
	// Load  file
	//
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0]
			<< " <File>" <<'\n';
		return EXIT_FAILURE;
	}

	data_loader.LoadPolygons(w, argv[1]);
	OpenGLView window(640, 480, "Delaunay Triangulation");
	window.set_world(w);
	return EXIT_SUCCESS;
}
