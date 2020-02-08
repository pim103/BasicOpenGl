#include "../../class/header/Screen.h"
#include "../../class/header/Window.h"
#include "../../class/header/Utils.h"

using namespace std;

Window::Window() {
	isActive = false;
}

void Window::SetPolygon(Polygon* nPolygon) {
	polygon = nPolygon;
	polygon->SetIsWindowPoly(true);
}

void Window::RemovePolygon() {
	polygon = nullptr;
	SetActive(false);
}

void Window::DrawFigure() {
	if (polygon != nullptr) {
		polygon->DrawFigure();
	}
}

void Window::SetActive(bool toggle) {
	isActive = toggle;
}

bool Window::CheckIfIsActive() {
	return (polygon != nullptr) & isActive;
}

vector<float*> Window::GetAllNormale() {
	vector<Segment*> windowSegs = polygon->GetSegments();
	vector<float *> normales;

	for each (Segment * seg in windowSegs)
	{
		normales.push_back(seg->GetNormale());
	}

	return normales;
}

float* Window::ApplyScreen(Segment *seg) {
	vector<Segment*> windowSegs = polygon->GetSegments();
	int segsSize = windowSegs.size();

	vector<Point*> allPoints = this->polygon->GetAllPoint();
	vector<float*> allNormale = GetAllNormale();

	Point* A = seg->getFirstPoint();
	Point *B = seg->getSecondPoint();

	float t, tinf, tsup;
	float DX, DY, WN, DN;
	Point* C;
	int i;

	float* coord = new float[4];
	coord[0] = A->getX() + 1;
	coord[1] = A->getY() + 1;
	coord[2] = B->getX() + 1;
	coord[3] = B->getY() + 1;

	tinf = 0;
	tsup = 1;
	DX = (B->getX() + 1) - (A->getX() + 1);
	DY = (B->getY() + 1) - (A->getY() + 1);

	for (int i = 0; i < segsSize; i++) {
		C = allPoints[i];
		DN = DX * allNormale[i][0] + DY * allNormale[i][1];
		WN = (coord[0] - (C->getX() + 1)) * allNormale[i][0] + (coord[1] - (C->getY() + 1)) * allNormale[i][1];

		if (DN == 0) {
			cout << "DN == 0" << endl;
			return nullptr;
		}

		t = -WN / DN;

		if (DN > 0) {
			if (t > tinf) {
				tinf = t;
			}
		}
		else {
			if (t < tsup) {
				tsup = t;
			}
		}
	}

	if (tinf < tsup) {
		if ((tinf < 0) && (tsup > 1)) {
			cout << "intern" << endl;
			return coord;
		}
		else {
			if ((tinf > 1) || (tsup < 0)) {
				cout << "Extern tinf : " << tinf << " tsup : " << tsup << endl;
				return nullptr;
			}
			else {
				if (tinf < 0) {
					tinf = 0;
				}
				else {
					if (tsup > 1) {
						tsup = 1;
					}
				}

				coord[2] = coord[0] + DX * tsup;
				coord[3] = coord[1] + DY * tsup;
				coord[0] = coord[0] + DX * tinf;
				coord[1] = coord[1] + DY * tinf;
			}
		}
	}
	else {
		cout << "tinf > tsup : tinf => " << tinf << " tsup => " << tsup << endl;
		return nullptr;
	}

	return coord;
}

// Function to calculate the max from a vector of floats 
float max(vector<float> t)
{
	float maximum = INT_MIN;
	for (int i = 0; i < t.size(); i++)
		if (t[i] > maximum)
			maximum = t[i];
	return maximum;
}

// Function to calculate the min from a vector of floats 
float min(vector<float> t)
{
	float minimum = INT_MAX;
	for (int i = 0; i < t.size(); i++)
		if (t[i] < minimum)
			minimum = t[i];
	return minimum;
}

/*
float* Window::ApplyScreen(Segment* seg) {
	vector<Segment*> windowSegs = polygon->GetSegments();
	int segsSize = windowSegs.size();

	vector<Point*> allPoints = GetAllPoint();
	vector<float*> allNormale = GetAllNormale();

	Point* A = seg->getFirstPoint();
	Point* B = seg->getSecondPoint();

	vector<float*> normal;

	for (int i = 0; i < segsSize; i++) {
		float* newNormal = new float[2];
		newNormal[0] = (allPoints[i]->getY() + 1) - (allPoints[(i + 1) % segsSize]->getY() + 1);
		newNormal[1] = (allPoints[(i + 1) % segsSize]->getX() + 1) - (allPoints[i]->getX() + 1);

		normal.push_back(newNormal);
	}

	float* p1_p0 = new float[2];
	p1_p0[0] = (B->getX() + 1) - (A->getX() + 1);
	p1_p0[1] = (B->getY() + 1) - (A->getY() + 1);

	vector<float*> p0_pei;

	for (int i = 0; i < segsSize; i++) {
		float* calcul = new float[2];
		calcul[0] = (allPoints[i]->getX() + 1) - (A->getX() + 1);
		calcul[1] = (allPoints[i]->getY() + 1) - (B->getY() + 1);
		
		p0_pei.push_back(calcul);
	}

	float* numerator = new float[segsSize];
	float* denominator = new float[segsSize];

	for (int i = 0; i < segsSize; i++) {
		numerator[i] = allNormale[i][0] * p0_pei[i][0] + allNormale[i][1] * p0_pei[i][1];
		denominator[i] = allNormale[i][0] * p1_p0[0] + allNormale[i][1] * p1_p0[1];
	}

	float* t = new float[segsSize];
	vector<float> tE, tL;

	for (int i = 0; i < segsSize; i++) {
		t[i] = (float)(numerator[i]) / (float)(denominator[i]);

		if (denominator[i] > 0) {
			tE.push_back(t[i]);
		}
		else {
			tL.push_back(t[i]);
		}
	}

	float temp[2];
	tE.push_back(0.f);
	temp[0] = max(tE);

	tL.push_back(1.f);
	temp[1] = min(tL);

	if (temp[0] >= temp[1]) {
		cout << "Extern " << temp[0] << " " << temp[1] << endl;
		return nullptr;
	}

	float* coord = new float[4];
	coord[0] = (float)A->getX() + (float)p1_p0[0] * (float)temp[0];
	coord[1] = (float)A->getY() + (float)p1_p0[1] * (float)temp[0];
	coord[2] = (float)B->getX() + (float)p1_p0[0] * (float)temp[1];
	coord[3] = (float)B->getY() + (float)p1_p0[1] * (float)temp[1];

	//cout << "p1Po " << p1_p0[0] << " " << p1_p0[1] << " temp " << temp[0] << " " << temp[1] << endl;
	//cout << coord[0] << " " << coord[1] << " " << coord[2] << " " << coord[3] << endl;

	return coord;
}*/

// calculate intersection point
Point* intersection(Point *point1, Point* point2, Point* point3, Point* point4)
{
	float x1 = point1->getX();
	float y1 = point1->getY();
	float x2 = point2->getX();
	float y2 = point2->getY();
	float x3 = point3->getX();
	float y3 = point3->getY();
	float x4 = point4->getX();
	float y4 = point4->getY();

	float* dc = new float[2];
	float* dp = new float[2];

	dc[0] = x1 - x2;
	dc[1] = y1 - y2;

	dp[0] = x3 - x4;
	dp[1] = y3 - y4;

	float n1 = x1 * y2 - y1 * x2;
	float n2 = x3 * y4 - y3 * x4;
	float n3 = 1.0 / (dc[0] * dp[1] - dc[1] * dp[0]);

	Point* intersectionPoint = new Point((n1 * dp[0] - n2 * dc[0]) * n3, (n1 * dp[1] - n2 * dc[1]) * n3);
	return intersectionPoint;
}

bool inside(Point *point1, Point* point2, Point *point, bool wasReversed) {
	float x = point->getX();
	float y = point->getY();

	float x1 = point1->getX();
	float y1 = point1->getY();
	float x2 = point2->getX();
	float y2 = point2->getY();

	double* coords = new double[2];
	coords = Utils::ConverOpenGlToMouseClickCoord(nullptr, x, y);

	double* coords1 = new double[2];
	coords1 = Utils::ConverOpenGlToMouseClickCoord(nullptr, x1, y1);

	double* coords2 = new double[2];
	coords2 = Utils::ConverOpenGlToMouseClickCoord(nullptr, x2, y2);

	double val = (coords2[1] - coords1[1]) * coords[0] + (coords1[0] - coords2[0]) * coords[1] + (coords2[0] * coords1[1] - coords1[0] * coords2[1]);

	if (wasReversed) {
		return val > 0;
	}
	else {
		return val < 0;
	}

}

void Window::ApplyScreenShuterlandHodgman(Polygon* poly) {
	int counter = 0;

	//TODO REBASE ALL COORD TO 0 - 2 And not to -1 - 1 
	vector<Point*> subjectPoints = poly->GetAllPoint();
	vector<Point*> windowPoints = polygon->GetAllPoint();

	vector<Point*> newPolyPoints;
	vector<Point*> inputPoints;

	int subjectSize = subjectPoints.size();
	int windowSize = windowPoints.size();

	Point* cp1;
	Point* cp2;
	Point* s;
	Point* e;

	bool insideE, insideS;

	bool wasReversed = false;
	bool isEnd = false;

	while (!isEnd) {
		subjectSize = subjectPoints.size();
		windowSize = windowPoints.size();
		newPolyPoints.clear();
		inputPoints.clear();
		newPolyPoints.resize(99);
		inputPoints.resize(99);

		for (int i = 0; i < subjectSize; i++) {
			newPolyPoints[i] = subjectPoints[i];
		}
		for (int i = 0; i < windowSize; i++) {
			for (int j = 0; j < subjectSize; j++) {
				inputPoints[j] = newPolyPoints[j];
			}

			counter = 0;
			cp1 = windowPoints[i];
			cp2 = windowPoints[(i + 1) % windowSize];

			for (int j = 0; j < subjectSize; j++) {
				s = inputPoints[j];
				e = inputPoints[(j + 1) % subjectSize];

				insideE = inside(cp1, cp2, e, wasReversed);
				insideS = inside(cp1, cp2, s, wasReversed);

				if (insideS && insideE) {
					newPolyPoints[counter] = e;
					counter++;
				}
				else if (!insideS && insideE) {
					newPolyPoints[counter] = intersection(cp1, cp2, s, e);
					counter++;
					newPolyPoints[counter] = e;
					counter++;
				}
				else if (insideS && !insideE) {
					newPolyPoints[counter] = intersection(cp1, cp2, s, e);
					counter++;
				}
			}

			subjectSize = counter;
		}

		if (!wasReversed && counter < 1) {
			wasReversed = true;
		}
		else {
			isEnd = true;
		}
	}

	if (counter > 0) {
		Segment* seg = nullptr;
		float* color = poly->GetColor();

		for (int i = 0; i < counter - 1; i++) {
			seg = new Segment(newPolyPoints[i], newPolyPoints[i + 1]);
			seg->SetColor(color);
			seg->DrawFigure();
		}

		seg = new Segment(newPolyPoints[counter - 1], newPolyPoints[0]);
		seg->SetColor(color);
		seg->DrawFigure();
	}
}