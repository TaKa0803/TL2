#include"TextureConverter/TextureConverter.h"

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<Windows.h>

enum Argument {
	kApplicationPath,		//アプリケーションのパス
	kFilePath,				//渡されたファイルのパス

	NumArgument
};

int main(int argc,char*argv[]) {

	for (int i = 0; i < argc; i++) {
		//文字列のi番を表示
		printf(argv[i]);
		printf("\n");
	}


	//
	assert(argc >= NumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));


	//テクスチャコンバータ
	TextureConverter converter;

	//テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);


	//COMライブラリ終了
	CoUninitialize();

	//system("pause");

	return 0;
}