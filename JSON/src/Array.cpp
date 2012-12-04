//
// Array.cpp
//
// $Id$
//
// Library: JSON
// Package: JSON
// Module:  Array
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/JSON/Array.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Stringifier.h"


using Poco::Dynamic::Var;


namespace Poco {
namespace JSON {


Array::Array()
{
}


Array::Array(const Array& copy) : _values(copy._values)
{
}


Array::~Array()
{
}


Var Array::get(unsigned int index) const
{
	Var value;
	try
	{
		value = _values.at(index);
	}
	catch(std::out_of_range&)
	{
		//Ignore, we return an empty value
	}
	return value;
}


Array::Ptr Array::getArray(unsigned int index) const
{
	Array::Ptr result;

	Var value = get(index);
	if ( value.type() == typeid(Array::Ptr) )
	{
		result = value.extract<Array::Ptr>();
	}
	return result;
}


Object::Ptr Array::getObject(unsigned int index) const
{
	Object::Ptr result;

	Var value = get(index);
	if ( value.type() == typeid(Object::Ptr) )
	{
		result = value.extract<Object::Ptr>();
	}
	return result;
}


bool Array::isNull(unsigned int index) const
{
	if ( index < _values.size() )
	{
		Dynamic::Var value = _values[index];
		return value.isEmpty();
	}
	return true;
}


bool Array::isObject(unsigned int index) const
{
	Var value = get(index);
	return value.type() == typeid(Object::Ptr);
}


void Array::stringify(std::ostream& out, unsigned int indent) const
{
	out << "[";
	if ( indent > 0 )
		out << std::endl;

	for(ValueVec::const_iterator it = _values.begin(); it != _values.end();)
	{
		for(int i = 0; i < indent; i++)
		{
			out << ' ';
		}

		Stringifier::stringify(*it, out, indent);

		if ( ++it != _values.end() )
		{
			out << ",";
			if ( indent > 0 )
			{
				out << std::endl;
			}
		}
	}

	if ( indent > 0 )
	{
		out << std::endl;
	}

	if ( indent > 0 )
		indent -= 2;

	for(int i = 0; i < indent; i++)
	{
		out << ' ';
	}

	out << "]";
}


} } // namespace Poco::JSON
