#include <time.h>
#include <Challenge/Physics/BVH/Octree.h>
#include <Challenge/Physics/Shapes/BoxShape.h>
using namespace challenge;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Octree tree(BoundingBox(5, 5, 5, 105, 105, 105), 3);

	BoxShape shape(glm::vec3(15, 15, 15), glm::vec3(5, 5, 5));
	tree.AddShape(&shape, new int(1));

	Ray pickRay(glm::vec3(95), glm::vec3(-1, -1, -1));
	float t = INFINITY;
	shape.RayIntersects(pickRay, t);
	auto pickedShape = tree.RayIntersection(pickRay);

	Logger::Log(LogDebug, "Shape ID: %d", *((int *)pickedShape->shape));
}