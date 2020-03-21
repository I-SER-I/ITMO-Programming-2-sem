#pragma once
#include <fstream>

class IGeoFig {
public:
	virtual double square() = 0;
    virtual double perimeter() = 0;
};

class CVector2D {
public:
    double x;
	double y;
    CVector2D();
	friend std::istream& operator>>(std::istream&, CVector2D&);
    friend std::ostream& operator<<(std::ostream&, const CVector2D&);
};

class IPhysObject {
public:
    virtual double mass() const = 0;
    virtual CVector2D position() const = 0;
    virtual bool operator==(const IPhysObject& obj) const = 0;
    virtual bool operator<(const IPhysObject& obj) const = 0;
	
};

class IPrintable
{
public:
    virtual void draw() = 0;
};

class IDialogueInitiable
{
public:
    virtual void initFromDialogue() = 0;
};

class BaseCObject
{
public:
	virtual const char* className() = 0;
    virtual unsigned int size() = 0;
};

class IFigure : public IGeoFig, public IPhysObject, public IPrintable, public IDialogueInitiable, public BaseCObject, public CVector2D
{
	
};