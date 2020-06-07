#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "object.h"

namespace DTLib {

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object{
protected:
	char *m_message;
	char *m_location;

	void init(const char *message, const char *file, int line);

public:
	Exception(const char *message);
	Exception(const char *file, int line);
	Exception(const char *message, const char *file, int line);

	Exception(const Exception &e);
	Exception &operator=(const Exception &e);

	virtual const char *message() const;
	virtual const char *location() const;

	virtual ~Exception() = 0;
	//virtual ~Exception();
};
	
class ArithmetricException : public Exception {
public:
	ArithmetricException() : Exception(0) { }
	ArithmetricException(const char *message) : Exception(message) { }
	ArithmetricException(const char *file, int line) : Exception(file, line) { }
	ArithmetricException(const char *message, const char *file, int line) : Exception(message, file, line) { }

	ArithmetricException(const ArithmetricException &e) : Exception(e) { }
	
	ArithmetricException& operator=(const ArithmetricException &e)
	{
		Exception::operator=(e);
		return *this;
	}
	
};
	
class NullPointerException : public Exception
{
public:
	NullPointerException() : Exception(0) { }
	NullPointerException(const char *message) : Exception(message) { }
	NullPointerException(const char *file, int line) : Exception(file, line) { }
	NullPointerException(const char *message, const char *file, int line) : Exception(message, file, line) { }

	NullPointerException(const NullPointerException &e) : Exception(e) { }
	
	NullPointerException& operator=(const NullPointerException &e)
	{
		Exception::operator=(e);
		return *this;
	}
	
};

class IndexOutOfBoundsException : public Exception
{
public:
	IndexOutOfBoundsException() : Exception(0) { }
	IndexOutOfBoundsException(const char *message) : Exception(message) { }
	IndexOutOfBoundsException(const char *file, int line) : Exception(file, line) { }
	IndexOutOfBoundsException(const char *message, const char *file, int line) : Exception(message, file, line) { }

	IndexOutOfBoundsException(const IndexOutOfBoundsException &e) : Exception(e) { }
	
	IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException &e)
	{
		Exception::operator=(e);
		return *this;
	}
	
};

class NoEnoughMemoryException : public Exception
{
public:
	NoEnoughMemoryException() : Exception(0) { }
	NoEnoughMemoryException(const char *message) : Exception(message) { }
	NoEnoughMemoryException(const char *file, int line) : Exception(file, line) { }
	NoEnoughMemoryException(const char *message, const char *file, int line) : Exception(message, file, line) { }

	NoEnoughMemoryException(const NoEnoughMemoryException &e) : Exception(e) { }
	
	NoEnoughMemoryException& operator=(const NoEnoughMemoryException &e)
	{
		Exception::operator=(e);
		return *this;
	}
	
};

class InvalidParameterException : public Exception
{
public:
	InvalidParameterException() : Exception(0) { }
	InvalidParameterException(const char *message) : Exception(message) { }
	InvalidParameterException(const char *file, int line) : Exception(file, line) { }
	InvalidParameterException(const char *message, const char *file, int line) : Exception(message, file, line) { }

	InvalidParameterException(const InvalidParameterException &e) : Exception(e) { }
	
	InvalidParameterException& operator=(const InvalidParameterException &e)
	{
		Exception::operator=(e);
		return *this;
	}
};

class InvalidOperationException : public Exception
{
public:
	InvalidOperationException() : Exception(0) { }
	InvalidOperationException(const char *message) : Exception(message) { }
	InvalidOperationException(const char *file, int line) : Exception(file, line) { }
	InvalidOperationException(const char *message, const char *file, int line) : Exception(message, file, line) { }

	InvalidOperationException(const InvalidOperationException &e) : Exception(e) { }
	
	InvalidOperationException& operator=(const InvalidOperationException &e)
	{
		Exception::operator=(e);
		return *this;
	}
};

}





#endif
