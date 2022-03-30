#include "std_lib_facilities.h"

class Complex {
public:
	int real, 
	Complex(tempReal = 0, tempImaginary = 0)
	{
		re = tempReal;
		im = tempImaginary;
	}
	Complex addComp(Complex C1, Complex C2)
	{
		Complex temp;
		temp.re = C1.re + C2.re;
		temp.im = C1.im + C2.im;
		return temp;
	}
};
	double modulus(Complex c);
	
private:
	double re = 0;
	double im = 0;
};

	int main()
	{
		std::complex<double> Complex(10.0, 2.0);
		cout << "Real part: " << re(Complex) << endl;
		cout << "Imaginary part: " << im(Complex) << endl;
		return 0;
	}