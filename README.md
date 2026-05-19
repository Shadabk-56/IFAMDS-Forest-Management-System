<div align="center">
  
# 🌲 IFAMDS
  
### Intelligent Forest Advisory & Multi-Structure Decision System

**CL2001 - Data Structures Project | Spring 2026**

*A complete console-based forest management simulation with zero STL dependencies.*

</div>

---

## 📋 Table of Contents

1. [Overview](#-overview)
2. [System Architecture](#-system-architecture)
3. [Data Structures](#-data-structures)
4. [Six Scenarios](#-six-scenarios)
5. [Menu System](#-menu-system)
6. [Sample Output](#-sample-output)
7. [Key Algorithms](#-key-algorithms)
8. [Development Timeline](#-development-timeline)
9. [Time Complexity](#-time-complexity)
10. [Building & Running](#-building--running)
11. [Author](#-author)

---

## 🎯 Overview

IFAMDS is a comprehensive forest fire management simulation built entirely from scratch in **C++17**.

### Key Features:
- 🔥 Fire Detection & Prediction
- 🚨 Emergency Response Coordination  
- 📊 Resource Allocation
- 🔄 System Recovery & Rollback
- 📈 Adaptive Performance Monitoring

### ⭐ Key Achievement
**Zero STL containers used** - Every data structure implemented manually.

---

## 🏗️ System Architecture
┌─────────────────────────────────────────────────────────────┐
│ IFAMDS CORE SYSTEM │
├───────────┬───────────┬───────────┬───────────────────────┤
│ Dept 1 │ Dept 2 │ Dept 3 │ Dept 4 │
│ Arrays │ Linked │ Stacks │ Queues │
│ (A1-A4) │ Lists │ (ECL) │ (Q1-Q4 + DSCH) │
│ │ (L1-L10) │ │ │
├───────────┼───────────┼───────────┼───────────────────────┤
│ Dept 5 │ Dept 6 │ Dept 7 │ Dept 8 │
│ Trees │ Graphs │ Hash │ Adaptive │
│ (T1-T12) │ (G1-G2) │ Tables │ Monitor (AMON) │
│ │ │ (H1-H3) │ │
└───────────┴───────────┴───────────┴───────────────────────┘

text

---

## 📊 Data Structures Implemented

| Structure | Instances | Complexity |
|-----------|-----------|------------|
| Static Arrays | A1, A3 | O(1), O(n) |
| Dynamic Arrays | A2, A4 | O(1), O(n) |
| Singly Linked Lists | L1, L2, L3 | O(1), O(n) |
| Doubly Linked Lists | L4, L5, L6 | O(1), O(n) |
| Circular Lists | L7, L8, L9, L10 | O(1), O(n) |
| FIFO Queues | Q1, Q2, Q4 | O(1) |
| Priority Queue (Min-Heap) | Q3 | O(log n) |
| Binary Trees | T1 to T12 | O(1), O(n) |
| Adjacency List Graph | G1 | O(V+E) |
| Adjacency Matrix Graph | G2 | O(V²) |
| Hash Table (Open Addressing) | H1 | O(1) avg |
| Hash Table (Separate Chaining) | H2 | O(1) avg |
| Direct Cache | H3 | O(1) |
| Stack (Checkpoint + Log) | ECL | O(1) |

---

## 🎮 Six Simulation Scenarios

| # | Scenario | Description |
|---|----------|-------------|
| 1 | 🔥 Cascading Fire | Fire spreads Zone 3 → 4 → 6 with rollback recovery |
| 2 | 📡 Sensor Failure | Faulty sensors trigger interpolation recovery |
| 3 | ⚠️ Multi-Factor Anomaly | Wildlife + Fire + Human detection simultaneous |
| 4 | 🔄 System Overload | Load balancing + cache warming + bottleneck detection |
| 5 | 🌍 Global Emergency | Ten-zone conflict resolution + synchronized BFS |
| 6 | 💾 State Recovery | Checkpoint/rollback + adaptive monitoring |

---

## 🖥️ Menu System
╔════════════════════════════════════════════════════════╗
║ IFAMDS - MAIN MENU ║
╠════════════════════════════════════════════════════════╣
║ 1. Input Environmental Data ║
║ 2. View Forest Grid Status ║
║ 3. Event Memory System ║
║ 4. Fire Detection and Control ║
║ 5. Task Scheduling System ║
║ 6. Decision System ║
║ 7. Spatial Routing System ║
║ 8. Hash-Based Fast Access System ║
║ 9. System Monitoring ║
║ 10. Scenario Simulation ║
║ 0. Exit System ║
╚════════════════════════════════════════════════════════╝

text

---

## 📈 Sample Output

### BFS Fire Spread Prediction
[G1-BFS] Fire spread from Zone3:
Level 0: Zone3
Level 1: Zone1 Zone6
Level 2: Zone0 Zone4 Zone8
Level 3: Zone2 Zone5 Zone7 Zone9

text

### Emergency Queue Processing
[Q3-EmergencyResponse] EMERGENCY dequeued: SYNC-Z0 Zone=0 Priority=1
[Q3-EmergencyResponse] EMERGENCY dequeued: SYNC-Z2 Zone=2 Priority=1
Total synchronized tasks dispatched: 6

text

### ECL Rollback Recovery
[ECL] Rolling back to: "SCENARIO2_PRE_FAIL" (tick=18)
[ECL] State restored. Execution resumed.
[ECL] Alternative Path: Zone2 replacing faulty=55.0 with interpolated=26.5

text

---

## 🧠 Key Algorithms

| Algorithm | Location | Time Complexity |
|-----------|----------|-----------------|
| Linear Probing | H1 (Hash Table) | O(1) average |
| Separate Chaining | H2 (Hash Table) | O(1) average |
| Binary Min-Heap | Q3 (Priority Queue) | O(log n) |
| Pre-order Traversal | T1-T12 (Trees) | O(n) |
| BFS (Adjacency List) | G1 | O(V+E) |
| BFS (Adjacency Matrix) | G2 | O(V²) |
| DFS (Recursive) | G1 | O(V+E) |
| Spatial Interpolation | A3 | O(1) |
| Noise Filter | L2 (Linked List) | O(n) |
| Heapify Up/Down | EmergencyQueue | O(log n) |

---

## ⏱️ Development Timeline

| Date | Hours | Work Done |
|------|-------|-----------|
| May 1 | 3h 40m | Arrays A1, A2, A3, A4 with interpolation |
| May 2 | 4h 15m | All Linked Lists (Singly, Doubly, Circular) |
| May 3 | 2h 50m | Queues Q1-Q4 + Dynamic Scheduler (DSCH) |
| May 4 | 4h 30m | Trees T1-T12 + Graphs G1-G2 (BFS/DFS) |
| May 5 | 3h 20m | Hash Tables H1, H2, H3 + ECL |
| May 6 | 2h 10m | Six Complete Simulation Scenarios |
| May 7 | 4h 45m | STL Replacement (MyStack, MyQueue, MinHeap) |
| May 8 | 3h 05m | Integration, Cleanup, Documentation |
| **Total** | **28h 55m** | |

---

## ⏰ Time Complexity Reference

| Operation | Data Structure | Complexity |
|-----------|----------------|------------|
| Access by index | Array | O(1) |
| Update single zone | Dynamic Array | O(1) |
| Insert front | Singly Linked List | O(1) |
| Insert back | Singly Linked List | O(n) |
| Search | Singly Linked List | O(n) |
| Insert back | Doubly Linked List | O(1) |
| Forward/Backward correction | Doubly Linked List | O(n) |
| Insert | Circular Linked List | O(1) |
| One monitoring cycle | Circular Linked List | O(n) |
| Enqueue/Dequeue | FIFO Queue | O(1) |
| Enqueue/Dequeue | Priority Queue | O(log n) |
| Add child | Tree | O(1) |
| Pre-order traversal | Tree | O(n) |
| BFS | Adjacency List Graph | O(V+E) |
| BFS | Adjacency Matrix Graph | O(V²) |
| DFS | Adjacency List Graph | O(V+E) |
| Insert/Search (avg) | Hash Table | O(1) |
| Get/Put | Direct Cache | O(1) |
| Push/Pop | Stack | O(1) |
| Capture checkpoint | ECL | O(n) |
| Rollback restore | ECL | O(n) |

---

## 🛠️ Building & Running

### Prerequisites
- C++17 compatible compiler (g++ 7+, clang 5+, MSVC 2017+)
- No external dependencies
- No STL required

### Compilation

**Linux / Mac:**
```bash
g++ -std=c++17 -Wall -Wextra -O2 IFAMDS_noSTL.cpp -o ifamds
./ifamds
Windows:

bash
g++ -std=c++17 -Wall -Wextra -O2 IFAMDS_noSTL.cpp -o ifamds.exe
ifamds.exe
Quick Test
After running the program:

text
Enter choice: 10
Then select: 6 (Run Full System Simulation)
📁 Project Structure
text
IFAMDS-Forest-Management-System/
│
├── IFAMDS_noSTL.cpp      # Main source code (4700+ lines)
├── README.md             # This file
├── LICENSE               # MIT License
├── .gitignore            # Git ignore rules
│
└── docs/
    └── IFAMDS_Project_Report.pdf
Source Code Sections
text
Section 1: Arrays (A1-A4) - Environmental Data
Section 2: Linked Lists (L1-L10) - Event Memory
Section 3: Queues (Q1-Q4) - Scheduling Engine
Section 4: Trees (T1-T12) - Decision Intelligence
Section 5: Graphs (G1-G2) - Routing Layer
Section 6: Hash Tables (H1-H3) - Indexing Layer
Section 7: Execution Control (ECL) - Stack Control
Section 8: Dynamic Scheduler (DSCH) - Queue Management
Section 9: Adaptive Monitor (AMON) - Performance
Section 10: Scenarios 1-6 - Simulations
Section 11: Main Menu - Interactive Interface
👨‍💻 Author
Shadab Khan
*CL2001 - Data Structures*
Department of Computer Science
Spring 2026

GitHub: @Shadabk-56

📜 License
This project is licensed under the MIT License - see the LICENSE file for details.

text
MIT License

Copyright (c) 2026 Shadab Khan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions...

Full license text available in LICENSE file.
<div align="center">
⭐ Star this repository if you found it useful! ⭐
Built with ❤️ using pure C++17 | 4700+ lines | 28+ hours | 0 STL containers

</div> ```
