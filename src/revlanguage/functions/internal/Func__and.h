/**
 * @file
 * This file contains the declaration and implementation
 * of the templated Func_and, which is used to to compare to values ( a && b).
 *
 * @brief Declaration and implementation of Func__and
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2012-06-12 10:25:58 +0200 (Tue, 12 Jun 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id: Func_vector.h 1626 2012-06-12 08:25:58Z hoehna $
 */

#ifndef Func__and_H
#define Func__and_H

#include "RlBoolean.h"
#include "RlTypedFunction.h"

#include <string>

namespace RevLanguage {
    
    class Func__and : public TypedFunction<RlBoolean> {
        
    public:
        Func__and();
        
        // Basic utility functions
        Func__and*                                              clone(void) const;                                          //!< Clone the object
        static const std::string&                               getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                  getClassTypeSpec(void);                                     //!< Get class type spec
        const std::string&                                      getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                         getTypeSpec(void) const;                                    //!< Get language type of the object
        
        // Regular functions
        RevBayesCore::TypedFunction<RevBayesCore::Boolean>*     createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                    getArgumentRules(void) const;                               //!< Get argument rules

        
    };
    
}


#endif


