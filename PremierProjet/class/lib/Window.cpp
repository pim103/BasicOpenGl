#include "../../class/header/Screen.h"
#include "../../class/header/Window.h"
#include "../../class/header/Utils.h"

using namespace std;

Window::Window() {
	isActive = false;
	type = TypeFigure::WINDOW;
}

void Window::SetPolygon(Polygon* nPolygon) {
	polygon = nPolygon;
	polygon->SetIsWindowPoly(true);
}

Polygon* Window::GetPolygon() {
	return polygon;
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

				insideE = Utils::inside(cp1, cp2, e, wasReversed);
				insideS = Utils::inside(cp1, cp2, s, wasReversed);

				if (insideS && insideE) {
					newPolyPoints[counter] = e;
					counter++;
				}
				else if (!insideS && insideE) {
					newPolyPoints[counter] = Utils::intersection(cp1, cp2, s, e);
					counter++;
					newPolyPoints[counter] = e;
					counter++;
				}
				else if (insideS && !insideE) {
					newPolyPoints[counter] = Utils::intersection(cp1, cp2, s, e);
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
			seg->ForcedDrawFigure();
		}

		seg = new Segment(newPolyPoints[counter - 1], newPolyPoints[0]);
		seg->SetColor(color);
		seg->ForcedDrawFigure();
	}
}

void Window::ApplyScreenShuterlandHodgman(Segment* seg) {
	int counter = 0;

	//TODO REBASE ALL COORD TO 0 - 2 And not to -1 - 1 
	vector<Point*> subjectPoints;
	subjectPoints.push_back(seg->getFirstPoint());
	subjectPoints.push_back(seg->getSecondPoint());
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

				insideE = Utils::inside(cp1, cp2, e, wasReversed);
				insideS = Utils::inside(cp1, cp2, s, wasReversed);

				if (insideS && insideE) {
					newPolyPoints[counter] = e;
					counter++;
				}
				else if (!insideS && insideE) {
					newPolyPoints[counter] = Utils::intersection(cp1, cp2, s, e);
					counter++;
					newPolyPoints[counter] = e;
					counter++;
				}
				else if (insideS && !insideE) {
					newPolyPoints[counter] = Utils::intersection(cp1, cp2, s, e);
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
		Segment* newSegment = new Segment(newPolyPoints[0], newPolyPoints[1]);
		newSegment->SetColor(seg->GetColors());
		newSegment->ForcedDrawFigure();
	}
}