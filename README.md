<div align="center">
  
# 🌲 IFAMDS
  
### Intelligent Forest Advisory & Multi-Structure Decision System

**CL2001 - Data Structures Project | Spring 2026**

*A complete console-based forest management simulation with zero STL dependencies.*

</div>

---

## 📋 Overview

IFAMDS is a comprehensive forest fire management simulation built from scratch in C++17 featuring:

- 🔥 Fire Detection & Prediction
- 🚨 Emergency Response Coordination  
- 📊 Resource Allocation
- 🔄 System Recovery & Rollback
- 📈 Adaptive Performance Monitoring

**Key Achievement:** Zero STL containers used - every data structure implemented manually.

---

## 🏗️ 8 Departments

| Dept | Structure | Components |
|------|-----------|------------|
| 1 | Arrays | A1, A2, A3, A4 |
| 2 | Linked Lists | L1-L10 (Singly, Doubly, Circular) |
| 3 | Stacks | ECL (Checkpoint + Step Log) |
| 4 | Queues | Q1, Q2, Q3 (Priority), Q4 + DSCH |
| 5 | Trees | T1-T12 (Decision Trees) |
| 6 | Graphs | G1 (Adj List), G2 (Adj Matrix) |
| 7 | Hash Tables | H1 (Open), H2 (Chaining), H3 (Cache) |
| 8 | Monitor | AMON (Adaptive Monitor) |

---

## 📊 Data Structures

| Structure | Instances | Complexity |
|-----------|-----------|------------|
| Static Arrays | A1, A3 | O(1), O(n) |
| Dynamic Arrays | A2, A4 | O(1), O(n) |
| Singly Linked Lists | L1, L2, L3 | O(1), O(n) |
| Doubly Linked Lists | L4, L5, L6 | O(1), O(n) |
| Circular Lists | L7-L10 | O(1), O(n) |
| FIFO Queues | Q1, Q2, Q4 | O(1) |
| Priority Queue | Q3 | O(log n) |
| Binary Trees | T1-T12 | O(1), O(n) |
| Adjacency List | G1 | O(V+E) |
| Adjacency Matrix | G2 | O(V²) |
| Hash Tables | H1, H2, H3 | O(1) avg |

---

## 🎮 Six Scenarios

1. **Cascading Fire** - Fire spreads Zone 3→4→6 with rollback
2. **Sensor Failure** - Faulty sensors trigger interpolation recovery  
3. **Multi-Factor Anomaly** - Wildlife + Fire + Human detection
4. **System Overload** - Load balancing + cache warming
5. **Global Emergency** - Ten-zone conflict resolution
6. **State Recovery** - Checkpoint/rollback testing

---

## 🛠️ Building & Running

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -O2 IFAMDS_noSTL.cpp -o ifamds
Run:

bash
./ifamds
On Windows:

bash
ifamds.exe
🖥️ Menu Options
text
1.  Input Environmental Data
2.  View Forest Grid Status
3.  Event Memory System
4.  Fire Detection and Control
5.  Task Scheduling System
6.  Decision System
7.  Spatial Routing System
8.  Hash-Based Fast Access System
9.  System Monitoring
10. Scenario Simulation
0.  Exit
📈 Sample Output
text
[G1-BFS] Fire spread from Zone3:
  Level 0: Zone3 
  Level 1: Zone1 Zone6 
  Level 2: Zone0 Zone4 Zone8 

[ECL] Rolling back to checkpoint
[ECL] State restored. Execution resumed.

[Q3] Emergency dequeued: SYNC-Z0 Priority=1
🧠 Key Algorithms
Algorithm	Location	Complexity
Linear Probing	H1	O(1) avg
Separate Chaining	H2	O(1) avg
Binary Min-Heap	Q3	O(log n)
BFS Adj List	G1	O(V+E)
BFS Adj Matrix	G2	O(V²)
DFS	G1	O(V+E)
Spatial Interpolation	A3	O(1)
⏱️ Development Timeline
Date	Hours	Work
May 1	3h 40m	Arrays A1-A4
May 2	4h 15m	Linked Lists
May 3	2h 50m	Queues + DSCH
May 4	4h 30m	Trees + Graphs
May 5	3h 20m	Hash Tables + ECL
May 6	2h 10m	6 Scenarios
May 7	4h 45m	STL Replacement
May 8	3h 05m	Documentation
Total	28h 55m	
👨‍💻 Author
Shadab Khan
CL2001 - Data Structures | Spring 2026
GitHub: @Shadabk-56

📜 License
MIT License - See LICENSE file

<div align="center"> **⭐ Star this repository if useful ⭐** </div> ```
