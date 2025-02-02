#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class Member {
	char* name = nullptr;
	int age = 0;
	char* membershipType = nullptr;
	static int memberCount;
	//forget about this, i tried to assign a 1:1 relationship so every member should have only one activity, attendance etc
	/*MembershipPlan membershipPlan;
	Activity activities;
	Attendance attendance;*/
public:
	Member() { memberCount++; }
	char* getName() {
		char* copy = new char[strlen(this->name) + 1];
		strcpy(copy, this->name);
		return copy;
	}
	void setName(const char* newname) {
		if (newname != nullptr) {
			delete[]name;
			name = new char[strlen(newname) + 1];
			strcpy(name, newname);
		}
		else {
			cerr << "Memory allocation failed for name." << endl;
		}
	}
	int getAge() {
		return this->age;
	}
	void setAge(int newAge) {
		if (newAge != 0) {
			this->age = newAge;
		}
	}
	char* getmembershipType() {
		char* copy = new char[strlen(this->membershipType) + 1];
		strcpy(copy, this->membershipType);
		return copy;
	}
	void setmembershipType(const char* newmem) {
		if (newmem != nullptr) {
			delete[]membershipType;
			this->membershipType = nullptr;
			this->membershipType = new char[strlen(newmem) + 1];
			strcpy(this->membershipType, newmem);
		}
	}
	static int getMemberCount() {
		return memberCount;
	}
	void displayMemberIfno() const {
		cout << "Name: " << name << ", Age: " << age << ", Membership Type: " << membershipType << std::endl;
	}
	Member(const char* name, int age, const char* me) {
		setName(name);
		setAge(age);
		setmembershipType(me);
	}

	Member(const Member& m) {
		/*setName(m.getName());
		setAge(m.getAge());
		setmembershipType(m.getmembershipType());*/
		if (m.name != nullptr) {
			delete[]name;
			name = new char[strlen(m.name) + 1];
			strcpy(name, m.name);
		}
		if (m.age != 0) {
			this->age = m.age;
		}
		if (m.membershipType != nullptr) {
			delete[]membershipType;
			this->membershipType = nullptr;
			this->membershipType = new char[strlen(m.membershipType) + 1];
			strcpy(this->membershipType, m.membershipType);
		}
	}
	Member& operator=(const Member& m) {
		if (this != &m) {
			delete[]name;
			delete[]membershipType;
			if (m.name != nullptr) {
				this->name = new char[strlen(m.name) + 1];
				strcpy(this->name, m.name);
			}
			this->age = m.age;
			if (m.membershipType != nullptr) {
				this->membershipType = new char[strlen(m.membershipType) + 1];
				strcpy(this->membershipType, m.membershipType);
			}
			/*membershipPlan = m.membershipPlan;
			attendance = m.attendance;
			activities = m.activities;*/

		}
		return *this;
	}
	//Input (>>) and output (<<).
	//Indexing([]), at least one arithmetic(+, -, etc.), increment / decrement
	//(++, --), negation(!), conditional(< , >= , etc.), and equality(== ).

	//what if we do the index op for membershipType
	//so we can return the first letter of
	//Premium - p
	//Standard - s and so on

	char operator[](int index) {
		return membershipType[index];
	}
	Member operator++() {
		this->memberCount++;
	}
	bool operator!() const {
		return age == 0;
	}
	bool operator<(const Member& nm) const {
		return this->age < nm.age;
	}
	bool operator>=(const Member& nm) const {
		return this->age >= nm.age;
	}
	bool operator==(const Member& nm) const {
		return (strcmp(this->name, nm.name) == 0) && (this->age == nm.age);
	}
	bool operator!=(const Member& m) {
		if (strcmp(this->membershipType, m.membershipType) == 0) return true;
		return false;
	}
	bool operator==(const Member& m) {
		if (strcmp(this->membershipType, m.membershipType) == 0)return false;
		return true;
	}
	/*bool operator<(const Member& m) const {
		return this->age <= m.age;
	}*/ //already defined
	bool operator>(const Member& m) const {
		return this->age >= m.age;
	}
	~Member() {
		if (this->name != nullptr) {
			delete[]name;
			this->name = nullptr;
		}
		if (this->membershipType != nullptr) {
			delete[]membershipType;
			this->membershipType = nullptr;
		}
	}
	void serialization() {
		ofstream f("members.bin", ios::binary);
		int length = strlen(this->name);
		f.write((char*)&length, sizeof(length));
		f.write(this->name, length + 1);
		f.write((char*)&this->age, sizeof(this->age));

		length = strlen(this->membershipType);
		f.write((char*)&length, sizeof(length));
		f.write(this->membershipType, length + 1);

		cout << "Member serialized successfully!" << endl;
		f.close();
	}
	void deserialization() {
		ifstream f("members.bin", ios::binary);
		if (!f) {
			cout << "Error opening file!" << endl;
			return;
		}

		int length;
		f.read((char*)&length, sizeof(int));
		this->name = new char[length + 1];
		f.read(this->name, length + 1);
		f.read((char*)&this->age, sizeof(this->age));

		f.read((char*)&length, sizeof(int));
		this->membershipType = new char[length + 1];
		f.read(this->membershipType, length + 1);

		cout << "Member deserialized successfully!" << endl;
		f.close();
	}
	friend ostream& operator<<(ostream& out, const Member& m) {
		out << m.name << endl;
		out << m.age << endl;
		out << m.membershipType << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Member& m) {
		cout << "If you dont want to enter a new object enter 'exit'" << endl;
		cout << "Name of the member: ";
		//in >> m.name;
		char aux[51];
		in >> ws;
		in.getline(aux, 50);
		if (strcmp(aux, "exit") == 0) {
			cout << "Just stopped the reading";
			return in;
		}
		delete[]m.name;
		m.name = new char[strlen(aux) + 1];
		strcpy(m.name, aux);

		cout << "Age: ";
		in >> m.age;
		cout << "Membership type: ";
		//in>>m.membershipType
		in >> ws;
		//getline(in, m.membershipType);
		in.getline(aux, 100);
		delete[]m.membershipType;
		m.membershipType = new char[strlen(aux) + 1];
		strcpy(m.membershipType, aux);
		return in;
	}
};
int Member::memberCount = 0;
class PremiumMember : public Member {
private:
	char* premiumLevel = nullptr;
	float discountPercentage = 0.0f;

public:
	PremiumMember(const char* name, int age, const char* membershipType, const char* premiumLevel, float discount)
		: Member(name, age, membershipType) {
		setPremiumLevel(premiumLevel);
		setDiscount(discount);
	}
	~PremiumMember() {
		delete[] premiumLevel;
	}
	void setPremiumLevel(const char* level) {
		if (level != nullptr) {
			delete[] premiumLevel;
			premiumLevel = new char[strlen(level) + 1];
			strcpy(premiumLevel, level);
		}
	}
	char* getPremiumLevel() {
		char* copy = new char[strlen(this->premiumLevel) + 1];
		strcpy(copy, this->premiumLevel);
		return copy;
	}
	void setDiscount(float discount) {
		if (discount >= 0.0f && discount <= 100.0f) {
			discountPercentage = discount;
		}
	}
	float getDiscount() const {
		return discountPercentage;
	}
};