/**
 * @file
 * This file contains the declaration of the RevLanguage polymorphicStateConverter, which
 * is used to convert a DNA alignment into a POMO alignment.
 *
 * @brief Declaration and implementation of polymorphicStateConverter
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2012-04-20 04:06:14 +0200 (Fri, 20 Apr 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id: Func_polymorphicStateConverter.h 1406 2012-04-20 02:06:14Z Boussau $
 */


#ifndef Func_polymorphicStateConverter_H
#define Func_polymorphicStateConverter_H

#include "RlFunction.h"

#include <string>

namespace RevLanguage {
    
    class Func_polymorphicStateConverter :  public Function {
        
    public:
        Func_polymorphicStateConverter( void );
        
        // Basic utility functions
        Func_polymorphicStateConverter*                                clone(void) const;                                                              //!< Clone the object
        static const std::string&                       getClassType(void);                                                             //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                         //!< Get class type spec
        const TypeSpec&                                 getTypeSpec(void) const;                                                        //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevPtr<Variable>                                execute(void);                                                                  //!< Execute function
        const ArgumentRules&                            getArgumentRules(void) const;                                                   //!< Get argument rules
        const TypeSpec&                                 getReturnType(void) const;                                                      //!< Get type of return value
        
    };
    
}

#endif