#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define M 1000 //satir deðeri
#define N 1000 //sütun deðeri
#define thread_sayi 4
int main()
{
	static double  A[M][N],
		B[M][N],
		C[M][N];
	double baslangic_z, bitis_z;
	double paralel_toplam_sure;
	double top = 0;
	int i, j, k;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = 1; //matrise random olarak deðer atamak için 1 yerine rand()%5 yazýlabilir. deðerler={0,1,2,3,4} olabilir. 
			B[i][j] = 1;
		}
	}
	//paralel olarak M*N'lik 2 matrisin çarpýmý
	baslangic_z = omp_get_wtime();
	omp_set_num_threads(thread_sayi);
#pragma omp parallel 
	{
#pragma omp for schedule(static)
		for (i = 0; i < M; i++)
		{

			for (k = 0; k < N; k++)
			{

				for (j = 0; j < N; j++)
				{
					top += A[i][j] * B[j][j];
				}
				C[i][k] = top;
				printf("%.0lf\t", C[i][k]);
				top = 0;
			}
			printf("\n");
		}
	}
	bitis_z = omp_get_wtime();
	paralel_toplam_sure = bitis_z - baslangic_z;
	//paralel sonuç
	printf("sure:%f(sn)\n", paralel_toplam_sure);
	return 0;
}