#include <string>
#include <Raytracer.hh>
#include "geometry.hh"

std::string Raytracer::create_string_for_ppm() {
	std::string ppm_file_content;
	int columns = 1080;
	int rows = 720;
	ppm_file_content.append("P3\n");
	ppm_file_content.append(std::to_string(columns));
	ppm_file_content.append(" ");
	ppm_file_content.append(std::to_string(rows));
	ppm_file_content.append("\n255\n");
	for (int i = rows-1; i >= 0; i--) {
		for (int j = 0; j < columns; j++) {
			Vec3f color(float(j) / float(columns), float(i) / float(rows), 0.2);
			int rounded_red = int(259.99 * color[0]);
			int rounded_green = int(255.99 * color[1]);
			int rounded_blue = int(255.99 * color[2]);
			ppm_file_content.append(std::to_string(rounded_red));
			ppm_file_content.append(" ");
			ppm_file_content.append(std::to_string(rounded_green));
			ppm_file_content.append(" ");
			ppm_file_content.append(std::to_string(rounded_blue));
			ppm_file_content.append("\n");
		}
	}
	return ppm_file_content;
}
