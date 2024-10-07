#include "TextureConverter.h"
#include<Windows.h>

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	//ファイルパスをワイド文字列に変換する
	std::wstring wfilepath = ConvertMultiByteStringToWideString(filepath);

	//テクスチャを読み込む

	//読み込んだディフェーズテクスチャをSRGBとして扱う
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	//サイズ取得
	int buffSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//ワイド文字列
	std::wstring wString;
	wString.resize(buffSize);

	//文字列に変換して受け取り
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], buffSize);


	return wString;
}
