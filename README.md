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

**CL2001 — Data Structures | Spring 2026**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B)](https://isocpp.org/)
[![STL](https://img.shields.io/badge/STL%20Usage-Zero-brightgreen?style=for-the-badge)](https://en.cppreference.com/)
[![Lines of Code](https://img.shields.io/badge/Lines%20of%20Code-~4700-orange?style=for-the-badge)]()
[![Data Structures](https://img.shields.io/badge/Data%20Structures-7%20Types-blue?style=for-the-badge)]()
[![Scenarios](https://img.shields.io/badge/Scenarios-6%20Complete-purple?style=for-the-badge)]()

*A complete C++ console simulation that integrates every major data structure — Arrays, Linked Lists, Stacks, Queues, Trees, Graphs, and Hash Tables — into a unified, real-world forest management system.*

</div>

---

## Table of Contents

- [Overview](#overview)
- [Architecture](#architecture)
- [Data Structures Implemented](#data-structures-implemented)
- [Departments](#departments)
- [Scenarios](#scenarios)
- [Menu System](#menu-system)
- [Compilation & Usage](#compilation--usage)
- [Time Complexity Reference](#time-complexity-reference)
- [Development Log](#development-log)
- [Authors](#authors)

---

## Overview

IFAMDS models a real-world forest environment where sensor data continuously flows through multiple processing layers and intelligent decisions emerge from the **combined interaction of all data structures** — not any single component in isolation.

The system monitors **10 forest zones** across a 4×4 grid, tracking temperature, humidity, smoke levels, and fire signals in real time. When anomalies are detected — fire spreading, sensor failures, or multi-factor threats — the system responds with rollback, rescheduling, and adaptive optimization automatically.

> **Key constraint:** Every data structure in this project — stacks, queues, priority queues, adjacency lists, hash tables — was implemented **from scratch**. Zero STL containers were used. `std::vector`, `std::stack`, `std::queue`, `std::priority_queue` — all replaced with custom fixed-size array implementations.

---

## Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                        IFAMDS SYSTEM                            │
├──────────────┬──────────────┬──────────────┬────────────────────┤
│  Dept 1      │  Dept 2      │  Dept 3      │  Dept 4            │
│  Arrays      │  Linked      │  Execution   │  Scheduler         │
│  A1–A4       │  Lists       │  Control     │  Q1–Q4 + DSCH      │
│  (Sensors)   │  L1–L10      │  ECL (Stack) │  (Task Queues)     │
├──────────────┼──────────────┼──────────────┼────────────────────┤
│  Dept 5      │  Dept 6      │  Dept 7      │  Dept 8            │
│  Trees       │  Graphs      │  Hash Tables │  Adaptive          │
│  T1–T12      │  G1–G2       │  H1–H3       │  Monitor (AMON)    │
│  (Decisions) │  (Routing)   │  (Indexing)  │  (Optimization)    │
└──────────────┴──────────────┴──────────────┴────────────────────┘
                              │
              ┌───────────────▼───────────────┐
              │     6 SCENARIO SIMULATIONS    │
              │  Fire | Sensor Failure |      │
              │  Anomaly | Overload |         │
              │  Global Emergency | Recovery  │
              └───────────────────────────────┘
```

---

## Data Structures Implemented

### Arrays — `A1` to `A4`

| ID | Type | Purpose |
|----|------|---------|
| **A1** | Static 1D Array | Baseline environmental reference values (25°C, 60% humidity, smoke=0) |
| **A2** | Dynamic 1D Array | Live sensor stream — updated continuously at runtime |
| **A3** | Static 2D Matrix (4×4) | Spatial temperature grid with interpolation and boundary detection |
| **A4** | Dynamic 2D Matrix (4×4) | Terrain risk scores updated as conditions worsen |

> **Key operation:** `A3.interpolate(r, c)` estimates missing sensor values from the arithmetic mean of up to 4 spatial neighbours. Used by the ECL Alternative Path to replace bad readings without halting the system.

---

### Linked Lists — `L1` to `L10`

| IDs | Variant | Role |
|-----|---------|------|
| **L1–L3** | Singly Linked | Raw event stream · Verified (noise-filtered) stream · Anomaly log |
| **L4–L6** | Doubly Linked | Forward propagation · Backward correction · State synchronization |
| **L7–L10** | Circular Linked | Local · System-wide · Emergency · Stability monitoring loops |

> Singly linked lists for append-only streams; doubly linked for bidirectional correction; circular for continuous surveillance that never terminates.

---

### Stacks — Execution Control Layer (ECL)

Two custom `MyStack<T, MAXSZ>` instances power the ECL:

- **Checkpoint Stack** — stores full `SystemSnapshot` objects (deep copy of A2). `rollback()` pops the top snapshot and restores the system to a verified safe state.
- **Step Log Stack** — records every `ExecutionStep` as an audit trail, inspectable newest-first.

```
Push = captureCheckpoint()   O(1)
Pop  = rollback()            O(1)  + O(n) for state restore
```

---

### Queues — `Q1` to `Q4`

Implemented via custom `MyQueue<T, MAXSZ>` (circular array FIFO):

| Queue | Type | Implementation | Priority |
|-------|------|----------------|----------|
| **Q1** | Routine Monitoring | Circular Array FIFO | Lowest |
| **Q2** | Continuous Surveillance | Circular Array FIFO | Medium |
| **Q3** | Emergency Response | **Binary Min-Heap** | Highest (lowest number = first) |
| **Q4** | Multi-Factor Decision | Circular Array FIFO | Medium-High |

---

### Trees — `T1` to `T12`

| Trees | Category |
|-------|----------|
| T1–T3 | Zone hierarchy · Sub-zone decomposition · Terrain classification |
| T4–T6 | Water resources · Fire equipment · Allocation priority |
| T7–T9 | Fire incident classification · Wildlife activity · Human detection |
| T10–T12 | Local response · Regional escalation · **Global emergency command** |

Decision scoring: `Score = w₁·fire + w₂·smoke + w₃·temperature`. If `Score > threshold` → emergency activated.

---

### Graphs — `G1` and `G2`

| Graph | Structure | Space | BFS | DFS |
|-------|-----------|-------|-----|-----|
| **G1** | Adjacency List | O(V+E) | ✅ O(V+E) | ✅ O(V+E) |
| **G2** | Adjacency Matrix | O(V²) | ✅ O(V²) | — |

Fire-aware cost update: `newCost = oldCost × (1 + fireLevel)` — burning corridors become prohibitively expensive.

---

### Hash Tables — `H1`, `H2`, `H3`

A three-tier indexing system mirroring real database design:

| Table | Strategy | Avg Complexity |
|-------|----------|----------------|
| **H1** | Open Addressing + Linear Probing | O(1) |
| **H2** | Separate Chaining (linked buckets) | O(1) |
| **H3** | Direct-Mapped Fast Cache | O(1) |

Hash function: `index = ZoneID mod 11` (prime table size for better distribution).

---

## Departments

```
Dept 1  │  Environmental Data Acquisition     →  Arrays A1–A4
Dept 2  │  Event Memory & Temporal Recall     →  Linked Lists L1–L10
Dept 3  │  Execution Control & Reasoning      →  Stack-based ECL
Dept 4  │  Task Scheduling & Prioritization   →  Queues Q1–Q4 + DSCH
Dept 5  │  Hierarchical Decision Intelligence →  Trees T1–T12
Dept 6  │  Spatial Connectivity & Routing     →  Graphs G1–G2
Dept 7  │  Indexing & Retrieval Acceleration  →  Hash Tables H1–H3
Dept 8  │  System Monitoring & Optimization   →  Adaptive Monitor (AMON)
```

---

## Scenarios

### Scenario 1 — Cascading Fire & Resource Conflict Resolution
Fire originates in Zone 3 and spreads toward Zones 4 and 6. The system captures a pre-fire ECL checkpoint, validates incoming readings, triggers a rollback on instability, escalates tasks from Q1 to Q3 via DSCH, classifies fire severity using T7, predicts spread via BFS on G1, and synchronizes all confirmed data to H1 and L6.

### Scenario 2 — Sensor Failure & System Reconstruction
Zone 2 sensors begin returning physically impossible values (temperature = 999°C, −8°C). L2 noise filter and ECL physical-limit checks reject all readings. The ECL step log is scanned backward for the last valid entry. A two-level rollback is available. Missing values are reconstructed via A3 spatial interpolation combined with historical readings. L5 backward correction fixes the event chain.

### Scenario 3 — Multi-Factor Anomaly Escalation
Three simultaneous threat types appear: wildfire risk (T7), wildlife movement (T8), and unauthorized human presence (T9). Each is classified independently, then combined into a multi-factor danger score. Zones scoring above 0.6 are escalated to L3 and Q3; others continue normal observation via Q1 and the L7 local loop.

### Scenario 4 — System Overload & Load Redistribution
A burst of 20+ simultaneous updates floods all queues. ECL captures a safe checkpoint. DSCH separates critical tasks and escalates fire-zone items to Q3. Q1/Q2 are held and rebalanced. H3 cache is pre-warmed with hot zones. Paused tasks are drained in controlled batches of 3. AMON offloads 15% from the bottleneck module and tunes alert thresholds.

### Scenario 5 — Global Multi-Zone Emergency Synchronization
All 10 zones receive conflicting, asynchronous updates simultaneously. ECL runs a full consistency scan, separating zones into conflicting and clean sets. L5 backward correction, ECL rollback, L4 forward propagation, and L6 state sync reconstruct a globally coherent state. T11 and T12 issue escalating alerts. G2 matrix BFS runs multi-origin spread analysis. Q3 receives a synchronized bulk dispatch.

### Scenario 6 — Execution Control & State Recovery
Exercises Departments 3, 4, and 8 in isolation. Corrupt values are deliberately injected. ECL detects them, pauses execution, rolls back, and runs the alternative path for remaining bad zones. DSCH re-adjusts priorities post-recovery. AMON performs bottleneck detection, threshold tuning, load redistribution, and full health reporting.

---

## Menu System

A hierarchical two-level menu — 10 groups × 4–6 sub-options = **46 total operations**:

```
═══════════════════════════════════════════════════════════════
  IFAMDS  |  Main Menu
═══════════════════════════════════════════════════════════════
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
───────────────────────────────────────────────────────────────
  0.  Exit System
═══════════════════════════════════════════════════════════════
```

---

## Compilation & Usage

### Requirements
- **Compiler:** `g++` with C++17 support
- **OS:** Linux · macOS · Windows (MinGW or MSVC)
- **Dependencies:** None — zero external libraries, zero STL containers

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -o IFAMDS IFAMDS_noSTL.cpp
```

### Run

```bash
./IFAMDS          # Linux / macOS
IFAMDS.exe        # Windows
```

### Quick Scenario Test

Launch the program → select **Menu 10** → **Sub-option 6** to run all six scenarios in sequence automatically.

---

## Time Complexity Reference

| Operation | Complexity | Component |
|-----------|-----------|-----------|
| Array access (single zone) | O(1) | A1, A2, A3, A4 |
| Array full scan | O(n) | A2.display(), A3.detectBoundaries() |
| Spatial interpolation | O(1) | A3.interpolate() |
| SLL insert-front | O(1) | L1–L3 |
| SLL insert-back | O(n) | L1–L3 |
| DLL insert-back | O(1) | L4–L6 |
| DLL correction (fwd/bwd) | O(n) | forwardCorrect / backwardCorrect |
| CLL insert | O(1) | L7–L10 |
| FIFO enqueue / dequeue | O(1) | Q1, Q2, Q4 |
| Priority Queue enqueue | O(log n) | Q3 min-heap |
| Priority Queue dequeue | O(log n) | Q3 min-heap |
| Stack push / pop | O(1) | ECL checkpoint + step log |
| Checkpoint capture | O(n) | ECL captureCheckpoint |
| Checkpoint rollback | O(n) | ECL rollback |
| Tree addChild | O(1) | T1–T12 |
| Tree pre-order traversal | O(n) | T1–T12 |
| Decision score evaluation | O(1) | evaluateDecision |
| Graph addEdge | O(1) | G1, G2 |
| BFS adjacency list | O(V+E) | G1.BFS |
| DFS adjacency list | O(V+E) | G1.runDFS |
| BFS adjacency matrix | O(V²) | G2.BFS |
| Hash insert / search (avg) | O(1) | H1, H2, H3 |
| Bottleneck detection | O(1) | AMON.detectBottleneck |
| Priority upgrade scan | O(n) | DSCH.adjustPriorities |
| Queue rebalancing | O(n) | DSCH.rebalanceQueues |

---

## Authors

<div align="center">

| | Contributor |
|--|-------------|
| 👨‍💻 | **Shadab Ahad** |
| 👨‍💻 | **Taha Amjad** |

*CL2001 — Data Structures · Department of Artificial Intelligence · Spring 2026*

</div>

---

<div align="center">

*Built from scratch, zero dependencies — FAST NUCES Islamabad.*

</div>
