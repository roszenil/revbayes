/**
 * @file
 * This file contains the implementation of TypeSpec, which
 * is used to hold type specifications.
 *
 * @brief Implementation of TypeSpec
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2010-09-06, version 1.0
 *
 * $Id$
 */

#include "RbException.h"
#include "RbNames.h"
#include "TypeSpec.h"
#include "Workspace.h"


/** Constructor for single object (dim = 0, ref = false; if container type, we translate it or throw an error) */
TypeSpec::TypeSpec( const std::string& objType )
    : type(Workspace::userWorkspace().getTypeSpec(objType).getType()),
      dim(Workspace::userWorkspace().getTypeSpec(objType).getDim()),
      reference(false) {

    if ( Workspace::userWorkspace().areTypesInitialized() && Workspace::userWorkspace().isXOfTypeY( type, Container_name ) )
        throw RbException( "Cannot convert container type name to language type specification" );
}


/** Complete constructor */
TypeSpec::TypeSpec(const std::string& objType, size_t objDim, bool ref)
    : type(objType), dim(objDim), reference(ref) {
}

/** Copy constructor */
TypeSpec::TypeSpec(const TypeSpec& ts)
: type(ts.type), dim(ts.dim), reference(ts.reference) {
    
}


/** Equals comparison */
bool TypeSpec::operator==(const TypeSpec& x) const {

    if (type == x.type && dim == x.dim && reference == x.reference)
        return true;
    else
        return false;
}


/** Type conversion operator to std::string */
TypeSpec::operator std::string( void ) const {

    return toString();
}


/** Check if it is a dimensionless object */
bool TypeSpec::isDimensionlessObject( void ) const {

    if ( type == RbObject_name && dim == 0 )
        return true;
    else
        return false;
}


/** Convert to string */
std::string TypeSpec::toString(void) const {

    std::string typeDesc = type;

    for (size_t i=0; i<dim; i++)
        typeDesc += "[]";

    if (reference)
        typeDesc += "&";

    return typeDesc;
}


/** Make sure we can print to stream using << operator */
std::ostream& operator<<(std::ostream& o, const TypeSpec& x) {

    o << x.toString();
    return o;
}


/** String concatenation using operator + */
std::string operator+(const std::string& s, const TypeSpec& x) {

    return s + x.toString();
}

