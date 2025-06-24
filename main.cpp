
#include <iostream>
#include <string>
using namespace std;

class Venue {
    string name, address;
    int capacity;
public:
    Venue(string n = "Default Hall", string a = "Main Street", int c = 100) : name(n), address(a), capacity(c) {}
    string getName() { return name; }
    string getAddress() { return address; }
    int getCapacity() { return capacity; }
    void setCapacity(int c) { capacity = c; }
};

class Schedule {
    string* sessions;
    int sessionCount;
    string startTime, endTime;
public:
    Schedule(string start = "09:00", string end = "17:00", int count = 0) : startTime(start), endTime(end), sessionCount(count) {
        sessions = new string[10];
    }
    void addSession(string s = "Welcome") {
        if (sessionCount < 10) {
            sessions[sessionCount++] = s;
        }
    }
    void display() {
        cout << "Schedule (" << startTime << " - " << endTime << "):\n";
        for (int i = 0; i < sessionCount; i++) {
            cout << "  - " << sessions[i] << endl;
        }
    }
    Schedule(const Schedule& other) {
        sessionCount = other.sessionCount;
        startTime = other.startTime;
        endTime = other.endTime;
        sessions = new string[10];
        for (int i = 0; i < sessionCount; i++)
            sessions[i] = other.sessions[i];
    }
    ~Schedule() {
        delete[] sessions;
    }
};

class Attendee {
    string name;
    int ticketID;
public:
    Attendee(string n = "Guest", int id = 0) : name(n), ticketID(id) {}
    string getName() { return name; }
    int getTicketID() { return ticketID; }
};

class GuestList {
    Attendee* attendees[100];
    int count;
public:
    GuestList() { count = 0; }
    void registerAttendee(string name = "Guest") {
        if (count < 100) {
            attendees[count++] = new Attendee(name, count + 1);
        }
    }
    void display() {
        cout << "Registered Attendees:\n";
        for (int i = 0; i < count; i++) {
            cout << "  " << attendees[i]->getName() << " (Ticket ID: " << attendees[i]->getTicketID() << ")\n";
        }
    }
    GuestList(const GuestList& other) {
        count = other.count;
        for (int i = 0; i < count; i++) {
            attendees[i] = new Attendee(*other.attendees[i]);
        }
    }
    ~GuestList() {
        for (int i = 0; i < count; i++) delete attendees[i];
    }
};

class Organizer {
    string name;
public:
    Organizer(string n = "Organizer") : name(n) {}
    string getName() { return name; }
};

class Event {
    string title, type, date;
    Venue* venue;
    Schedule schedule;
    GuestList guestList;
    Organizer* organizer;
public:
    Event(string t = "Untitled", string ty = "General", string d = "2025-01-01", Venue* v = nullptr, Organizer* o = nullptr)
        : title(t), type(ty), date(d), venue(v), organizer(o) {}

    void addSession(string s = "Welcome") {
        schedule.addSession(s);
    }

    void registerAttendee(string name = "Guest") {
        guestList.registerAttendee(name);
    }

    void display() {
        cout << "\n=== Event Details ===\n";
        cout << "Event: " << title << " (" << type << ")\nDate: " << date << "\nVenue: " << (venue ? venue->getName() : "None")
             << "\nOrganizer: " << (organizer ? organizer->getName() : "None") << "\n";
        schedule.display();
        guestList.display();
    }

    Event(const Event& other) : title(other.title), type(other.type), date(other.date),
        schedule(other.schedule), guestList(other.guestList) {
        venue = other.venue;
        organizer = other.organizer;
    }
};

int main() {
    Venue* venue = nullptr;
    Organizer* organizer = nullptr;
    Event* event = nullptr;
    Event* clonedEvent = nullptr;

    int choice;
    do {
        cout << "\n====== Event Management Menu ======\n";
        cout << "1. Create Venue\n";
        cout << "2. Create Organizer\n";
        cout << "3. Create Event\n";
        cout << "4. Add Session to Event\n";
        cout << "5. Register Attendee\n";
        cout << "6. Display Event\n";
        cout << "7. Clone Event\n";
        cout << "8. Display Cloned Event\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        string input;
        switch (choice) {
        case 1:
            {
                string name, address;
                int cap;
                cout << "Enter Venue Name: "; getline(cin, name);
                cout << "Enter Address: "; getline(cin, address);
                cout << "Enter Capacity: "; cin >> cap; cin.ignore();
                venue = new Venue(name, address, cap);
                cout << "Venue created successfully.\n";
            }
            break;
        case 2:
            {
                string orgName;
                cout << "Enter Organizer Name: ";
                getline(cin, orgName);
                organizer = new Organizer(orgName);
                cout << "Organizer created.\n";
            }
            break;
        case 3:
            {
                string title, type, date;
                cout << "Enter Event Title: "; getline(cin, title);
                cout << "Enter Event Type: "; getline(cin, type);
                cout << "Enter Date (YYYY-MM-DD): "; getline(cin, date);
                event = new Event(title, type, date, venue, organizer);
                cout << "Event created.\n";
            }
            break;
        case 4:
            if (event) {
                cout << "Enter session name: ";
                getline(cin, input);
                event->addSession(input);
                cout << "Session added.\n";
            } else {
                cout << "Create an event first.\n";
            }
            break;
        case 5:
            if (event) {
                cout << "Enter attendee name: ";
                getline(cin, input);
                event->registerAttendee(input);
                cout << "Attendee registered.\n";
            } else {
                cout << "Create an event first.\n";
            }
            break;
        case 6:
            if (event) {
                event->display();
            } else {
                cout << "No event to display.\n";
            }
            break;
        case 7:
            if (event) {
                clonedEvent = new Event(*event);
                cout << "Event cloned successfully.\n";
            } else {
                cout << "No event to clone.\n";
            }
            break;
        case 8:
            if (clonedEvent) {
                clonedEvent->display();
            } else {
                cout << "No cloned event to display.\n";
            }
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    delete event;
    delete clonedEvent;
    delete venue;
    delete organizer;
    return 0;
}

