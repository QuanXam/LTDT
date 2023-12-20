#include <stdio.h>
#define MAX 10
#define inputfile "Test4_01.txt"

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

void TimDinhLienThong(DOTHI &g, int nhan[MAX], int i){
	for (int j=0; j<g.n; j++){
		if (g.a[i][j]!=0 && nhan[i]!=nhan[j]){
			nhan[j] = nhan[i];
			TimDinhLienThong(g, nhan, j);
		}
	}
}

int So_TPLT(DOTHI &g){
	int SoTPLT = 0, nhan[MAX];
	for (int i=0; i<g.n; i++)
		nhan[i] = 0;
	for (int i=0; i<g.n; i++)
		if (nhan[i]==0){
			SoTPLT++;
			nhan[i] = SoTPLT;
			TimDinhLienThong(g, nhan, i);
		} 
	return SoTPLT;
}

int ChuaXet[MAX];

typedef struct EDGE{
	int u, v, value;
}CANH;

CANH T[MAX];

void Prim(DOTHI g){
	if (So_TPLT(g)!=1){
		printf("Do thi ko lien thong, dung thuat toan Prim!\n");
		return;
	}
	int nT = 0;
	int ChuaXet[MAX];
	for (int i=0; i<g.n; i++)
		ChuaXet[i] = 0;
	ChuaXet[0] = 1;
	while (nT<g.n-1){
		CANH Canh_NhoNhat;
		int GiaTriNhoNhat = 1000;
		for (int i=0; i<g.n; i++){
			if (ChuaXet[i]==1){
				for (int j=0; j<g.n; j++)
					if (ChuaXet[j]==0 && g.a[i][j]!=0 && GiaTriNhoNhat>g.a[i][j]){
						Canh_NhoNhat.u = i;  
						Canh_NhoNhat.v = j;
						Canh_NhoNhat.value = g.a[i][j];
						GiaTriNhoNhat = g.a[i][j];
					}
			}
		}
		T[nT++] = Canh_NhoNhat;
		ChuaXet[Canh_NhoNhat.v] = 1;
	}
	int TrongSo_KhungCay = 0;
	printf("Cay khung nho nhat cua do thi la \n   ");
	for (int i=0; i<nT-1; i++){
		printf("(%d,%d); ", T[i].u, T[i].v);
		TrongSo_KhungCay += T[i].value;
	}
	printf("(%d,%d)\n", T[nT-1].u, T[nT-1].v);
	TrongSo_KhungCay += T[nT-1].value;
	printf("Tong trong so cua khung cay la: %d\n", TrongSo_KhungCay);
}


int main(){
	DOTHI g;	
	if (DocMTKe(inputfile, g)==1){
		printf("Doc thong tin do thi tu file thanh cong!\n\n");
		XuatMTKe(g);
		Prim(g);
	}
	
	return 0;
}
