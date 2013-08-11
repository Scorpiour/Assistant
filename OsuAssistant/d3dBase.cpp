#include "d3dProcBase.h"

D3DBaseClass::D3DBaseClass()
{
}

D3DBaseClass::~D3DBaseClass()
{
	this->cleanD3D();
}

void D3DBaseClass::initD3D(HWND hWnd,int width,int height)
{
	//Crate D3D interface
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd,sizeof(scd));

	//True = windowed, False = Full-screen
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4; //MSAA
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	D3D11CreateDeviceAndSwapChain(
				NULL,						//*pAdapter
				D3D_DRIVER_TYPE_HARDWARE,	//D3D_DRIVER_TYPE DriveType
				NULL,						//HMODULE software
				NULL,						//UINT Flags
				NULL,						//D3D_FEATURE_LEVEL *p
				NULL,						//UINT FeatureLevels
				D3D11_SDK_VERSION,			//UINT SDK_VERSION
				&scd,						
				&swapchain,
				&dev,
				NULL,
				&devcon);

	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID*)(&pBackBuffer));

	dev->CreateRenderTargetView(pBackBuffer,NULL,&backBuffer);

	pBackBuffer->Release();

	devcon->OMSetRenderTargets(1,&backBuffer,NULL);

	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort,sizeof(viewPort));

	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = float(width);
	viewPort.Height = float(height);

	devcon->RSSetViewports(1,&viewPort);

	initPipeline();
	initGraphics();

}

void D3DBaseClass::renderFrame(void)
{
	devcon->ClearRenderTargetView(backBuffer,D3DXCOLOR(0.125,0.125,0.125,1.0));

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	//select which vertex buffer to display
	devcon->IASetVertexBuffers(0,1,&pVBuffer,&stride,&offset);

	//select which primtive type we choose to use
	devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw the vertex buffer to the back buffer
	devcon->Draw(3,0);

	swapchain->Present(0,0);
}

void D3DBaseClass::cleanD3D(void)
{
	swapchain->SetFullscreenState(FALSE,NULL);

	pLayout->Release();
	pVS->Release();
	pPS->Release();
	pVBuffer->Release();

	swapchain->Release();
	backBuffer->Release();
	dev->Release();
	devcon->Release();
}

bool D3DBaseClass::sendAsyncMessage(void)
{
	return  false;
}

bool D3DBaseClass::acceptAsyncMessage(pIAsyncMessage)
{
	return true;
}

void D3DBaseClass::initGraphics(void)
{
	VERTEX OurVertices[]=
	{
		{0.0f,	0.5f,	0.0f,	D3DXCOLOR(1.0f,0.0f,0.0f,1.0f)},
		{0.45f,	-0.5f,	0.0f,	D3DXCOLOR(0.0f,1.0f,0.0f,1.0f)},
		{-0.45f,-0.5f,	0.0f,	D3DXCOLOR(0.0f,0.0f,1.0f,1.0f)}
	};
	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd,sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	dev->CreateBuffer(&bd,NULL,&pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer,NULL,D3D11_MAP_WRITE_DISCARD,NULL,&ms);
	memcpy(ms.pData,OurVertices,sizeof(OurVertices));

	devcon->Unmap(pVBuffer,NULL);
}

void D3DBaseClass::initPipeline(void)
{
	ID3D10Blob* VS;
	ID3D10Blob* PS;

	D3DX11CompileFromFile(L"shaderTriangle.hlsl",0,0,"VShader","vs_5_0",0,0,0,&VS,0,0);
	D3DX11CompileFromFile(L"shaderTriangle.hlsl",0,0,"PShader","ps_5_0",0,0,0,&PS,0,0);

	dev->CreateVertexShader(VS->GetBufferPointer(),VS->GetBufferSize(),NULL,&pVS);
	dev->CreatePixelShader(PS->GetBufferPointer(),PS->GetBufferSize(),NULL,&pPS);

	devcon->VSSetShader(pVS,0,0);
	devcon->PSSetShader(pPS,0,0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	dev->CreateInputLayout(ied,2,VS->GetBufferPointer(),VS->GetBufferSize(),&pLayout);
	devcon->IASetInputLayout(pLayout);
}	