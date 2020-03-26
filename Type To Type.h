#pragma once
#pragma once

#include<string>

namespace tp_to_type {
	
	

	class Widget {

		int some_required_value;
		std::string widget_name;
	public:
		Widget(int some_required_value, std::string widget_name) :some_required_value(some_required_value), widget_name(widget_name) {}
		auto getName() const {

			return widget_name;

		}

	};

	class TERA {

		std::string name;
	public:
		TERA(std::string name) :name(name) {}
		auto getName() const {
			return name;
		}

	};



	template<typename T>
	struct type_to_type {

		typedef T value_type;
	};

	template<unsigned n>
	struct int2type {

	  enum{value=n};

	};



	template<typename T, typename U>
	T* create(const U& arg, type_to_type<T>) {

		return new T(arg);

	}

	template<typename U>
	Widget* create(const U& arg, type_to_type<Widget>) {

		return new Widget(-1, arg);

	}


}