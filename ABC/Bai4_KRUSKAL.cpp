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

typedef struct canh{
	int u, v, value;
}CANH;

void SapXepTang(CANH E[100], int tongsocanh){
	for (int i=0; i<tongsocanh-1; i++)
		for (int j=0; j<tongsocanh-1; j++)
			if (E[i].value>E[j].value){
				CANH t = E[i];
				E[i] = E[j];
				E[j] = t;
			}
}

void Kruskal(DOTHI g){
	CANH listEdge[MAX];
	int tongsocanh = 0;
	for (int i=0; i<g.n; i++)
		for (int j=0; j<g.n; j++)
			if (g.a[i][j]>0){
				listEdge[tongsocanh].u = i;
				listEdge[tongsocanh].v = j;
				listEdge[tongsocanh].value = g.a[i][j];
				tongsocanh++;
			}
	SapXepTang(listEdge, tongsocanh);
	int nT = 0;
	CANH T[MAX];
	int nhan[MAX];
	for (int i=0; i<g.n; i++)
		nhan[i] = i;
	int canhdangxet = 0;
	while (nT<g.n && canhdangxet<tongsocanh){
		CANH edge = listEdge[canhdangxet];
		int u = nhan[edge.u], v = nhan[edge.v];
		if (u!=v){
			T[nT++] = edge;
			for (int j=0; j<g.n; j++)
				if (nhan[j]==v)
					nhan[j] = u;
		}
		canhdangxet++;
	}
	if (nT!=g.n-1)
		printf("\nDo thi ko lien thong!\n");
	else{
		int TrongSo_CayKhung = 0;
		printf("Cay khung nho nhat cua do thi la\n");
		for (int i=0; i<nT; i++){
			printf("(%d,%d); ", T[i].u, T[i].v);
			TrongSo_CayKhung += T[i].value;
		}
		printf("\nTong trong so cay khung la: %d\n", TrongSo_CayKhung);
	}	
}


int main(){
	DOTHI g;	
	if (DocMTKe(inputfile, g)==1){
		printf("Doc thong tin do thi tu file thanh cong!\n\n");
		XuatMTKe(g);
		Kruskal(g);
	}
	
	return 0;
}
