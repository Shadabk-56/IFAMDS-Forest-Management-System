<div align="center">

```
██╗███████╗ █████╗ ███╗   ███╗██████╗ ███████╗
██║██╔════╝██╔══██╗████╗ ████║██╔══██╗██╔════╝
██║█████╗  ███████║██╔████╔██║██║  ██║███████╗
██║██╔══╝  ██╔══██║██║╚██╔╝██║██║  ██║╚════██║
██║██║     ██║  ██║██║ ╚═╝ ██║██████╔╝███████║
╚═╝╚═╝     ╚═╝  ╚═╝╚═╝     ╚═╝╚═════╝ ╚══════╝
```

# Intelligent Forest Advisory & Multi-Structure Decision System

**A complete C++ console simulation integrating all major data structures for real-world forest management**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![STL](https://img.shields.io/badge/STL%20Usage-Zero-brightgreen?style=for-the-badge)](https://github.com)
[![Lines of Code](https://img.shields.io/badge/Lines%20of%20Code-~4700-orange?style=for-the-badge)](https://github.com)
[![Scenarios](https://img.shields.io/badge/Scenarios-6%20Complete-purple?style=for-the-badge)](https://github.com)
[![Course](https://img.shields.io/badge/Course-CL2001%20Data%20Structures-red?style=for-the-badge)](https://github.com)

<br/>

*Built from scratch — every stack, queue, tree, graph, and hash table is a custom implementation.*

</div>

---

## 📖 About

IFAMDS is a fully console-based C++ simulation that models a real-world **forest management and emergency response system**. Sensor data flows through multiple processing layers and decisions emerge from the combined interaction of all major data structures — none working in isolation.

The system was architected across **eight departments**, each responsible for a distinct computational concern, and implements **every data structure** covered in a university-level Data Structures course — all written from scratch without using a single STL container.

> **Course:** CL2001 — Data Structures &nbsp;|&nbsp; **Spring 2026**  
> **Authors:** [Your Name] & Taha

---

## 🏗️ System Architecture

The system is divided into 8 departments, each owning a specific layer of the data pipeline:

```
┌─────────────────────────────────────────────────────────────────┐
│                        IFAMDS SYSTEM                            │
├──────────────┬──────────────────────────────────────────────────┤
│  Dept 1      │  Environmental Data Acquisition  →  Arrays A1–A4 │
│  Dept 2      │  Event Memory & Reconstruction   →  Lists L1–L10 │
│  Dept 3      │  Execution Control & Reasoning   →  Stack (ECL)  │
│  Dept 4      │  Task Scheduling & Allocation    →  Queues Q1–Q4 │
│  Dept 5      │  Hierarchical Decision Intel.    →  Trees T1–T12 │
│  Dept 6      │  Spatial Connectivity & Routing  →  Graphs G1–G2 │
│  Dept 7      │  Indexing & Retrieval             →  Hash H1–H3  │
│  Dept 8      │  System Monitoring & Adaptation  →  AMON         │
└──────────────┴──────────────────────────────────────────────────┘
```

---

## 🗂️ Data Structures Implemented

Every data structure below was built from the ground up — **no STL, no standard containers.**

### 📦 Arrays (A1 – A4)
| Structure | Type | Purpose |
|-----------|------|---------|
| **A1** | Static 1D Array | Baseline environmental reference values (fixed normal conditions) |
| **A2** | Dynamic 1D Array | Live sensor stream — updated at runtime per zone |
| **A3** | Static 2D Matrix (4×4) | Spatial temperature grid — supports interpolation & boundary detection |
| **A4** | Dynamic 2D Matrix (4×4) | Terrain risk scores — updated as conditions evolve |

### 🔗 Linked Lists (L1 – L10)
| Structure | Type | Purpose |
|-----------|------|---------|
| **L1–L3** | Singly Linked | Raw event stream, verified stream, anomaly log |
| **L4–L6** | Doubly Linked | Forward propagation, backward correction, state sync |
| **L7–L10** | Circular | Local, system-wide, emergency, and stability monitoring loops |

### 📚 Stacks & Queues
| Structure | Implementation | Purpose |
|-----------|---------------|---------|
| **Checkpoint Stack** | `MyStack<SystemSnapshot>` — array-based | ECL rollback — full A2 snapshot on every unsafe state entry |
| **Step Log Stack** | `MyStack<ExecutionStep>` — array-based | Complete execution audit trail, newest first |
| **Q1, Q2, Q4** | `MyQueue<Task>` — circular array FIFO | Routine monitoring, surveillance, multi-factor decisions |
| **Q3** | Binary min-heap array | Emergency priority queue — lowest priority number processed first |

### 🌳 Trees (T1 – T12)
Twelve decision trees covering the full decision hierarchy:

```
T1–T3   →  Structural (Zone hierarchy, sub-zone decomp., terrain)
T4–T6   →  Resources  (Water, fire control equipment, allocation)
T7–T9   →  Incidents  (Fire class., wildlife activity, human activity)
T10–T12 →  Decisions  (Local zone, regional escalation, global alert)
```

Each tree evaluates a weighted risk score: `Score = w₁·fire + w₂·smoke + w₃·temp`

### 🕸️ Graphs (G1 – G2)
| Graph | Representation | Complexity |
|-------|---------------|------------|
| **G1** | Adjacency List (`Edge[][]`) | BFS/DFS: O(V+E) &nbsp;\|&nbsp; Space: O(V+E) |
| **G2** | Adjacency Matrix (`double[][]`) | BFS: O(V²) &nbsp;\|&nbsp; Edge lookup: O(1) |

Both support **BFS** (fire spread simulation) and G1 additionally supports **DFS** (path tracing). Fire-aware cost update: `newCost = distance × (1 + fireLevel)`

### #️⃣ Hash Tables (H1 – H3)
| Table | Strategy | Purpose |
|-------|----------|---------|
| **H1** | Open addressing + linear probing | Primary zone data index — O(1) average |
| **H2** | Separate chaining | Collision resolution — linked chain per bucket |
| **H3** | Direct-mapped cache | Fast retrieval — O(1) put/get for hot zones |

Hash function: `index = ZoneID mod 11` (prime table size for better distribution)

---

## 🎬 Scenarios

Six complete forest-based simulation scenarios are included:

| # | Scenario | Key Structures Used |
|---|----------|-------------------|
| **1** | **Cascading Fire & Resource Conflict Resolution** | A2, ECL, L1/L2, DSCH, Q3, T7, T10, T11, G1 BFS |
| **2** | **Sensor Failure & System Reconstruction** | ECL rollback (×2), L2 filter, A3 interpolation, L5 BWD, H1 |
| **3** | **Multi-Factor Anomaly Escalation** | T7/T8/T9, multi-factor score, L3, Q3, G1 BFS, T12 |
| **4** | **System Overload & Load Redistribution** | DSCH rebalance, H3 cache, ECL, AMON threshold tuning |
| **5** | **Global Multi-Zone Emergency Synchronization** | ECL global scan, L4/L5/L6, T11/T12, G2 BFS, Q3 burst |
| **6** | **Execution Control & State Recovery** | Dept 3 (ECL), Dept 4 (DSCH), Dept 8 (AMON) in isolation |

---

## ⚡ Complexity Reference

| Operation | Time | Location |
|-----------|------|----------|
| Array access / update | O(1) | A1, A2, A3, A4 |
| Spatial interpolation | O(1) | A3 |
| SLL insert-front | O(1) | L1–L3 |
| SLL noise filter | O(n) | L2 |
| DLL insert-back | O(1) | L4–L6 |
| DLL correction | O(n) | L4 FWD, L5 BWD |
| CLL insert | O(1) | L7–L10 |
| FIFO enqueue/dequeue | O(1) | Q1, Q2, Q4 |
| Priority Queue enqueue | O(log n) | Q3 |
| Priority Queue dequeue | O(log n) | Q3 |
| Tree traversal (pre-order) | O(n) | T1–T12 |
| Decision score evaluation | O(1) | All trees |
| G1 BFS / DFS | O(V+E) | G1 |
| G2 BFS | O(V²) | G2 |
| Hash insert / search (avg) | O(1) | H1, H2, H3 |
| ECL checkpoint capture | O(n) | ECL |
| ECL rollback (restore) | O(n) | ECL |
| DSCH priority adjustment | O(n log n) | DSCH |
| AMON bottleneck detection | O(6) = O(1) | AMON |

---

## 🖥️ Menu System

The system provides a **two-level hierarchical menu** with 10 functional groups and 46 total sub-operations:

```
Main Menu
├── 1.  Input Environmental Data
│       1.1 Add Sensor Reading   1.2 Store in Dynamic Array
│       1.3 Compare with Baseline  1.4 Validate & Filter Noise
├── 2.  View Forest Grid Status
├── 3.  Event Memory System
├── 4.  Fire Detection and Control
├── 5.  Task Scheduling System
├── 6.  Decision System
├── 7.  Spatial Routing System
├── 8.  Hash-Based Fast Access System
├── 9.  System Monitoring
└── 10. Scenario Simulation
         10.6 Run Full System Simulation (all 6 scenarios)
```

---

## 🚀 Build & Run

### Requirements
- A C++17-compatible compiler (`g++`, `clang++`, or MSVC)
- No external dependencies — zero libraries required beyond the standard headers

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o IFAMDS IFAMDS_noSTL.cpp
```

### Run

```bash
./IFAMDS
```

> **Windows:**
> ```cmd
> g++ -std=c++17 -Wall -Wextra -O2 -o IFAMDS.exe IFAMDS_noSTL.cpp
> IFAMDS.exe
> ```

### Quick Start — Run All 6 Scenarios

Once the program starts:
1. The system initializes all 8 departments automatically
2. From the main menu, select **`10`** → Scenario Simulation
3. Select **`6`** → Run Full System Simulation

---

## 📁 Repository Structure

```
IFAMDS/
├── IFAMDS_noSTL.cpp          # Complete source code (~4,700 lines)
├── IFAMDS_Project_Report.docx # Full project report with dev log
└── README.md                  # This file
```

---

## 🔑 Key Design Decisions

**Why no STL?**  
Every container — `MyStack<T>`, `MyQueue<T>`, the binary min-heap, the adjacency list — was built from scratch using fixed-size arrays. This eliminates dynamic memory overhead, makes the code fully portable, and demonstrates a deep understanding of each data structure's internals.

**Why circular arrays for queues?**  
The circular array queue (`MyQueue`) offers O(1) enqueue and dequeue without shifting elements, matches the performance of `std::queue<deque>`, and avoids heap fragmentation from linked-node queues.

**Why a stack for checkpoints?**  
LIFO matches the rollback pattern exactly — the system always wants to restore the *most recently* captured safe state. The push/pop operations are O(1), and the fixed-size array-based stack avoids any heap allocation during a crisis moment when performance matters most.

---

## 🛠️ Development Timeline

| Date | Hours | Milestone |
|------|-------|-----------|
| 1 May | 3h 40m | Arrays A1–A4 with interpolation & boundary detection |
| 2 May | 4h 15m | All 10 linked list classes (SLL, DLL, CLL) |
| 3 May | 2h 50m | Queues Q1–Q4 + Dynamic Scheduler (DSCH) |
| 4 May | 4h 30m | 12 decision trees + both graph classes (BFS/DFS) |
| 5 May | 3h 20m | Hash tables H1–H3 + full ECL (checkpoint + rollback) |
| 6 May | 2h 10m | All 6 scenarios integrated and tested |
| 7 May | 4h 45m | **Full STL removal** — replaced all containers with custom implementations |
| 8 May | 3h 05m | Final integration, edge cases, time complexity comments, report |

**Total: 28 hours 55 minutes across 8 days**

---

## 👥 Authors

<table>
  <tr>
    <td align="center">
      <b>[Your Name]</b><br/>
      <sub>Co-developer</sub>
    </td>
    <td align="center">
      <b>Taha</b><br/>
      <sub>Co-developer</sub>
    </td>
  </tr>
</table>

CL2001 — Data Structures &nbsp;|&nbsp; Spring 2026 &nbsp;|&nbsp; Department of Computer Science

---

<div align="center">
  <sub>Built with 💚 and zero STL containers.</sub>
</div>
