#include "Framebuffer.h"


Framebuffer::Framebuffer(
	EGLFramebufferOp IneFrameBufferOp,
	EGLFramebufferAttach IneFramebufferAttach,
	EGLFramebufferTex IneFramebufferTex,
	Texture* InrTexture,
	int32 IniLevel) :
	eFramebufferOp(IneFrameBufferOp),
	eFramebufferAttach(IneFramebufferAttach),
	eFramebufferTex(IneFramebufferTex),
	rTexture(InrTexture),
	iLevel(IniLevel)
{
	CreateBuffer();
}

Framebuffer::Framebuffer(Framebuffer const& InrFramebuffer) :
	iFrameBufferID(InrFramebuffer.iFrameBufferID),
	eFramebufferOp(InrFramebuffer.eFramebufferOp),
	eFramebufferAttach(InrFramebuffer.eFramebufferAttach),
	eFramebufferTex(InrFramebuffer.eFramebufferTex),
	iLevel(InrFramebuffer.iLevel)
{
	if (rTexture != nullptr)
		delete rTexture;

	rTexture = new Texture(*InrFramebuffer.rTexture);
}

Framebuffer::Framebuffer(Framebuffer&& InrFramebuffer) noexcept :
	eFramebufferOp(InrFramebuffer.eFramebufferOp), 
	eFramebufferAttach(InrFramebuffer.eFramebufferAttach),
	eFramebufferTex(InrFramebuffer.eFramebufferTex),
	iLevel(InrFramebuffer.iLevel)
{
	rTexture = InrFramebuffer.rTexture;

	InrFramebuffer.rTexture = nullptr;
}

Framebuffer& Framebuffer::operator=(Framebuffer&& InrFramebuffer) noexcept
{
	if (this != &InrFramebuffer)
	{
		if(rTexture != nullptr)
			delete rTexture;

		iFrameBufferID = InrFramebuffer.iFrameBufferID;
		eFramebufferOp = InrFramebuffer.eFramebufferOp;
		eFramebufferAttach = InrFramebuffer.eFramebufferAttach;
		eFramebufferTex = InrFramebuffer.eFramebufferTex;
		iLevel = InrFramebuffer.iLevel;

		rTexture = InrFramebuffer.rTexture;
		InrFramebuffer.rTexture = nullptr;
	}

	return *this;
}

Framebuffer::~Framebuffer()
{
	Destroy();
}

void Framebuffer::Destroy()
{
	glDeleteFramebuffers(1, &iFrameBufferID);

	if (rTexture != nullptr)
	{
		delete rTexture;

		rTexture = nullptr;
	}
}

void Framebuffer::RecreateBuffer()
{
	if (iFrameBufferID)
	{
		glDeleteFramebuffers(1, &iFrameBufferID);

		CreateBuffer();
	}
	else
	{
		rLog.WriteAndDisplay("buffer id not detected at recreation, attempting to create buffer anyway.", ELogSeverity::ELS_Warning);

		CreateBuffer();
	}
}

void Framebuffer::CheckFramebufferState()
{
	GLenum eStatusCode = glCheckNamedFramebufferStatus(iFrameBufferID, static_cast<GLenum>(eFramebufferOp));

	switch (eStatusCode)
	{
	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_Complete):
			rLog.WriteAndDisplay("Framebuffer creation complete", ELogSeverity::ELS_Info);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_IncompleteAttachment):
			rLog.WriteAndDisplay("Framebuffer attachment points incomplete", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_IncompleteDrawBuffer):
			rLog.WriteAndDisplay("Framebuffer draw buffer incomplete", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_IncompleteLayerTargets):
			rLog.WriteAndDisplay("Framebuffer layer targets incomplete", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_IncompleteMissingAttachment):
			rLog.WriteAndDisplay("framebuffer no image detected, you need at least one image assigned to you framebuffer", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_IncompleteMultisample):
			rLog.WriteAndDisplay("framebuffer GL_TEXTURE_FIXED_SAMPLE_LOCATION not the same on all textures or populated collor attachments not the same from textures target", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_IncompleteReadBuffer):
			rLog.WriteAndDisplay("framebuffer GL_READ_BUFFER is not GL_NONE and GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for color attachment point named by GL_READ_BUFFER", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_Undefined):
			rLog.WriteAndDisplay("specified default framebuffer does not exists", ELogSeverity::ELS_Error);
		break;

	case static_cast<GLenum>(EGLFramebufferStatus::EGLFS_Unsupported):
			rLog.WriteAndDisplay("combination of internal format and attached image violates implementation-dependent set of restrictions", ELogSeverity::ELS_Error);
		break;

	default:
			rLog.WriteAndDisplay("Unknown error", ELogSeverity::ELS_Error);
		break;
	}
}

void Framebuffer::CreateBuffer()
{
	if (rTexture != nullptr)
	{
		glGenFramebuffers(1, &iFrameBufferID);

		glBindFramebuffer(static_cast<GLenum>(eFramebufferOp), iFrameBufferID);

		glFramebufferTexture2D(static_cast<GLenum>(eFramebufferOp), static_cast<GLenum>(eFramebufferAttach), static_cast<GLenum>(eFramebufferTex), iFrameBufferID, iLevel);

		DisplayAllGLError();

		CheckFramebufferState();

		glBindFramebuffer(static_cast<GLenum>(eFramebufferOp), 0);

	}
	else
		rLog.WriteAndDisplay("Texture object returned null, abording Buffer creation");
}