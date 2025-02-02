#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class MembershipPlan {
private:
	char* planName = nullptr;
	int duration = 0; //in days
	int costPlan = 0;
	int nrOfBenefits = 0;
	char* benefits = nullptr;
	//char** benefits=nullptr; //it will be an array of benefits
	//i tried so hard and got so far but in the end it doesnt even matter

public:

	char* getPlanName() {
		if (planName == nullptr) return nullptr;
		char* copy = new char[strlen(planName) + 1];
		strcpy(copy, this->planName);
		return copy;
	}
	void setPlanName(const char* newplanname) {
		if (newplanname != nullptr) {
			delete[]planName;
			this->planName = new char[strlen(newplanname) + 1];
			strcpy(this->planName, newplanname);
		}
	}
	int getDuration() {
		return this->duration;
	}
	void setDuration(int newdur) {
		if (newdur > 0) {
			this->duration = newdur;
		}
	}
	int getNrOfBene() {
		return this->nrOfBenefits;
	}
	void setNrOfBen(int newNrBEn) {
		this->nrOfBenefits = newNrBEn;
	}
	char* getBenefits() {
		if (benefits == nullptr) return nullptr;
		if (nrOfBenefits == 0) return nullptr;
		char* copy = new char[strlen(benefits) + 1];
		strcpy(copy, this->benefits);
		return copy;
	}
	void setBenefits(const char* newBenefits, int newnrofben) {
		if (newBenefits != nullptr && newnrofben != 0) {
			delete[]benefits;
			this->nrOfBenefits = newnrofben;
			this->benefits = new char[strlen(newBenefits) + 1];
			strcpy(this->benefits, newBenefits);
		}
		else {
			delete[] benefits;
			benefits = nullptr;
			nrOfBenefits = 0;
		}
	}
	int getCost() {
		return this->costPlan;
	}
	void setCost(int newcost) {
		this->costPlan = newcost;
	}
	void displayMEmbPlan() const {
		cout << "Plan Name: " << planName << ", Duration: " << duration << " days, Cost: " << costPlan << ", Benefits: " << benefits << endl;
	}
	MembershipPlan() {}
	MembershipPlan(const char* planName, int duration, int cost) {
		setPlanName(planName);
		setDuration(duration);
		setCost(cost);
	}
	MembershipPlan(const char* planName, int dur, int cost, int nrben, const char* benefits) {
		setPlanName(planName);
		setDuration(dur);
		setCost(cost);
		setNrOfBen(nrben);
		setBenefits(benefits, nrben);
	}
	MembershipPlan(const MembershipPlan& mp) {
		//setPlanName(mp.getPlanName());
		//setDuration(mp.getDuration());
		//setCost(mp.getCost());
		//setNrOfBen(mp.getNrOfBene());
		////char** benefitscopy = mp.getBenefits();
		////setBenefits(mp.getBenefits(), mp.getNrOfBene());
		//setBenefits(mp.getBenefits(), mp.getNrOfBene());
		if (mp.planName != nullptr) {
			this->planName = new char[strlen(mp.planName) + 1];
			strcpy(this->planName, mp.planName);
		}
		this->duration = mp.duration;
		this->costPlan = mp.costPlan;
		this->nrOfBenefits = mp.nrOfBenefits;

		if (mp.benefits != nullptr && mp.nrOfBenefits > 0) {
			this->benefits = new char[mp.nrOfBenefits];
			for (int i = 0; i < mp.nrOfBenefits; ++i) {
				this->benefits = new char[strlen(mp.benefits) + 1];
				strcpy(this->benefits, mp.benefits);
			}
		}
		else {
			this->benefits = nullptr;
			this->nrOfBenefits = 0;
		}
	}

	MembershipPlan& operator=(const MembershipPlan& mp) {
		if (this != &mp) {
			if (planName != nullptr) {
				delete[]planName;
				this->planName = nullptr;
				this->planName = new char[strlen(mp.planName) + 1];
				strcpy(this->planName, mp.planName);
			}
			this->duration = mp.duration;
			this->costPlan = costPlan;
			this->nrOfBenefits = mp.nrOfBenefits;
			if (benefits != nullptr) {
				delete[]benefits;
				this->benefits = nullptr;
				this->benefits = new char[strlen(mp.benefits) + 1];
				strcpy(this->benefits, mp.benefits);
			}
			return *this;
		}
	}
	int operator+=(int newcost) {
		this->costPlan += newcost;
		return this->costPlan;
	}
	char operator[](int index) {
		return planName[index];
	}
	bool operator<(const MembershipPlan& other) const {
		return this->duration < other.duration;
	}
	bool operator>=(const MembershipPlan& other) const {
		return this->duration >= other.duration;
	}
	bool operator==(const MembershipPlan& nm) const {
		return (strcmp(this->planName, nm.planName) == 0);
	}
	bool operator!=(const MembershipPlan& nm) {
		if (strcmp(this->planName, nm.planName) == 0) return true;
		return false;
	}
	bool operator==(const MembershipPlan& nm) {
		if (strcmp(this->planName, nm.planName) == 0)return false;
		return true;
	}
	//these operator it will be efficiently for discounts or price increases
	/*int operator+=(int newcost) {
		this->costPlan += newcost;
		return this->costPlan;
	}*/ //already defined
	int operator-=(int newcost) {
		this->costPlan -= newcost;
		return this->costPlan;
	}
	~MembershipPlan() {
		if (planName != nullptr) {
			delete[]planName;
			this->planName = nullptr;
		}
		if (benefits != nullptr) {
			delete[] benefits;
			benefits = nullptr;
		}
	}
	void serialization() {
		ofstream f("plans.bin", ios::binary);
		if (!f) {
			cout << "Error opening file for writing!" << endl;
			return;
		}
		int length = strlen(planName);
		f.write((char*)&length, sizeof(length));
		if (planName) f.write(planName, length + 1);
		f.write((char*)&duration, sizeof(duration));
		f.write((char*)&costPlan, sizeof(costPlan));

		length = strlen(benefits);
		f.write((char*)&length, sizeof(length));
		if (benefits) f.write(benefits, length + 1);

		cout << "Membership Plan serialized..." << endl;
		f.close();
	}

	void deserialization() {
		ifstream f("plans.bin", ios::binary);
		if (!f) {
			cout << "Error opening file!" << endl;
			return;
		}

		int length;
		f.read((char*)&length, sizeof(length));
		delete[] planName;
		if (length > 0) {
			planName = new char[length + 1];
			f.read(planName, length + 1);
		}
		else {
			planName = nullptr;
		}
		f.read((char*)&duration, sizeof(duration));
		f.read((char*)&costPlan, sizeof(costPlan));

		f.read((char*)&length, sizeof(length));
		delete[] benefits;
		if (length > 0) {
			benefits = new char[length + 1];
			f.read(benefits, length + 1);
		}
		else {
			benefits = nullptr;
		}

		cout << "Membership Plan deserialized successfully..." << endl;
		f.close();
	}
	friend ostream& operator<<(ostream& out, const MembershipPlan& mp) {
		out << mp.planName << endl;
		out << mp.duration << endl;
		out << mp.costPlan << endl;
		out << mp.nrOfBenefits << endl;
		out << mp.benefits << endl;
		return out;
	}
	friend istream& operator>>(istream& in, MembershipPlan& mp) {
		cout << "If you dont want to enter a new object enter 'exit'" << endl;
		cout << "Name of the plan: ";
		char aux[51];
		in >> ws;
		in.getline(aux, 50);
		if (strcmp(aux, "exit") == 0) {
			cout << "Just stopped the reading";
			return in;
		}
		delete[]mp.planName;
		mp.planName = new char[strlen(aux) + 1];
		strcpy(mp.planName, aux);

		cout << "Duration (in days): ";
		in >> mp.duration;
		cout << "Cost of the plan: ";
		in >> mp.costPlan;
		cout << "Nr of benefits: ";
		in >> mp.nrOfBenefits;
		cout << "Write " << mp.nrOfBenefits << " benefit/s:  ...  ";
		in >> ws;
		in.getline(aux, 100);
		delete[]mp.benefits;
		mp.benefits = new char[strlen(aux) + 1];
		strcpy(mp.benefits, aux);
		return in;
	}
};