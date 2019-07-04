#include <gtest/gtest.h>
#include <Raytracer.hh>

TEST(Raytracer_tests, RaytracerCreation_ReturnsValid) {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	ASSERT_NE(raytracer.get(), nullptr);
}

TEST(Raytracer_tests, WriteToPPM_ReturnsNonNull) {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	std::string result = raytracer->create_string_for_ppm();
	ASSERT_STRNE("", result.c_str());
}
