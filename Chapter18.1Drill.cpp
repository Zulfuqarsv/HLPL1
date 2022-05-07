#include "std_lib_facilities.h"


void print_array(const int gl[], int n)

{
for (int i = 0; i<n; ++i) cout << gl[i] <<"\n";
}

const int garray=10;

int ga[garray]={1,2,4,8,16,32,64,128,256,512};

void f(int gl[],int n)
{
const int larray=10;
int la[larray];
for(int i=0;i<larray;++i)
{
la[i]=ga[i];	
}
cout<<"\n";
print_array(la,larray);
cout<<"\n";

int* p =new int[n];

for(int i=0;i<n;++i)

{
p[i]=gl[i];
}

print_array(p,n);
cout<<"\n";
delete[] p;
}

int main()
try
{
f(ga,garray);
const int larray=10;
int aa[larray]={1};
for(int i=1;i<larray;++i)

{
aa[i]=(i+1)*aa[i-1];	
}

f(aa,larray);
}

catch(exception& e)

{
cerr<<"exception: "<<e.what()<<endl;
}

catch(...)
{
cerr<<"exception\n"<<"\n";
}
