#include <iostream>
#include <memory>
#include <fstream>
#include <Raytracer.hh>
#include <geometry.hh>

int main() {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	std::string output = raytracer->create_string_for_ppm();
	std::ofstream out("output.ppm");
	out << output;
	out.close();
	return 0;
}