#include<stdio.h>
#include<stdlib.h>
int main() {
	int temp = NULL;
	
	int Text[64][16] = { NULL, };
	char str[1000] = { 0, };

	char str_Data[64][16] = { 0, };
	int int_Data[64][16] = { 0, };

	int SubBytesTable[16][6] = { 0x29, 0x23, 0xbe, 0x84, 0xe1, 0x6c, 0xd6, 0xae, 0x52, 0x90, 0x49, 0xf1, 0xf1, 0xbb, 0xe9, 0xeb,
								 0xb3, 0xa6, 0xdb, 0x3c, 0x87, 0xc, 0x3e, 0x99, 0x24, 0x5e, 0xd, 0x1c, 0x6, 0xb7, 0x47, 0xde,
								 0xb3, 0x12, 0x4d, 0xc8, 0x43, 0xbb, 0x8b, 0xa6, 0x1f, 0x3, 0x5a, 0x7d, 0x9, 0x38, 0x25, 0x1f,
								 0x5d, 0xd4, 0xcb, 0xfc, 0x96, 0xf5, 0x45, 0x3b, 0x13, 0xd, 0x89, 0xa, 0x1c, 0xdb, 0xae, 0x32,
								 0x20, 0x9a, 0x50, 0xee, 0x40, 0x78, 0x36, 0xfd, 0x12, 0x49, 0x32, 0xf6, 0x9e, 0x7d, 0x49, 0xdc,
								 0xad, 0x4f, 0x14, 0xf2, 0x44, 0x40, 0x66, 0xd0, 0x6b, 0xc4, 0x30, 0xb7, 0x32, 0x3b, 0xa1, 0x22	};
	/*
	FILE *fp = fopen("d.txt", "w");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 16; j++) {
			fprintf(fp, "0x%x, ", rand() % 256);
			
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	*/

#pragma region ���ڿ� �Է¹ޱ�

	printf("���ڿ��� �Է��Ͻÿ� : ");

	//���ڿ� �Է¹ޱ�
	gets(str);

	printf("\n\n==============================\n\n");
	printf("�Է¹��� ���ڿ�]\n\n%s\n", str);
#pragma endregion


#pragma region �빮�� ��ȯ �� ���ĺ� �� Ż��
	//�빮�� ��ȯ �� ���ĺ� �� Ż��
	for (int i = 0; i < sizeof(str); i++) {
		if (str[i] >= 97 && str[i] <= 122) {
			str[i] -= 32;
		}
		else if ( !( str[i] >= 65 && str[i] <= 90 ) ) {
			if( str[i] != NULL)
				str[i] = 32;
		}
	}


	printf("%s", str);
	//Trim(); ���� ����
	for (int i = 0; i < sizeof(str); i++) {
		if (str[i] == 32) {
			for (int l = 1; l+i < sizeof(str); l++) {
				if (str[l] == NULL) {
					//printf("fsfsdfsdf");
					i = sizeof(str);
					break;
				}
				str[i + l] = str[i + l+1];
			}
		}
		
		/*
		
		for (int j = 0; j < i; j++) {
			if (str[j] == 32) {
				str[j] = str[i];
			}
		}*/
	}




	printf("\n\n==============================\n\n");
	printf("�빮�� ��ȯ �� ���ĺ� �� Ż��]\n\n%s\n", str);
#pragma endregion


#pragma region State������ ����

	printf("\n\n==============================\n\n");
	printf("State ����]\n");
	//State ����
	for (int i = 0; i < sizeof(str) / 16; i++) {
		for (int j = 0; j < 16; j++) {
			//State ������ ���� ��ĭ ����
			if (j % 4 == 0) {
				printf("\n");
			}

			//str_Data�� str�� 1State ������ �й��ؼ� ����
			str_Data[i][j] = (str[i * 16 + j]);

			//str�� ���� ������ State ���� ���� ����
			if (str_Data[i][j] == NULL) {

//str_Data[i][j] = "!";
				i = sizeof(str)/16;
				break;
			}

			//A�� 0���� ���ظ��߱�
			str_Data[i][j] -= 65;

			//��� ���
			printf("%2x ", str_Data[i][j]);
		}
		//State���� ������ ������
		printf("\n");
	}
#pragma endregion


#pragma region SubBytes
	printf("\n\n==============================\n\n");
	printf("Substitute Byte]\n");

	for (int i = 0; i < sizeof(str) / 16; i++) {
		for (int j = 0; j < 16; j++) {
			//State ������ ���� ��ĭ ����
			if (j % 4 == 0) {
				printf("\n");
			}

			
			//str�� ���� ������ State ���� ���� ����
			if (str_Data[i][j] == /*"!"*/NULL) {

				printf("check");
				int_Data[i][j] = -1;
				i = sizeof(str)/16;
				j = 16;
				
				break;
			}

			int_Data[i][j] = SubBytesTable[((int)str_Data[i][j] / 16)][((int)str_Data[i][j] % 16)];


			//��� ���
			printf("%4x ", int_Data[i][j]);

		}
		//State���� ������ ������
		printf("\n");
	}
#pragma endregion

#pragma region ShiftRows
	printf("\n\n==============================\n\n");
	printf("ShiftRows]\n");


	for (int i = 0; i < sizeof(str) / 16; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < j; k++) {
				for (int l = 0; l < 3; l++) {

					if (int_Data[i][4 * (j + 1) - (l + 1)] == -1) {
						i = sizeof(str) / 16;
						j = 4;
						k = j;
						break;
					}

					temp = int_Data[i][4 * (j+1) - (l + 1)];
					int_Data[i][4 * (j+1) - (l + 1)] = int_Data[i][4 * j];
					int_Data[i][4*j] = temp;
					
				}
			}
		}
	}

	//��´��
	for (int i = 0; i < sizeof(str) / 16; i++) { //��üstate���
			for (int j = 0; j < 16; j++) { //state���
				//State ������ ���� ��ĭ ����
				if (j % 4 == 0) {
					printf("\n");
				}

				//str�� ���� ������ State ���� ���� ����
				if (str_Data[i][j] == /*"!"*/ NULL) {

					printf("check");
					i = sizeof(str) / 16;
					break;
				}
				
				printf("%4x ", int_Data[i][j]);
			}
	}

#pragma endregion
}