#include<iostream>
using namespace std;


void swap_v(int a, int b)
{
	int temp; temp=a, a=b; b=temp;
}

void swap_r(int& a, int& b)
{
	int temp; temp=a, a=b; b=temp;
}

void swap_cr(const int& a, const int& b) {}

int main() {

	int x=7;
	int y=9;
	swap_v(x, y);

	printf("x: %d, y: %d\n", x, y);

	swap_cr(7, 9);
	const int cx=7;
	const int cy=9;
	printf("cx: %d, cy: %d\n", cx, cy);
	swap_cr(cx, cy);
	printf("cx: %d, cy: %d\n", cx, cy);
	swap_v(7.7, 9.9);
	double dx=7.7;
	double dy=9.9;
	swap_v(dx, dy);
	swap_cr(7.7, 9.9);
	printf("dx: %l, dy: %l\n", x, y);
}
