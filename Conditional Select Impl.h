#pragma once
template<bool test, typename T1, typename T2>
struct select_type {

	typedef T2 type;

};

template<typename T1, typename T2>
struct select_type<true, T1, T2> {

	typedef T1 type;

};

