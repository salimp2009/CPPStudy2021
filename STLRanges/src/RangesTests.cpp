#include "RangesPCH.hpp"

#include "RangesExamples01.hpp"
#include "RangesContainerView.hpp"
#include "RangesFilterPythonStyle.hpp"
#include "STLSpan/SpanStaticDynamic.hpp"
#include "ContainerImprovements/ContImprovements.hpp"


auto main()->int
{
	//RangeExample01();
	//RangeProjection();
	//ViewsKeysValue_Test();
	//ViewsKeys_FunctCompose();
	//ViewsIota_FunctCompose();
	//ViewsIota_PrimeNumbers();
	//ContainerView_CustomView();
	//FilterRanges_PythonStyle();
	//TransforMapRanges_PythonStyle();
	//MapFilterRanges_PythonStyle();
	//DynamicExtent_Span();
	//StaticDynamicExtent_Span();
	//spanTransform_ModifyElem();
	SpanMemberFunctions();
	ConstRange_ModifiableObjects();
	ConstExpr_Vector();
	makeArray();

}