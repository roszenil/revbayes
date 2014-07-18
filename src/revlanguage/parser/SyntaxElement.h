#ifndef SyntaxElement_H
#define SyntaxElement_H

#include "RevObject.h"
#include "RevPtr.h"
#include "Variable.h"

#include <iostream>
#include <string>

namespace RevLanguage {

    /* Forward declarations */
    class Environment;

    /**
     * @brief Interface for syntax elements
     *
     * SyntaxElement is the base class for nodes in the syntax tree. The nodes either
     * have one or more operands, which are themselves syntax elements, or they have
     * no operands and simply a predefined result of type (smart pointer to) Variable.
     * In the former case, the elements correspond to interior nodes in the syntax tree
     * and in the latter case, they correspond to terminal nodes.
     *
     * The destructor of syntax elements should delete the entire syntax tree rooted at the
     * element. This is accomplish by simply cycling through all syntax elements referenced
     * by the syntax element to be destroyed, calling the destructor of each element in turn.
     * The base class does not reference any other syntax elements and therefore has an empty
     * destructor.
     */
    class SyntaxElement {

    public:
        virtual                        ~SyntaxElement(void) {}                                                              //!< Destructor; delete syntax subtree

        // Basic utility functions you have to override
        virtual SyntaxElement*          clone(void) const = 0;                                                              //!< Clone object
        virtual void                    printValue(std::ostream& o) const = 0;                                              //!< Print info about object

        // Regular functions
        virtual RevPtr<Variable>        evaluateContent(Environment& env) = 0;                                              //!< Get semantic value (static)
        virtual RevPtr<Variable>        evaluateLHSContent(Environment& env, const std::string& varType);                   //!< Get semantic value (static)
        virtual RevPtr<Variable>        evaluateDynamicContent(Environment& env);                                           //!< Get semantic value (dynamic, if different)
        virtual bool                    isAssignment(void) const;                                                           //!< Is this an assignment statement element?
        virtual bool                    isConstExpression(void) const;                                                      //!< Is subtree constant expr?

    protected:
                                        SyntaxElement(void) {}                                                              //!< Protected constructor, just in case
    };

}

#endif

