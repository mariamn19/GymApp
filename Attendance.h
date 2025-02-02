#pragma once
#include<iostream>
#include<fstream>	
using namespace std;

class Attendance {
	int nrDays = 0;
	int* hours = nullptr;
	char* lastAttendance = nullptr;
public:
	int getNrdays() {
		return nrDays;
	}
	void setNrdays(int newnrdays) {
		this->nrDays = newnrdays;
	}
	int* getHours() {
		if (nrDays == 0)return nullptr;
		int* copy = new int[nrDays];
		for (int i = 0; i < nrDays; i++) {
			copy[i] = hours[i];
		}
		return copy;
	}
	void setHours(const int* nh, int ndays) {
		delete[]hours;
		if (ndays != 0 && nh != 0) {
			this->hours = new int[ndays];
			for (int i = 0; i < ndays; i++) {
				this->hours[i] = nh[i];
			}
			nrDays = ndays;
		}
		else {
			this->hours = nullptr;
			nrDays = 0;
		}
	}
	char* getLastAt() {
		if (lastAttendance != nullptr) {
			char* copy = new char[strlen(this->lastAttendance) + 1];
			strcpy(copy, this->lastAttendance);
			return copy;
		}
	}
	void setLastAt(const char* newat) {
		if (newat != nullptr) {
			lastAttendance = new char[strlen(newat) + 1];
			strcpy(lastAttendance, newat);
		}
		else lastAttendance = nullptr;
	}
	void displayAttendance() const {
		cout << "Number of Days: " << nrDays << ", Last Attendance: " << lastAttendance << endl;
	}
	Attendance() {}
	Attendance(int nrdays, const int* hours) {
		setNrdays(nrdays);
		setHours(hours, nrdays);
	}
	Attendance(int nrDays, const char* lastAttendance) {
		this->nrDays = nrDays;
		this->hours = new int[nrDays]; // Assuming hours for each day
		this->lastAttendance = new char[strlen(lastAttendance) + 1];
		strcpy(this->lastAttendance, lastAttendance);
	}
	Attendance(int nrdays, const int* hours, const char* newdate) {
		setNrdays(nrdays);
		setHours(hours, nrdays);
		setLastAt(newdate);
	}
	Attendance(const Attendance& at) {
		this->nrDays = at.nrDays;
		setHours(at.hours, at.nrDays);
		/*if (at.nrDays != 0) {
			this->hours = new int[at.nrDays];
			for (int i = 0; i < at.nrDays; i++)
				this->hours[i] = at.hours[i];
		}
		else {
			this->hours = nullptr;
		}*/
		if (at.lastAttendance != nullptr) {
			this->lastAttendance = new char[strlen(at.lastAttendance) + 1];
			strcpy(this->lastAttendance, at.lastAttendance);
		}
	}
	Attendance& operator=(const Attendance& at) {
		if (this != &at) {
			delete[] hours;
			delete[]lastAttendance;
			this->nrDays = at.nrDays;
			if (at.hours != nullptr) {
				this->hours = new int[at.nrDays];
				for (int i = 0; i < at.nrDays; i++)
					this->hours[i] = at.hours[i];
			}
			else {
				this->hours = nullptr;
			}
			if (at.lastAttendance != nullptr) {
				this->lastAttendance = new char[strlen(at.lastAttendance) + 1];
				strcpy(this->lastAttendance, at.lastAttendance);
			}
		}
		return *this;
	}
	//increasing the nr of days and adding the hours corresponding
	/*Attendance& operator+=(Attendance& at) {
		this->nrDays = at.nrDays;
		int daysToAdd = at.nrDays-this->nrDays;
		for (int i = this->nrDays; i < at.nrDays; i++) {
			this->hours[i] = at.hours[i];
		}
		return *this;}*/
	bool operator==(const Attendance& at) const {
		if (this->nrDays != at.nrDays) return false;
		for (int i = 0; i < this->nrDays; i++) {
			if (this->hours[i] != at.hours[i]) return false;
		}
		return (strcmp(this->lastAttendance, at.lastAttendance) == 0);
	}
	//to get a specific nr of hours in a specific day
	char operator[](int index) {
		return this->hours[index];
	}
	bool operator!=(const Attendance& at) const {
		return !(*this == at);
	}
	bool operator!=(const Attendance& at) {
		if (this->nrDays != at.nrDays) return true;
		return false;
	}
	bool operator==(const Attendance& at) {
		if (this->nrDays != at.nrDays) return false;
		return true;
	}
	bool operator<(const Attendance& nm) const {
		return this->nrDays < nm.nrDays;
	}
	bool operator>=(const Attendance& nm) const {
		return this->nrDays >= nm.nrDays;
	}
	//i dont think this will be relatable, 
	//it will be more corrct to assign the newnrdays to the nrdays of current object
	//rather than adding them up
	int operator+=(int newdays) {
		this->nrDays += newdays;
		return this->nrDays;
	}

	~Attendance() {
		if (hours != nullptr)
			delete[]hours;
		if (lastAttendance != nullptr)
			delete[]lastAttendance;
	}
	void serialization() const {
		ofstream f("attendance.bin", ios::binary | ios::app);
		f.write((char*)&nrDays, sizeof(nrDays));
		f.write((char*)hours, nrDays * sizeof(int));

		int length = strlen(lastAttendance);
		f.write((char*)&length, sizeof(length));
		f.write(lastAttendance, length + 1);

		cout << "Attendance serialized successfully!" << endl;
		f.close();
	}
	void deserialization() {
		ifstream f("attendance.bin", ios::binary);
		if (!f) {
			cout << "Error opening file!" << endl;
			return;
		}

		f.read((char*)&nrDays, sizeof(nrDays));
		hours = new int[nrDays];
		f.read((char*)hours, nrDays * sizeof(int));

		int length;
		f.read((char*)&length, sizeof(length));
		lastAttendance = new char[length + 1];
		f.read(lastAttendance, length + 1);

		cout << "Attendance deserialized successfully!" << endl;
		f.close();
	}
	friend ostream& operator<<(ostream& out, const Attendance& at) {
		out << "Nr of Days: " << at.nrDays << "\nHours: ";
		if (at.hours != nullptr)
			for (int i = 0; i < at.nrDays; i++) {
				out << at.hours[i] << " ";
			}
		if (at.lastAttendance != nullptr)
			out << "\nLast Attendance: " << at.lastAttendance << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Attendance& at) {
		cout << "Nr of days: ";
		in >> at.nrDays;
		cout << "Hours: (enter " << at.nrDays << ")...";
		delete[]at.hours;
		at.hours = new int[at.nrDays];
		for (int i = 0; i < at.nrDays; i++) {
			in >> at.hours[i];
		}
		cout << "Last attendance: (please enter a date in format dd-mm-yyy)...";
		char aux[51];
		in >> ws;
		in.getline(aux, 51);
		delete[]at.lastAttendance;
		at.lastAttendance = new char[strlen(aux) + 1];
		strcpy(at.lastAttendance, aux);
		//in >> at.lastAttendance;
		return in;
	}
};