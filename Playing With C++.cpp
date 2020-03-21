// Playing With C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Policy Based Design.h"
#include "Conditional Select Impl.h"
#include "Type To Type.h"


auto print80dash() {

	static std::string dash_string(80, '-');
	std::cout << dash_string;
}

// Demonstrates the use of policy based design
void  policy_based_design_demo() {
	WidgetManager<OPNewCreator<Widget>> widget_manager;
	widget_manager.doSomething();
	print80dash();
}

// Demonstrates the std::conditional's implementation
void select_type_demo() {

	select_type<false, int, float>::type t = 6;
	std::cout << t<<'\n';
	print80dash();
}

// Shows the use of type to type struct
void type_to_type_demo() {
	auto TERA_instance = create(std::string("FirstWidget"), type_to_type<TERA>());
	auto widget_instance = create(std::string("FirstWidget"), type_to_type<Widget>());

	std::cout << "WIDGET : " << widget_instance->getName() << "\n";
	std::cout << "TERA : " << widget_instance->getName() << "\n";
	print80dash();
}




int main()
{
	policy_based_design_demo();
	select_type_demo();
	type_to_type_demo();
   
	std::cin.get();
}

