#include "ArgumentRule.h"
#include "Func_writeNexus.h"
#include "RbException.h"
#include "RevNullObject.h"
#include "RlAbstractHomologousDiscreteCharacterData.h"
#include "RlContinuousCharacterData.h"
#include "RlDnaState.h"
#include "RlString.h"
#include "RlTree.h"
#include "NexusWriter.h"



using namespace RevLanguage;


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'B'.
 *
 * \return A new copy of myself 
 */
Func_writeNexus* Func_writeNexus::clone( void ) const 
{
    
    return new Func_writeNexus( *this );
}


/** 
 * Execute the function. 
 * Here we will extract the character data object from the arguments and get the file name
 * into which we shall write the character data. Then we simply create a NexusWriter
 * instance and delegate the work
 *
 * \return NULL because the output is going into a file
 */
RevPtr<RevVariable> Func_writeNexus::execute( void )
{
    
    // get the information from the arguments for reading the file
    const RlString& fn = static_cast<const RlString&>( args[0].getVariable()->getRevObject() );
    RevBayesCore::NexusWriter fw( fn.getValue() );
    fw.openStream();

    
//    const AbstractCharacterData& ac = static_cast<const AbstractCharacterData&>( args[1].getVariable()->getRevObject() );

    if ( this->args[1].getVariable()->getRevObject().getTypeSpec().isDerivedOf( AbstractHomologousDiscreteCharacterData::getClassTypeSpec() ) )
    {
        const RevBayesCore::AbstractHomologousDiscreteCharacterData &data = static_cast< const AbstractHomologousDiscreteCharacterData & >( args[1].getVariable()->getRevObject() ).getValue();
        fw.writeNexusBlock( data );
    }
    else if ( this->args[1].getVariable()->getRevObject().getTypeSpec().isDerivedOf( ContinuousCharacterData::getClassTypeSpec() ) )
    {
        const RevBayesCore::ContinuousCharacterData &data = static_cast< const ContinuousCharacterData & >( args[1].getVariable()->getRevObject() ).getValue();
        fw.writeNexusBlock( data );
    }
    else if ( this->args[1].getVariable()->getRevObject().getTypeSpec().isDerivedOf( Tree::getClassTypeSpec() ) )
    {
        const RevBayesCore::Tree &data = static_cast< const Tree & >( args[1].getVariable()->getRevObject() ).getValue();
        fw.writeNexusBlock( data );
    }
    else
    {
        fw.closeStream();
        throw RbException("We currently only support writing of homologous discrete|continuous character matrices to a nexus file.");
    }

    fw.closeStream();
    
    return NULL;
}


/** 
 * Get the argument rules for this function.
 *
 * The argument rules of the writeNexus function are:
 * (1) the filename which must be a string.
 * (2) the data object that must be some character matrix.
 *
 * \return The argument rules.
 */
const ArgumentRules& Func_writeNexus::getArgumentRules( void ) const 
{
    
    static ArgumentRules argumentRules = ArgumentRules();
    static bool rulesSet = false;
    
    if (!rulesSet) 
    {
        argumentRules.push_back( new ArgumentRule( "filename", RlString::getClassTypeSpec(), "The name of the file.", ArgumentRule::BY_VALUE, ArgumentRule::ANY ) );
        std::vector<TypeSpec> dataTypes;
        dataTypes.push_back( AbstractHomologousDiscreteCharacterData::getClassTypeSpec() );
        dataTypes.push_back( ContinuousCharacterData::getClassTypeSpec() );
        dataTypes.push_back( Tree::getClassTypeSpec() );

        argumentRules.push_back( new ArgumentRule( "data", dataTypes, "The character data matrix to print.", ArgumentRule::BY_VALUE, ArgumentRule::ANY ) );
        rulesSet = true;
    }
    
    return argumentRules;
}


/**
 * Get Rev type of object 
 *
 * \return The class' name.
 */
const std::string& Func_writeNexus::getClassType(void) 
{ 
    
    static std::string revType = "Func_writeNexus";
    
	return revType; 
}


/**
 * Get class type spec describing type of an object from this class (static).
 *
 * \return TypeSpec of this class.
 */
const TypeSpec& Func_writeNexus::getClassTypeSpec(void) 
{ 
    
    static TypeSpec revTypeSpec = TypeSpec( getClassType(), new TypeSpec( Function::getClassTypeSpec() ) );
    
	return revTypeSpec; 
}


/**
 * Get the primary Rev name for this function.
 */
std::string Func_writeNexus::getFunctionName( void ) const
{
    // create a name variable that is the same for all instance of this class
    std::string f_name = "writeNexus";
    
    return f_name;
}


/**
 * Get type-specification on this object (non-static).
 *
 * \return The type spec of this object.
 */
const TypeSpec& Func_writeNexus::getTypeSpec( void ) const 
{
    
    static TypeSpec typeSpec = getClassTypeSpec();
    
    return typeSpec;
}


/** 
 * Get the return type of the function. 
 * This function does not return anything so the return type is NULL.
 *
 * \return NULL
 */
const TypeSpec& Func_writeNexus::getReturnType( void ) const 
{
    
    static TypeSpec returnTypeSpec = RevNullObject::getClassTypeSpec();
    return returnTypeSpec;
}




