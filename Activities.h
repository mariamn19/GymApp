#pragma once
#include<iostream>
#include<fstream>

using namespace std;
class Activity {
	char* typeActivity = nullptr;
	int duration = 0;
	int caloriesBurned = 0;
	int sets = 0; //how many sets to do for each activity
	int* moves = nullptr; //and how many moves in each set to execute
public:
	char* getTypeActivity() {
		if (typeActivity) {
			char* copy = new char[strlen(typeActivity) + 1];
			strcpy(copy, this->typeActivity);
			return copy;
		}
		return nullptr;
	}
	void setTypeActivity(const char* newType) {
		if (newType != nullptr) {
			delete[]typeActivity;
			this->typeActivity = nullptr;
			this->typeActivity = new char[strlen(newType) + 1];
			strcpy(this->typeActivity, newType);
		}
	}
	int getDuration() {
		return this->duration;
	}
	void setDuratino(int newdur) {
		this->duration = newdur;
	}
	int getCalories() {
		return this->caloriesBurned;
	}
	void setCalories(int newcal) {
		this->caloriesBurned = newcal;
	}
	int getSets() {
		return this->sets;
	}
	void setSets(int newset) {
		this->sets = newset;
	}
	int* getMoves() {
		if (sets == 0) return nullptr;
		int* v = new int[sets];
		for (int i = 0; i < sets; i++) {
			v[i] = moves[i];
		}
		return v;
	}
	void setMoves(const int* newmoves, int sets) {
		delete[]moves;
		if (newmoves && sets != 0) {
			this->moves = new int[sets];
			for (int i = 0; i < sets; ++i) {
				this->moves[i] = newmoves[i];
			}
			sets = 0;
		}
		else {
			this->moves = nullptr;
			sets = 0;
		}
	}
	void displayActivity() const {
		cout << "Activity: " << typeActivity << ", Duration: " << duration << " mins, Calories Burned: " << caloriesBurned << ", Sets: " << sets << endl;
	}
	Activity() {
	}
	Activity(const char* type, int duration, int caloriesBurned) {
		setTypeActivity(type);
		setDuratino(duration);
		setCalories(caloriesBurned);
	}
	Activity(const char* typeActivity, int duration, int caloriesBurned, int sets) {
		this->typeActivity = new char[strlen(typeActivity) + 1];
		strcpy(this->typeActivity, typeActivity);
		this->duration = duration;
		this->caloriesBurned = caloriesBurned;
		this->sets = sets;
	}
	Activity(const char* type, int duration, int calories, int nrofsets, const int* move) {
		//setTypeActivity(type);
		if (type != nullptr) {
			this->typeActivity = new char[strlen(type) + 1];
			strcpy(this->typeActivity, type);
		}
		this->duration = duration;
		this->caloriesBurned = calories;
		this->sets = nrofsets;
		//setMoves(move,nrofsets);
		if (move && nrofsets != 0) {
			this->moves = new int[nrofsets];
			for (int i = 0; i < sets; ++i) {
				this->moves[i] = move[i];
			}
		}
	}
	Activity(const Activity& ac) {
		//setTypeActivity(ac.getTypeActivity());
		if (ac.typeActivity != nullptr) {
			this->typeActivity = new char[strlen(ac.typeActivity) + 1];
			strcpy(this->typeActivity, ac.typeActivity);
		}
		this->duration = ac.duration;
		this->caloriesBurned = ac.caloriesBurned;
		this->sets = ac.sets;
		//setMoves(getMoves(),getSets());
		if (ac.moves && ac.sets != 0) {
			this->moves = new int[ac.sets];
			for (int i = 0; i < ac.sets; ++i) {
				this->moves[i] = ac.moves[i];
			}
		}
	}
	Activity& operator=(const Activity& ac) {
		if (this != &ac) {
			setTypeActivity(ac.typeActivity);
			setDuratino(ac.duration);
			setCalories(ac.caloriesBurned);
			setSets(ac.sets);
			if (ac.moves != nullptr && sets != 0) {
				delete[] moves;
				moves = nullptr;
				sets = ac.sets;
				if (sets > 0) { //if i didnt do this verification -->   buffer overrun warning
					moves = new int[sets];
					for (int i = 0; i < ac.sets; i++) {              // ^
						moves[i] = ac.moves[i];                      // |
						//If moves is allocated with a size < ac.set ---|
					}
				}
			}
			else {
				this->moves = nullptr;
				this->sets = 0;
			}
		}
		return *this;
	}
	//operatori
	//increase the duration and the caloriesburned
	Activity& operator+=(const Activity& nac) {
		this->duration += nac.duration;
		this->caloriesBurned += nac.caloriesBurned;
		return *this;
	}
	int operator+=(int newduration) {
		this->duration += newduration;
		return this->duration;
	}
	int operator-=(int newdur) {
		this->duration = this->duration - newdur;
		return this->duration;
	}
	//what if i return only the nr of moves from a specific set
	int operator[](int index) {
		return this->moves[index];
	}
	bool operator!=(const Activity& at) {
		if (this->caloriesBurned != at.caloriesBurned) return true;
		return false;
	}
	bool operator==(const Activity& at) {
		if (this->caloriesBurned != at.caloriesBurned) return false;
		return true;
	}
	bool operator<(const Activity& nm) const {
		return this->caloriesBurned < nm.caloriesBurned;
	}
	bool operator>=(const Activity& nm) const {
		return this->caloriesBurned >= nm.caloriesBurned;
	}


	~Activity() {
		if (typeActivity != nullptr) {
			delete[]typeActivity;
			this->typeActivity = nullptr;
		}
		if (moves != nullptr) {
			/*for (int i = 0; i < sets; i++)
				delete &moves[i];*/
			delete[] moves;
		}
	}
	void displayActiv() const {
		cout << "Activity Type: " << (typeActivity ? typeActivity : "None") << endl;
		cout << "Duration: " << duration << " minutes" << endl;
		cout << "Calories Burned: " << caloriesBurned << endl;
	}
	void serialization() {
		ofstream f("activities.bin", ios::binary);
		if (!f) {
			cout << "Error opening file!" << endl;
			return;
		}
		int length = strlen(typeActivity);
		f.write((char*)&length, sizeof(length));
		f.write(typeActivity, length + 1);
		f.write((char*)&duration, sizeof(duration));
		f.write((char*)&caloriesBurned, sizeof(caloriesBurned));
		f.write((char*)&sets, sizeof(sets));

		if (sets > 0) {
			f.write((char*)moves, sets * sizeof(int));
		}

		cout << "Activity serialized successfully!" << endl;
		f.close();
	}

	void deserialization() {
		ifstream f("activities.bin", ios::binary);
		if (!f) {
			cout << "Error opening file!" << endl;
			return;
		}

		delete[] typeActivity;
		delete[] moves;
		typeActivity = nullptr;
		moves = nullptr;
		int length;
		f.read((char*)&length, sizeof(length));
		typeActivity = new char[length + 1];
		f.read(typeActivity, length + 1);
		f.read((char*)&duration, sizeof(duration));
		f.read((char*)&caloriesBurned, sizeof(caloriesBurned));
		f.read((char*)&sets, sizeof(sets));

		if (sets > 0) {
			moves = new int[sets];
			f.read((char*)moves, sets * sizeof(int));
		}

		cout << "Activity deserialized successfully!" << endl;
		f.close();
	}
	friend ostream& operator<<(ostream& out, const Activity& ac) {
		cout << "Type activity: ";
		out << ac.typeActivity << endl;
		cout << "Duration: ";
		out << ac.duration << "min." << endl;
		cout << "Calories burned: ";
		out << ac.caloriesBurned << endl;
		cout << "Nr of sets: ";
		out << ac.sets << endl;
		cout << "Series of moves: ";
		for (int i = 0; i < ac.sets; ++i) {
			out << ac.moves[i] << " ";
		}
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Activity& ac) {
		cout << "If you dont want to enter a new object enter 'exit'" << endl;
		cout << "Type of activity:  ";
		char aux[51];
		in >> ws;
		in.getline(aux, 50);
		if (strcmp(aux, "exit") == 0) {
			cout << "Just stopped the reading";
			return in;
		}
		delete[]ac.typeActivity;
		ac.typeActivity = new char[strlen(aux) + 1];
		strcpy(ac.typeActivity, aux);

		cout << "Duration (in mins): ";
		in >> ac.duration;
		cout << "Calories burned:  ";
		in >> ac.caloriesBurned;
		cout << "Nr of sets: ";
		in >> ac.sets;
		if (ac.moves != nullptr) {
			delete[]ac.moves;
		}
		ac.moves = new int[ac.sets];
		cout << "Write " << ac.sets << " series of moves:  ...  ";
		for (int i = 0; i < ac.sets; i++) {
			in >> ac.moves[i];
		}
		return in;
	}
};