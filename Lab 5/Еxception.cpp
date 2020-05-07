#include "Åxception.h"

Exception::Exception(string, int) = default;
Exception::~Exception() = default;
int Exception::Code() const {
	return code;
}
string Exception::What() const {
	return err;
}