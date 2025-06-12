#include <iostream>
#include <string>
using namespace std;

// -------------------- Patient Structure --------------------
struct Patient {
    string name;
    int age;
    string condition;
    int severity;
};

// -------------------- Max Heap --------------------
const int MAX = 100;
Patient heap[MAX];
int heapSize = 0;

void swap(Patient &a, Patient &b) {
    Patient temp = a;
    a = b;
    b = temp;
}

void insertPatient(Patient p) {
    if (heapSize >= MAX - 1) {
        cout << "Queue is full!\n\n";
        return;
    }

    heapSize++;
    heap[heapSize] = p;

    int current = heapSize;
    while (current > 1 && heap[current].severity > heap[current / 2].severity) {
        swap(heap[current], heap[current / 2]);
        current = current / 2;
    }

    cout << "                                    ==> Patient added to queue <==\n\n";
}

Patient extractMaxPatient() {
    if (heapSize == 0) {
        return {"", 0, "", 0};
    }

    Patient top = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;

    int current = 1;
    while (true) {
        int left = 2 * current;
        int right = 2 * current + 1;
        int largest = current;

        if (left <= heapSize && heap[left].severity > heap[largest].severity)
            largest = left;
        if (right <= heapSize && heap[right].severity > heap[largest].severity)
            largest = right;

        if (largest != current) {
            swap(heap[current], heap[largest]);
            current = largest;
        } else {
            break;
        }
    }

    return top;
}

void showQueueSorted() {
    if (heapSize == 0) {
        cout << "                                     ==> No patients in the queue <==\n\n";
        return;
    }

    cout << "\n                                      Patients in Queue (by severity):\n";
    cout << "                                      --------------------------------\n";
    for (int i = 1; i <= heapSize; ++i) {
        cout << i << ". Name: " << heap[i].name
             << ", Age: " << heap[i].age
             << ", Condition: " << heap[i].condition
             << ", Severity: " << heap[i].severity << "\n\n";
    }
    cout << endl;
}

// -------------------- Linked List for Treated History --------------------
struct TreatedPatient {
    string name;
    int age;
    string condition;
    float bill;
    TreatedPatient* next;
};

struct LinkedList {
    TreatedPatient* head;
};

float calculateBill(string condition, int severity) {
    float base = 1000, conditionCharge = 0;

    if (condition == "fracture") conditionCharge = 2000;
    else if (condition == "heart_attack") conditionCharge = 5000;
    else if (condition == "burn") conditionCharge = 3000;
    else conditionCharge = 1000;

    return base + (severity * 500) + conditionCharge;
}

void insertAtFront(LinkedList* list, TreatedPatient* newNode) {
    newNode->next = list->head;
    list->head = newNode;
}

void generateBill(LinkedList* list, Patient p) {
    float amount = calculateBill(p.condition, p.severity);

    TreatedPatient* newNode = new TreatedPatient{p.name, p.age, p.condition, amount, nullptr};
    insertAtFront(list, newNode);

    cout << "==> Bill for " << p.name << ": $" << amount << "\n\n";
}

// --- Hash Table Section ---
const int HASH_SIZE = 100;

struct HashEntry {
    string name;
    int age;
    string condition;
    bool occupied;
    bool isTreated;
};

HashEntry hashTable[HASH_SIZE];

//  hash function on name
int hashFunction(string name) {
    int sum = 0;
    for (char ch : name)
        sum += ch;
    return sum % HASH_SIZE;
}

void insertToHash(string name, int age, string condition, bool isTreated = false) {
    int index = hashFunction(name);
    int start = index;

    
    while (hashTable[index].occupied) {
        if (hashTable[index].name == name && 
            hashTable[index].age == age && 
            hashTable[index].condition == condition) {
            
            hashTable[index].isTreated = isTreated;
            return;
        }
        index = (index + 1) % HASH_SIZE;
        if (index == start) break; 
    }

    
    index = hashFunction(name);
    start = index;
    while (hashTable[index].occupied) {
        index = (index + 1) % HASH_SIZE;
        if (index == start) {
            cout << "Hash table full! Cannot insert more patients.\n";
            return;
        }
    }

    // Insert new entry
    hashTable[index].name = name;
    hashTable[index].age = age;
    hashTable[index].condition = condition;
    hashTable[index].occupied = true;
    hashTable[index].isTreated = isTreated;
}

void removeFromHash(string name, int age, string condition) {
    int index = hashFunction(name);
    int start = index;

    while (hashTable[index].occupied) {
        if (hashTable[index].name == name && 
            hashTable[index].age == age && 
            hashTable[index].condition == condition) {
            hashTable[index].isTreated = true;
            return;
        }
        index = (index + 1) % HASH_SIZE;
        if (index == start) break;
    }
}
//link list display
void displayHistory(LinkedList* list) {
    if (list->head == nullptr) {
        cout << "                                    ==> No patients treated yet <==\n\n";
        return;
    }

    cout << "\n                                         Treated Patient History:\n";
    cout << "                                         ------------------------\n";
    TreatedPatient* temp = list->head;
    int count = 1;

    while (temp != nullptr) {
        cout << count++ << ". Name: " << temp->name
             << ", Age: " << temp->age
             << ", Condition: " << temp->condition
             << ", Bill: $" << temp->bill
             << ", Status: Treated\n\n";
        temp = temp->next;
    }

    cout << "\nEnter patient name to delete or -1 to skip: ";
    string nameToDelete;
    cin >> nameToDelete;

    if (nameToDelete == "-1") {
        cout << "==> No deletion performed.\n\n";
        return;
    }

    TreatedPatient* curr = list->head;
    TreatedPatient* prev = nullptr;

    while (curr != nullptr) {
        if (curr->name == nameToDelete) {
            
		//remove from hash table
            int index = hashFunction(curr->name);
            int start = index;
            while (hashTable[index].occupied) {
                if (hashTable[index].name == curr->name && 
                    hashTable[index].age == curr->age && 
                    hashTable[index].condition == curr->condition) {
                    hashTable[index].occupied = false;
                    break;
                }
                index = (index + 1) % HASH_SIZE;
                if (index == start) break;
            }

            if (prev == nullptr)
                list->head = curr->next;
            else
                prev->next = curr->next;

            delete curr;
            cout << "==> Patient '" << nameToDelete << "' deleted from history.\n\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Patient '" << nameToDelete << "' not found.\n\n";
}

void addPatient() {
    string name, condition;
    int age, severity;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter condition: ";
    cin >> condition;
    cout << "Enter severity (1 to 10): ";
    cin >> severity;

    Patient p = {name, age, condition, severity};
    insertPatient(p);
    insertToHash(name, age, condition, false);
}

void treatPatient(LinkedList* list) {
    if (heapSize == 0) {
        cout << "                                     ==> No patients in queue <==\n\n";
        return;
    }

    Patient p = extractMaxPatient();
    cout << "\nTreating Patient:\n";
    cout << "------------------\n\n";
    cout << "Name: " << p.name << "\n";
    cout << "Age: " << p.age << "\n";
    cout << "Condition: " << p.condition << "\n";
    cout << "Severity: " << p.severity << "\n\n";

    removeFromHash(p.name, p.age, p.condition);
    generateBill(list, p);
    insertToHash(p.name, p.age, p.condition, true);
}
// search from hash
void searchPatient() {
    cout << "Search by:\n";
    cout << "1. Name\n";
    cout << "2. Condition\n";
    cout << "3. Age\n";
    cout << "Enter choice: ";
    int option;
    cin >> option;

    bool found = false;

    if (option == 1) {
        string searchName;
        cout << "Enter name to search: ";
        cin >> searchName;

        cout << "\nMatching patients found:\n";
        for (int i = 0; i < HASH_SIZE; i++) {
            if (hashTable[i].occupied && hashTable[i].name == searchName) {
                string status = hashTable[i].isTreated ? "Treated" : "In Queue";
                cout << "Name: " << hashTable[i].name
                     << ", Age: " << hashTable[i].age
                     << ", Condition: " << hashTable[i].condition
                     << ", Status: " << status << "\n";
                found = true;
            }
        }
    } else if (option == 2) {
        string searchCond;
        cout << "Enter condition to search: ";
        cin >> searchCond;

        cout << "\nMatching patients found:\n";
        for (int i = 0; i < HASH_SIZE; i++) {
            if (hashTable[i].occupied && hashTable[i].condition == searchCond) {
                string status = hashTable[i].isTreated ? "Treated" : "In Queue";
                cout << "Name: " << hashTable[i].name
                     << ", Age: " << hashTable[i].age
                     << ", Condition: " << hashTable[i].condition
                     << ", Status: " << status << "\n";
                found = true;
            }
        }
    } else if (option == 3) {
        int searchAge;
        cout << "Enter age to search: ";
        cin >> searchAge;

        cout << "\nMatching patients found:\n";
        for (int i = 0; i < HASH_SIZE; i++) {
            if (hashTable[i].occupied && hashTable[i].age == searchAge) {
                string status = hashTable[i].isTreated ? "Treated" : "In Queue";
                cout << "Name: " << hashTable[i].name
                     << ", Age: " << hashTable[i].age
                     << ", Condition: " << hashTable[i].condition
                     << ", Status: " << status << "\n";
                found = true;
            }
        }
    } else {
        cout << "Invalid option!\n";
        return;
    }

    if (!found) {
        cout << "No matching patients found.\n";
    }

    cout << "\n";
}

// -------------------- Main --------------------
int main() {
    LinkedList* treatedList = new LinkedList();
    treatedList->head = nullptr;

    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i].occupied = false;

 
    int choice;
    while (true) {
        cout << "============================================ Patient Compliance Menu =============================================\n";
        cout << "1. Add patient\n";
        cout << "2. Show patients in queue (by severity)\n";
        cout << "3. Treat next patient\n";
        cout << "4. Patient history (treated)\n";
        cout << "5. Search patient (by name, condition, or age)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: showQueueSorted(); break;
            case 3: treatPatient(treatedList); break;
            case 4: displayHistory(treatedList); break;
            case 5: searchPatient(); break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid option!\n"; break;
        }
    }
}
