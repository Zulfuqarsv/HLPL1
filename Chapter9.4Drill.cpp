#include "std_lib_facilities.h"


namespace Chrono
{
enum class Month
{
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month operator+(const Month& m, int n)

{
	
int r=int(m)+n;

r%=int(Month::dec);

if(r== 0) return Month::dec;  
return Month(r);
}

Month operator-(const Month& m, int n) 
                       {return (m+(-n)); }

Month& operator+=(Month& m, int n) 
                       {m= m +n; return m; }

bool operator<(const Month& m, int n)
                       { return int(m)< n;}

bool operator>(const Month& m, int n) 
                       { return int(m)> n; }

class Date
{
public:
class Invalid {};
Date(int yy, Month mm, int dd);
void add_day(int n);
Month month() const 
{ return m; }

int day() const 
{ return d; }

int year() const 
{ return y; }

private:
int y;
Month m;
int d;
bool is_valid();
};

Date::Date(int yy, Month mm, int dd)
:y{yy}, m{mm}, d{dd}
{
    if (!is_valid()) throw Invalid{};
}

bool Date::is_valid()

{
if(d< 1 || d> 31) return false;
if (m< Month::jan || m > Month::dec) return false;
return true;
}

void Date::add_day(int n)

{

int n_d = n% 31;
int n_m = (n/ 31) % 12;
int n_y = n /(31*12);
d += n_d;

if (d >31) { ++n_m;d -= 31; }
if (d < 1)  {--n_m; d += 31; }
 
if (Month::dec< (int(m)+n_m)) ++n_y;
if (Month::jan > (int(m)+n_m))--n_y;
m +=n_m;
y+= n_y;
}

ostream& operator<<(ostream& os, const Date& d)
{
return os <<'('<< d.year()
          <<','<< int(d.month())
          <<','<< d.day()
		  << ')';
}

};

int main()
try

{
	
using Chrono::Date;
using Chrono::Month;

Date today{1978, Month::jun, 25};
Date tomorrow{today};
tomorrow.add_day(1);


cout << "Today: " << today << '\n';
cout << "Tomorrow: " << tomorrow << '\n';

    
Date test{2015, Month::may, 6};

test.add_day(8);
cout << "May 14 2015? " << test << '\n';

test.add_day(-19);
cout << "April 26 2015? "<< test<< '\n';

test = Date{2022, Month::may, 7};
test.add_day(-7);
cout << "April 31 2022? " <<test << '\n';

test.add_day(+29);
cout <<"May 29 2022? " <<test << '\n';

test.add_day(+2400);
cout<< "Nearly 6 years later? "<< test << '\n';

test.add_day(-1825); 
cout <<"Nearly 5 years before? " << test << '\n';

Date today_e{2002, Month::jun, -7};

return 0;
}

catch(exception& e)

{
cerr<< e.what() << '\n';
return 1;
}

catch(Chrono::Date::Invalid)

{
cerr <<"Invalid date(negative)!\n";
return 2;
}

catch(...)

{
cerr << "Unknown exception!!\n";
return 3;
}
