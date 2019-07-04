#include <gtest/gtest.h>
#include <Raytracer.hh>

TEST(Raytracer_tests, RaytracerCreation_ReturnsValid) {
	std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>();
	ASSERT_NE(raytracer.get(), nullptr);
}
