#include"DxLib.h"
#include<stdio.h>
#include<malloc.h>
#include<time.h>
#pragma warning(disable:4996)
#define ALL_LINES 8192

struct list {
	int data;
	list*next;
};
struct list*header;//ヘッダ
struct list*now;//今
struct list*before;//前

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init();
	srand((unsigned)time(NULL));//乱数初期化


	printfDx("何かキーを押して読み込み\n");
	WaitKey();
	ClearDrawScreen();

	//読み込み
	char *filename = "list.txt";
	FILE *filehandle;
	int readdata[ALL_LINES];

	if ((filehandle = fopen(filename, "rb")) == NULL) {
		printfDx("ファイルオープンエラー");
		WaitKey();
		DxLib_End();
		return 0;
	}
	else {
		///ファイルからデーターを読み込む
		fread(&readdata, sizeof(int), ALL_LINES, filehandle);
		fclose(filehandle);///解放
	}

	printfDx("何かキーを押して項目数を調べる\n");
	WaitKey();
	ClearDrawScreen();

	//項目数を調べる
	int lines;
	lines = ((sizeof(readdata)) / (sizeof(readdata[0])));

	printfDx("%d個。何かキーを押してリスト構造構成\n", lines);
	WaitKey();
	ClearDrawScreen();

	//リスト構造化
	int k = 0;
	while (k < lines) {
		now = (list*)malloc(sizeof(struct list));
		if (now != 0) {//作成成功
			now->data = readdata[k];//リストに配列を代入
			now->next = NULL;//今のところ次はいない

			printfDx("%d->data=%d\n", now, now->data);

			if (k == 0) {//まだ未登録だったら
				header = now;
				before = now;
			}
			else {//すでにデーターがあったら
				before->next = now;
				before = now;
			}
			k++;
		}
	}

	printfDx("リスト構造構成完了。何かキーを押して全消去\n");
	WaitKey();
	ClearDrawScreen();

	//全消去
	struct list *d = header;
	struct list *temp;
	while (d != NULL) {
		temp = d;
		d = d->next;
		free(temp);
	}

	printfDx("全消去完了!!\n\n\n\n");



	printfDx("何かキーを押してリスト生成\n");
	WaitKey();
	ClearDrawScreen();

	//リスト構造に項目作成

	now = (list*)malloc(sizeof(struct list));
	if (now != 0) {//作成成功
		now->data = rand() % 512 + 1;//乱数
		now->next = NULL;//今のところ次はいない

		header = now;
		before = now;

		printfDx("%d->data=%d\n", now, now->data);
	}
	for (int i = 0; i < ALL_LINES; i++) {
		now = (list*)malloc(sizeof(struct list));
		if (now != 0) {//作成成功
			now->data = rand() % 512 + 1;//乱数
			now->next = NULL;//今のところ次はいない

			before->next = now;
			before = now;
			printfDx("%d->data=%d\n", now, now->data);
		}
	}

	printfDx("何かキーを押して配列化\n");
	WaitKey();
	ClearDrawScreen();

	//項目数を調べる
	struct list *p;

	p = header;
	int i = 0;
	while (p != NULL) {
		p = p->next;
		i++;
	}

	//配列の用意と代入
	int *savedata;
	savedata = (int*)malloc(i * sizeof(int));//メモリ確保

	p = header;
	i = 0;
	while (p != NULL) {
		savedata[i] = p->data;//配列にリストを代入
		p = p->next;
		i++;
	}

	printfDx("何かキーを押して保存\n");
	WaitKey();
	ClearDrawScreen();

	//保存
//	FILE *filehandle;
	filehandle = fopen("list.txt", "wb");
	fwrite(savedata, sizeof(int), ALL_LINES, filehandle);//書き込み
	fclose(filehandle);//閉じる

	printfDx("何かキーを押して終了\n");
	WaitKey();
	ClearDrawScreen();

	//全消去
	d = header;
	while (d != NULL) {
		temp = d;
		d = d->next;
		free(temp);
	}

	DxLib_End();
	return 0;

}