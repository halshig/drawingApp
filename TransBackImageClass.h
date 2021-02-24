#pragma once

#include <windows.h>
#include<d2d1.h>
#include<d2d1_1.h>
#include<d2d1_1helper.h>
#include<d3d11.h>
#include<dxgi.h>
#include<dxgi1_2.h>
#include<wrl.h>
#include<vector>
#include<d2d1effects.h>
#include<d2d1effects_2.h>
#include<wincodec.h>
#include<wincodecsdk.h>
#include<string>
#include<debugapi.h>

#pragma comment(lib,"d2d1.lib")

//背景の透明部分の格子画像のクラス

class TransBackImage {
public:
	TransBackImage(ID2D1DeviceContext *d2context,int _width,int _height);
	ID2D1Bitmap* GetTransBackImage();
private:
	float width;
	float height;
	int interval;
	ID2D1BitmapRenderTarget* bmrt = nullptr;
	ID2D1Bitmap* transbm = nullptr;
	ID2D1SolidColorBrush* gray = nullptr;

};

//---------------------------------------------------------------------------------------------

TransBackImage::TransBackImage(ID2D1DeviceContext* d2context, int _width, int _height) {
	width = (float)_width;
	height = (float)_height;
	interval = 20;
	d2context->CreateCompatibleRenderTarget(
		D2D1_SIZE_F{ width,height },
		&bmrt
	);
	bmrt->CreateSolidColorBrush(D2D1_COLOR_F{ 0.4,0.4,0.4,1 }, &gray);
	//draw
	bmrt->BeginDraw();
	bmrt->Clear(D2D1_COLOR_F{ 0.7,0.7,0.7,1 });
	int gap = 0;
	for (int i = 0; i < width + interval; i += interval) {
		for (int j = 0; j < height + interval; j += interval*2) {
			bmrt->FillRectangle(D2D1_RECT_F{ (float)i,(float)(j  + gap),(float)(i + interval),(float)(j + interval + gap)}, gray);
		}
		if (gap == interval) {
			gap = 0;
		}
		else if (gap == 0) {
			gap = interval;
		}
	}
	bmrt->EndDraw();
	bmrt->GetBitmap(&transbm);
}

ID2D1Bitmap* TransBackImage::GetTransBackImage() {
	return transbm;
}
