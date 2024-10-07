#include "TextureConverter.h"
#include<Windows.h>

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	//�t�@�C���p�X�����C�h������ɕϊ�����
	std::wstring wfilepath = ConvertMultiByteStringToWideString(filepath);

	//�e�N�X�`����ǂݍ���

	//�ǂݍ��񂾃f�B�t�F�[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
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
