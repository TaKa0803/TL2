#include<cstdio>
#include<cstdlib>

int main(int argc,char*argv[]) {

	for (int i = 0; i < argc; i++) {
		//文字列のi番を表示
		printf(argv[i]);
		printf("\n");
	}

	system("pause");

	return 0;
}