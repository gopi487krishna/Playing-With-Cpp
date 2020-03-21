#pragma once
#include<algorithm>
#include<string>
#include <typeinfo>
// type_info class  by default limits the user of its abilities such as assignment and copy construction
// This class is a wrapper around type info to give back its abilities
class TypeInfo {

public:
	// For containers;
	TypeInfo();
	TypeInfo(const type_info& typeinformation):typeinfo(&typeinformation) {}
	TypeInfo(const TypeInfo& typeinformation):typeinfo(typeinformation.typeinfo){}
	TypeInfo& operator= (const TypeInfo& typeinformation)  {
		

		this->typeinfo = typeinformation.typeinfo;	
	}
	bool before(const TypeInfo& typeinformation)const  {
		return typeinfo->before(*typeinformation.typeinfo);
	}

	std::string name() {
		return std::string(typeinfo->name());
	}
private:
	const type_info*typeinfo;
	friend bool operator == (const TypeInfo& lhs, const TypeInfo& rhs);
	friend bool operator != (const TypeInfo& lhs, const TypeInfo& rhs);
	friend bool operator <  (const TypeInfo& lhs, const TypeInfo& rhs);
	friend bool operator <= (const TypeInfo& lhs, const TypeInfo& rhs);
	friend bool operator >  (const TypeInfo& lhs, const TypeInfo& rhs);
	friend bool operator >= (const TypeInfo& lhs, const TypeInfo& rhs);

};


bool operator == (const TypeInfo& lhs, const TypeInfo& rhs) {
	return lhs.typeinfo == rhs.typeinfo;
	 
}
bool operator != (const TypeInfo& lhs, const TypeInfo& rhs) {
	return lhs.typeinfo != rhs.typeinfo;
}
 bool operator <  (const TypeInfo& lhs, const TypeInfo& rhs) {
	return lhs.before(rhs);
}
 bool operator <= (const TypeInfo& lhs, const TypeInfo& rhs) {
	 return lhs.before(rhs) || lhs == rhs;
}
 bool operator >  (const TypeInfo& lhs, const TypeInfo& rhs) {
	 return !(lhs.before(rhs)) && lhs != rhs;
}
 bool operator >= (const TypeInfo& lhs, const TypeInfo& rhs) {
	 return !(lhs.before(rhs));
}



