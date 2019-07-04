#include <iostream>
#include <memory>
#include <fstream>
#include <Raytracer.hh>
#include <Geometry.hh>

int main() {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	Sphere sphere(Vec3f(-3, 0, -16), 2);
	raytracer->render(sphere);
	exit(EXIT_SUCCESS);
}