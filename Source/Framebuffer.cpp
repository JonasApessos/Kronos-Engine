#include "Framebuffer.h"


Framebuffer::Framebuffer(
	EFramebufferOp IneFrameBufferOp,
	EFramebufferAttach IneFramebufferAttach,
	EFramebufferTex IneFramebufferTex,
	Texture* InrTexture,
	int32 IniLevel) :
	eFramebufferOp(IneFrameBufferOp),
	eFramebufferAttach(IneFramebufferAttach),
	eFramebufferTex(IneFramebufferTex),
	rTexture(InrTexture),
	iLevel(IniLevel)
{
	rLog = Log("LogFrameBuffer");

	CreateBuffer();
}

Framebuffer::Framebuffer(const Framebuffer& InrFramebuffer) :
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
	GLenum eStatusCode = glCheckNamedFramebufferStatus(iFrameBufferID, eFramebufferOp);

	switch (eStatusCode)
	{
	case EFramebufferStatus::EFS_Complete:
		rLog.WriteAndDisplay("Framebuffer creation complete", ELogSeverity::ELS_Info);
		break;

	case EFramebufferStatus::EFS_IncompleteAttachment:
		rLog.WriteAndDisplay("Framebuffer attachment points incomplete", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_IncompleteDrawBuffer:
		rLog.WriteAndDisplay("Framebuffer draw buffer incomplete", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_IncompleteLayerTargets:
		rLog.WriteAndDisplay("Framebuffer layer targets incomplete", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_IncompleteMissingAttachment:
		rLog.WriteAndDisplay("framebuffer no image detected, you need at least one image assigned to you framebuffer", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_IncompleteMultisample:
		rLog.WriteAndDisplay("framebuffer GL_TEXTURE_FIXED_SAMPLE_LOCATION not the same on all textures or populated collor attachments not the same from textures target", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_IncompleteReadBuffer:
		rLog.WriteAndDisplay("framebuffer GL_READ_BUFFER is not GL_NONE and GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for color attachment point named by GL_READ_BUFFER", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_Undefined:
		rLog.WriteAndDisplay("specified default framebuffer does not exists", ELogSeverity::ELS_Error);
		break;

	case EFramebufferStatus::EFS_Unsupported:
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

		glBindFramebuffer(eFramebufferOp, iFrameBufferID);

		glFramebufferTexture2D(eFramebufferOp, eFramebufferAttach, eFramebufferTex, iFrameBufferID, iLevel);

		DisplayAllGLError();

		CheckFramebufferState();

		glBindFramebuffer(eFramebufferOp, 0);

	}
	else
		rLog.WriteAndDisplay("Texture object returned null, abording Buffer creation");
}