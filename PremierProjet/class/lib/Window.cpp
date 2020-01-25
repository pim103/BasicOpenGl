#include "../../class/header/Screen.h"
#include "../../class/header/Window.h"


Window::Window() {
	isActive = false;
}

void Window::SetPolygon(Polygon* nPolygon) {
	polygon = nPolygon;
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
	return polygon != nullptr & isActive;
}

vector<Point *> Window::GetAllPoint() {
	vector<Point*> allPoints;
	vector<Segment*> windowSegs = polygon->GetSegments();

	for (int i = 0; i < windowSegs.size() - 1; i++) {
		if (i == 0) {
			allPoints.push_back(windowSegs[i]->getFirstPoint());
			allPoints.push_back(windowSegs[i]->getSecondPoint());
		}
		else {
			allPoints.push_back(windowSegs[i]->getSecondPoint());
		}
	}

	return allPoints;
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

	vector<Point*> allPoints = GetAllPoint();
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