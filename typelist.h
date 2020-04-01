#pragma once
#include "Type To Type.h"


// The semantics of Typelist is similar to Linked List but everything is done at compile time and NOT for VALUES but TYPES!!!


// Represents a null type
struct NullType {};

// Represents Empty Type
struct EmptyType {};


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


	template<class TList, unsigned int index,class substype> struct TypeAtNonStrict;

	template<unsigned int index, class substype> struct TypeAtNonStrict<NullType, index, substype> {

		typedef substype Result;

	};

	template<class Head, class Tail, class substype> struct TypeAtNonStrict<TypeList<Head, Tail>, 0,substype> {


		typedef Head Result;

	};
	template<class Head, class Tail, unsigned int index, class substype> struct TypeAtNonStrict<TypeList<Head, Tail>, index, substype> {

		typedef typename TypeAtNonStrict<Tail, index - 1, substype>::Result Result;
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



	template<typename T>
	struct holder {
		typedef T holding_type;
		T value;
	};




	// Class Hierarchy Generator :  This class acts as a code generator for many different uses ( like tuple )
	// Input  : TypeList, Holder(Holds a value of required Type)
	// Output : A type that has publicly inherited itself from Holders of all the types in TypeList

	template<class TypeList, template<class> class Holder>
	struct HierarchyGen;

	template<class AtomicType, template<class> class Holder>
	struct HierarchyGen : public Holder<AtomicType> {

	    // Leftbase in all case represents the value Holder
		typedef Holder<AtomicType> LeftBase;
	};

	template<class Head,class Tail, template<class>class Holder>
	struct HierarchyGen < TypeList<Head, Tail>, Holder> : public HierarchyGen<Head, Holder>, public HierarchyGen<Tail, Holder> {

		typedef HierarchyGen<Head,Holder> LeftBase;
		typedef HierarchyGen<Tail,Holder> RightBase;
	};


	// If null type do nothing 
	template< template<class>class Holder>
	struct HierarchyGen< NullType, Holder> {};


	//At : This structure helps us in getting the type at given index
	// Input  : HierarchyGen , index
	// Output : The type at index
	// Algorithm:
	/*
	   if index is 0 then
		  Result = current_Hierarchygen::LeftBase
	   else 
		  Result = At<current_Hierarchygen::RightBase , index-1>
	
	*/

	// Primary template
	template<class hierarchgen, unsigned int index>
	struct At;

	
	template<class hierarchgen, unsigned int index>
	struct At {


		typedef typename At<typename hierarchgen::RightBase, index - 1>::Result Result;

	};

	template<class hierarchgen>
	struct At<hierarchgen,0> {

		typedef  typename hierarchgen::LeftBase Result;
	};




	// Functions cannot be partially specialized Hence the type2type and int2type trick is used
	template< class Hierarchy, class Result>
	inline Result& Get_Helper(Hierarchy& obj, tp_to_type::type_to_type<Result>, tp_to_type::int2type<0>){
		// Assign main object to the required type ( Perticular value instance ( Holder) will be then accessed )
		typename  Hierarchy::LeftBase& subobj= obj;
		return subobj;	
	}

	template<class Hierarchy,class Result, unsigned  index>
	inline Result& Get_Helper(Hierarchy& obj, tp_to_type::type_to_type<Result> dummy, tp_to_type::int2type<index>) {
		// Its traversing a hierarchy recursively
		typename  Hierarchy::RightBase& subobj = obj;
		return Get_Helper(subobj, dummy, tp_to_type::int2type<index - 1>());
	}


	template<unsigned index, class Hierarchy>
	typename At<Hierarchy, index>::Result::holding_type& Get(Hierarchy& obj) {

		typedef typename At<Hierarchy, index>::Result Result;
		return Get_Helper(obj, tp_to_type::type_to_type<Result>(), tp_to_type::int2type<index>()).value;
	}
}

// Some repetition is there in basic version future versions should not have this problem( If you want to add more types just include your increased macro

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1, TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1, TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1, TYPELIST_4(T2,T3,T4,T5)>
