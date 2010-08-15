/**
 * @file
 * This file contains the declaration of MemberObject, an abstract base
 * class for complex objects with member variables and methods.
 *
 * @todo For now, we do not allow function overloading. Overriding is manual.
 *
 * @brief Declaration of MemberObject
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2009-12-14 12:43:32 +0100 (Mån, 14 Dec 2009) $
 * @author The RevBayes core development team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-08-27, version 1.0
 *
 * $Id: MemberObject.h 194 2009-12-14 11:43:32Z ronquist $
 */

#ifndef MemberObject_H
#define MemberObject_H

#include "Frame.h"
#include "MethodTable.h"
#include "RbComplex.h"

#include <set>
#include <string>

class ArgumentRule;
class DAGNode;
class StringVector;

class MemberObject: public RbComplex {

    public:
        virtual                    ~MemberObject(void) {}                                                         //!< Destructor

        // Basic utility functions
        virtual RbObject*           clone(void) const = 0;                                                        //!< Clone object
        virtual bool                equals(const RbObject* x) const;                                              //!< Equals comparison
        virtual const StringVector& getClass(void) const;                                                         //!< Get class vector
        virtual void                printValue(std::ostream& o) const;                                            //!< Print value for user
        virtual std::string         toString(void) const;                                                         //!< Complete info

        // Member variable functions
        const MemberTable&          getMembers(void) const { return members; }                                    //!< Get members
        virtual const MemberRules&  getMemberRules(void) const = 0;                                               //!< Get member rules
        const RbObject*             getValue(const std::string& name);                                            //!< Get member value
        const RbObject*             getValue(const std::string& name) const;                                      //!< Get member value (const)
        const DAGNode*              getVariable(const std::string& name) const;                                   //!< Get member variable
        void                        setName(const std::string& name);                                             //!< Set base name of variables
        void                        setValue(const std::string& name, RbObject* val);                             //!< Set member value
        virtual void                setVariable(const std::string& name, DAGNode* var);                           //!< Set member variable

        // Member method functions
        const RbObject*             executeMethod(const std::string& name, int funcId);                           //!< Execute method with preprocessed args
        const RbObject*             executeMethod(const std::string& name, std::vector<Argument>& args);          //!< Execute method
        virtual const MethodTable&  getMethodInits(void) const = 0;                                               //!< Get method specifications
        const MethodTable&          getMethods(void) const { return methods; }                                    //!< Get methods
        int                         setArguments(const std::string& name, std::vector<Argument>& args);           //!< Set arguments of method

	protected:
        RbObject*                   convertTo(const std::string& type) const;                                     //!< Convert to type
        bool                        isConvertibleTo(const std::string& type) const;                               //!< Is convertible to type and dim?
									MemberObject(const MemberRules& memberRules, const MethodTable& methodInits); //!< Constructor

        // Protected functions
        virtual const RbObject*     executeOperation(const std::string& name, std::vector<DAGNode*>& args) = 0;   //!< Execute method
        DAGNode*                    getVariable(const std::string& name);                                         //!< Get member variable (non-const)

        // Members keep track of variables and functions belonging to the object
        MemberTable                 members;                                                                      //!< Member variables
        MethodTable                 methods;                                                                      //!< Member methods

        // Friend class
        friend class                DistributionFunction;                                                         //!< Give distribution function access
};

#endif

