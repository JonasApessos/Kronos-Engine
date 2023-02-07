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
	if (rTexture != nullptr)
	{
		glGenFramebuffers(1, &iFrameBufferID);
		glBindFramebuffer(eFramebufferOp, iFrameBufferID);

		glFramebufferTexture2D(eFramebufferOp, eFramebufferAttach, eFramebufferTex, rTexture->GetId(), iLevel);

		glBindFramebuffer(eFramebufferOp, 0);

		GLenum CodeCheck = glCheckNamedFramebufferStatus(iFrameBufferID, eFramebufferOp);

		if (CodeCheck == EFramebufferStatus::EFS_Complete)
			cout << "Frame buffer created" << "\n";
		else
		{
			cerr << "Failed to init frame buffer with code: " << CodeCheck << "\n";

			cerr << glGetError() << "\n";
		}
	}
	else
		cerr << "Texture object returned null\n";
}

Framebuffer::~Framebuffer()
{
	Destroy();
}

void Framebuffer::Destroy()
{
	glDeleteFramebuffers(1, &iFrameBufferID);
}