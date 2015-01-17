
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
	// Load  file
	//
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0]
			<< " <File>" <<'\n';
		return EXIT_FAILURE;
	}

	Vector2<int> a (1, 4);
	Vector2<int> b (2, 3);
	Vector2<int> d (0, 2);
	Vector2<float> c(0.f, 3.f);
	std::cout << a << b << a + b << a.Dot(b) << ' ' << d.Length() << std::endl;
	std::cout << c.Length() << std::endl;

	/*OpenGLView window(640, 480, "Delaunay Triangulation");
	FileLoader data_loader;
	data_loader.LoadPolygons(window.get_world(),
			argv[1]); */
	return EXIT_SUCCESS;
}
