
#define FLOAT float
class Fourier {
public:
	static enum DIRECTION : int {
		FORWARD = 1,
		REVERSE = -1
	};
	void static fft(FLOAT* data, const int length, const DIRECTION direction);

};