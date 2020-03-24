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


	// Erase(Typelist, Type) : Provides a new typelist with the without the 'Type'
	// Input : Typelist , Type
	// Output : Result that gives the new typelist
	/* Algorithm :
	
		if TypeList is NullType and Type is T
			Result = NullType
		if TypeList is TypeList(T,Tail) and Type is T
			Result = Tail
		else  < Head, Tail, Type>
			Result= TypeList<Head,Erase<Tail,T>::Result>;	
	*/
	
	// Primary Template
	template<class Typelist, class Type> struct Erase {};
	template<class T> struct Erase<NullType, T> { typedef NullType Result; };
	template<class T, class Tail> struct Erase<TypeList<T, Tail>, T> { typedef Tail Result; };
	template<class Head, class Tail, class Type> struct Erase<TypeList<Head, Tail>, Type> { typedef TypeList < Head, typename Erase<Tail, Type>::Result> Result; };


	// Erase All ( Typelist, Type) : Same as erase but removes every occurence of type
	template<class Typelist, class Type> struct Erase_ALL {};
	template<class T> struct Erase_ALL<NullType, T> { typedef NullType Result; };
	template<class T, class Tail> struct Erase_ALL<TypeList<T, Tail>, T> { typedef typename Erase_ALL<Tail, T>::Result Result; };
	template<class Head, class Tail, class Type> struct Erase_ALL<TypeList<Head, Tail>, Type> { typedef TypeList < Head, typename Erase_ALL<Tail, Type>::Result> Result; };

	//Replace ( TypeList, OldType, NewType) : Replaces the occurence of OldType with NewType
	// Input  : TypeList, OldType, NewType
	// Output : Result
	/* Algorithm:
	
		if(Typelist is NullType) then
		Result = NullType
		else if TypeList is Typelist<OldEL,Tail> 
		then  Result =TypeList<Newel, Tail>
		else< Head, Tail, OldEl, NewEl> 
		 Result = TypeList<Head, Replace<Tail,OldEl,NewEl>::Result >
	*/

	//Primary template
	template<class TypeList, class OldType, class NewType> struct Replace;
	template<class OldEl, class NewEl> struct Replace<NullType, OldEl, NewEl> { typedef NullType Result; };
	template<class OldEl, class NewEl, class Tail> struct Replace<TypeList<OldEl, Tail>, OldEl, NewEl> { typedef TypeList<NewEl, Tail> Result; };
	template<class Head, class Tail, class OldEl, class NewEl> struct Replace<TypeList<Head,Tail>,OldEl,NewEl> { typedef TypeList< Head, typename Replace<Tail, OldEl, NewEl>::Result> Result; };


	// Append : Appends a type to the typelist
	// Input  : Typelist and Type
	// Output : New Typelist with added type
	/* Algorithm
	  if TypeList is NullType and Type is T
	     Result= TypeList<T,NullType>
	 else if TypeList is TypeList(head, tail ) and Type is NullType
		Result = TypeList(head,tail)

	else< Head, Tail ,Type>
		Result= TypeList ( Head, Append(Tail,T)::Result )	
	*/

	template<class TypeList, class Type> struct Append;
	template<class T> struct Append<NullType, T> { typedef TypeList<T, NullType> Result;};
	template<class Head, class Tail>struct Append<TypeList<Head, Tail>, NullType> { typedef TypeList<Head, Tail> Result; };
	template<class Head, class Tail, class T> struct Append<TypeList<Head, Tail>, T> { typedef TypeList < Head, typename Append<Tail, T>::Result> Result; };



}

// Some repetition is there in basic version future versions should not have this problem( If you want to add more types just include your increased macro

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1, TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1, TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1, TYPELIST_4(T2,T3,T4,T5)>
