#include "AminoAcidState.h"
#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "DnaState.h"
#include "MetropolisHastingsMove.h"
#include "ModelVector.h"
#include "Move_NarrowExchangeCharacterHistory.h"
#include "NarrowExchangeCharacterHistoryProposal.h"
#include "RbException.h"
#include "RealPos.h"
#include "RlAbstractHomologousDiscreteCharacterData.h"
#include "RlRateGenerator.h"
#include "RlTimeTree.h"
#include "RnaState.h"
#include "StandardState.h"
#include "StochasticNode.h"
#include "TypedDagNode.h"
#include "TypeSpec.h"


using namespace RevLanguage;

/**
 * Default constructor.
 *
 * The default constructor does nothing except allocating the object.
 */
Move_NarrowExchangeCharacterHistory::Move_NarrowExchangeCharacterHistory() : Move()
{

}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the move.
 */
Move_NarrowExchangeCharacterHistory* Move_NarrowExchangeCharacterHistory::clone(void) const
{

    return new Move_NarrowExchangeCharacterHistory(*this);
}


/**
 * Create a new internal move object.
 *
 * This function simply dynamically allocates a new internal move object that is
 * associated with the variable (DAG-node). The internal move object is created by calling its
 * constructor and passing the move-parameters (the variable and other parameters) as arguments of the
 * constructor. The move constructor takes care of the proper hook-ups.
 *
 * \return A new internal distribution object.
 */
void Move_NarrowExchangeCharacterHistory::constructInternalObject( void )
{
    // we free the memory first
    delete value;

    // now allocate a new sliding move
    double w = static_cast<const RealPos &>( weight->getRevObject() ).getValue();
    RevBayesCore::TypedDagNode<RevBayesCore::Tree>* tmp = static_cast<const TimeTree &>( tree->getRevObject() ).getDagNode();
    RevBayesCore::StochasticNode<RevBayesCore::Tree> *n = static_cast<RevBayesCore::StochasticNode<RevBayesCore::Tree> *>( tmp );

    RevBayesCore::TypedDagNode<RevBayesCore::AbstractHomologousDiscreteCharacterData>* ctmc_tdn   = static_cast<const RevLanguage::AbstractHomologousDiscreteCharacterData&>( ctmc->getRevObject() ).getDagNode();
    RevBayesCore::StochasticNode<RevBayesCore::AbstractHomologousDiscreteCharacterData>* ctmc_sn  = static_cast<RevBayesCore::StochasticNode<RevBayesCore::AbstractHomologousDiscreteCharacterData>* >(ctmc_tdn);
    RevBayesCore::TypedDagNode<RevBayesCore::RateGenerator>* qmap_tdn                             = static_cast<const RateGenerator&>( rate_generator->getRevObject() ).getDagNode();

    std::string mt = ctmc_sn->getValue().getDataType();
    RevBayesCore::Proposal *p = NULL;
    
    if (mt == "DNA")
    {
        RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::DnaState> *tmp_p = new RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::DnaState>(n,ctmc_sn);
        tmp_p->setRateGenerator( qmap_tdn );
        p = tmp_p;
    }
    else if (mt == "RNA")
    {
        RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::RnaState> *tmp_p = new RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::RnaState>(n,ctmc_sn);
        tmp_p->setRateGenerator( qmap_tdn );
        p = tmp_p;
    }
    else if (mt == "AA" || mt == "Protein")
    {
        RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::AminoAcidState> *tmp_p = new RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::AminoAcidState>(n,ctmc_sn);
        tmp_p->setRateGenerator( qmap_tdn );
        p = tmp_p;
    }
    else if (mt == "Standard")
    {
        RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::StandardState> *tmp_p = new RevBayesCore::NarrowExchangeCharacterHistoryProposal<RevBayesCore::StandardState>(n,ctmc_sn);
        tmp_p->setRateGenerator( qmap_tdn );
        p = tmp_p;
    }
    
    value = new RevBayesCore::MetropolisHastingsMove(p,w);

}


/**
 * Get Rev type of object
 *
 * \return The class' name.
 */
const std::string& Move_NarrowExchangeCharacterHistory::getClassType(void)
{

    static std::string rev_type = "Move_NarrowExchangeCharacterHistory";

    return rev_type;
}


/**
 * Get class type spec describing type of an object from this class (static).
 *
 * \return TypeSpec of this class.
 */
const TypeSpec& Move_NarrowExchangeCharacterHistory::getClassTypeSpec(void)
{

    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( Move::getClassTypeSpec() ) );

    return rev_type_spec;
}


/**
 * Get the Rev name for the constructor function.
 *
 * \return Rev name of constructor function.
 */
std::string Move_NarrowExchangeCharacterHistory::getMoveName( void ) const
{
    // create a constructor function name variable that is the same for all instance of this class
    std::string c_name = "NarrowExchangeCharacterHistory";

    return c_name;
}


/**
 * Get the member rules used to create the constructor of this object.
 *
 * The member rules of the scale move are:
 * (1) the variable which must be a time-tree.
 *
 * \return The member rules.
 */
const MemberRules& Move_NarrowExchangeCharacterHistory::getParameterRules(void) const
{

    static MemberRules memberRules;
    static bool rules_set = false;

    if ( !rules_set )
    {
        memberRules.push_back( new ArgumentRule( "tree", TimeTree::getClassTypeSpec(), "The tree variable on which this move operates.", ArgumentRule::BY_REFERENCE, ArgumentRule::STOCHASTIC ) );
        memberRules.push_back( new ArgumentRule( "ctmc", AbstractHomologousDiscreteCharacterData::getClassTypeSpec(), "The ctmc.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::STOCHASTIC ) );
        memberRules.push_back( new ArgumentRule( "qmap", RateGenerator::getClassTypeSpec(), "The rate matrix.", ArgumentRule::BY_CONSTANT_REFERENCE, ArgumentRule::ANY ) );

        /* Inherit weight from Move, put it after variable */
        const MemberRules& inheritedRules = Move::getParameterRules();
        memberRules.insert( memberRules.end(), inheritedRules.begin(), inheritedRules.end() );

        rules_set = true;
    }

    return memberRules;
}


/**
 * Get type-specification on this object (non-static).
 *
 * \return The type spec of this object.
 */
const TypeSpec& Move_NarrowExchangeCharacterHistory::getTypeSpec( void ) const
{

    static TypeSpec type_spec = getClassTypeSpec();

    return type_spec;
}


/**
 * Print the value for the user.
 */
void Move_NarrowExchangeCharacterHistory::printValue(std::ostream &o) const
{

    o << "NarrowExchangeCharacterHistory(";
    if (tree != NULL)
    {
        o << tree->getName();
    }
    else
    {
        o << "?";
    }
    o << ")";

}


/**
 * Set a member variable.
 *
 * Sets a member variable with the given name and store the pointer to the variable.
 * The value of the variable might still change but this function needs to be called again if the pointer to
 * the variable changes. The current values will be used to create the distribution object.
 *
 * \param[in]    name     Name of the member variable.
 * \param[in]    var      Pointer to the variable.
 */
void Move_NarrowExchangeCharacterHistory::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{

    if ( name == "tree" )
    {
        tree = var;
    }
    else if ( name == "ctmc" )
    {
        ctmc = var;
    }
    else if ( name == "qmap")
    {
        rate_generator = var;
    }
    else
    {
        Move::setConstParameter(name, var);
    }

}
