#ifndef __INCLUDE_D3DPROCBASE_H__
#define __INCLUDE_D3DPROCBASE_H__

#define CUSTOMFVF (D3DFVF_XYZRHW|D3DFVF+DIFFUSE)

#include "main.h"

#include <d3d11.h>
#include "D3DX11.h"
#include "D3DX10.h"

typedef class D3DBaseClass:IDealer
{
protected:
	IDXGISwapChain *swapchain;
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;
	ID3D11RenderTargetView *backBuffer;

	ID3D11InputLayout *pLayout;
	ID3D11VertexShader *pVS;
	ID3D11PixelShader *pPS;
	ID3D11Buffer *pVBuffer;

	struct VERTEX
	{
		FLOAT X;
		FLOAT Y;
		FLOAT Z;
		D3DXCOLOR color;
	};
public:
	explicit D3DBaseClass();
	virtual ~D3DBaseClass();
	void initD3D(HWND hWnd,int width,int height);
	void cleanD3D(void);
	void renderFrame(void);

	void initGraphics(void);
	void initPipeline(void);

	virtual bool sendAsyncMessage(void);
	virtual bool acceptAsyncMessage(pIAsyncMessage);

}D3DBase;

#endif

