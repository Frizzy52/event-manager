main.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Event {
    int id;
    string title;
    string date;      // формат YYYY-MM-DD
    string location;
};

vector<Event> events;
const string filename = "events.json";

// -------------------- ЗАВАНТАЖЕННЯ --------------------
void loadData() {
    events.clear();
    ifstream file(filename);

    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Event e;

        ss >> e.id;
        ss.ignore();
        getline(ss, e.title, '|');
        getline(ss, e.date, '|');
        getline(ss, e.location);

        events.push_back(e);
    }

    file.close();
}

// -------------------- ЗБЕРЕЖЕННЯ --------------------
void saveData() {
    ofstream file(filename);

    for (auto &e : events) {
        file << e.id << " "
             << e.title << "|"
             << e.date << "|"
             << e.location << "\n";
    }

    file.close();
}

// -------------------- ДОДАТИ ПОДІЮ --------------------
void addEvent() {
    Event e;

    cout << "Enter ID: ";
    cin >> e.id;
    cin.ignore();

    cout << "Enter title: ";
    getline(cin, e.title);

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, e.date);

    cout << "Enter location: ";
    getline(cin, e.location);

    events.push_back(e);
    saveData();

    cout << "Event added!\n";
}

// -------------------- ПОКАЗ ВСІХ --------------------
void showAll() {
    if (events.empty()) {
        cout << "No events.\n";
        return;
    }

    for (auto &e : events) {
        cout << "ID: " << e.id << "\n";
        cout << "Title: " << e.title << "\n";
        cout << "Date: " << e.date << "\n";
        cout << "Location: " << e.location << "\n";
        cout << "----------------------\n";
    }
}

// -------------------- ПОШУК --------------------
void searchEvent() {
    string key;
    cout << "Enter title to search: ";
    cin.ignore();
    getline(cin, key);

    bool found = false;

    for (auto &e : events) {
        if (e.title.find(key) != string::npos) {
            cout << e.id << " | " << e.title << " | "
                 << e.date << " | " << e.location << "\n";
            found = true;
        }
    }

    if (!found) cout << "Not found.\n";
}

// -------------------- ВИДАЛЕННЯ --------------------
void deleteEvent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    auto it = remove_if(events.begin(), events.end(),
                        [id](Event &e) { return e.id == id; });

    if (it != events.end()) {
        events.erase(it, events.end());
        saveData();
        cout << "Deleted!\n";
    } else {
        cout << "ID not found.\n";
    }
}

// -------------------- МЕНЮ --------------------
void menu() {
    int choice;

    do {
        cout << "\n===== EVENT MANAGER =====\n";
        cout << "1. Add event\n";
        cout << "2. Show all events\n";
        cout << "3. Search event\n";
        cout << "4. Delete event\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: addEvent(); break;
            case 2: showAll(); break;
            case 3: searchEvent(); break;
            case 4: deleteEvent(); break;
            case 0: cout << "Bye!\n"; break;
            default: cout << "Wrong choice!\n";
        }

    } while (choice != 0);
}

// -------------------- MAIN --------------------
int main() {
    loadData();
    menu();
    return 0;
}
