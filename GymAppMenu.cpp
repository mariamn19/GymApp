#include<iostream>
#include<fstream>
#include<vector>
#include"Members.h"
#include"Activities.h"
#include"Attendance.h"
#include"MembershipPlan.h"

using namespace std;

void addMembers() {
	vector<Member> members;
	string choice;
	do {
		Member m;
		cin >> m;
		members.push_back(m);

		cout << "Would you like to add another member? (yes/no): ";
		cin >> choice;
	} while (choice == "yes");

	cout << "Would you like to view the current members? (yes/no): ";
	cin >> choice;
	if (choice == "yes") {
		for (const auto& member : members) {
			cout << member;
		}
	}
}

void addPlans() {
	vector<MembershipPlan> plans;
	string choice;
	do {
		MembershipPlan mp;
		cout << "Enter details for a new plan: ";
		cin >> mp;
		plans.push_back(mp);

		cout << "Would you like to add another plan? (yes/no): ";
		cin >> choice;
	} while (choice == "yes");

	cout << "Would you like to view all the plans? (yes/no): ";
	cin >> choice;
	if (choice == "yes") {
		for (const auto& plan : plans) {
			cout << plan;
		}
	}

}

void addActivities() {
	vector<Activity> activities;
	string choice;
	do {
		Activity ac;
		cout << "Enter details for a new activity: ";
		cin >> ac;
		activities.push_back(ac);

		cout << "Would you like to add another activity? (yes/no): ";
		cin >> choice;
	} while (choice == "yes");

	cout << "Would you like to view the activities? (yes/no): ";
	cin >> choice;
	if (choice == "yes") {
		for (const auto& activity : activities) {
			cout << activity;
		}
	}
}

void viewAttendance() {
	vector<Attendance> attendances;
	char* choice{};
	do {
		Attendance ar;
		cin >> ar;
		attendances.push_back(ar);
		cout<<"Would you like to add another attendance? (yes/no): ";
		cin >> choice;
		} while (choice == "yes");
	cout << "Would you like to view the attendance? (yes/no): ";
	cin >> choice;
	if (choice == "yes") {
		for (const auto& attendance : attendances) {
			cout << attendance;
		}
	}
}

int main() {
	int choice;
	while (true) {
		cout << "***************GYM APP*****************" << endl;
		cout << "***What would you like to do?..." << endl;
		cout << "1. Add a member" << endl;
		cout << "2. Add plans" << endl;
		cout << "3. Add activities" << endl;
		cout << "4. View attendance" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";

		if (!(cin >> choice)) {
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
		switch (choice) {
		case 1:
			addMembers();
			break;
		case 2:
			addPlans();
			break;
		case 3:
			addActivities();
			break;
		case 4:
			viewAttendance();
			break;
		case 5:
			cout << "Exiting the application. Goodbye!" << endl;
			return 0;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}

	return 0;
}
