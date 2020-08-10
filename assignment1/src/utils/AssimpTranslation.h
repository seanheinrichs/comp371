#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>
#include <iostream>
#include <vector>
#include <string>
#include "../Objects/geometry/Model.h"
#include "../Objects/geometry/ModelContainer.h"
#include "../Objects/geometry/shape.h"
#include "../Opengl_a/Vertex.h"
#include "../Opengl_a/Texture.h"
#include "../Opengl_a/VertexComponent.h"
#define MAX_TEX 32
#include "../Common.h"

static Texture getTexture(const char* path)
{
	for (unsigned int i = 0; i < MAX_TEX; i++) 
	{
		if (std::string(path) == g_textures[i].path) 
		{
			return g_textures[i];
		}
	}
	return Texture(path);
}

static std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture = getTexture(str.C_Str());
		texture.type = typeName;
		texture.path = std::string(str.C_Str());
		textures.push_back(texture);
	}
	return textures;
}


static Model* processMesh(aiMesh *mesh, const aiScene *scene)
{
	Model* model = new Model(true, true, false, true, "new model");
	Shape* shape = new Shape();

	//vector<Vertex> vertices;
	//vector<unsigned int> indices;
	std::vector<Texture> textures;
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
							0,
							0)
					));
			}

			shape->vc->appendVertex(vertex);

		}


	}

	/*
	// process material
	if (mesh->mMaterialIndex >= 0)
	{
		std::cout << "mesh has material" << std::endl;
		std::cout << textures.size() << std::endl;
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::cout << textures.size() << std::endl;

	}

	*/
	

	
	


	model->addPolygon(shape);
	//model->textures = textures;
	model->textureIndex = 13;

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
	//const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return (ModelContainer*)nullptr;
	}
	std::string directory = path.substr(0, path.find_last_of('/'));

	return processNode(scene->mRootNode, scene);
}

