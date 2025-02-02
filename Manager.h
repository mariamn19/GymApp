#pragma once
#include<iostream>
#include<fstream>
#include"Members.h"
#include"Activities.h"
#include"Attendance.h"
#include"MembershipPlan.h"

using namespace std;	
class GymManager {
	Member* members;
	Activity* activities;
	Attendance* attendances;
	MembershipPlan* plans;
	int gymCapacity;
	int memberCount;
public:
	GymManager(int capacity = 10) : gymCapacity(capacity), memberCount(0) {
		members = new Member[gymCapacity];
		activities = new Activity[gymCapacity];
		attendances = new Attendance[gymCapacity];
		plans = new MembershipPlan[gymCapacity];
	}

	int getMemberCount() const {
		return memberCount;
	}
	const MembershipPlan& getPlan() const { return *plans; }
	const Attendance& getAttendance() const { return *attendances; };
	const Activity& getActivity()const { return *activities; };
	Member* getMember(int index) const {
		if (index >= 0 && index < memberCount) {
			return &members[index];
		}
		return nullptr;
	}
	Attendance* getAttendance(int index) const {
		if (index >= 0 && index < memberCount) {
			return &attendances[index];
		}
		return nullptr;
	}
	Activity* getActivity(int index) const {
		if (index >= 0 && index < memberCount) {
			return &activities[index];
		}
		return nullptr;
	}
	void addMember(const char* name, int age, const char* membershipType) {
		if (memberCount < gymCapacity) {
			members[memberCount++] = Member(name, age, membershipType);
		}
		else {
			cout << "Member capacity of " << gymCapacity << " is reached!" << endl;
		}
	}
	void identifyTrendyMembershipPlan() {
		int planCount = 0;
		int* planCounts = new int[gymCapacity]();
		const char* trendyPlan = nullptr;
		int maxCount = 0;
		for (int i = 0; i < memberCount; ++i) {
			planCount++;
		}
		for (int i = 0; i < memberCount; ++i) {
			const char* membershipType = members[i].getmembershipType();
			if (membershipType == nullptr) continue;
			for (int j = 0; j < gymCapacity; ++j) {
				if (plans[j].getPlanName() == nullptr) continue;
				if (strcmp(membershipType, plans[j].getPlanName()) == 0) {
					planCounts[j]++;
					if (planCounts[j] > maxCount) {
						maxCount = planCounts[j];
						trendyPlan = plans[j].getPlanName();
					}
					break;
				}
			}
		}
		if (trendyPlan) {
			cout << "Trendy Membership Plan: " << trendyPlan << " with " << maxCount << " members." << endl;
		}
		else {
			cout << "No members found." << endl;
		}
		delete[] planCounts;
	}

	void showAttendanceByDate(const char* date) {
		cout << "Attendance records for date " << date << " are ";
		int attendanceCount = 0;
		/*for (int i = 0; i < memberCount; ++i) {
			if (strcmp(attendances[i].getLastAt(), date) == 0) {
				attendanceCount++;
			}
		}*/
		for (int i = 0; i < memberCount; ++i) {
			Attendance* attendance = getAttendance(i);
			if (attendance && strcmp(attendance->getLastAt(), date) == 0) {
				attendanceCount++;
			}
		}
		cout << attendanceCount << endl;
	}
	int calculateRevenue() {
		int totalRevenue = 0;
		for (int j = 0; j < gymCapacity; ++j) {
			if (plans[j].getPlanName() != nullptr) {
				totalRevenue += plans[j].getCost();
			}
			else return 0;
		}
		cout << "Total Revenue: $" << totalRevenue << endl;
		return totalRevenue;
	}

	void generateReport() {
		cout << "Total Members: " << memberCount << endl;
		identifyTrendyMembershipPlan();
		showAttendanceByDate("01-01-2025");
		calculateRevenue();
	}
	void displayMembers() const {
		cout << "Total Members: " << Member::getMemberCount() << endl;
		for (int i = 0; i < memberCount; ++i) {
			members[i].displayMemberIfno();
		}
	}
	~GymManager() {
		delete[] members;
		delete[] activities;
		delete[] attendances;
		delete[] plans;
	}
	void saveToBinaryFiles() {
		ofstream membersFile("members.dat", ios::binary);
		ofstream activitiesFile("activities.dat", ios::binary);
		ofstream attendancesFile("attendances.dat", ios::binary);
		ofstream plansFile("plans.dat", ios::binary);

		membersFile.write((char*)&memberCount, sizeof(memberCount));
		for (int i = 0; i < memberCount; ++i) {
			members[i].serialization();
		}
		for (int i = 0; i < memberCount; ++i) {
			activities[i].serialization();
		}
		for (int i = 0; i < memberCount; ++i) {
			attendances[i].serialization();
		}
		for (int i = 0; i < gymCapacity; ++i) {
			plans[i].serialization();
		}
		membersFile.close();
		activitiesFile.close();
		attendancesFile.close();
		plansFile.close();
	}
	void loadFromBinaryFiles() {
		ifstream membersFile("members.dat", ios::binary);
		ifstream activitiesFile("activities.dat", ios::binary);
		ifstream attendancesFile("attendances.dat", ios::binary);
		ifstream plansFile("plans.dat", ios::binary);

		if (membersFile.is_open()) {
			membersFile.read((char*)&memberCount, sizeof(memberCount));
			for (int i = 0; i < memberCount; ++i) {
				members[i].deserialization();
			}
		}
		if (activitiesFile.is_open()) {
			for (int i = 0; i < memberCount; ++i) {
				activities[i].deserialization();
			}
		}
		if (attendancesFile.is_open()) {
			for (int i = 0; i < memberCount; ++i) {
				attendances[i].deserialization();
			}
		}
		if (plansFile.is_open()) {
			for (int i = 0; i < gymCapacity; ++i) {
				plans[i].deserialization();
			}
		}
		membersFile.close();
		activitiesFile.close();
		attendancesFile.close();
		plansFile.close();
	}
};
static void menu(GymManager& gymManager) {
	int choice;
	do {
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice == 1) {
			// Logic to add a new member
			char name[50];
			int age;
			char membershipType[50];

			cout << "Enter member name: ";
			cin >> ws;
			cin.getline(name, 50);
			cout << "Enter member age: ";
			cin >> age;
			cout << "Enter membership type: ";
			cin >> ws;
			cin.getline(membershipType, 50);

			gymManager.addMember(name, age, membershipType);
			cout << "Member added successfully!" << endl;
			break;
		}
		else if (choice == 2) {
			// Logic to view attendance
			cout << "Attendance Records:" << endl;
			for (int i = 0; i < gymManager.getMemberCount(); ++i) {
				Attendance* attendance = gymManager.getAttendance(i);
				if (attendance) {
					attendance->displayAttendance();
				}
			}
			break;
		}
		else if (choice == 3) {
			// Logic to generate reports
			AttendanceReport attendanceReport(gymManager);
			RevenueReport revenueReport(gymManager);
			ActivityTrendReport activityTrendReport(gymManager);

			attendanceReport.generateReport();
			revenueReport.generateReport();
			activityTrendReport.generateReport();
			break;
		}
		else if (choice == 4) {
			cout << "Exiting..." << endl;
			break;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 4);
}
class ReportGenerator {
public:
	virtual void generateReport() = 0; // Pure virtual method
	virtual void displayReport() { // Non-pure virtual method
		cout << "Displaying report..." << endl;
	}
};

class AttendanceReport : public ReportGenerator {
	GymManager& gymManager;
public:
	AttendanceReport(GymManager& gm) : gymManager(gm) {}
	void generateReport() override {
		cout << "Generating Attendance Report..." << endl;
		for (int i = 0; i < gymManager.getMemberCount(); ++i) {
			Attendance* attendance = gymManager.getAttendance(i);
			if (attendance) {
				attendance->displayAttendance();
			}
		}
	}
};

class RevenueReport : public ReportGenerator {
	GymManager& gymManager;
public:
	RevenueReport(GymManager& gm) : gymManager(gm) {}
	void generateReport() override {
		cout << "Generating Revenue Report..." << endl;
		int totalRevenue = gymManager.calculateRevenue();
		cout << "Total Revenue: $" << totalRevenue << endl;
	}
};

class ActivityTrendReport : public ReportGenerator {
	GymManager& gymManager;
public:
	ActivityTrendReport(GymManager& gm) : gymManager(gm) {}
	void generateReport() override {
		cout << "Generating Activity Trend Report..." << endl;
		for (int i = 0; i < gymManager.getMemberCount(); ++i) {
			Activity* activity = gymManager.getActivity(i);
			if (activity) {
				activity->displayActivity();
			}
		}
	}
};
static void displayMenu() {
	cout << "***************GYM APP******************" << endl;
	cout << "        1. Add New Member" << endl;
	cout << "        2. View Attendance" << endl;
	cout << "        3. Generate Reports" << endl;
	cout << "        4. Exit" << endl;
}