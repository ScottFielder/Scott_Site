#include <math.h>
#include "Fourier.h"

#define PI 3.141592653589793238462643383279502884197

/// This is my C++ interpretation of the original Fortran algorithm - SSF
/// The input is a 2*n (n being the number of sample points) array of floating
/// point values. The int "length" the actual length of the entire array (2*n).  
/// The real and imaginary components of the input are data[0] - real and data[1] -
/// imaginary; data[2] - real, data[3] - imaginary. 
/// In math terms it is: data[even] + i*data[odd]
/// If the data is a sampled set, then let data[even] be those values and let data[odd]
/// be zero (0.0). 

void Fourier::fft(FLOAT* data, const int length, const DIRECTION direction){
	int i, j;
	int n, mmax, m, istep;
	FLOAT tempreal, tempimg, wreal, wtemp, wpreal, wpimg, wimg;
	FLOAT theta, sign;

	sign = (FLOAT)direction;
	int nn = length / 2;/// As mentioned above nn is the length of the data sample
	n = nn << 1;		/// Cute trick - too sexy for me

	/// This part is called the bit-reversal - it does the exchange of two complex numbers
	j = 1;
	for (i = 1; i<n; i += 2) {  
		if (j > i) {
			wtemp = data[j - 1], data[j - 1] = data[i - 1], data[i - 1] = wtemp;///swap (data[j - 1], data[i - 1]);
			wtemp = data[j], data[j] = data[i], data[i] = wtemp;				///swap (data[j], data[i]);
		}
		m = nn;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}

	/// This is the Danielson-Lanczos part of the FFT process
	mmax = 2;
	while (n > mmax) {
		istep = mmax << 1;
		
		theta = sign*(6.28318530717959 / mmax);
		wtemp = sin(0.5*theta);
		wpreal = -2.0*wtemp*wtemp;
		wpimg = sin(theta);
		wreal = 1.0;
		wimg = 0.0;
		for (m = 1; m<mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j = i + mmax;
				tempreal = wreal*data[j - 1] - wimg*data[j];
				tempimg = wreal*data[j] + wimg*data[j - 1];
				data[j - 1] = data[i - 1] - tempreal;
				data[j] = data[i] - tempimg;
				data[i - 1] += tempreal;
				data[i] += tempimg;
			}
			wreal = (wtemp = wreal)*wpreal - wimg*wpimg + wreal;
			wimg = wimg*wpreal + wtemp*wpimg + wimg;
		}
		mmax = istep;
	}

#undef PI
}