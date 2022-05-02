/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"
#include <string.h>
#include <errno.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ", __FILE__,		\
				__LINE__);				\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

double *copy(int N, double *A) {
	int i,j;
	double *aux = calloc(N * N,sizeof(double));
	DIE(aux == NULL, "calloc aux");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			aux[i * N + j] = A[i * N + j];
		}
	}

	return aux;
}
/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	double *C = calloc(N * N , sizeof(double));
	DIE(C == NULL, "calloc result");
	double *BA = calloc(N * N, sizeof(double));
	DIE(BA == NULL, "calloc BA");
	double *B_tB = calloc(N * N , sizeof(double));
	DIE(B_tB == NULL, "calloc transpusa");

	B_tB = copy(N , B);
	/* B_tB */
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit,
				N, N, 1.0, B, N, B_tB, N);

	
	/*BA */
	/*BA = A */
	BA = copy(N, A);
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit,
				N, N, 1.0, B, N, BA, N);
	
	/* C = B_tB */
	C = copy(N, B_tB);
	/* C = BAA_tA + C*/
	cblas_dgemm(CblasRowMajor,
				CblasNoTrans,
				CblasTrans,
				N,
				N,
				N,
				1.0,
				BA,
				N,
				A,
				N,
				1.0,
				C, N);
	free(BA);
	free(B_tB);
	return C;
}
