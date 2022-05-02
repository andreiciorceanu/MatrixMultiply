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
 * Add your optimized implementation here
 */

/* Calculam BA,
	B - matrice normala,
	A - matrice superior triunghiulara
*/
void matrix_multiply1(int N, double *A, double *B, double *result) {
	register int i, j, k;
	register double *orig_pa;
	register double *pa;
	register double *pb;
	register double suma;

	for (i = 0; i < N; i++) {
		orig_pa = B + i * N;

		for (j = 0; j < N; j++) {
			pa = orig_pa + i;
			pb = A + i * N + j;
			suma = 0;

			for (k = 0; k <= j; k++) {
				suma += *pa * *pb;
				pa++;
				pb++;
			}
			result[i * N + j] = suma;
		}
	}
}

/* Calculam C = XA_t,
	X = BA - matrice normala,
	A_t - matrice inferior triunghiulara
*/
void matrix_multiply2(int N, double *A, double *B, double *result) {
	register int i, j, k;
	register double *orig_pa;
	register double *pa, *pb;
	register double suma;

	for (i = 0; i < N; i++) {
		orig_pa = B + i * N;
		for (j = 0; j < N; j++) {
			pa = orig_pa + j;
			pb = A + j * (N + 1);
			suma = 0;
			
			for (k = j; k < N; k++) {
				suma += *pa * *pb;
				pa++;
				pb++;
			}
			result[i * N + j] = suma;
		}
	}
}

double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	/* alocare memorie */
	double *BA = calloc(N * N, sizeof(double));
	DIE(BA == NULL, "calloc BA");
	double *C = calloc(N * N, sizeof(double));
	DIE(C == NULL, "calloc C");
	matrix_multiply1(N, A, B, BA);
	/* C = BAA_t */
	matrix_multiply2(N, A, BA, C);
	/* C = C + D
	unde D = B_t * B */
	register int i, j ,k;
	register double *orig_pa;
	register double *pa, *pb;
	register double suma;

	for (i = 0; i < N; i++) {
		orig_pa = B + i * N;
		for (j = 0; j < N; j++) {
			pa = orig_pa + j;
			pb = B + j * (N + 1);
			suma = 0;
			for (k = 0; k < N; k++) {
				suma += *pa * *pb;
				pa++;
				pb++;
			}
			C[i * N + j] = C[i * N + j] + suma;
		}
	}
	free(BA);
	return C;	
}
