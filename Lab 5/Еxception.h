#pragma once
#include <string>
using namespace std;

class Exception {
public:
    Exception(string, int);
	~Exception();
	int Code() const;
	string What() const;
private:
    string err;
    int code;
};