#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define inputfile "Test1_05.txt"

typedef struct GRAPH{
	int n;
	int a[MAX][MAX];
}DOTHI;

int DocMTKe(const char TenFile[], DOTHI &g){
	FILE *f = fopen(TenFile, "rt");
	if (f==NULL){
		printf("Ko mo dc file!");
		return 0;
	}
	fscanf(f, "%d", &g.n);
	for (int i=0; i<g.n; i++){
		for (int j=0; j<g.n; j++)
			fscanf(f, "%d", &g.a[i][j]);
	}
	fclose(f);
	return 1;
}

void TimCacDinhLienThong(DOTHI g, int nhan[MAX], int i){
	for (int j=0; j<g.n; j++){
		if (g.a[i][j] != 0 && nhan[j] != nhan[i]){
			nhan[j] = nhan[i];
			TimCacDinhLienThong(g, nhan, j);
		}
	}
}

void XetLienThong(DOTHI g){
	int Nhan[MAX];
	for (int i=0; i<g.n; i++)
		Nhan[i] = 0;
	int SoTPLT = 0;
	for (int i=0; i<g.n; i++){
		if (Nhan[i] == 0){
			SoTPLT++;
			Nhan[i] = SoTPLT;
			TimCacDinhLienThong(g, Nhan, i);
		}
	}
	printf("So thanh phan lien thong la %d \n", SoTPLT);
	for (int i=1; i<=SoTPLT; i++){
		printf("Thanh phan lien thong thu [%d] gom cac dinh: ", i);
		for (int j=0; j<g.n; j++){
			if (Nhan[j]==i)
				printf("%d ", j);
		}
		printf("\n");
	}
}


int main(){
	DOTHI g;
	if (DocMTKe(inputfile, g)==1){
		printf("Da doc thanh cong du lieu do thi!\n\n");
		XetLienThong(g);
	}
	return 0;
}
