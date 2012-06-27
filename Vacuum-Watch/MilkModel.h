// #ifndef MILKMODEL_H
// #define MILKMODEL_H
// 
// // byte-align structures
// #ifdef _MSC_VER
// #	pragma pack( push, packing )
// #	pragma pack( 1 )
// #	define PACK_STRUCT
// #elif defined( __GNUC__ )
// #	define PACK_STRUCT	__attribute__((packed))
// #else
// #	error you must byte-align these structures with the appropriate compiler directives
// #endif
// 
// //	Mesh
// typedef struct tagMesh
// {
// 	int materialIndex;
// 	int numTriangles;
// 	int *pTriangleIndices;
// } PACK_STRUCT MESH;
// 
// //	Material properties
// typedef struct tagMaterial
// {
// 	float ambient[4], diffuse[4], specular[4], emissive[4];
// 	float shininess;
// 	GLuint texture;
// 	char *pTextureFilename;
// } PACK_STRUCT MATERIAL;
// 
// //	Triangle structure
// typedef struct tagTriangle
// {
// 	float vertexNormals[3][3];
// 	float s[3], t[3];
// 	unsigned short vertexIndices[3];
// } PACK_STRUCT TRIANGLE;
// 
// //	Vertex structure
// typedef struct tagVertex
// {
// 	float location[3];
// } PACK_STRUCT VERTEX;
// 
// // File header
// typedef struct MS3DHeader
// {
// 	char ID[10];
// 	int version;
// } PACK_STRUCT MS3DHEADER;
// 
// // Vertex information
// typedef struct MS3DVertex
// {
// 	unsigned char flags;
// 	float vertex[3];
// 	char boneID;
// 	unsigned char refCount;
// } PACK_STRUCT MS3DVERTEX;
// 
// // Triangle information
// typedef struct MS3DTriangle
// {
// 	unsigned short flags;
// 	unsigned short vertexIndices[3];
// 	float vertexNormals[3][3];
// 	float s[3], t[3];
// 	unsigned char smoothingGroup;
// 	unsigned char groupIndex;
// } PACK_STRUCT MS3DTRIANGLE;
// 
// // Material information
// typedef struct MS3DMaterial
// {
//     char name[32];
// 	float ambient[4], diffuse[4], specular[4], emissive[4];
//     float shininess;	// 0.0f - 128.0f
//     float transparency;	// 0.0f - 1.0f
//     unsigned char mode;	// 0, 1, 2 is unused now
//     char texture[128];
//     char alphamap[128];
// } PACK_STRUCT MS3DMATERIAL;
// 
// // Default alignment
// #ifdef _MSC_VER
// #	pragma pack( pop, packing )
// #endif
// 
// #undef PACK_STRUCT
// 
// int loadModelData(const char *filename);
// void loadTextures();
// void freeModel();
// void drawModel(int bInvertColor);
// 
// #endif // ndef MILKMODEL_H