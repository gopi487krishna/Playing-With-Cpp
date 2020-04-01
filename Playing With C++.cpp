// Playing With C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Policy Based Design.h"
#include "Conditional Select Impl.h"
#include "Type To Type.h"
#include "SUPERSUB_CompileTime.h"
#include "Type_traits.h"
#include "typelist.h"
#include "TypeInfo.h"
#include "Strip Const Volatile Qualifiers.h"
#include "Functor.h"
#include <vector>

#define PRINT_FUNC_NAME {print80dash(); std::cout<<__FUNCTION__<<'\n';print80dash();}
auto print_empty_lines(int n) {
	while (n--) { std::cout << '\n'; }
}
auto print80dash() {

	static std::string dash_string(80, '-');
	std::cout << dash_string<<'\n';
}

// Demonstrates the use of policy based design
void  policy_based_design_demo() {
	
	PRINT_FUNC_NAME
	policy_bs_design::WidgetManager<policy_bs_design::OPNewCreator<policy_bs_design::Widget>> widget_manager;
	widget_manager.doSomething();
	print_empty_lines(4);
}

// Demonstrates the std::conditional's implementation
void select_type_demo() {
	PRINT_FUNC_NAME
	cond_select::select_type<false, int, float>::type t = 6;
	std::cout << t<<'\n';
	print_empty_lines(4);
}

// Shows the use of type to type struct
void type_to_type_demo() {
	
	PRINT_FUNC_NAME
	
	tp_to_type::TERA* TERA_instance = tp_to_type::create(std::string("FirstWidget"), tp_to_type::type_to_type<tp_to_type::TERA>());
	tp_to_type::Widget* widget_instance = tp_to_type::create(std::string("FirstWidget"), tp_to_type::type_to_type<tp_to_type::Widget>());

	std::cout << "WIDGET : " << widget_instance->getName() << "\n";
	std::cout << "TERA : " << TERA_instance->getName() << "\n";
	print_empty_lines(4);
}


void detect_inheritablity_and_conversion_at_runtime() {

	PRINT_FUNC_NAME

	class A {};
	class B :public A {};
	class C {};
	std::cout <<"B inherits from A "<< std::boolalpha << convertiblity_at_runtime::Conversion<B,A>::exists << '\n';
	std::cout <<"C inherits from A " << std::boolalpha << convertiblity_at_runtime::Conversion<C, A>::exists << '\n';


    print_empty_lines(4);
}

void is_same_demo() {

	PRINT_FUNC_NAME
	std::cout << "int and float " << std::boolalpha << Type_Traits::is_same<int, float>::value;
	std::cout << "int and int " << std::boolalpha << Type_Traits::is_same<int, int>::value;

	print_empty_lines(4);
}

void is_pointer() {

	PRINT_FUNC_NAME
	std::cout << "int is pointer ?"<<std::boolalpha << Type_Traits::is_pointer<int>::value;
	std::cout << "vector<Type>::iterator is pointer ?" << std::boolalpha << Type_Traits::is_pointer<std::vector<int>::iterator>::value;
	print_empty_lines(4);
}


void typelist_total_types() {

	PRINT_FUNC_NAME
	std::cout << "Length<TYPELIST(char,std::string,int)> :" << GTypeList::Length<TYPELIST_3(char, std::string, int)>::value;
	print_empty_lines(4);
}

void typelist_type_at() {

	PRINT_FUNC_NAME
	std::cout << "type_at<TYPELIST(char,std::string,int)  :" << TypeInfo(typeid(GTypeList::typeAt<TYPELIST_3(char,std::string,int),1>::Result)).name();
	print_empty_lines(4);
}

void typelist_type_at_non_strict() {

	PRINT_FUNC_NAME
	std::cout << "type_at_non_strict<TYPELIST(char,std::string,int),5>  :" << TypeInfo(typeid(GTypeList::TypeAtNonStrict<TYPELIST_3(char, std::string, int), 5,EmptyType>::Result)).name();
	print_empty_lines(4);
}
void typelist_check_if_type_present_at() {
	PRINT_FUNC_NAME
	std::cout << "char is present at in indexOf<TYPELIST(char,long,float) : " << GTypeList::indexOf<TYPELIST_3(char, long, float), char>::value;
	std::cout << "\ndouble is present at in indexOf<TYPELIST(char,long,float) : " << GTypeList::indexOf<TYPELIST_3(char, long, float), double>::value;
	print_empty_lines(4);
}

void strip_const() {

	PRINT_FUNC_NAME
	std::cout << "Type Name: (const int ) to (" << typeid(strip_cv::un_const<const int>::Type).name() << ")" ;
	print_empty_lines(4);
}

void strip_volt() {

	PRINT_FUNC_NAME
	std::cout<<"Type Name: ( volatile int ) to ("<<typeid(strip_cv::un_volt<volatile int>::Type).name()<<")";
	print_empty_lines(4);
}
void erase_type() {

	PRINT_FUNC_NAME
	std::cout << "(int, char, long) Erase -> char : " << GTypeList::Length<GTypeList::Erase<TYPELIST_3(int, char, float), char>::Result>::value;
	print_empty_lines(4);
}
void erase_type_all() {

	PRINT_FUNC_NAME
	std::cout << "(float,char,float,double,float) Erase -> float : " << GTypeList::Length<GTypeList::Erase_ALL<TYPELIST_5(float,char,float,double,float),float>::Result>::value;
	print_empty_lines(4);
}

void replace_type() {

	PRINT_FUNC_NAME
	std::cout << "Replace ( int,float,char) to (int float,double) :" << typeid(GTypeList::Replace<TYPELIST_3(int, float, char), char, double>::Result).name();
	print_empty_lines(4);
}

void append_type() {

	PRINT_FUNC_NAME
	std::cout << "Append (int,float,char) ->(int,float,double) : " << typeid(GTypeList::Append<TYPELIST_3(int, float, char), double>::Result).name();
	print_empty_lines(4);
}


struct ms {

	int operator()(int a, double b) { return a+b; }

};
void functor_test() {

	PRINT_FUNC_NAME
	ms t;
	Functor<int, TYPELIST_2( int, double)> my_functor(t);
	std::cout << "Functor Result: " << my_functor(2,4.5);
	print_empty_lines(4);

}


template<class TypeList>
using tuple = GTypeList::HierarchyGen < TypeList, GTypeList::holder>;

void tuple_check() {
	PRINT_FUNC_NAME
	tuple<TYPELIST_3(int,int,int)> my_tuple;
	GTypeList::Get<0>(my_tuple) = 4;
	GTypeList::Get<1>(my_tuple) = 8;
	GTypeList::Get<2>(my_tuple) = 7;
	std::cout << " tuple<int,int,int> {4,8,7) :" << GTypeList::Get<0>(my_tuple)<<" "<< GTypeList::Get<1>(my_tuple)<<" "<< GTypeList::Get<2>(my_tuple);
	GTypeList::Get<0>(my_tuple) = 9;
	GTypeList::Get<1>(my_tuple) = 9;
	GTypeList::Get<2>(my_tuple) = 9;
	std::cout << "\nAfter Modifying :" << GTypeList::Get<0>(my_tuple) << " " << GTypeList::Get<1>(my_tuple) << " " << GTypeList::Get<2>(my_tuple);
	std::cout << "\n" << sizeof(my_tuple);


	print_empty_lines(4);
}


int main()
{
	policy_based_design_demo();
	select_type_demo();
	type_to_type_demo();
	detect_inheritablity_and_conversion_at_runtime();
	is_same_demo();
	is_pointer();
	typelist_total_types();
	typelist_type_at();
	typelist_check_if_type_present_at();
	strip_const();
	strip_volt();
	erase_type();
	erase_type_all();
	replace_type();
	append_type();
	tuple_check();
	typelist_type_at_non_strict();
	functor_test();

	std::cin.get();
}

