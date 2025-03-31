# Employee scheduler

import random

def scheduler():
    """Schedule employees based on preferences and contraints"""

    workdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
    shifts = ["morning", "afternoon", "evening"]

    # Existing employees
    employees = {
        "Alice": {"preferences": {}, "days_worked": 0},
        "Bob": {"preferences": {}, "days_worked": 0},
        "Charles": {"preferences": {}, "days_worked": 0},
        "David": {"preferences": {}, "days_worked": 0},
        "Elliott": {"preferences": {}, "days_worked": 0},
        "Fred": {"preferences": {}, "days_worked": 0},
        "Greg": {"preferences": {}, "days_worked": 0},
        "Henry": {"preferences": {}, "days_worked": 0},
    }

    # Schedule
    schedule = {day: {shift: [] for shift in shifts} for day in workdays}

    # User Input for employee
    while True:
        name = input("Enter employee name (or 'done' to finish): ")
        if name.lower() == "done":
            break
        if not name.strip(): # checking to make sure name is not blank
            print("Employee name cannot be blank. Please enter a valid name or 'done'.")
            continue # Re-loop to beginning to ask for a name
        if name not in employees:
            employees[name] = {"preferences": {}, "days_worked": 0} # adding new employee name if it doesn't exist.

    # Get preferences for all employees
    for name, data in employees.items():
        for day in workdays:
            preference = input(f"Enter {name}'s preferred shift for {day} (morning, afternoon, evening, or blank to randomize): ").lower()
            if preference:
                data["preferences"][day] = preference
            else:
                data["preferences"][day] = None # No preference
    
    # Scheduling Logic
    for day in workdays:
        for shift in shifts:
            preferred_employees = [
                name
                for name, data in employees.items()
                # Limit days worked to maximum of 5
                if data["preferences"][day] == shift 
                and data["days_worked"] < 5 
                and name not in [emp for employee_list in schedule[day].values() for emp in employee_list]
            ]

            random.shuffle(preferred_employees)

            count = 0
            # If less than 2 on a shift, populate with employees with no days worked
            while len(schedule[day][shift]) < 2:
                if preferred_employees:
                    employee = preferred_employees.pop(0)
                    schedule[day][shift].append(employee)
                    employees[employee]["days_worked"] += 1
                    count += 1
                else:
                    # Random assignment of remaining employees if less than 2 people are available.
                    available_employees = [
                        name
                        for name, data in employees.items()
                        if data["days_worked"] < 5
                        and name not in [emp for employee_list in schedule[day].values() for emp in employee_list]
                    ]  
                    if available_employees:
                        employee = random.choice(available_employees)
                        schedule[day][shift].append(employee)
                        employees[employee]["days_worked"] += 1
                    else:
                        break # No more employees available.

    # Fill remaining slots with random assignments
    for day in workdays:
        for shift in shifts:
            while len(schedule[day][shift]) < 2:
                available_employees = [
                    name
                    for name, data in employees.items()
                    if data["days_worked"] < 5
                    and name not in [emp for employee_list in schedule[day].values() for emp in employee_list]
                ]
                if available_employees:
                    employee = random.choice(available_employees)
                    schedule[day][shift].append(employee)
                    employees[employee]["days_worked"] += 1
                else:
                    break # No more employees available.
    
    # Scheduling Conflicts
    for day in workdays:
        for shift in shifts:
            for employee in schedule[day][shift]:
                if employees[employee]["preferences"][day] and employees[employee]["preferences"][day] != shift:
                    # Conflict
                    if (
                        employees[employee]["preferences"][day] in schedule[day]
                        and len(schedule[day][employees[employee]["preferences"][day]]) < 21
                    ):
                        schedule[day][employees[employee]["preferences"][day]].append(employee)
                        schedule[day][shift].remove(employee)
                    else:
                        found = False
                        # Assign employee to next day for possible shift.
                        for next_day in workdays[workdays.index(day) :] + workdays[: workdays.index(day)]:
                            if next_day != day:
                                for possible_shift in shifts:
                                    if (
                                        len(schedule[next_day][possible_shift]) < 21
                                    ):
                                        schedule[next_day][possible_shift].append(employee)
                                        schedule[day][shift].remove(employee)
                                        found = True
                                        break
                                if found:
                                    break
    
    # Printing Final Schedule
    print("\n Schedule Printout: ")
    for day, shift_data in schedule.items():
        print(f"\n {day}: ")
        for shift, assigned_employees in shift_data.items():
            print(f"  {shift.capitalize()}: {', '.join(assigned_employees)}")

if __name__ == "__main__":
    scheduler()
