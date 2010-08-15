/**
 * @file
 * This file contains the implementation of StringVector, a complex type
 * used to hold string vectors.
 *
 * @brief Implementation of StringVector
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes core development team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-09-08, version 1.0
 * @extends RbComplex
 *
 * $Id$
 */

#include "IntVector.h"
#include "RbException.h"
#include "RbNames.h"
#include "RbString.h"
#include "StringVector.h"

#include <sstream>


/** Construct empty vector of length n */
StringVector::StringVector(size_t n) : Container() {

    value.resize(n);
}


/** Construct vector with one string x */
StringVector::StringVector(const std::string& x) : Container() {

    value.push_back(x);
}


/** Construct vector with n strings x */
StringVector::StringVector(size_t n, const std::string& x) : Container() {

    for (size_t i = 0; i < n; i++)
        value.push_back(x);
}


/** Constructor from std::string vector */
StringVector::StringVector(const std::vector<std::string>& x) : Container() {

    value = x;
}


/** Comparison  with operator== */
bool StringVector::operator==(const StringVector& sv) const {

	if ( size() != sv.size() )
		return false;
	for (size_t i=0; i<size(); i++)
		{
		if (value[i] != sv.value[i])
			return false;
		}
	return true;
}


/** Concatenation with operator+ */
StringVector StringVector::operator+(const StringVector& x) const {

    StringVector tempVec = *this;
    for (size_t i = 0; i < x.value.size(); i++)
        tempVec.push_back(x.value[i]);

    return tempVec;
}

/** Convert to object of another class. The caller manages the object. */
RbObject* StringVector::convertTo(const std::string& type) const {

    return NULL;
}

/** Clone function */
StringVector* StringVector::clone() const {

    return new StringVector(*this);
}


/** Pointer-based equals comparison */
bool StringVector::equals(const RbObject* obj) const {

    // Use built-in fast down-casting first
    const StringVector* p = dynamic_cast<const StringVector*> (obj);
    if (p != NULL) {
        if (value.size() != p->value.size())
            return false;
        for (size_t i=0; i<value.size(); i++) {
            if (value[i] != p->value[i])
                return false;
        }
        return true;
    }

    // Try converting the value to a string vector
    p = dynamic_cast<const StringVector*> (obj->convert(getType()));
    if (p == NULL)
        return false;

    bool result = true;
    if (value.size() != p->value.size())
        result = false;
    else {
        for (size_t i=0; i<value.size(); i++)
            result = result && (value[i] == p->value[i]);
    }

    delete p;
    return result;
}


/** Get class vector describing type of object */
const StringVector& StringVector::getClass() const {

    static StringVector rbClass = StringVector(StringVector_name) + RbComplex::getClass();
    return rbClass;
}


/** Get element for parser (read-only) */
const RbObject* StringVector::getElement(const IntVector& index) const {

    static RbString x;

    if (index.size() != 0)
        throw (RbException("Index error"));
    if (index[0] >= (int)value.size() || index[0] < 0)
        throw (RbException("Index out of bound"));

    x.setValue(value[index[0]]);
    return &x;
}


/** Get element class */
const std::string& StringVector::getElementType(void) const {

    static std::string rbType = RbString_name;
    return rbType;
}


/** Get element length for parser */
const IntVector& StringVector::getLength() const {

    static IntVector length = IntVector(0);

    length[0] = int(value.size());
    return length;
}

/** Convert to object of another class. The caller manages the object. */
bool StringVector::isConvertibleTo(const std::string& type) const {

    return false;
}

/** Allow parser to resize the string vector */
void StringVector::resize(IntVector const& len) {

    if ( len.size() != 1 )
        throw (RbException("Length specification error"));

    value.resize(len[0]);
}


/** Allow parser to set an element (any type conversion is done by the parser) */
void StringVector::setElement(const IntVector& index, RbObject* val) {

    if ( !val->isType(RbString_name) )
        throw (RbException("Type mismatch"));

    if (index.size() != 1 || index[0] < 1 )
        throw (RbException("Index error"));

    if ( index[0] >= int(value.size()) ) {
        int oldLen = int(value.size());
        resize(index[0]);
        for (int i=oldLen; i<index[0]; i++)
            value[i] = "";
    }

    value[index[0]] = ((RbString*)(val))->getValue();
}


/** Allow parser to rearrange the container (actually do not allow it) */
void StringVector::setLength(const IntVector& len) {

    if ( len.size() != 1 && len[0] != int(value.size()) )
        throw (RbException("Length specification error"));
}


/** Print value for user */
void StringVector::printValue(std::ostream& o) const {

    o << "{ ";
    for (std::vector<std::string>::const_iterator i = value.begin(); i!= value.end(); i++) {
        if (i != value.begin())
            o << ", ";
        o << "\"" << (*i) << "\"";
    }
    o <<  " }";
}


/** Complete info about object */
std::string StringVector::toString(void) const {

    std::ostringstream o;
    o << "StringVector: value = ";
    printValue(o);
    
    return o.str();
}

