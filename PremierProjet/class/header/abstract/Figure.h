#pragma once
#include <iostream>
using namespace std;

class Figure {
private:
public:
	virtual void DrawFigure() {
		cout << "Need Figure to draw" << endl;
	}
};