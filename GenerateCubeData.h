#pragma once
#include <vector>
#include <glm.hpp>
#include <iostream>
#include <fstream>

void load()
{
	std::vector< unsigned int > fvertexIndices, fuvIndices, fnormalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen("cube.obj", "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);

		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndices[3], uvIndices[3], normalIndices[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndices[0], &uvIndices[0], &normalIndices[0], &vertexIndices[1], &uvIndices[1], &normalIndices[1], &vertexIndices[2], &uvIndices[2], &normalIndices[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			}

			fvertexIndices.push_back(vertexIndices[0]);
			fvertexIndices.push_back(vertexIndices[1]);
			fvertexIndices.push_back(vertexIndices[2]);
			fuvIndices.push_back(uvIndices[0]);
			fuvIndices.push_back(uvIndices[1]);
			fuvIndices.push_back(uvIndices[2]);
			fnormalIndices.push_back(normalIndices[0]);
			fnormalIndices.push_back(normalIndices[1]);
			fnormalIndices.push_back(normalIndices[2]);
		}
	}

	std::vector<glm::vec3> vertexPos;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// For each vertex of each triangle
	for (unsigned int i = 0; i < fvertexIndices.size(); i++) {
		unsigned int vertexIndex = fvertexIndices[i];
		unsigned int uvIndex = fuvIndices[i];
		//unsigned int normalIndex = fnormalIndices[i];

		vertexPos.push_back(temp_vertices[vertexIndex - 1]);
		uvs.push_back(temp_uvs[uvIndex - 1]);
		//normals.push_back(temp_normals[normalIndex - 1]);
	}

	fclose(file);

	std::ofstream myfile;
	myfile.open("data.txt");
	for (unsigned int i = 0; i < fvertexIndices.size(); i++) {
	
		myfile << vertexPos[i].x << ',' << vertexPos[i].y << ',' << vertexPos[i].z << ',' << std::endl;
	}
	myfile << std::endl;
	for (unsigned int i = 0; i < fvertexIndices.size(); i++) {

		myfile << uvs[i].x << ',' << uvs[i].y << ',' << std::endl;
	}
	myfile << std::endl;
	for (unsigned int i = 0; i < fvertexIndices.size(); i++) {

		myfile << uvs[i].x << ',' << uvs[i].y << ',' << std::endl;
	}

	myfile.close();


}