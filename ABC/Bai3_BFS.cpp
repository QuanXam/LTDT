#include <stdio.h>
#define MAX 10
#define inputfile "Test3_01.txt"

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

int LuuVet[MAX];
int ChuaXet[MAX];

struct QUEUE{
	int size;
	int a[MAX];
};

void Creat_Queue(QUEUE &q){
	q.size = 0;
}

int DayGiaTriVao_Queue(QUEUE &q, int value){
	if (q.size<MAX){
		q.a[q.size++] = value;
		return 1;
	}
	return 0;
}

int LayGiaTriKhoi_Queue(QUEUE &q, int &value){
	if (q.size<=0)
		return 0;
	value = q.a[0];
	for (int i=0; i<q.size-1; i++)
		q.a[i] = q.a[i+1];
	q.size--;
	return 1;
}

int KT_QueueRong(QUEUE q){
	return q.size <= 0;
}

void BFS(int v, GRAPH g){
	QUEUE q;
	Creat_Queue(q);
	DayGiaTriVao_Queue(q, v);
	while (!KT_QueueRong(q)){
		LayGiaTriKhoi_Queue(q, v);
		ChuaXet[v] = 1;
		for (int u=0; u<g.n; u++){
			if (g.a[v][u]!=0 && ChuaXet[u]==0){
				DayGiaTriVao_Queue(q, u);
//				if (LuuVet[u]==-1)  Ping ???
					LuuVet[u] = v;
			}
		}
	}
}

void DuyetTheo_BFS(int S, int F, GRAPH g){
	for (int i=0; i<g.n; i++){
		LuuVet[i] = -1;
		ChuaXet[i] = 0;	
	}
	BFS(S, g);
	if (ChuaXet[F]==1){
		printf("\nDuong di tu dinh [%d] den dinh [%d] la: \n\t", S, F);
		printf("%d ", F);
		int i = LuuVet[F];
		while (i != -1){
			printf("<- %d ", i);
			i = LuuVet[i];
		}
		printf("\n");
	}
	else 
		printf("Ko co duong di tu dinh [%d] den dinh [%d] \n", S, F);
}

int NhapDinh(DOTHI &g, const char *tb){
	int value;
	int done = 0;
	while (!done){
		fflush(stdin);
		printf("%s [0..%d] (-1 = stop): ", tb, g.n-1);
		scanf("%d", &value);
		if (value==-1)
			return -1;
		done = (value>=0 && value<=g.n-1);
	}
	return value;
}


int main(){
	DOTHI g;	
	if (DocMTKe(inputfile, g)==1){
		printf("Doc thong tin do thi tu file thanh cong!\n\n");
		XuatMTKe(g);
		int s, f;
		s = NhapDinh(g, "Nhap dinh bat dau");
		if (s!=-1)
			f = NhapDinh(g, "Nhap dinh ket thuc");
		if (s!=-1 && f!=-1)
			DuyetTheo_BFS(s, f, g);
	}
	
	return 0;
}
