#pragma once
#include "Base.h"

class Circle : public IFigure {
public:
	Circle();
	~Circle();
	double square() override;
	double perimeter() override;
	double mass() const override;
	CVector2D position() const override;
	bool operator==(const IPhysObject& obj) const override;
	bool operator<(const IPhysObject& obj) const override;
	void draw() override;
	void initFromDialogue() override;
	const char* className() override;
	unsigned int size() override;
private:
	CVector2D center;
	double radius = 0;
	double weight = 0;
	const char* name = "Circle";
};