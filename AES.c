#include<stdio.h>
#include<stdlib.h>
int main() {
	int temp = NULL;	
	int b = 0;
	int Text[64][16] = { NULL, };
	char str[1000] = { NULL, };// 입력받는 용도

	char str_Data[64][16]= { NULL, }; // state 단위로 분해, 출력용
	int int_Data[64][16] = { NULL, }; // 연산용
	int Mixed_Data[64][16] = { 0, };	
	char str_Decryption[64][16] = { NULL, };
	int int_Decryption[64][16] = { NULL, };




	int SubBytesTable[16][6] = { 0x29, 0x23, 0xbe, 0x84, 0xe1, 0x6c, 0xd6, 0xae, 0x52, 0x90, 0x49, 0xf1, 0xbb, 0xe9, 0xeb, 0xb3,
								 0xa6, 0xdb, 0x3c, 0x87, 0xc, 0x3e, 0x99, 0x24, 0x5e, 0xd, 0x1c, 0x6, 0xb7, 0x47, 0xde, 0x12,
								 0x4d, 0xc8, 0x43, 0x8b, 0x1f, 0x3, 0x5a, 0x7d, 0x9, 0x38, 0x25, 0x5d, 0xd4, 0xcb, 0xfc, 0x96,
								 0xf5, 0x45, 0x3b, 0x13, 0x89, 0xa, 0x32, 0x20, 0x9a, 0x50, 0xee, 0x40, 0x78, 0x36, 0xfd, 0xf6,
								 0x9e, 0xdc, 0xad, 0x4f, 0x14, 0xf2, 0x44, 0x66, 0xd0, 0x6b, 0xc4, 0x30, 0xa1, 0x22, 0x91, 0x9d,
								 0xda, 0xb0, 0xca, 0x2, 0xb9, 0x72, 0x2c, 0x80, 0x7e, 0xc5, 0xd5, 0xb2, 0xea, 0xc9, 0xcc, 0x53 };
	int MixColumn[16] = { 2, 3, 1, 1,
							1, 2, 3, 1,
							1, 1, 2, 3,
							3, 1, 1, 2 };
	/*
	int fpb[256] = { 0, };

	FILE *fp = fopen("d.txt", "w");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 16; j++) {
			while (b == 0) {
				
				temp = rand() % 256;
				if (fpb[temp] == 0) {
					fpb[temp] = -1;
					b = 1;
				}

			}
			fprintf(fp, "0x%x, ", temp );
			b = 0;
			
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	*/

#pragma region 문자열 입력받기

	printf("문자열을 입력하시오 : ");

	//문자열 입력받기
	gets(str);

	printf("\n\n==============================\n\n");
	printf("입력받은 문자열]\n\n%s\n", str);
#pragma endregion
#pragma region 대문자 변환 및 알파벳 외 탈락
	//대문자 변환 및 알파벳 외 탈락
	for (int i = 0; i < sizeof(str); i++) {
		if (str[i] >= 97 && str[i] <= 122) {
			str[i] -= 32;
		}
		else if ( !( str[i] >= 65 && str[i] <= 90 ) ) {
			if( str[i] != NULL)
				str[i] = 32;
		}
	}

	for (int i = 0; i <= sizeof(str); i++) {
		if (str[i] == 32) {// 공백

			for (int k = 0; k + i <= sizeof(str); k++) {
				if (str[i+ k + 1] == NULL) {

				} else {
					
					str[i + k] = str[i + k + 1];
				}
			}		i--;	
		}
			
	}
	printf("\n\n==============================\n\n");
	printf("대문자 변환 및 알파벳 외 탈락]\n\n%s\n", str);
#pragma endregion
#pragma region State단위로 정렬

	printf("\n\n==============================\n\n");
	printf("State 정렬]\n");
	//State 정렬
	for (int i = 0; i < sizeof(str) / 16; i++) {
		for (int j = 0; j < 16; j++) {
			//State 나누기 위한 한칸 공백
			if (j % 4 == 0) {
				printf("\n");
			}

			//str_Data에 str을 1State 단위로 분배해서 정렬
			if (str[i * 16 + j]!=NULL) {
				str_Data[i][j] = (str[i * 16 + j]);
			}

			//str의 값이 끝나면 State 삽입 끊고 정리
			if (str_Data[i][j] == NULL) {

//str_Data[i][j] = "!";
				i = sizeof(str)/16;
				break;
			}

			//A를 0으로 기준맞추기
			str_Data[i][j] -= 65;

			//출력 담당
			printf("%2x ", str_Data[i][j]);
		}
		//State간의 여백을 나누기
		printf("\n");
	}
#pragma endregion
#pragma region SubBytes
	printf("\n\n==============================\n\n");
	printf("Substitute Byte]\n");

	for (int i = 0; i < sizeof(str) / 16; i++) {
		for (int j = 0; j < 16; j++) {
			//State 나누기 위한 한칸 공백
			if (j % 4 == 0) {
				printf("\n");
			}
			//str의 값이 끝나면 State 삽입 끊고 정리
			if ((str_Data[i][j] == /*"!"*/NULL) && (str_Data[i][j] != 0) || i *16 + j >= _mbstrlen(str)) {
				//printf("check");
				int_Data[i][j] = -1;
				i = sizeof(str)/16;
				j = 16;	
				break;
			}

			int_Data[i][j] = SubBytesTable[((int)str_Data[i][j] / 16)][((int)str_Data[i][j] % 16)];


			//출력 담당
			printf("%4x ", int_Data[i][j]);

		}
		//State간의 여백을 나누기
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
						b = 1;
						continue;
					}

					temp = int_Data[i][4 * (j+1) - (l + 1)];
					int_Data[i][4 * (j+1) - (l + 1)] = int_Data[i][4 * j];
					int_Data[i][4*j]= temp;
					
				}
				if (b == 1) {
					k = j;
					j = 4;
					i = sizeof(str) / 16;
				}
			}
		}
	}

	//출력담당
	for (int i = 0; i < sizeof(str) / 16; i++) { //전체state출력
			for (int j = 0; j < 16; j++) { //state출력
				//State 나누기 위한 한칸 공백
				if (j % 4 == 0) {
					printf("\n");
				}

				//str의 값이 끝나면 State 삽입 끊고 정리
				if ((str_Data[i][j] == /*"!"*/NULL) && (str_Data[i][j] != 0) || i * 16 + j >= _mbstrlen(str)) {

					//printf("check");
					i = sizeof(str) / 16;
					break;
				}
				printf("%4x ", int_Data[i][j]);
			}
			printf("\n");
	}

#pragma endregion



#pragma region MixColumns
	printf("\n\n==============================\n\n");
	printf("MixColumns]\n");
	for (int i = 0; i < _mbstrlen(str); i++) {

		for (int j = 0; j < 16; j++) {
			Mixed_Data[i / 16][j % 16] = int_Data[i / 16][j % 4] * MixColumn[(j / 4) * 4] +
				int_Data[i / 16][(j % 4) + 4] * MixColumn[(j / 4) * 4 + 1] +
				int_Data[i / 16][(j % 4) + 8] * MixColumn[(j / 4) * 4 + 2] +
				int_Data[i / 16][(j % 4) + 12] * MixColumn[(j / 4) * 4 + 3];
		}

	}

	//출력담당
	for (int i = 0; i < sizeof(str) / 16; i++) { //전체state출력
		for (int j = 0; j < 16; j++) { //state출력
			//State 나누기 위한 한칸 공백
			if (j % 4 == 0) {
				printf("\n");
			}

			//str의 값이 끝나면 State 삽입 끊고 정리
			if ((str_Data[i][j] == /*"!"*/NULL) && (str_Data[i][j] != 0) || i * 16 + j >= _mbstrlen(str)) {

				//printf("check");
				i = sizeof(str) / 16;
				break;
			}
			printf("%4x ", Mixed_Data[i][j]);
		}
		printf("\n");
	}
#pragma endregion

#pragma region Decryption
	printf("\n\n==============================\n\n");
	printf("Decryption]\n");

	printf("1. MixColumns\n");

	printf("2. ShiftRows\n");
	
	strcpy(int_Decryption, int_Data);
	strcpy(str_Decryption, str_Data);
	
	for (int a = 0; ;a++) {
		for (int b = 0;;) { // 2층
		}

		for (int c = 0;;) { //3층
		}
		
		for (int d = 0;;) { //4층
		}
	}


	printf("3. SubBytes\n");











#pragma endregion
	}