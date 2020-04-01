#pragma once
#include "typelist.h"
#include <memory>


// Primary template
template<class R, class TList>
class FunctorImpl;

// Partial Specialization for FunctorImpl
template<class R>
class FunctorImpl<R, NullType> {

public:
	virtual R operator ()() = 0;
	virtual FunctorImpl* clone()const =0;
	virtual ~FunctorImpl() {}

};

template<class R, class T1>
class FunctorImpl<R, TYPELIST_1(T1)> {

public:
	virtual R operator ()(T1) = 0;
	virtual FunctorImpl* clone()const = 0;
	virtual ~FunctorImpl() {}
};

template<class R, class T1,class T2>
class FunctorImpl<R, TYPELIST_2(T1,T2)> {

public:
	virtual R operator ()(T1,T2) = 0;
	virtual FunctorImpl* clone()const = 0;
	virtual ~FunctorImpl() {}
};




template<class ParentFunctor, class Func>
class FunctorHandler :public FunctorImpl<typename ParentFunctor::Result_Type, typename ParentFunctor::ParamList> {

public:
	FunctorHandler(const Func& func) : func(func) {}
	FunctorHandler* clone()const { return new FunctorHandler(*this); }
	typename ParentFunctor::Result_Type operator()() { return func(); }
	typename ParentFunctor::Result_Type operator()(typename ParentFunctor::Param1 v1) { return func(v1); }
	typename ParentFunctor::Result_Type operator()(typename ParentFunctor::Param1 v1, typename ParentFunctor::Param2 v2) { return func(v1,v2); }

private:
	Func func;

};


template<class R, class TList>
class Functor {

public:

	typedef TList ParamList;
	typedef R Result_Type;
	typedef typename GTypeList::TypeAtNonStrict<TList, 0, EmptyType>::Result Param1;
	typedef typename GTypeList::TypeAtNonStrict<TList, 1, EmptyType>::Result Param2;
	


	R operator()() { return (*func_impl)();}
	R operator() (Param1 p1) { return (*func_impl)(p1);}
	R operator() (Param1 p1,Param2 p2) { return (*func_impl)(p1,p2);}

	
	template<typename Func>
	Functor<R,TList>(const Func& func):func_impl( new FunctorHandler<Functor,Func>(func))  {}


	
	Functor() {}
	Functor(const Functor& other_functor) :func_impl(other_functor.func_impl) {}
	explicit Functor(std::unique_ptr<FunctorImpl<R, TList>>o_func_impl) :func_impl(o_func_impl) {}


private:
	std::unique_ptr<FunctorImpl<R, TList>>func_impl;

};

