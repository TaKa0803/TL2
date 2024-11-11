#pragma once
#include<string>
#include"../external/DirectXTex/d3dx12.h"


#include"../external/DirectXTex/DirectXTex.h"
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
	
	/// <summary>
	/// フォルダパスとファイル名の分離
	/// </summary>
	/// <param name="filepath"></param>
	void SeparateFilePath(const std::wstring& filepath);

	/// <summary>
	/// DDSテクスチャとしてファイル書き出し
	/// </summary>
	void SaveDDSTextureToFile();
private:

	//画像の情報
	DirectX::TexMetadata metadata_;

	//画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;

private:

	//ディレクトリパス
	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//ファイル拡張子
	std::wstring fileExt_;

};