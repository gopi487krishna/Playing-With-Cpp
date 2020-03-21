// Playing With C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Policy Based Design.h"


// Demonstrates the use of policy based design
void  policy_based_design_demo() {
	WidgetManager<OPNewCreator<Widget>> widget_manager;
	widget_manager.doSomething();

}

int main()
{
	policy_based_design_demo();
   
}

