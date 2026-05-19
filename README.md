<div align="center">
  
# 🌲 IFAMDS
  
### Intelligent Forest Advisory & Multi-Structure Decision System

**CL2001 - Data Structures Project | Spring 2026**

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()
[![Lines of Code](https://img.shields.io/badge/Lines-4700+-orange.svg)]()

*A complete console-based forest management simulation implementing 8 core data structure departments with zero STL dependencies.*

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [System Architecture](#-system-architecture)
- [Data Structures Implemented](#-data-structures-implemented)
- [Six Simulation Scenarios](#-six-simulation-scenarios)
- [Building & Running](#-building--running)
- [Menu System](#-menu-system)
- [Sample Output](#-sample-output)
- [Key Algorithms](#-key-algorithms)
- [Development Timeline](#-development-timeline)
- [Time Complexity Reference](#-time-complexity-reference)
- [Author](#-author)

---

## 🎯 Overview

**IFAMDS** is a comprehensive forest fire management simulation built entirely from scratch in **C++17**. The system models real-time forest monitoring enabling:

- 🔥 **Fire Detection & Prediction**
- 🚨 **Emergency Response Coordination**
- 📊 **Resource Allocation**
- 🔄 **System Recovery & Rollback**
- 📈 **Adaptive Performance Monitoring**

### ⭐ Key Achievement
**Zero STL containers used** - Every data structure implemented manually.

---


---

## 📊 Data Structures Implemented

| Structure | Instances | Time Complexity |
|-----------|-----------|-----------------|
| Static Arrays | A1, A3 | O(1), O(n) |
| Dynamic Arrays | A2, A4 | O(1), O(n) |
| Singly Linked Lists | L1, L2, L3 | O(1), O(n) |
| Doubly Linked Lists | L4, L5, L6 | O(1), O(n) |
| Circular Lists | L7-L10 | O(1), O(n) |
| FIFO Queues | Q1, Q2, Q4 | O(1) |
| Priority Queue | Q3 | O(log n) |
| Binary Trees | T1-T12 | O(1), O(n) |
| Adjacency List Graph | G1 | O(V+E) |
| Adjacency Matrix Graph | G2 | O(V²) |
| Hash Table (Open Addressing) | H1 | O(1) avg |
| Hash Table (Chaining) | H2 | O(1) avg |
| Direct Cache | H3 | O(1) |
| Stack (Checkpoint) | ECL | O(1) |

---

## 🎮 Six Simulation Scenarios

| # | Scenario | Description |
|---|----------|-------------|
| 1 | 🔥 Cascading Fire | Fire spreads Zone 3→4→6 with rollback recovery |
| 2 | 📡 Sensor Failure | Faulty sensors trigger interpolation recovery |
| 3 | ⚠️ Multi-Factor Anomaly | Wildlife + Fire + Human anomalies simultaneously |
| 4 | 🔄 System Overload | Load balancing + cache warming + bottleneck detection |
| 5 | 🌍 Global Emergency | Ten-zone conflict resolution + synchronized BFS |
| 6 | 💾 State Recovery | Checkpoint/rollback + adaptive monitoring |

---

## 🛠️ Building & Running

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -O2 IFAMDS_noSTL.cpp -o ifamds

# Run
./ifamds

# On Windows
ifamds.exe

