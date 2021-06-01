#include "Templpch.h"

#include "TemplateBasicsExamples.hpp"
#include "VariadicTemplates.hpp"
#include "TrickyBasicsExamples.hpp"
#include "Concepts/ConceptExamples.hpp"
#include "Concepts/ConceptExamples2.hpp"


int main()
{
	//FunctionTemplates_Basics();
	//NonTemplateParams_Basics();
	VariadicTemplate_Basics(); 
	//FoldingBinaryTree();
	//VariadicIndices();
	//VariadicBases_Overloader();
	//TrickyBasics01();
	//TrickyBasics_Arrays();
	//ArrayOverloads_Test();
	//MemberFunctSpecialization_Test();
	//VariableTemplates_Test();
	//greatCommonDiv_Concepts();
	//compileTimePredicate_Concepts();
	//customConceptExample1_();
	//ConceptsIn_VariadicTemplates();
	//TestingCustomConcept();
	//FunctionOverloadingConcepts();
	//SpecializeTemplates_Concepts();
	conceptBasedDispatch();
	placeHolders_Concepts();
	overloadWithConcepts();
	dataValidateCheck_Concepts();

	return 0;
}