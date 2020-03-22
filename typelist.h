#pragma once

// The semantics of Typelist is similar to Linked List but everything is done at compile time and NOT for VALUES but TYPES!!!


// Represents a null type
struct NullType {};


// Basic datastructure for holding collection of  types
template<typename H, typename T>
struct TypeList {
	typedef H Head;
	typedef T Tail;
};


namespace GTypeList {

	// Getting length of TypeList
	// Basic Algorithm:
	/*
		if type is NullType
			return 0;
		else return 1+length( n-1 th list)


	*/

	template <class TList> struct Length;

	template<> struct Length<NullType> {
		enum { value = 0 };
	};

	template<typename T, typename U>struct Length<TypeList<T, U>> {

		enum { value = 1+ Length<U>::value};
	};



	// TypeatIndex	: TypeAtIndex simply provides the type at the given index
	// input		: A typlist and an index
	// output		: Result which contains the required type
	// Algorithm	:
	/*
		-> Its simple ! . Traverse the List  and decrease the index until it becomes 0 
		-> When it is 0 this means we have found the type
		-> Return that type safely to the original caller

	*/


	template<class TList, unsigned int index> struct typeAt;
	
	template<class Head, class Tail>struct typeAt<TypeList<Head,Tail>,0> {

		typedef Head Result;

	};

	template<class Head, class Tail, unsigned int index >struct typeAt<TypeList<Head, Tail>, index> {
		typedef typename typeAt<Tail, index - 1>::Result Result;

	};


	//indexOf(Type) : indexOf gets the index of type specified or -1 if not present ( Mind Blower )
	// input  : A type
	// output : A Compile time constant that depicts index
	/* Algorithm:
		Only linear search will work here due to the nature of list
		Now to search
		if TypeList(Head)== T
			return 0;
		else if TypeList(Head)== NullType
			return -1;
		else 
			set temp= algorithm(Typelist(Tail))::value
			set value = temp==-1?-1:1+temp;
	*/
	
	
	template<class Tlist, class T> struct indexOf;
	
	// If no match
	template<class T>struct indexOf<NullType, T> {
		enum { value = -1 };
	};
	template<class Tail, class T>struct indexOf<TypeList<T, Tail>, T> {
		enum{value=0};
	};


	template<class Head, class Tail, class T> struct indexOf<TypeList<Head, Tail>, T> {

	private:
		enum { temp = indexOf<Tail, T>::value };
	public:
		enum { value = temp == -1 ? -1 : 1 + temp };

	};


}

// Some repetition is there in basic version future versions should not have this problem( If you want to add more types just include your increased macro

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1, TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1, TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1, TYPELIST_4(T2,T3,T4,T5)>
