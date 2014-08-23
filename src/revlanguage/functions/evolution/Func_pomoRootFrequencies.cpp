//
//  Func_pomoRootFrequencies.cpp
//  RevBayesCore
//
//  Created by Bastien Boussau on 22/8/14.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Func_pomoRootFrequencies.h"
#include "ModelVector.h"
#include "Natural.h"
#include "PomoRootFrequenciesFunction.h"
#include "RlAbstractCharacterData.h"
#include "RlDnaState.h"
#include "RlDeterministicNode.h"
#include "RlRateMatrix.h"
#include "RlSimplex.h"
#include "RlTaxon.h"
#include "TypedDagNode.h"

using namespace RevLanguage;

/** default constructor */
Func_pomoRootFrequencies::Func_pomoRootFrequencies( void ) : Function( ) {
    
}


/** Clone object */
Func_pomoRootFrequencies* Func_pomoRootFrequencies::clone( void ) const {
    
    return new Func_pomoRootFrequencies( *this );
}


RevPtr<Variable> Func_pomoRootFrequencies::execute() {
    //Four arguments, root_base_frequencies, root_polymorphism_proportion, Q, virtual_population_size
    
    RevBayesCore::TypedDagNode<std::vector<double> >* rbf = static_cast<const Simplex &>( this->args[0].getVariable()->getRevObject() ).getDagNode();
    
    RevBayesCore::TypedDagNode< double >* rpp = static_cast<const Real &>( this->args[1].getVariable()->getRevObject() ).getDagNode();
    
    RevBayesCore::TypedDagNode<RevBayesCore::RateMatrix >* q = static_cast<const RateMatrix &>( this->args[2].getVariable()->getRevObject() ).getDagNode();

    RevBayesCore::TypedDagNode< int >* n = static_cast<const Natural &>( this->args[3].getVariable()->getRevObject() ).getDagNode();

    RevBayesCore::PomoRootFrequenciesFunction* pomorf = new RevBayesCore::PomoRootFrequenciesFunction( rbf, rpp, q, n );
    
    DeterministicNode< std::vector< double >  > *detNode = new DeterministicNode< std::vector< double >  >("", pomorf, this->clone());
    
    ModelVector<RealPos>* value = new ModelVector<RealPos>( detNode );
    
    return new Variable( value );

}


/* Get argument rules */
const ArgumentRules& Func_pomoRootFrequencies::getArgumentRules( void ) const {
    
    static ArgumentRules argumentRules = ArgumentRules();
    static bool          rulesSet = false;
    
    if ( !rulesSet )
    {
        //Four arguments, root_base_frequencies, root_polymorphism_proportion, Q, virtual_population_size

        argumentRules.push_back( new ArgumentRule( "root_base_frequencies", true, Simplex::getClassTypeSpec() ) );
        argumentRules.push_back( new ArgumentRule( "root_polymorphism_proportion"    , true, Real::getClassTypeSpec() ) );
        argumentRules.push_back( new ArgumentRule( "mutation_rate_matrix"    , true, RateMatrix::getClassTypeSpec() ) );
        argumentRules.push_back( new ArgumentRule( "virtualNe"    , true, Natural::getClassTypeSpec() ) );
        
        rulesSet = true;
    }
    
    return argumentRules;
}


const std::string& Func_pomoRootFrequencies::getClassType(void) {
    
    static std::string revType = "Func_pomoRootFrequencies";
    
	return revType;
}

/* Get class type spec describing type of object */
const TypeSpec& Func_pomoRootFrequencies::getClassTypeSpec(void) {
    
    static TypeSpec revTypeSpec = TypeSpec( getClassType(), new TypeSpec( Function::getClassTypeSpec() ) );
    
	return revTypeSpec;
}


/* Get return type */
const TypeSpec& Func_pomoRootFrequencies::getReturnType( void ) const {
    
    static TypeSpec returnTypeSpec = Simplex::getClassTypeSpec();
    
    return returnTypeSpec;
}


const TypeSpec& Func_pomoRootFrequencies::getTypeSpec( void ) const {
    
    static TypeSpec typeSpec = getClassTypeSpec();
    
    return typeSpec;
}
