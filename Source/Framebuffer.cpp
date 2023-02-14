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

	if (rTexture != nullptr)
	{
		glGenFramebuffers(1, &iFrameBufferID);
		glBindFramebuffer(eFramebufferOp, iFrameBufferID);

		glFramebufferTexture2D(eFramebufferOp, eFramebufferAttach, eFramebufferTex, rTexture->GetId(), iLevel);

		glBindFramebuffer(eFramebufferOp, 0);

		GLenum CodeCheck = glCheckNamedFramebufferStatus(iFrameBufferID, eFramebufferOp);

		if (CodeCheck == EFramebufferStatus::EFS_Complete)
			rLog.WriteAndDisplay("Frame buffer created");
		else
			rLog.WriteAndDisplay("Failed to init frame buffer with code: " + to_string(CodeCheck), ELogSeverity::ELS_Error);
	}
	else
		rLog.WriteAndDisplay("Texture object returned null");
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