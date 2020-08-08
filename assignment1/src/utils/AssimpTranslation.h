#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>
#include <iostream>
#include "../Objects/geometry/Model.h"
#include "../Objects/geometry/ModelContainer.h"
#include "../Objects/geometry/shape.h"
#include "../Opengl_a/Vertex.h"
#include "../Opengl_a/VertexComponent.h"


static Model* processMesh(aiMesh *mesh, const aiScene *scene)
{
	Model* model = new Model(true, true, false, true, "new model");
	Shape* shape = new Shape(glm::vec3(0.0f));

	//vector<Vertex> vertices;
	//vector<unsigned int> indices;
	//vector<Texture> textures;
	unsigned int i = 0;
	for (unsigned int a = 0; a < mesh->mNumFaces; a++)
	{
		aiFace face = mesh->mFaces[a];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			i = face.mIndices[j];
			Vertex vertex;
			// process vertex positions, normals and texture coordinates
			vertex.addVertexComponent(
				VertexComponent(POSITION,
					glm::vec3(
						mesh->mVertices[i].x,
						mesh->mVertices[i].y,
						mesh->mVertices[i].z)
				));

			vertex.addVertexComponent(
				VertexComponent(NORMAL,
					glm::vec3(
						mesh->mNormals[i].x,
						mesh->mNormals[i].y,
						mesh->mNormals[i].z)
				));

			if (mesh->mTextureCoords[0])
			{
				vertex.addVertexComponent(
					VertexComponent(TEXTURE,
						glm::vec2(
							mesh->mTextureCoords[0][i].x,
							mesh->mTextureCoords[0][i].y)
					));
			}
			else
			{
				vertex.addVertexComponent(
					VertexComponent(TEXTURE,
						glm::vec2(
							mesh->mTextureCoords[0][i].x,
							mesh->mTextureCoords[0][i].y)
					));
			}

			shape->vc->appendVertex(vertex);

		}


	}


	// process material
	//if (mesh->mMaterialIndex >= 0)
	//{

	//}

	model->addPolygon(shape);

	return model;
}

static ModelContainer* processNode(aiNode *node, const aiScene *scene)
{
	ModelContainer* mc = new ModelContainer();

	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		mc->addModel(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ModelContainer* temp = processNode(node->mChildren[i], scene);
		for (std::vector<Model*>::iterator it = temp->models.begin(); it < temp->models.end(); it++)
			mc->addModel(*it);
	}
	return mc;
}

static ModelContainer* loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return (ModelContainer*)nullptr;
	}
	std::string directory = path.substr(0, path.find_last_of('/'));

	return processNode(scene->mRootNode, scene);
}

