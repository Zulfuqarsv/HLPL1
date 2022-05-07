#include "std_lib_facilities.h"

const char number = '8';
const char quit   = 'q';
const char print  = '=';
const char name   = 'a';
const char let    = 'L'; 
const string declkey = "let";
const string result  = "= ";
const string prompt  = "> ";

constexpr char sqrttoken = 'S';
const string sqrtkey = "sqrt";

constexpr char powtoken = 'P';
const string powkey="pow";

const string quitkey = "exit";

double sqrt_calculation();
double pow_calculation();
double expression();

class Variable {
	
	public:
	string name;
	double value;
};

vector<Variable>var_table;
double get_value(string s)
{
	for (int i = 0; i<var_table.size(); ++i)
       if (var_table[i].name == s) return var_table[i].value;
    error("get: undefined variable ", s);

}


void set_value(string s, double d)
{
	for (int i = 0; i<var_table.size(); ++i)
        if (var_table[i].name == s) {
            var_table[i].value = d;
            return;
        }
    error("set: undefined variable ", s);}


bool is_declared(string var)
{
	for (int i = 0; i<var_table.size(); ++i)
      if (var_table[i].name == var) return true;
    return false;

}

double define_name (string var, double val)
{
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable{var,val});
	return val;

}


class Token
{
    public:
	char kind;
	double value;
	string name;
	Token(): kind(0) {}
	Token(char ch):             kind(ch), value(0) {}
	Token(char ch, double val): kind(ch), value(val) {}
	Token(char ch, string n):   kind(ch), name(n) {}
};

class Token_stream
{

public:
	Token_stream();
	void putback(Token t);
	Token get();
    void ignore(char c);
private:
	bool full;
	Token buffer;
};


Token_stream::Token_stream() :full(false), buffer(0){}

void Token_stream::putback(Token t)

{
	if (full) error("putback() into full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full)
	{
	full = false;
	return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch)
	
{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case print:
	case name:
	case quit:
	case ',':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		
	{	cin.putback(ch);
	double val;
	cin >> val;
	return Token(number, val);
	}
	
	default:
		{
		 if(isalpha(ch))
		 {
		 
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
            cin.putback(ch);
            if (s == declkey) return Token(let);
            
            else if (s == sqrtkey) return Token(sqrttoken);
            
    		else if (s==powkey) return Token(powtoken);
    		
    		else if (s == quitkey) return Token(quit);
    		
				else if (is_declared(s))
				return Token(number, get_value(s));
            return Token(name,s);
        }
        
		error("Bad token");
	}
	
	return 0;
}
}



void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch=0;
	while (cin >> ch)
		if (ch == c) return;
}



Token_stream ts;


double expression();
double sqrt_calculation()
{
    char ch;
    if (cin.get(ch) && ch != '(')
        error("'(' is required at starting of sqrt");
    cin.putback(ch);

    double d = expression();
    if(d < 0) error("negative value can not be under sqrt");
    return sqrt(d);

}
double pow_calculation()
{
    Token t = ts.get();
    if (t.kind != '(') error("'(' is expected in starting of pow");
    
    double base = expression();

    t = ts.get();
    if (t.kind != ',') error("',' expected in after base in pow");

    double temp_exponent = expression();
    int exponent = narrow_cast<int>(temp_exponent);

    t = ts.get();
    if (t.kind != ')') error("')' is expected at the ending of power formula");

    return pow(base, exponent);
}

   double primary()
   {
   	
	Token t = ts.get();
    switch (t.kind)
	{
    case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
	
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case '+':
		return primary();
	case sqrttoken:
        return sqrt_calculation();
    case powtoken:
    	return pow_calculation();
    default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	
	while(true)
	{
        switch (t.kind)
		{
		
		case '*':
		 {
		left *= primary();
		t = ts.get();
		break;
	     }
		case '/':
		{	
		double d = primary();
		if (d == 0) error("division by zero");
		left /= d;
		t = ts.get();
		break;
		}
		case '%':
        {
        double d = primary();
		if (d == 0) error("%: division by zero");
		left = fmod (left, d);
		t = ts.get();
		break;
        }
		
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression()
{
	
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		
		case '+':
			left += term();
			t = ts.get();
			break;
		
		case '-':
			left -= term();
			t = ts.get();
			break;
		
		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
    if (t.kind != name) error ("Name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("= Missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name,d);
    return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}
 
void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit)
		{
			keep_window_open();
			return ;}
		ts.putback(t);
		cout <<result << statement() << endl;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}



int main()

try
{
	cout << "Welcome to calculator\n";
    cout << "There is a list of operators:\n";
    cout << "Addition is  '+'" << endl;
	cout << "Subtraction is  '-'" << endl;
	cout << "Multiplication is  '*'"<< endl;
	cout << "Division is  '/'" << endl;
	cout << "Modulo is  '%'" << endl;
	cout << "Squareroot is 'sqrt()'" << endl;
	cout << "Power is 'pow(base,exponent)'" << endl;
	cout << "Result is '='" << endl;
	cout << "Use let to make the variables" << endl;
	cout << "Enter a 'q' to exit" << endl;
	cout << "Please write an expression:";
	define_name("k", 1000);
	calculate();
	keep_window_open();
	return 0;
}
catch (runtime_error& e)
{
    cerr << e.what() << endl;
    keep_window_open("~~");
    return 1;
} 
catch (...)
{
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
}
/*
Grammar:
	
	Calculation:
		Statement
		Print
		Quit
		Calculation Statement
	Print:
		=
	Quit:
		q
	Statement:
		Declaration
		Expression
	Declaration:
		"let" Name "=" Expression
	Name:
		string literal
	Expression:
		Term
		Expression + Term
		Expression – Term
	Term:
		Primary
		Term * Primary
		Term / Primary
		Term % Primary
	Primary:
		Number
		( Expression )
		– Primary
		+ Primary
	Number:
		floating-point-literal
*/
