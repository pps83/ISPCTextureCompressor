//
//  Copyright (c) 2016 Intel Corporation
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this 
//  software and associated documentation files (the "Software"), to deal in the Software 
//  without restriction, including without limitation the rights to use, copy, modify, 
//  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
//  permit persons to whom the Software is furnished to do so, subject to the following 
//  conditions: 
//
//  The above copyright notice and this permission notice shall be included in all copies 
//  or substantial portions of the Software.  
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
//  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
//  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once

#include "DXUT.h"
#include <tchar.h>
#include "ispc_texcomp.h"

typedef void (CompressionFunc)(const rgba_surface* input, BYTE* output);

extern CompressionFunc* gCompressionFunc;
extern bool gMultithreaded;

extern double gCompTime;
extern double gCompRate;
extern int gTexWidth;
extern int gTexHeight;
extern double gRGBError;
extern double gRGBAError;
extern double gAlphaError;

extern ID3D11ShaderResourceView* gUncompressedSRV; // Shader resource view for the uncompressed texture resource.
extern ID3D11ShaderResourceView* gCompressedSRV; // Shader resource view for the compressed texture resource.
extern ID3D11ShaderResourceView* gErrorSRV; // Shader resource view for the error texture.

// Textured vertex.
struct Vertex
{
    D3DXVECTOR3 position;
	D3DXVECTOR2 texCoord;
};

struct VS_CONSTANT_BUFFER
{
	D3DXMATRIX mView;
};

extern ID3D11InputLayout* gVertexLayout;
extern ID3D11Buffer* gQuadVB;
extern ID3D11Buffer* gConstantBuffer;
extern ID3D11VertexShader* gVertexShader;
extern ID3D11PixelShader* gRenderTexturePS;
extern ID3D11SamplerState* gSamPoint;

void Initialize();
HRESULT CreateTextures(LPTSTR file);
void DestroyTextures();
HRESULT LoadTexture(LPTSTR file);
HRESULT PadTexture(ID3D11ShaderResourceView** textureSRV);
HRESULT SaveTexture(ID3D11ShaderResourceView* textureSRV, LPTSTR file);
HRESULT CompressTexture(ID3D11ShaderResourceView* uncompressedSRV, ID3D11ShaderResourceView** compressedSRV);
HRESULT ComputeError(ID3D11ShaderResourceView* uncompressedSRV, ID3D11ShaderResourceView* compressedSRV, ID3D11ShaderResourceView** errorSRV);
HRESULT RecompressTexture();

void ComputeRMSE(const BYTE *errorData, const INT width, const INT height);

void InitWin32Threads();
void DestroyThreads();

void StoreDepthStencilState();
void RestoreDepthStencilState();
HRESULT DisableDepthTest();

VOID CompressImage(const rgba_surface* input, BYTE* output);
VOID CompressImageST(const rgba_surface* input, BYTE* output);
VOID CompressImageMT(const rgba_surface* input, BYTE* output);
DWORD WINAPI CompressImageMT_Thread( LPVOID lpParam );

int GetBytesPerBlock(CompressionFunc* fn);
DXGI_FORMAT GetFormatFromCompressionFunc(CompressionFunc* fn);

void CompressImageBC1(const rgba_surface* input, BYTE* output);
void CompressImageBC2(const rgba_surface* input, BYTE* output);
void CompressImageBC3(const rgba_surface* input, BYTE* output);
void CompressImageBC7_ultrafast(const rgba_surface* input, BYTE* output);
void CompressImageBC7_veryfast(const rgba_surface* input, BYTE* output);
void CompressImageBC7_fast(const rgba_surface* input, BYTE* output);
void CompressImageBC7_basic(const rgba_surface* input, BYTE* output);
void CompressImageBC7_slow(const rgba_surface* input, BYTE* output);
void CompressImageBC7_alpha_ultrafast(const rgba_surface* input, BYTE* output);
void CompressImageBC7_alpha_veryfast(const rgba_surface* input, BYTE* output);
void CompressImageBC7_alpha_fast(const rgba_surface* input, BYTE* output);
void CompressImageBC7_alpha_basic(const rgba_surface* input, BYTE* output);
void CompressImageBC7_alpha_slow(const rgba_surface* input, BYTE* output);
