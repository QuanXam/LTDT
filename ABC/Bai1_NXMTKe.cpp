#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define inputfile "Test1_02.txt"

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

void XuatMTKe(DOTHI g){
	printf("So dinh cua do thi la: %d", g.n);
	printf("\nMa tran ke cua do thi la:\n");
	for (int i=0; i<g.n; i++){
		printf("  ");
		for (int j=0; j<g.n; j++)
			printf("%3d ", g.a[i][j]);
		printf("\n");
	}
}

int KTMTKe_HopLe(DOTHI g){
	for (int i=0; i<g.n; i++){
		if (g.a[i][i] != 0)
			return 0;
	}
	return 1;
}

int KTDOTHI(DOTHI g){
	for (int i=0; i<g.n; i++){
		for (int j=0; j<g.n; j++){
			if (g.a[i][j] != g.a[j][i])
				return 0;
		}
	}
	return 1;
}


int main(){
	DOTHI g;
	if (DocMTKe(inputfile, g)==1){
		printf("Doc thong tin do thi tu file thanh cong!\n\n");
		XuatMTKe(g);
		printf("Do thi co mt ke: %s", KTMTKe_HopLe(g)==1?"Hop le!":"Ko hop le!");
		printf("\nDo thi thuoc dang: %s", KTDOTHI(g)==1?"Vo huong!":"Co huong!");
	}
	
	return 0;
}
