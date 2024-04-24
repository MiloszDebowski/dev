#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>

using namespace std;


class rectangle
{
private:
	double height,base;
public:
	void setHeight(double height0){ height = height0; }
	double getHeight() { return height; }
	double getBase() { return base; }
	void setBase(double base0){ base = base0; }
};






int main()
{
	int figureCount = 4;
	rectangle* Rectangles = new rectangle[figureCount];
	double a = 0.5;
	double b = 2.5;
	for (int i = 0; i < figureCount; i++)
	{
		Rectangles[i].setBase((b-a)/figureCount);
		cout << endl << "Base:" << Rectangles[i].getBase() << endl;
		Rectangles[i].setHeight(sin((Rectangles[i].getBase()*(i+1))+(Rectangles[i].getBase()/2)));
		cout << endl << "Height:" << Rectangles[i].getHeight() << endl;
	}
	
	double solution;
	double sum = 0.0;
	for (int i = 0; i < figureCount; i++)
	{
		sum += Rectangles[i].getHeight();
	}
	solution = sum * Rectangles[0].getBase();
	cout << solution;
	
	delete[] Rectangles;
	return 0;
}