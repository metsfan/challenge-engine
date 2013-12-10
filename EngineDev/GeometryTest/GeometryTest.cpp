#include <time.h>
#include <Engine/Physics/BVH/Octree.h>
#include <Engine/Physics/Shapes/AABBShape.h>
using namespace challenge;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Octree tree(BoundingBox(5, 5, 5, 105, 105, 105), 3);

	AABBShape shape(glm::vec3(15, 15, 15), 5, 5, 5);
	tree.AddShape(&shape, new int(1));

	Ray pickRay(glm::vec3(95), glm::vec3(-1, -1, -1));
	float t = INFINITY;
	shape.RayIntersects(pickRay, t);
	auto pickedShape = tree.RayIntersection(pickRay);

	Logger::log(LogDebug, "Shape ID: %d", *((int *)pickedShape->shape));
}