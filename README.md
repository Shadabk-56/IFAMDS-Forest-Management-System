<div align="center">
  
# 🌲 IFAMDS
  
### Intelligent Forest Advisory & Multi-Structure Decision System

**CL2001 - Data Structures Project | Spring 2026**

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()

*A complete console-based forest management simulation implementing 8 core data structure departments with zero STL dependencies.*

</div>

---

## 📋 Overview

IFAMDS is a comprehensive forest fire management simulation built from scratch in C++. The system models a real-time forest monitoring environment where sensor data flows through multiple processing layers, enabling intelligent decision-making for fire detection, resource allocation, and emergency response.

**Key Achievement:** All data structures (stacks, queues, priority queues, linked lists, trees, graphs, hash tables) were implemented manually without using any STL containers.

---

## 🏗️ System Architecture

┌─────────────────────────────────────────────────────────────┐
│ IFAMDS CORE SYSTEM │
├─────────────┬─────────────┬─────────────┬──────────────────┤
│ Dept 1 │ Dept 2 │ Dept 3 │ Dept 4 │
│ Arrays │Linked Lists │ Stacks │ Queues │
│ (A1-A4) │ (L1-L10) │ (ECL) │ (Q1-Q4 + DSCH) │
├─────────────┼─────────────┼─────────────┼──────────────────┤
│ Dept 5 │ Dept 6 │ Dept 7 │ Dept 8 │
│ Trees │ Graphs │Hash Tables │Adaptive Monitor │
│ (T1-T12) │ (G1-G2) │ (H1-H3) │ (AMON) │
└─────────────┴─────────────┴─────────────┴──────────────────┘


---

## 📊 Data Structures Implemented

| Structure | Instances | Operations | Complexity |
|-----------|-----------|------------|------------|
| **Static Arrays** | A1, A3 | O(1) access, O(n) scan | O(1)/O(n) |
| **Dynamic Arrays** | A2, A4 | O(1) update, O(n) scan | O(1)/O(n) |
| **Singly Linked Lists** | L1-L3 | Insert front O(1), Insert back O(n) | O(1)/O(n) |
| **Doubly Linked Lists** | L4-L6 | Insert O(1), Correction O(n) | O(1)/O(n) |
| **Circular Lists** | L7-L10 | Insert O(1), Cycle O(n) | O(1)/O(n) |
| **FIFO Queues** | Q1, Q2, Q4 | Enqueue/Dequeue O(1) | O(1) |
| **Priority Queue** | Q3 | Enqueue/Dequeue O(log n) | O(log n) |
| **Binary Trees** | T1-T12 | Add O(1), Traversal O(n) | O(1)/O(n) |
| **Adjacency List** | G1 | BFS/DFS O(V+E) | O(V+E) |
| **Adjacency Matrix** | G2 | BFS O(V²), Lookup O(1) | O(V²)/O(1) |
| **Hash Table (OA)** | H1 | Avg O(1), Worst O(n) | O(1)/O(n) |
| **Hash Table (SC)** | H2 | Avg O(1), Worst O(n) | O(1)/O(n) |
| **Direct Cache** | H3 | Get/Put O(1) | O(1) |
| **Stack (Checkpoint)** | ECL | Push/Pop O(1) | O(1) |

---

## 🎮 Six Simulation Scenarios

### 1. 🔥 Cascading Fire & Resource Conflict
Fire spreads from Zone 3 → 4 → 6 with priority escalation and rollback recovery.

### 2. 📡 Sensor Failure & Reconstruction
Faulty Zone 2 sensors trigger rollback + spatial interpolation for recovery.

### 3. ⚠️ Multi-Factor Anomaly Escalation
Wildlife + Fire + Human anomalies detected and prioritized simultaneously.

### 4. 🔄 System Overload & Load Redistribution
Flood of updates triggers dynamic load balancing and cache warming.

### 5. 🌍 Global Multi-Zone Emergency
Ten-zone conflict resolution with synchronized BFS and bulk dispatch.

### 6. 💾 Execution Control & State Recovery
Dedicated testing of checkpoint/rollback and adaptive monitoring.

---

## 🛠️ Building & Running

### Prerequisites
- C++17 compatible compiler (g++ 7+, clang 5+, MSVC 2017+)
- No external dependencies

### Compilation

```bash
# Using g++
g++ -std=c++17 -Wall -Wextra -O2 IFAMDS_noSTL.cpp -o ifamds

# Run the executable
./ifamds

## Quick Test
# Run all 6 scenarios automatically
> Enter choice: 10
> Then select: 6 (Run Full System Simulation)

## 🖥️ Menu System
╔══════════════════════════════════════════════════════════╗
║   IFAMDS  |  Intelligent Forest Advisory & Multi-Structure ║
║            |  Decision System  [MAIN MENU]                 ║
╠══════════════════════════════════════════════════════════╣
║   1.  Input Environmental Data                            ║
║   2.  View Forest Grid Status                             ║
║   3.  Event Memory System                                 ║
║   4.  Fire Detection and Control                          ║
║   5.  Task Scheduling System                              ║
║   6.  Decision System                                     ║
║   7.  Spatial Routing System                              ║
║   8.  Hash-Based Fast Access System                       ║
║   9.  System Monitoring                                   ║
║   10. Scenario Simulation                                 ║
║   0.  Exit System                                         ║
╚══════════════════════════════════════════════════════════╝


