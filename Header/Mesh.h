#pragma once
#include <glm/glm.hpp>

#include "Vector.h"
#include "Texture.h"
#include "Shader.h"

#include <string>
#include <vector>

using KronosPrim::uint32, KronosPrim::uint64;
using std::string, std::vector, std::to_string, std::hash;

enum class EGLBufferTarget : uint32
{
	EGLBDT_ArrayBuffer = GL_ARRAY_BUFFER,
	EGLBDT_AtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
	EGLBDT_CopyReadBuffer = GL_COPY_READ_BUFFER,
	EGLBDT_CopyWriteBuffer = GL_COPY_WRITE_BUFFER,
	EGLBDT_DispatchIndirectBuffer = GL_DISPATCH_INDIRECT_BUFFER,
	EGLBDT_DrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
	EGLBDT_ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
	EGLBDT_PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
	EGLBDT_PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
	EGLBDT_QueryBuffer = GL_QUERY_BUFFER,
	EGLBDT_ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
	EGLBDT_TextureBuffer = GL_TEXTURE_BUFFER,
	EGLBDT_TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
	EGLBDT_UniformBuffer = GL_UNIFORM_BUFFER
};

enum class EGLBufferTUsage : uint32
{
	EGLBDU_StreamDraw = GL_STREAM_DRAW,
	EGLBDU_StreamRead = GL_STREAM_READ,
	EGLBDU_StreamCopy = GL_STREAM_COPY,
	EGLBDU_StaticDraw = GL_STATIC_DRAW,
	EGLBDU_StaticRead = GL_STATIC_READ,
	EGLBDU_StaticCopy = GL_STATIC_COPY,
	EGLBDU_DynamicDraw = GL_DYNAMIC_DRAW,
	EGLBDU_DynamicRead = GL_DYNAMIC_READ,
	EGLBDU_DynamicCopy = GL_DYNAMIC_COPY
};

enum class EGLDrawMode : uint32
{
	EGLDM_Points = GL_POINTS,
	EGLDM_LineStrip = GL_LINE_STRIP,
	EGLDM_LineLoop = GL_LINE_LOOP,
	EGLDM_Lines = GL_LINES,
	EGLDM_LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
	EGLDM_LinesAdjacency = GL_LINES_ADJACENCY,
	EGLDM_TriangleStrip = GL_TRIANGLE_STRIP,
	EGLDM_TriangleFan = GL_TRIANGLE_FAN,
	EGLDM_Triangles = GL_TRIANGLES,
	EGLDM_TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	EGLDM_TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
	EGLDM_Pathes = GL_PATCHES
};


/** \class MeshBase
*   \brief Abstract class for geometry mesh.
*    
*   Abstract class to manage geometry mesh.
*/
class MeshBase
{
public:
	MeshBase(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture>& InrTextures);
	MeshBase(MeshBase const& InrBaseMesh);
	MeshBase(MeshBase&& InrMaseMesh);
	
	virtual ~MeshBase() = 0;

	virtual void Draw(Shader& InrShader) = 0; //!< Abstract method, Draw the mesh list

	constexpr inline void SetDrawMode(EGLDrawMode IneDrawMode);

	constexpr inline uint32 GetVAO() const;	//!< Get the Vertex Array ID
	constexpr inline uint32 GetVBO() const; //!< Get the Vertex Buffer ID
	constexpr inline uint32 GetEBO() const; //!< Get the Element Buffer ID

	constexpr inline uint64 GetHash() const; //!< Get Hash ID of object, this will be changed in the future

	inline vector<SVector> GetVertices() const; //!< Get Vertices array
	inline vector<uint32> GetIndices() const; //!< Get Indices array
	inline vector<Texture> GetTextures() const; //!< Get Textures array

	inline EGLDrawMode GetDrawMode() const;

protected:
	uint64 iID; //!< Object ID
	uint64 iHash; //!< Object hashed ID

	uint32 VAO, VBO, EBO;

	vector<SVector> rVertices; //!< Vertices Array
	vector<uint32> rIndices; //!< Indices Array
	vector<Texture> rTextures; //!< Textures Array

	EGLDrawMode eDrawMode = EGLDrawMode::EGLDM_Triangles;

	virtual void SetupMesh() = 0; //!< Abstract method, Setup the geometric mesh, runs on construction of object

private:
	static uint64 iNumMeshes;
};

constexpr inline void MeshBase::SetDrawMode(EGLDrawMode IneDrawMode) { eDrawMode = IneDrawMode; }

constexpr inline uint32 MeshBase::GetVAO() const { return VAO; }
constexpr inline uint32 MeshBase::GetVBO() const { return VBO; }
constexpr inline uint32 MeshBase::GetEBO() const { return EBO; }

constexpr inline uint64 MeshBase::GetHash() const { return iHash; }

inline vector<SVector> MeshBase::GetVertices() const { return rVertices; }
inline vector<uint32> MeshBase::GetIndices() const { return rIndices; }
inline vector<Texture> MeshBase::GetTextures() const { return rTextures; }

inline EGLDrawMode MeshBase::GetDrawMode() const { return eDrawMode; }

/** \class Mesh
*   \brief class to manages geometry
*    
*   class to manages geometry
*/
class Mesh : public MeshBase 
{
public:
	Mesh(vector<SVector>& InrVertices, vector<uint32>& InrIndices, vector<Texture>& InrTextures);
	Mesh(Mesh const& InrMesh);
	Mesh(Mesh&& InrMesh);

	Mesh operator=(Mesh const& InrMesh);
	Mesh operator=(Mesh&& InrMesh);

	void Draw(Shader& InrShader) override;

	~Mesh();

	void Destroy();
protected:
	Log rLog = Log("LogMesh");

	virtual void SetupMesh() override;
private:
	
};
