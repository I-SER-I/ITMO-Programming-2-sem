#include <algorithm>
#include <iostream>
#include <vector>
#include "Circle.h"
#include "Triangle.h"
using namespace std;

enum Commands
{
	ADD = 1,
	SHOW_ALL,
	SUM_PERIMETERS,
	SUM_AREAS,
	CENTRE_MASS,
	MEMORY,
	SORT,
	EXIT
};
enum Figure
{
	CIRCLE = 1,
	TRIANGLE = 2,
};

int main() {
	vector<IFigure*> system;
	int command;
	double x, y, sumP, sumS, massAll;
	CVector2D centerMass;
	while(true) {
		cout << "1. Add figure " << endl;
		cout << "2. Show all figures" << endl;
		cout << "3. Sum all perimeters" << endl;
		cout << "4. Sum all areas" << endl;
		cout << "5. System weight center" << endl;
		cout << "6. Show figures memory" << endl;
		cout << "7. Sort" << endl;
		cout << "8. Exit" << endl;
		cout << "Add command: ";	
		cin >> command;
		cout << endl;
		switch (command) {
		case ADD:
			cout << "\t1. Circle" << endl;
			cout << "\t2. Triangle" << endl;
			cout << "\tAdd command: ";
			cin >> command;
			cout << endl;
			switch (command)
			{
			case CIRCLE:
				system.push_back(new Circle());
				break;
			case TRIANGLE:
				system.push_back(new Triangle());
				break;
			default:
				cout << "\tFigure not found" << endl;
				break;
			}
			break;
		case SHOW_ALL:
			for (auto& figure : system)
				figure->draw();
			break;
		case SUM_PERIMETERS:
			sumP = 0;
			for (auto& figure : system)
				sumP += figure->perimeter();
			cout << "Perimeter system: " << sumP << endl;
			cout << endl;
			break;
		case SUM_AREAS:
			sumS = 0;
			for (auto& figure : system)
				sumS += figure->square();
			cout <<"Area system: " << sumS << endl;
			cout << endl;
			break;
		case CENTRE_MASS:
			massAll = 0;
			x = 0;
			y = 0;
			for (auto& figure : system) {
				x += figure->position().x * figure->mass();
				y += figure->position().y * figure->mass();
				massAll += figure->mass();
			}
			centerMass.x = x / massAll;
			centerMass.y = y / massAll;
			cout << "Center weight coords: " << centerMass << endl;
			cout << endl;
			break; 
		case MEMORY:
			cout << "Figures memory: ";
			for (auto& figure : system)
				cout << figure->size() << " ";
			cout << endl;
			cout << endl;
			break;
		case SORT:
			sort(system.begin(), system.end(), [](IFigure* x, IFigure* y) {return *x < *y; });
			cout << "Successes" << endl;
			cout << "Figures weight: ";
			for (auto& figure : system)
				cout << figure->mass() << " ";
			cout << endl;
			cout << endl;
			break;
		case EXIT:
			return 0;
		default:
			cout << "Command not found" << endl;
			cout << endl;
			break;
		}
	}
}