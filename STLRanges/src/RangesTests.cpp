#include "RangesPCH.hpp"

#include "RangesExamples01.hpp"
#include "RangesContainerView.hpp"
#include "RangesFilterPythonStyle.hpp"
#include "STLSpan/SpanStaticDynamic.hpp"
#include "ContainerImprovements/ContImprovements.hpp"
#include "ChronoCalendarTimeZones/DatesTimeZoneExamples.hpp"
#include "FilterViewPerformanceIssue.hpp"
#include "ChronoCalendarTimeZones/TimeZoneExamples.hpp"
#include "Formatting/TextFormatExamples.hpp"
#include "ThreeWayComparision/ThreeWayCompareTests.hpp"
#include "DesignatedInitialization/DesignatedInitializationTests.hpp"
#include "ConstEvalConstInit/ConstEvalConstInitTests.hpp"
#include "NonTypeTemplateParams/NTTPTests.hpp"


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
	//FilterView_LazyEvaluation();
	//FilterView_PerformaceIssue();
	//DynamicExtent_Span();
	//StaticDynamicExtent_Span();
	//spanTransform_ModifyElem();
	//SpanMemberFunctions();
	//ConstRange_ModifiableObjects();
	//ConstExpr_Vector();
	//makeArray();
	//makeShared();
	//eraseif();
	//checkwithContains();
	//stringPrefixSuffixCheck();
	//safeIntegerComparision();
	//mathConstants();
	//midPointLerp();
	//getEndian();
	//bitOperations();
	//timeofDay();
	//calendarDates();
	//calendarDates2();
	//systemDaysExample();
	//checkValidDates();
	//querryCalendarDates();
	//calculateOrdinalDates();
	//localTimeTest1();
	//variousTimeZones();
	//oldwayFormatting();
	//FormatwithLocales();
	//FormatFillAlign();
	//FormatSign();
	//CustomFormat_V1();
	//CustomFormat_Vector();
	//WidthPrecisionSpecifier();
	//DecHexOctTypeSpecifier();
	//formatArgumentOrder();
	//customFormatBuffer();
	//FormatTofixedSizedBuffer();
	//customLogger();
	//ThreeWayComparision_Test1();
	//StringComparision_Test1();
	//SpaceShipOperator_Test1();
	//AddressSort();
	//LegacyWrapCompare();
	//LexicographicalComparision();
	//reWriteCompareExpressions();
	//userDefinedvsAutoComparisions();
	//AggregateIinitialization();
	//ReturnValueOptimization();
	//DirectInitializeAggregates();
	//AggregatesAndCTAD();
	//constEvalSqr();
	//constEvalInitExprSqr();
	staticInitializationFiasco();
	floatingPointNTTP();
	classTypeNTTP();
	FormatWithSpecifierCount();
	ConditionalExplicitConstructor();
	classTypeDoubleNTTP2();
	stringLiteralNTTP2();
	
	// NOT COMPILING due to MSVC Bug in std::format_to() function when used for customizing std::formatter!!
	//custformatStockIndex_V3();
}