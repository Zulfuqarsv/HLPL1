#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct Point
{
	int x;
	int y;
	Point(int x, int y)
	
	{
		this->x = x;
		this->y = y;
	}
	
};

int main()

{

	vector<Point> points={ Point(1,1), Point(1,2) ,Point(1,3) ,Point(1,4) };
	for (int i = 0; i < points.size(); i++) {
		cout << points[i].x << ":" << points[i].y << "\n";
		
	}

	ofstream of("mydata.txt");
	for (int i = 0; i < points.size(); i++)
	
	{
		of << points[i].x << "\n";
		of << points[i].y << "\n";
		
	}
	
	of.close();

	vector<Point>processed_points;
	ifstream ifs("mydata.txt");
	for (int i = 0; i < points.size(); i++)
	
	{
		Point p(0, 0);
		ifs >> p.x;
		ifs >> p.y;

		processed_points.push_back(p);
	}
	
	
	ifs.close();

	cout << "\n";
	for (int i = 0; i < processed_points.size(); i++)
	
	{
		string err = " ";
		if (processed_points[i].x != points[i].x || processed_points[i].y != points[i].y)
		
		{
			err = " different";
		}
		
		cout << processed_points[i].x << ":" << processed_points[i].y << err << "\n";
	}
	
	return 0;
}
