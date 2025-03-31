#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <algorithm>
#include <limits>

using namespace std;

struct Employee {
    map<string, string> preferences;
    int days_worked;
};

int main() {
    vector<string> workdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; // Workdays
    vector<string> shifts = {"morning", "afternoon", "evening"}; // Shift types

    // List of existing employees.
    map<string, Employee> employees = {
        {"Alice", {{}, 0}},
        {"Bob", {{}, 0}},
        {"Charles", {{}, 0}},
        {"David", {{}, 0}},
        {"Elliott", {{}, 0}},
        {"Fred", {{}, 0}},
        {"Greg", {{}, 0}},
        {"Henry", {{}, 0}}
    }; 

    //map of schedule to include workdays, shifts
    map<string, map<string, vector<string>>> schedule; 
    for (const auto& day : workdays) {
        for (const auto& shift : shifts) {
            schedule[day][shift] = {};
        }
    }

    // User Input for employees
    while (true) {
        string name;
        cout << "Enter employee name (or 'done' to finish): ";
        getline(cin, name);
        if (name == "done") {
            break;
        }
        if (name.empty() || all_of(name.begin(), name.end(), ::isspace)) {
            cout << "Employee name cannot be blank. Please enter a valid name or 'done'." << endl;
            continue;
        }
        if (employees.find(name) == employees.end()) {
            employees[name] = {{}, 0};
        }
    }

    // Employee preferences
    for (auto& [name, data]: employees) {
        for (const auto& day: workdays) {
            string preference;
            cout << "Enter " << name << "'s preferred shift for " << day << " (morning, afternoon, evening, or blank to randomize): ";
            getline(cin, preference);
            transform(preference.begin(), preference.end(), preference.begin(), ::tolower);
            if (!preference.empty()) {
                data.preferences[day] = preference;
            } else {
                data.preferences[day] = ""; // No preference for shift.
            }
        }
    }

    // Scheduling Logic
    random_device rd;
    mt19937 g(rd());

    for (const auto& day: workdays) {
        for (const auto& shift: shifts) {
            vector<string> preferred_employees;
            for (const auto& [name, data]: employees) {
                if (data.preferences.at(day) == shift && data.days_worked < 5) {
                    bool already_scheduled = false;
                    for (const auto& shift_schedule : schedule[day]) {
                        if (find(shift_schedule.second.begin(), shift_schedule.second.end(), name) != shift_schedule.second.end()) {
                            already_scheduled = true;
                            break;
                        }
                    }
                    if (!already_scheduled) {
                        preferred_employees.push_back(name);
                    }
                }
            }
            shuffle(preferred_employees.begin(), preferred_employees.end(), g);

            while (schedule[day][shift].size() < 2) {
                if (!preferred_employees.empty()) {
                    string employee = preferred_employees.front();
                    preferred_employees.erase(preferred_employees.begin());
                    schedule[day][shift].push_back(employee);
                    employees[employee].days_worked++;
                } else {
                    vector<string> available_employees;
                    for (const auto& [name, data]: employees) {
                        if (data.days_worked < 5) {
                            bool already_scheduled = false;
                            for (const auto& shift_schedule: schedule[day]) {
                                if (find(shift_schedule.second.begin(), shift_schedule.second.end(), name) != shift_schedule.second.end()) {
                                    already_scheduled = true;
                                    break;
                                }
                            }
                            if (!already_scheduled) {
                                available_employees.push_back(name);
                            }
                        }
                    }
                    if (!available_employees.empty()) {
                        uniform_int_distribution<> dist(0, available_employees.size() - 1);
                        string employee = available_employees[dist(g)];
                        schedule[day][shift].push_back(employee);
                        employees[employee].days_worked++;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    // Fill remaining slots
        for (const auto& day : workdays) {
            for (const auto& shift : shifts) {
                while (schedule[day][shift].size() < 2) {
                    vector<string> available_employees;
                    for (const auto& [name, data]: employees) {
                        if (data.days_worked < 5) {
                            bool already_scheduled = false;
                            for (const auto& shift_schedule : schedule[day]) {
                                if (find(shift_schedule.second.begin(), shift_schedule.second.end(), name) != shift_schedule.second.end()) {
                                    already_scheduled = true;
                                    break;
                                }
                            }
                            if (!already_scheduled) {
                                available_employees.push_back(name);
                            }
                        }
                    }
                    if (!available_employees.empty()) {
                        uniform_int_distribution<> dist(0, available_employees.size() - 1);
                        string employee = available_employees[dist(g)];
                        schedule[day][shift].push_back(employee);
                        employees[employee].days_worked++;
                    } else {
                        break;
                    }
                }
            }
        }

    // Scheduling Conflicts
    for (const auto& day : workdays) {
        for (const auto& shift: shifts) {
            for (auto it = schedule[day][shift].begin(); it != schedule[day][shift].end();) {
                string employee = *it;
                if (!employees[employee].preferences[day].empty() && employees[employee].preferences[day] != shift) {
                    if (schedule[day].find(employees[employee].preferences[day]) != schedule[day].end() && schedule[day][employees[employee].preferences[day]].size() < 21) {
                        schedule[day][employees[employee].preferences[day]].push_back(employee);
                        it = schedule[day][shift].erase(it);
                    } else {
                        bool found = false;
                        for (size_t i = find(workdays.begin(), workdays.end(), day) - workdays.begin(); i < workdays.size() + find(workdays.begin(), workdays.end(), day) - workdays.begin(); ++i) {
                            string next_day = workdays[i % workdays.size()];
                            if (next_day != day) {
                                for (const auto& possible_shift : shifts) {
                                    if (schedule[next_day][possible_shift].size() < 21) {
                                        schedule[next_day][possible_shift].push_back(employee);
                                        it = schedule[day][shift].erase(it);
                                        found = true;
                                        break;
                                    }
                                }
                                if (found) {
                                    break;
                                }
                            }
                        }
                        if (!found) {
                            ++it;
                        }
                    }
                } else {
                    ++it;
                }
            }
        }
    }

    // Print Schedule
    cout << "\nSchedule Printout: " << endl;
    for (const auto& day : workdays) {
        cout << "\n" << day << ": " << endl;
        for (const auto& shift : shifts) {
            cout << "  " << shift[0] << string(shift.begin() + 1, shift.end()) << ": ";
            for (const auto& employee : schedule[day][shift]) {
                cout << employee << ", ";
            }
            cout << endl;
        }
    }

    return 0;
}
