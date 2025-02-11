#pragma once
#include<string>
#include"../external/DirectXTex/d3dx12.h"


#include"../external/DirectXTex/DirectXTex.h"
//�e�N�X�`���R���o�[�^
class TextureConverter {

public:
	
	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�
	/// </summary>
	/// <param name="filepath">�t�@�C���p�X</param>
	/// <param name="numOptions">�I�v�V������</param>
	/// <param name="options">�I�v�V�����z��</param>
	void ConvertTextureWICToDDS(const std::string& filepath,int numOptions =0,char*options[]=nullptr);

	/// <summary>
	/// �g�p���@�̏o��
	/// </summary>
	static void OutputUsage();
private:
	/// <summary>
	/// �e�N�X�`���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filepath">�t�@�C���p�X</param>
	void LoadWICTextureFromFile(const std::string& filepath);

	/// <summary>
	/// �}���`�o�C�g����������C�h������ɕϊ�
	/// </summary>
	/// <param name="mString">�}���`�o�C�g������</param>
	/// <returns>���C�h������</returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
	
	/// <summary>
	/// �t�H���_�p�X�ƃt�@�C�����̕���
	/// </summary>
	/// <param name="filepath"></param>
	void SeparateFilePath(const std::wstring& filepath);
	
	/// <summary>
	/// DDS�e�N�X�`���Ƃ��ăt�@�C�������o��
	/// </summary>
	/// <param name="numOptions">�I�v�V�����̐�</param>
	/// <param name="options">�I�v�V�����̔z��</param>
	void SaveDDSTextureToFile(int numOptions,char*options[]);
private:

	//�摜�̏��
	DirectX::TexMetadata metadata_;

	//�摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scratchImage_;

private:

	//�f�B���N�g���p�X
	std::wstring directoryPath_;
	//�t�@�C����
	std::wstring fileName_;
	//�t�@�C���g���q
	std::wstring fileExt_;

};