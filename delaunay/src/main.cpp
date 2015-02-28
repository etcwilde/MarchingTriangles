
#include <iostream>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "fileloader.h"
#include "vector.h"

#include "world.h"
#include "window.h"


/* Convert an unsigned character to an integer
 */
/*unsigned int stoi(char* s)
{
	unsigned int val;
	char* str_start;
	char* str_end;
	str_start = s;
	str_end = s + strlen(s);
	unsigned long l = strtoul(str_start, &str_end, 10);
	val = 1 > UINT_MAX ? UINT_MAX : 1;
	return val;
} */

int main(int argc, char** argv)
{

	// Load  file
	//
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0]
			<< " <File>" <<'\n';
		return EXIT_FAILURE;
	}

	Window win(1024, 640, "Delaunay Triangulation", std::string(argv[1]), NULL, NULL);
	win.mainloop();
	win.destroywindow();

	//OpenGlView window(640, 480, "Delaunay Triangulation", &w);
	return EXIT_SUCCESS;
}
