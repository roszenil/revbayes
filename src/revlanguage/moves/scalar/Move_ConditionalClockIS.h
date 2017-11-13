#ifndef Move_ConditionalClockIS_H
#define Move_ConditionalClockIS_H

#include "RlMove.h"
#include "TypedDagNode.h"

#include <ostream>
#include <string>

namespace RevLanguage {
    
    /**
     * @brief Rev Wrapper of a scaling move on all elements of a real valued vector.
     *
     * This class is the RevLanguage wrapper of ConditionalClockIS.
     *
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @copyright GPL version 3
     * @since 2016-08-31, version 1.0
     */
    class Move_ConditionalClockIS : public Move {
        
    public:
        
        Move_ConditionalClockIS(void);                                                                                                                    //!< Default constructor
        
        // Basic utility functions
        virtual Move_ConditionalClockIS*            clone(void) const;                                                                              //!< Clone the object
        void                                        constructInternalObject(void);                                                                  //!< We construct the a new internal move.
        static const std::string&                   getClassType(void);                                                                             //!< Get Rev type
        static const TypeSpec&                      getClassTypeSpec(void);                                                                         //!< Get class type spec
        std::string                                 getMoveName(void) const;                                                                        //!< Get the name used for the constructor function in Rev.
        const MemberRules&                          getParameterRules(void) const;                                                                  //!< Get member rules (const)
        virtual const TypeSpec&                     getTypeSpec(void) const;                                                                        //!< Get language type of the object
        virtual void                                printValue(std::ostream& o) const;                                                              //!< Print value (for user)
        
    protected:
        
        void                                        setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);               //!< Set member variable
        
        RevPtr<const RevVariable>                   x;                                                                                              //!< The variable holding the real valued vector.
        RevPtr<const RevVariable>                   tree;                                                                                              //!< The variable holding the real valued vector.
        RevPtr<const RevVariable>                   numInvariantSites;                                                                                         //!< The variable for the tuning parameter.
        RevPtr<const RevVariable>                   numSites;                                                                                         //!< The variable for the tuning parameter.
        RevPtr<const RevVariable>                   clockIsLogScale;                                                                                         //!< The variable for the tuning parameter.
        RevPtr<const RevVariable>                   sigma;                                                                                         //!< The variable for the tuning parameter.
        RevPtr<const RevVariable>                   tune;                                                                                           //!< The variable telling if to tune or not.
        
    };
    
}

#endif
