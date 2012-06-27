// #include <windows.h>
// #include <stdio.h>
// #include <gl\gl.h>
// #include <gl\glu.h>
// #include <gl\glaux.h>
// 
// #include "MilkModel.h"
// 
// //	Meshes used
// int numMeshes = 0;
// MESH *pMeshes = NULL;
// 
// //	Materials used
// int numMaterials = 0;
// MATERIAL *pMaterials = NULL;
// 
// //	Triangles used
// int numTriangles = 0;
// TRIANGLE *pTriangles = NULL;
// 
// //	Vertices Used
// int numVertices = 0;
// VERTEX *pVertices = NULL;
// 
// int loadModelData(const char *filename)
// {
// 	FILE *fp;
// 	MS3DHEADER *pHeader;
// 	MS3DVERTEX *pVertex;
// 	MS3DTRIANGLE *pTriangle;
// 	MS3DMATERIAL *pMaterial;
// 	unsigned short aWord;
// 	char aChar;
// 	int i, j;
// 
// 	fp = fopen(filename, "rb");
// 	if(fp == NULL) return 0;	// "Couldn't open the model file."
// 
// 	pHeader = calloc(1, sizeof(MS3DHEADER));
// 	fread(pHeader, sizeof(MS3DHEADER), 1, fp);
// 
// 	if(strncmp( pHeader->ID, "MS3D000000", 10 ) != 0 )
// 	{
// 		fclose(fp);
// 		return 0; // "Not a valid Milkshape3D model file."
// 	}
// 
// 	if(pHeader->version < 3 || pHeader->version > 4)
// 	{
// 		fclose(fp);
// 		return 0; // "Unhandled file version. Only Milkshape3D Version 1.3 and 1.4 is supported." );
// 	}
// 	free(pHeader);
// 
// 	//get vertex data
// 	fread(&aWord, sizeof(unsigned short), 1, fp);
// 	numVertices = aWord;
// 	pVertices = calloc(numVertices, sizeof(VERTEX));
// 
// 	pVertex = calloc(1, sizeof(MS3DVERTEX));
// 	for ( i = 0; i < numVertices; i++ )
// 	{
// 		fread(pVertex, sizeof(MS3DVERTEX), 1, fp);
// 		memcpy( pVertices[i].location, pVertex->vertex, sizeof( float )*3 );
// 	}
// 	free(pVertex);
// 
// 	//get triangle data
// 	fread(&aWord, sizeof(unsigned short), 1, fp);
// 	numTriangles = aWord;
// 	pTriangles = calloc(numTriangles, sizeof(TRIANGLE));
// 
// 	pTriangle = calloc(1, sizeof(MS3DTRIANGLE));
// 	for (i=0; i<numTriangles; i++)
// 	{
// 		fread(pTriangle, sizeof(MS3DTRIANGLE), 1, fp);
// 		memcpy( pTriangles[i].vertexNormals, pTriangle->vertexNormals, sizeof( float )*9 );
// 		memcpy( pTriangles[i].s, pTriangle->s, sizeof( float )*3 );
// 		memcpy( pTriangles[i].t, pTriangle->t, sizeof( float )*3 );
// 		memcpy( pTriangles[i].vertexIndices, pTriangle->vertexIndices, sizeof(unsigned short)*3 );
// 		pTriangles[i].t[0] = 1.0f-pTriangles[i].t[0]; //need transform
// 		pTriangles[i].t[1] = 1.0f-pTriangles[i].t[1];
// 		pTriangles[i].t[2] = 1.0f-pTriangles[i].t[2];
// 	}
// 	free(pTriangle);
// 
// 	//get mesh data
// 	fread(&aWord, sizeof(unsigned short), 1, fp);
// 	numMeshes = aWord;
// 	pMeshes = calloc(numMeshes, sizeof(MESH));
// 	for ( i = 0; i < numMeshes; i++ )
// 	{
// 		fseek(fp, sizeof(byte), SEEK_CUR);	// flags
// 		fseek(fp, 32, SEEK_CUR);			// name
// 
// 		fread(&aWord, sizeof(unsigned short), 1, fp);
// 		pMeshes[i].numTriangles = aWord;
// 		pMeshes[i].pTriangleIndices = calloc(pMeshes[i].numTriangles, sizeof(int));
// 		for (j=0; j<pMeshes[i].numTriangles; j++)
// 		{
// 			fread(&aWord, sizeof(unsigned short), 1, fp);
// 			pMeshes[i].pTriangleIndices[j] = aWord;
// 		}
// 		fread(&aChar, sizeof(char), 1, fp);
// 		pMeshes[i].materialIndex = aChar;
// 	}
// 
// 	//get material data
// 	fread(&aWord, sizeof(unsigned short), 1, fp);
// 	numMaterials = aWord;
// 	pMaterials = calloc(numMaterials, sizeof(MATERIAL));
// 
// 	pMaterial = calloc(1, sizeof(MS3DMATERIAL));
// 	for ( i = 0; i < numMaterials; i++ )
// 	{
// 		fread(pMaterial, sizeof(MS3DMATERIAL), 1, fp);
// 		memcpy( pMaterials[i].ambient, pMaterial->ambient, sizeof( float )*4 );
// 		memcpy( pMaterials[i].diffuse, pMaterial->diffuse, sizeof( float )*4 );
// 		memcpy( pMaterials[i].specular, pMaterial->specular, sizeof( float )*4 );
// 		memcpy( pMaterials[i].emissive, pMaterial->emissive, sizeof( float )*4 );
// 		pMaterials[i].shininess = pMaterial->shininess;
// 		pMaterials[i].pTextureFilename = calloc(strlen(pMaterial->texture)+1, sizeof(char));
// 		strcpy( pMaterials[i].pTextureFilename, pMaterial->texture );
// 	}
// 	free(pMaterial);
// 
// 	fclose(fp);
// 	return 1;
// }
// 
// void loadTextures()
// {
// 	int i;
// 	FILE *fp;
// 	GLuint texture;
// 	AUX_RGBImageRec *pImage;
// 
// 	for(i=0; i<numMaterials; i++)
// 	{
// 		texture = 0;
// 		pImage = NULL;
// 		if(strlen(pMaterials[i].pTextureFilename) > 0)
// 		{
// 			fp = fopen(pMaterials[i].pTextureFilename, "r");
// 			if(fp)
// 			{
// 				fclose(fp); //open just for test
// 				pImage = auxDIBImageLoad(pMaterials[i].pTextureFilename);
// 			}
// 			if(pImage!=NULL && pImage->data!=NULL)
// 			{
// 				glGenTextures(1, &texture);
// 
// 				glBindTexture(GL_TEXTURE_2D, texture);
// 				glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
// 				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
// 				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
// 
// 				free(pImage->data);
// 				free(pImage);
// 			}
// 		}
// 		pMaterials[i].texture = texture;
// 	}
// }
// 
// void freeModel()
// {
// 	int i;
// 
// 	for(i=0; i<numMeshes; i++)
// 		free(pMeshes[i].pTriangleIndices);
// 	for(i=0; i<numMaterials; i++)
// 		free(pMaterials[i].pTextureFilename);
// 
// 	numMeshes = 0;
// 	if(pMeshes != NULL)
// 	{
// 		free(pMeshes);
// 		pMeshes = NULL;
// 	}
// 
// 	numMaterials = 0;
// 	if (pMaterials != NULL)
// 	{
// 		free(pMaterials);
// 		pMaterials = NULL;
// 	}
// 
// 	numTriangles = 0;
// 	if (pTriangles != NULL)
// 	{
// 		free(pTriangles);
// 		pTriangles = NULL;
// 	}
// 
// 	numVertices = 0;
// 	if (pVertices != NULL)
// 	{
// 		free(pVertices);
// 		pVertices = NULL;
// 	}
// }
// 
// void drawModel(int bInvertColor)
// {
// 	int i, j, k;
// 	GLboolean texEnabled;
// 
// 	texEnabled = glIsEnabled(GL_TEXTURE_2D);
// 
// 	// Draw by Mesh
// 	for (i=0; i<numMeshes; i++)
// 	{
// 		int materialIndex;
// 		materialIndex = pMeshes[i].materialIndex;
// 		if (materialIndex >= 0 )
// 		{
// 			if(bInvertColor)
// 			{
// 				float diffuse[4], specular[4];
// 				diffuse[0] = 1.0f-pMaterials[materialIndex].diffuse[0];
// 				diffuse[1] = 1.0f-pMaterials[materialIndex].diffuse[1];
// 				diffuse[2] = 1.0f-pMaterials[materialIndex].diffuse[2];
// 				diffuse[3] = 1.0f-pMaterials[materialIndex].diffuse[3];
// 				specular[0] = 1.0f-pMaterials[materialIndex].specular[0];
// 				specular[1] = 1.0f-pMaterials[materialIndex].specular[1];
// 				specular[2] = 1.0f-pMaterials[materialIndex].specular[2];
// 				specular[3] = 1.0f-pMaterials[materialIndex].specular[3];
// 
// 				glMaterialfv( GL_FRONT, GL_AMBIENT, pMaterials[materialIndex].ambient );
// 				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
// 				glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
// 				glMaterialfv( GL_FRONT, GL_EMISSION, pMaterials[materialIndex].emissive );
// 				glMaterialf( GL_FRONT, GL_SHININESS, pMaterials[materialIndex].shininess );
// 			}
// 			else
// 			{
// 				glMaterialfv( GL_FRONT, GL_AMBIENT, pMaterials[materialIndex].ambient );
// 				glMaterialfv( GL_FRONT, GL_DIFFUSE, pMaterials[materialIndex].diffuse );
// 				glMaterialfv( GL_FRONT, GL_SPECULAR, pMaterials[materialIndex].specular );
// 				glMaterialfv( GL_FRONT, GL_EMISSION, pMaterials[materialIndex].emissive );
// 				glMaterialf( GL_FRONT, GL_SHININESS, pMaterials[materialIndex].shininess );
// 			}
// 
// 			if ( pMaterials[materialIndex].texture > 0 )
// 			{
// 				glBindTexture( GL_TEXTURE_2D, pMaterials[materialIndex].texture );
// 				glEnable( GL_TEXTURE_2D );
// 			}
// 			else
// 				glDisable( GL_TEXTURE_2D );
// 		}
// 		else
// 		{
// 			glDisable( GL_TEXTURE_2D );
// 		}
// 
// 		glBegin(GL_TRIANGLES);
// 		{
// 			for (j=0; j<pMeshes[i].numTriangles; j++)
// 			{
// 				int triangleIndex;
// 				TRIANGLE* pTri;
// 
// 				triangleIndex = pMeshes[i].pTriangleIndices[j];
// 				pTri = &pTriangles[triangleIndex];
// 
// 				for(k=0; k<3; k++)
// 				{
// 					int index;
// 
// 					index = pTri->vertexIndices[k];
// 					glNormal3fv(pTri->vertexNormals[k]);
// 					glTexCoord2f(pTri->s[k], pTri->t[k]);
// 					glVertex3fv(pVertices[index].location);
// 				}
// 			}
// 		}
// 		glEnd();
// 	}
// 
// 	if ( texEnabled )
// 		glEnable( GL_TEXTURE_2D );
// 	else
// 		glDisable( GL_TEXTURE_2D );
// }