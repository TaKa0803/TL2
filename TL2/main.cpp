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


	//コマンドライン引数指定なし
	if (argc < NumArgument) {
		//使い方の表示
		TextureConverter::OutputUsage();
		return 0;
	}

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));


	//テクスチャコンバータ
	TextureConverter converter;

	//オプション数
	int numOptions = argc - NumArgument;
	//オプション配列
	char** options = argv + NumArgument;

	//テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);


	//COMライブラリ終了
	CoUninitialize();

	//system("pause");

	return 0;
}