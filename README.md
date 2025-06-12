🏥 Patient Compliance System

Hey there!  
This is a simple C++ project I made to simulate how emergency rooms might handle patients based on how serious their condition is.  
It’s a console app using core DSA concepts like heaps, hash tables, and linked lists — don’t worry, it’s beginner-friendly and all clean code!



🔧 Features

- 🏃‍♂️ Add new patients with name, age, condition, and severity (1 to 10)
- ⏫ Uses a Max Heap to make sure serious cases are handled first
- 💉 Treats the highest severity patient with one click
- 💸 Smart Billing based on condition & severity (fracture, heart_attack, etc.)
- 🔍 Search patients by name, age, or condition using a custom hash table
- 🧾 Keeps a history of treated patients (linked list style)
- ❌ You can even delete someone from history if needed



📁 Data Structures Used

- **Max Heap** → For emergency priority queue  
- **Linked List** → For patient treatment history  
- **Hash Table (Linear Probing)** → For quick patient search



🚀 How to Run

1. Open the `.cpp` file in any C++ IDE (VS Code, Code::Blocks, Dev-C++, whatever you like)
2. Compile it (press Run or Ctrl+F9 depending on your IDE)
3. Follow the menu and try it out — it's all text-based!



🧠 Billing Rules (Simple logic)

Just a basic idea:
- `fracture` → $2000
- `heart_attack` → $5000
- `burn` → $3000
- anything else → $1000  
Total Bill = Base $1000 + conditionFee + severity × $500


