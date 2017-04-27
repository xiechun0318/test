// CodedStructuredLight_decode.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

using namespace cv;
using namespace std;

Mat1b computeShadowMask(const Mat1b& blackImage, const Mat1b& whiteImage, size_t threshold)
{
	Mat1b shadowMask = Mat1b::zeros(blackImage.size());
	for (int j = 0; j < shadowMask.rows; ++j) {
		for (int i = 0; i < shadowMask.cols; ++i) {
			if (whiteImage(j, i) > blackImage(j, i) + threshold) {
				shadowMask(j, i) = 255;
				//git test
			}
		}
	}
	return shadowMask;
}

Mat2f computeDecodeImage(Ptr<structured_light::GrayCodePattern>& graycode, const vector<Mat1b>& captured_pattern, const Mat1b& mask)
{
	Mat2f decodedImage = Mat2f::zeros(mask.size());
	for (int j = 0; j < decodedImage.rows; ++j) {
		for (int i = 0; i < decodedImage.cols; ++i) {
			if (mask(j, i) == 0) {
				continue;
			}
			Point projPixel;
			bool error = graycode->getProjPixel(captured_pattern, i, j, projPixel);
			if (error) {
				continue;
			}
			decodedImage(j, i)[0] = (float)projPixel.x;
			decodedImage(j, i)[1] = (float)projPixel.y;
		}
	}
	return decodedImage;
}

int main()
{
    return 0;
}

