#pragma once

namespace strip_cv {

	// unconst : Removes the const specifier from the Type and gives back the type
	template<typename T> struct un_const { typedef T Type; };
	template<typename T> struct un_const<const T> { typedef T Type; };

	// unvolt  : Removes the volatile specifier from the Type and gives it back
	template<typename T> struct un_volt { typedef T Type; };
	template<typename T> struct un_volt<volatile T> { typedef T Type; };
}
