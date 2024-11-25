#include "TextureConverter.h"
#include<Windows.h>

using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);

	//読み込んだディフェーズテクスチャをSRGBとして扱う
	SaveDDSTextureToFile();
}


void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	//ファイルパスをワイド文字列に変換する
	std::wstring wfilepath = ConvertMultiByteStringToWideString(filepath);

	//テクスチャを読み込む
	HRESULT result = DirectX::LoadFromWICFile(wfilepath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));



	//フォルダパスとファイル名を分離
	SeparateFilePath(wfilepath);


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

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring execeptExt;

	//区切り文字が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');

	//検索がヒットした場合
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前までを抜き出す
		execeptExt = filePath.substr(0, pos1);

	}
	else {
		fileExt_ = L"";
		execeptExt =filePath;
	}

	//区切り文字がでてくる一番最後の部分を検索
	pos1 = execeptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = execeptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = execeptExt.substr(pos1 + 1, execeptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字の'/'が出てくる一番最後の部分を検索
	pos1 = execeptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = execeptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = execeptExt.substr(pos1 + 1, execeptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字がないのでファイル名のみとして扱う
	directoryPath_ = L"";
	fileName_ = execeptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	DirectX::ScratchImage mipChain;
	//ミップマップ生成
	HRESULT result;
	result = DirectX::GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	ScratchImage converted;
	result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL, 1.0f, converted);
	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	//読み込んだテクスチャをSRGBとして扱う
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	std::wstring filepath = directoryPath_ + fileName_ + L".dds";

	//DDSファイル書き出し
	result = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, filepath.c_str());
	assert(SUCCEEDED(result));
}
