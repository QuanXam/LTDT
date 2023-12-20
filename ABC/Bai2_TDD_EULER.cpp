#include <stdio.h>
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

struct STACK{
	int a[100];
	int size;
};

void Creat_Stack(STACK &s){
	s.size = 0;
}

void DayGiaTriVao_Stack(STACK &s, int value){
	if (s.size<100){
		s.a[s.size] = value;
		s.size++;
	}
}

void TimDuongDi(int i, DOTHI &g, STACK &s){
	for (int j=0; j<g.n; j++){
		if (g.a[i][j]!=0){
			g.a[i][j] = g.a[j][i] = 0;
			TimDuongDi(j, g, s);
		}
	}
	DayGiaTriVao_Stack(s, i+1);
}

int BacDinh(DOTHI &g, int v){
	int bac = 0;
	for (int i=0; i<g.n; i++){
		if (g.a[v][i]!=0)
			bac++;
	}
	return bac;
}

int TimDuongDi_Euler(DOTHI g){
	int x=0;
	int dem=0;
	int timthay=0;
	for (int i=0; i<g.n; i++){
		if (BacDinh(g, i)%2 != 0){
			x=i;
			dem++;
			if (timthay==0)
				timthay =1;
		}
	}
	
	if (!timthay || dem!=2)
		return 0;
	DOTHI t = g;
	STACK s;
	Creat_Stack(s);
	TimDuongDi(x, t, s);
	
	for (int i=0; i<g.n; i++){
		for (int j=0; j<g.n; j++){
			if (t.a[i][j]!=0 || t.a[j][i]!=0)
				return 0;
		}
	}
	if (s.a[0]==s.a[s.size-1])
		return 0;
	printf("\nDuong di Euler: ");
	while (s.size!=0){
		printf("%d ", s.a[--s.size]);
	}
	return 1;
}


int main(){
	DOTHI g;
	if (DocMTKe(inputfile, g)==1){
		printf("Doc thong tin do thi tu file thanh cong!\n\n");
		XuatMTKe(g);
		if (!TimDuongDi_Euler(g))
			printf("\nKo co duong di Euler trong do thi!\n");
	}
	
	return 0;
}
