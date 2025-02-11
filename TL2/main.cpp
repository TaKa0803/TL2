#include"TextureConverter/TextureConverter.h"

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<Windows.h>

enum Argument {
	kApplicationPath,		//�A�v���P�[�V�����̃p�X
	kFilePath,				//�n���ꂽ�t�@�C���̃p�X

	NumArgument
};

int main(int argc,char*argv[]) {

	for (int i = 0; i < argc; i++) {
		//�������i�Ԃ�\��
		printf(argv[i]);
		printf("\n");
	}


	//�R�}���h���C�������w��Ȃ�
	if (argc < NumArgument) {
		//�g�����̕\��
		TextureConverter::OutputUsage();
		return 0;
	}

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));


	//�e�N�X�`���R���o�[�^
	TextureConverter converter;

	//�I�v�V������
	int numOptions = argc - NumArgument;
	//�I�v�V�����z��
	char** options = argv + NumArgument;

	//�e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath]);


	//COM���C�u�����I��
	CoUninitialize();

	//system("pause");

	return 0;
}