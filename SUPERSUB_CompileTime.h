#pragma once

//Detecting inheritance and convertiblity at runtime
namespace convertiblity_at_runtime {
	template<typename T, typename U>
	class Conversion {

		
		typedef char SmallType;
		struct BigType { int dummy; };

		// In case T's default ctor is private or protected
		static T makeT();

		// Selects this overload if U is base of T ( or any ctor exists). No need to define it!!!
		static SmallType Test(U);
		// Selects  this overload if any other ( Templates cannot be used as they would be the best match always shadowing the above overload )
		static BigType Test(...);

	public:
		// If SmallType is expressions result type based on overloading rules ( sizeof will not evaluate expr ) then inherited and convertible
		
		const inline static auto exists = sizeof(Test(makeT())) == sizeof(SmallType);
		

	};
}