#include <stdio.h>
#define MAX 10
#define VOCUC 1000
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

int Sau_Nut[MAX][MAX];
int L[MAX][MAX];

void Floyd(DOTHI g){
	for (int i=0; i<g.n; i++){
		for (int j=0; j<g.n; j++){
			if (g.a[i][j]>0){
				Sau_Nut[i][j] = j;
				L[i][j] = g.a[i][j];
			}
			else{
				Sau_Nut[i][j] = -1;
				L[i][j] = VOCUC;
			}
		}
	}
	for (int k=0; k<g.n; k++){
		for (int i=0; i<g.n; i++){
			for (int j=0; j<g.n; j++){
				if (L[i][j]>L[i][k]+L[k][j]){
					L[i][j] = L[i][k] + L[k][j];
					Sau_Nut[i][j] = Sau_Nut[i][k];
				}
			}
		}
	}
	int S, F;
	printf("Nhap vao dinh bat dau: ");
	scanf("%d", &S);
	printf("Nhap vao dinh ket thuc: ");
	scanf("%d", &F);
	if (Sau_Nut[S][F]==-1)
		printf("Ko co duong di tu dinh [%d] den dinh [%d]\n", S, F);
	else{
		printf("duong di ngan nhat tu dinh [%d] den dinh [%d] la:\n", S, F);
		printf("\t%d", S);
		int u = S;
		while (Sau_Nut[u][F]!=F){
			u = Sau_Nut[u][F];
			printf(" --> %d", u);
		}
		printf(" --> %d", F);
		printf("\n~Voi tong trong so la: %d", L[S][F]);
	}
}


int main(){
	DOTHI g;	
	if (DocMTKe(inputfile, g)==1){
		printf("Doc thong tin do thi tu file thanh cong!\n\n");
		XuatMTKe(g);
		Floyd(g);
	}
	
	return 0;
}
