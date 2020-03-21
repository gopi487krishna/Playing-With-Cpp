#pragma once
namespace Type_Traits {

	// is_same : Checks whether two types are same or not
	template<typename T, typename U> struct is_same { static const inline bool value = false; };
	template<typename T> struct is_same<T, T> { static const inline bool value = true;};

	// is_pointer : Checks whether a type is pointer or not
	template<typename T>struct is_pointer { static const inline bool value = false;};
	template<typename T>struct is_pointer<T*> { static const inline bool value = true; };

	
	
}