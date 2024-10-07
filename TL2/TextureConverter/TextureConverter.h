#pragma once
#include<string>

//テクスチャコンバータ
class TextureConverter {

public:
	/// <summary>
	/// テクスチャをWICからDDSに変換
	/// </summary>
	/// <param name="filepath">ファイルパス</param>
	void ConvertTextureWICToDDS(const std::string& filepath);


private:
	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filepath">ファイルパス</param>
	void LoadWICTextureFromFile(const std::string& filepath);

	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	/// <param name="mString">マルチバイト文字列</param>
	/// <returns>ワイド文字列</returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
};