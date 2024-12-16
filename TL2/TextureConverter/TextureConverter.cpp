#include "TextureConverter.h"
#include<Windows.h>

using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);

	//�ǂݍ��񂾃f�B�t�F�[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	SaveDDSTextureToFile();
}


void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	//�t�@�C���p�X�����C�h������ɕϊ�����
	std::wstring wfilepath = ConvertMultiByteStringToWideString(filepath);

	//�e�N�X�`����ǂݍ���
	HRESULT result = DirectX::LoadFromWICFile(wfilepath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));



	//�t�H���_�p�X�ƃt�@�C�����𕪗�
	SeparateFilePath(wfilepath);


}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	//�T�C�Y�擾
	int buffSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//���C�h������
	std::wstring wString;
	wString.resize(buffSize);

	//������ɕϊ����Ď󂯎��
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], buffSize);


	return wString;
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring execeptExt;

	//��؂蕶�����o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');

	//�������q�b�g�����ꍇ
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//��؂蕶���̑O�܂ł𔲂��o��
		execeptExt = filePath.substr(0, pos1);

	}
	else {
		fileExt_ = L"";
		execeptExt =filePath;
	}

	//��؂蕶�����łĂ����ԍŌ�̕���������
	pos1 = execeptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = execeptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = execeptExt.substr(pos1 + 1, execeptExt.size() - pos1 - 1);
		return;
	}

	//��؂蕶����'/'���o�Ă����ԍŌ�̕���������
	pos1 = execeptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = execeptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = execeptExt.substr(pos1 + 1, execeptExt.size() - pos1 - 1);
		return;
	}

	//��؂蕶�����Ȃ��̂Ńt�@�C�����݂̂Ƃ��Ĉ���
	directoryPath_ = L"";
	fileName_ = execeptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	DirectX::ScratchImage mipChain;
	//�~�b�v�}�b�v����
	HRESULT result;
	result = DirectX::GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	//ScratchImage converted;
	//result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
	//	DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL, 1.0f, converted);
	//if (SUCCEEDED(result)) {
	//	scratchImage_ = std::move(converted);
	//	metadata_ = scratchImage_.GetMetadata();
	//}

	//�ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	std::wstring filepath = directoryPath_ + fileName_ + L".dds";

	//DDS�t�@�C�������o��
	result = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, filepath.c_str());
	assert(SUCCEEDED(result));
}
