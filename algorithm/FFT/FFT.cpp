#define  _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

constexpr int MAX_SIZE = 1 << 21;
constexpr double PI = 3.1415926535897932;

typedef enum TransType { POSITIVE = 1, INVERSE = -1 } Dir;
struct complex{
	double real, imag;
	complex(double xx = 0, double yy = 0) { real = xx, imag = yy; }
};
complex operator + (complex a, complex b) { return complex(a.real + b.real, a.imag + b.imag); }
complex operator - (complex a, complex b) { return complex(a.real - b.real, a.imag - b.imag); }
complex operator * (complex a, complex b) {
	return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}

complex F[MAX_SIZE], G[MAX_SIZE];

inline int read();
inline void swap(complex F[], int i, int j);
void FFT(complex F[], int limit, int type, int rev[]);
void ComplexFFT();
void RealFFT();

int main(void) {
	freopen("test.in", "r", stdin);

	RealFFT();

	return 0;
}

void ComplexFFT() {
	int n = read(), m = read();
	for (int i = 0; i <= n; i++)
		F[i].real = read();
	for (int i = 0; i <= m; i++)
		G[i].real = read();

	int limit = 1, L = 0;
	while (limit <= (n + m)) {
		limit <<= 1;
		L++;
	}
	int* rev = (int*)calloc(limit, sizeof(int));
	for (int i = 0; i < limit; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));

	FFT(F, limit, POSITIVE, rev);
	FFT(G, limit, POSITIVE, rev);
	for (int i = 0; i < limit; i++)
		F[i] = F[i] * G[i];
	FFT(F, limit, INVERSE, rev);
	free(rev);

	for (int i = 0; i <= n + m; i++)
		printf("%d ", (int)(F[i].real + 0.5));
}

void RealFFT() {
	int n = read(), m = read();
	for (int i = 0; i <= n; i++)
		F[i].real = read();
	for (int i = 0; i <= m; i++)
		F[i].imag = read();

	int limit = 1, L = 0;
	while (limit <= (n + m)) {
		limit <<= 1;
		L++;
	}
	int* rev = (int*)calloc(limit, sizeof(int));
	for (int i = 0; i < limit; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));

	FFT(F, limit, POSITIVE, rev);
	for (int i = 0; i < limit; i++)
		F[i] = F[i] * F[i];
	FFT(F, limit, INVERSE, rev);
	free(rev);

	for (int i = 0; i <= n + m; i++)
		printf("%d ", (int)(F[i].imag / 2 + 0.5));
}

void FFT(complex F[], int limit, int type, int rev[]) {
	complex Wm, w, t, u;

	for (int i = 0; i < limit; i++)
		if (i < rev[i])
			swap(F, i, rev[i]);
	for (int m = 2; m <= limit; m <<= 1) {
		Wm = { cos(2 * PI / m), type * sin(2 * PI / m) };
		for (int k = 0; k < limit; k += m) {
			w = { 1, 0 };
			for (int j = 0; j < (m >> 1); j++) {
				t = w * F[k + j + (m >> 1)];
				u = F[k + j];
				F[k + j] = u + t;
				F[k + j + (m >> 1)] = u - t;
				w = w * Wm;
			}
		}
	}
	if (type == INVERSE) {
		for (int i = 0; i < limit; i++) {
			F[i].real /= limit;
			F[i].imag /= limit;
		}
	}
}

inline int read(){
	char c = getchar(); int x = 0, sign = 1;

	while (c < '0' || c> '9'){
		if (c == '-')
			sign = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') { 
		x = x * 10 + c - '0';
		c = getchar(); 
	}
	return sign * x;
}

inline void swap(complex F[], int i, int j) {
	complex temp = F[i];
	F[i] = F[j];
	F[j] = temp;
}