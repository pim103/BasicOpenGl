#pragma once
#include <iostream>
using namespace std;

enum TypeFigure
{
	SEGMENT,
	POLYGON,
	WINDOW
};

class Figure {
private:
public:
	TypeFigure type = SEGMENT;

	virtual void DrawFigure() {
		cout << "Need Figure to draw" << endl;
	}
};