#pragma once

#include <iostream>

namespace policy_bs_design {
	class Widget {};

	template<typename T>
	class OPNewCreator {

	public:
		static T* create() {
			std::cout << "OPNewCreate::Create" << "\n";
			return new T;
		}

	};


	template<typename T>
	class MallocCreator {
	public:
		static T* create() {

			std::cout << "MallocCreator::Create" << "\n";
			void* rawbuffer = std::malloc(sizeof(T));
			if (!rawbuffer) {
				return nullptr;
			}
			return new (rawbuffer) T;
		}

	};

	template<typename T>
	class PrototypeBasedCreator {

		static T* ptr_prototype_obj = nullptr;
	public:
		PrototypeBasedCreator(T* ptr_proto = nullptr) :ptr_prototype_obj(ptr_proto) {}
		static T* getPrototype() {
			return ptr_prototype_obj;
		}
		static void setPrototype(T* ptr_proto) {
			ptr_prototype_obj = ptr_proto;
		}
		static T* create() {
			std::cout << "PrototypeBasedCreator::Create" << "\n";
			ptr_prototype_obj->clone();
		}
	};

	template< class Policy>
	class WidgetManager :Policy {
	public:
		void doSomething() {

			std::cout << "WidgetManager::doSomething()\n";
			create();
		}
	};
}


