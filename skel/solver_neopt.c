/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
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
/*
 * Add your unoptimized implementation here
 */

/* Calculam BA,
	B - matrice normala,
	A - matrice superior triunghiulara
*/
void matrix_multiply1(int N, double *A, double *B, double *result) {
	int i, j, k;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= j; k++) {
				result[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}
}

/* Calculam C = XA_t,
	X = BA - matrice normala,
	A_t - matrice inferior triunghiulara
*/
void matrix_multiply2(int N, double *A, double *B, double *result) {
	int i, j, k;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = j; k < N; k++) {
				result[i * N + j] += B[i * N + k] * A[j * N + k];
			}
		}
	}
}

double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	/* alocare memorie */
	double *BA = calloc(N * N, sizeof(double));
	DIE(BA == NULL, "calloc BA");
	double *C = calloc(N * N, sizeof(double));
	DIE(C == NULL, "calloc C");
	double *D = calloc(N * N, sizeof(double));
	DIE(D == NULL, "calloc D");
	matrix_multiply1(N, A, B, BA);
	/* C = BAA_t */
	matrix_multiply2(N, A, BA, C);
	/* C = C + D
	unde D = B_t * B */
	int i, j ,k;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				D[i * N + j] += B[i * N + k] * B[j * N + k];
			}
			C[i * N + j] += D[i * N + j];
		}
	}
	free(BA);
	free(D);
	return C;
}
