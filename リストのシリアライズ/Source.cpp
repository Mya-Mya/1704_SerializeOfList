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
struct list*header;//�w�b�_
struct list*now;//��
struct list*before;//�O

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init();
	srand((unsigned)time(NULL));//����������


	printfDx("�����L�[�������ēǂݍ���\n");
	WaitKey();
	ClearDrawScreen();

	//�ǂݍ���
	char *filename = "list.txt";
	FILE *filehandle;
	int readdata[ALL_LINES];

	if ((filehandle = fopen(filename, "rb")) == NULL) {
		printfDx("�t�@�C���I�[�v���G���[");
		WaitKey();
		DxLib_End();
		return 0;
	}
	else {
		///�t�@�C������f�[�^�[��ǂݍ���
		fread(&readdata, sizeof(int), ALL_LINES, filehandle);
		fclose(filehandle);///���
	}

	printfDx("�����L�[�������č��ڐ��𒲂ׂ�\n");
	WaitKey();
	ClearDrawScreen();

	//���ڐ��𒲂ׂ�
	int lines;
	lines = ((sizeof(readdata)) / (sizeof(readdata[0])));

	printfDx("%d�B�����L�[�������ă��X�g�\���\��\n", lines);
	WaitKey();
	ClearDrawScreen();

	//���X�g�\����
	int k = 0;
	while (k < lines) {
		now = (list*)malloc(sizeof(struct list));
		if (now != 0) {//�쐬����
			now->data = readdata[k];//���X�g�ɔz�����
			now->next = NULL;//���̂Ƃ��뎟�͂��Ȃ�

			printfDx("%d->data=%d\n", now, now->data);

			if (k == 0) {//�܂����o�^��������
				header = now;
				before = now;
			}
			else {//���łɃf�[�^�[����������
				before->next = now;
				before = now;
			}
			k++;
		}
	}

	printfDx("���X�g�\���\�������B�����L�[�������đS����\n");
	WaitKey();
	ClearDrawScreen();

	//�S����
	struct list *d = header;
	struct list *temp;
	while (d != NULL) {
		temp = d;
		d = d->next;
		free(temp);
	}

	printfDx("�S��������!!\n\n\n\n");



	printfDx("�����L�[�������ă��X�g����\n");
	WaitKey();
	ClearDrawScreen();

	//���X�g�\���ɍ��ڍ쐬

	now = (list*)malloc(sizeof(struct list));
	if (now != 0) {//�쐬����
		now->data = rand() % 512 + 1;//����
		now->next = NULL;//���̂Ƃ��뎟�͂��Ȃ�

		header = now;
		before = now;

		printfDx("%d->data=%d\n", now, now->data);
	}
	for (int i = 0; i < ALL_LINES; i++) {
		now = (list*)malloc(sizeof(struct list));
		if (now != 0) {//�쐬����
			now->data = rand() % 512 + 1;//����
			now->next = NULL;//���̂Ƃ��뎟�͂��Ȃ�

			before->next = now;
			before = now;
			printfDx("%d->data=%d\n", now, now->data);
		}
	}

	printfDx("�����L�[�������Ĕz��\n");
	WaitKey();
	ClearDrawScreen();

	//���ڐ��𒲂ׂ�
	struct list *p;

	p = header;
	int i = 0;
	while (p != NULL) {
		p = p->next;
		i++;
	}

	//�z��̗p�ӂƑ��
	int *savedata;
	savedata = (int*)malloc(i * sizeof(int));//�������m��

	p = header;
	i = 0;
	while (p != NULL) {
		savedata[i] = p->data;//�z��Ƀ��X�g����
		p = p->next;
		i++;
	}

	printfDx("�����L�[�������ĕۑ�\n");
	WaitKey();
	ClearDrawScreen();

	//�ۑ�
//	FILE *filehandle;
	filehandle = fopen("list.txt", "wb");
	fwrite(savedata, sizeof(int), ALL_LINES, filehandle);//��������
	fclose(filehandle);//����

	printfDx("�����L�[�������ďI��\n");
	WaitKey();
	ClearDrawScreen();

	//�S����
	d = header;
	while (d != NULL) {
		temp = d;
		d = d->next;
		free(temp);
	}

	DxLib_End();
	return 0;

}