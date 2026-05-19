#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <climits>
using namespace std;

struct Edge {
    int    dest;
    double cost;
};

template<typename T, int MAXSZ>
class MyStack {
public:
    T   data[MAXSZ];
    int topIdx;          

    MyStack() : topIdx(-1) {}

    
    bool push(const T& val) {
        if (topIdx + 1 >= MAXSZ) {
            cout << "  [MyStack] OVERFLOW — capacity " << MAXSZ << " exceeded!\n";
            return false;
        }
        data[++topIdx] = val;
        return true;
    }

    
    T pop() {
        if (topIdx < 0) { cout << "  [MyStack] UNDERFLOW!\n"; return T(); }
        return data[topIdx--];
    }

    
    T&       peek()       { return data[topIdx]; }
    const T& peek() const { return data[topIdx]; }

    bool empty()  const { return topIdx < 0; }
    int  size()   const { return topIdx + 1; }

    
    const T& at(int i) const { return data[i]; }
    T&       at(int i)       { return data[i]; }
};

template<typename T, int MAXSZ>
class MyQueue {
public:
    T   data[MAXSZ];
    int frontIdx, backIdx, sz;

    MyQueue() : frontIdx(0), backIdx(0), sz(0) {}

    
    bool push(const T& val) {
        if (sz == MAXSZ) {
            cout << "  [MyQueue] OVERFLOW — capacity " << MAXSZ << " exceeded!\n";
            return false;
        }
        data[backIdx] = val;
        backIdx = (backIdx + 1) % MAXSZ;
        sz++;
        return true;
    }

    
    T pop() {
        if (sz == 0) { cout << "  [MyQueue] UNDERFLOW!\n"; return T(); }
        T val   = data[frontIdx];
        frontIdx = (frontIdx + 1) % MAXSZ;
        sz--;
        return val;
    }

    
    T&       front()       { return data[frontIdx]; }
    const T& front() const { return data[frontIdx]; }

    bool empty() const { return sz == 0; }
    int  size()  const { return sz; }

    
    const T& at(int i) const { return data[(frontIdx + i) % MAXSZ]; }
};

const int    MAX_ZONES        = 10;
const int    GRID_ROWS        = 4;
const int    GRID_COLS        = 4;
const int    HASH_SIZE        = 11;   
const double TEMP_THRESHOLD   = 45.0; 
const double SMOKE_THRESHOLD  = 70.0; 
const double HUMID_THRESHOLD  = 20.0; 
const double NOISE_DELTA      = 5.0;  

struct StaticBaseline {
    double temperature[MAX_ZONES]; 
    double humidity[MAX_ZONES];    
    double smokeLevel[MAX_ZONES];  

    
    void initialize() {
        for (int i = 0; i < MAX_ZONES; i++) {
            temperature[i] = 25.0;
            humidity[i]    = 60.0;
            smokeLevel[i]  = 0.0;
        }
    }

    void display() const {
        cout << "\n[A1] Static Environmental Baseline Array:\n";
        cout << left << setw(8)  << "Zone"
                     << setw(14) << "Temp(C)"
                     << setw(16) << "Humidity(%)"
                     << "SmokeLevel\n";
        cout << string(50, '-') << "\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            cout << left << setw(8)  << i
                         << setw(14) << temperature[i]
                         << setw(16) << humidity[i]
                         << smokeLevel[i] << "\n";
        }
    }
};

struct DynamicSensorArray {
    double temperature[MAX_ZONES];
    double humidity[MAX_ZONES];
    double smokeLevel[MAX_ZONES];
    int    fireSignal[MAX_ZONES]; 

    
    void initialize() {
        double tmps[] = { 27,  30,  55,  28,  65,  26,  35,  29,  25,  52 };
        double hums[] = { 55,  50,  22,  58,  13,  62,  40,  57,  60,  15 };
        double smks[] = {  5,  10,  72,   8,  88,   3,  30,   7,   0,  78 };
        for (int i = 0; i < MAX_ZONES; i++) {
            temperature[i] = tmps[i];
            humidity[i]    = hums[i];
            smokeLevel[i]  = smks[i];
            
            fireSignal[i]  = (temperature[i] > TEMP_THRESHOLD ||
                              smokeLevel[i]  > SMOKE_THRESHOLD) ? 1 : 0;
        }
    }

    
    void updateZone(int zone, double t, double h, double s) {
        if (zone < 0 || zone >= MAX_ZONES) {
            cout << "  [A2] ERROR: Invalid zone " << zone << "\n";
            return;
        }
        temperature[zone] = t;
        humidity[zone]    = h;
        smokeLevel[zone]  = s;
        fireSignal[zone]  = (t > TEMP_THRESHOLD || s > SMOKE_THRESHOLD) ? 1 : 0;
        cout << "  [A2] Zone " << zone << " updated -> T=" << t
             << "C  H=" << h << "%  S=" << s
             << "  Fire=" << fireSignal[zone] << "\n";
    }

    void display() const {
        cout << "\n[A2] Dynamic Sensor Stream Array (Live Readings):\n";
        cout << left << setw(7) << "Zone"
                     << setw(11) << "Temp(C)"
                     << setw(14) << "Humidity(%)"
                     << setw(10) << "Smoke"
                     << "FireSignal\n";
        cout << string(55, '-') << "\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            cout << left << setw(7) << i
                         << setw(11) << temperature[i]
                         << setw(14) << humidity[i]
                         << setw(10) << smokeLevel[i]
                         << fireSignal[i]
                         << (fireSignal[i] ? " << FIRE ALERT" : "") << "\n";
        }
    }
};

struct StaticGridMatrix {
    double grid[GRID_ROWS][GRID_COLS];

    void initialize() {
        double vals[GRID_ROWS][GRID_COLS] = {
            { 25, 30, 28, 27 },
            { 27, 46, 32, 29 },
            { 26, 29, 31, 52 },
            { 24, 28, 35, 25 }
        };
        for (int r = 0; r < GRID_ROWS; r++)
            for (int c = 0; c < GRID_COLS; c++)
                grid[r][c] = vals[r][c];
    }

    
    double interpolate(int r, int c) const {
        double sum = 0; int cnt = 0;
        if (r > 0)           { sum += grid[r-1][c]; cnt++; }
        if (r < GRID_ROWS-1) { sum += grid[r+1][c]; cnt++; }
        if (c > 0)           { sum += grid[r][c-1]; cnt++; }
        if (c < GRID_COLS-1) { sum += grid[r][c+1]; cnt++; }
        return cnt ? sum / cnt : 0.0;
    }

    
    void detectBoundaries() const {
        cout << "\n  [A3] Boundary Detection:\n";
        bool found = false;
        for (int r = 0; r < GRID_ROWS; r++) {
            for (int c = 0; c < GRID_COLS; c++) {
                
                if (c + 1 < GRID_COLS && fabs(grid[r][c] - grid[r][c+1]) > 10) {
                    cout << "    BOUNDARY: (" << r << "," << c << ")="
                         << grid[r][c] << "  <-->  (" << r << "," << c+1 << ")="
                         << grid[r][c+1] << "\n";
                    found = true;
                }
                
                if (r + 1 < GRID_ROWS && fabs(grid[r][c] - grid[r+1][c]) > 10) {
                    cout << "    BOUNDARY: (" << r << "," << c << ")="
                         << grid[r][c] << "  <-->  (" << r+1 << "," << c << ")="
                         << grid[r+1][c] << "\n";
                    found = true;
                }
            }
        }
        if (!found) cout << "    No significant boundaries detected.\n";
    }

    
    void detectAnomalies() const {
        cout << "\n  [A3] Anomaly Detection (threshold=" << TEMP_THRESHOLD << "C):\n";
        bool found = false;
        for (int r = 0; r < GRID_ROWS; r++)
            for (int c = 0; c < GRID_COLS; c++)
                if (grid[r][c] > TEMP_THRESHOLD) {
                    cout << "    ANOMALY at (" << r << "," << c
                         << "): Temp=" << grid[r][c] << "C  [FIRE RISK]\n";
                    found = true;
                }
        if (!found) cout << "    No anomalies found.\n";
    }

    void display() const {
        cout << "\n[A3] Static Forest Grid Matrix (temperature °C):\n";
        cout << "     ";
        for (int c = 0; c < GRID_COLS; c++) cout << setw(7) << "Col" + to_string(c);
        cout << "\n";
        for (int r = 0; r < GRID_ROWS; r++) {
            cout << "Row" << r << " ";
            for (int c = 0; c < GRID_COLS; c++)
                cout << setw(7) << fixed << setprecision(1) << grid[r][c];
            cout << "\n";
        }
    }
};

struct DynamicTerrainMatrix {
    double terrain[GRID_ROWS][GRID_COLS];

    void initialize() {
        
        for (int r = 0; r < GRID_ROWS; r++)
            for (int c = 0; c < GRID_COLS; c++)
                terrain[r][c] = 0.20 + 0.05 * (r + c);
    }

    
    void updateTerrain(int r, int c, double risk) {
        if (r >= 0 && r < GRID_ROWS && c >= 0 && c < GRID_COLS) {
            terrain[r][c] = risk;
            cout << "  [A4] Terrain (" << r << "," << c << ") -> risk=" << risk << "\n";
        }
    }

    void display() const {
        cout << "\n[A4] Dynamic Terrain Expansion Matrix (risk 0.0-1.0):\n";
        cout << "     ";
        for (int c = 0; c < GRID_COLS; c++) cout << setw(7) << "Col" + to_string(c);
        cout << "\n";
        for (int r = 0; r < GRID_ROWS; r++) {
            cout << "Row" << r << " ";
            for (int c = 0; c < GRID_COLS; c++)
                cout << setw(7) << fixed << setprecision(2) << terrain[r][c];
            cout << "\n";
        }
    }
};

struct ForestEvent {
    double value;
    int    zoneID;
    string timestamp;
    string eventType; 

    ForestEvent(double v=0, int z=0, string ts="t0", string et="raw")
        : value(v), zoneID(z), timestamp(ts), eventType(et) {}
};

struct SLLNode {
    ForestEvent data;
    SLLNode*    next;
    SLLNode(ForestEvent e) : data(e), next(nullptr) {}
};

class SinglyLinkedList {
public:
    SLLNode* head;
    string   listName;
    int      size;

    SinglyLinkedList(const string& n) : head(nullptr), listName(n), size(0) {}

    
    void insertBack(ForestEvent e) {
        SLLNode* node = new SLLNode(e);
        if (!head) { head = node; size++; return; }
        SLLNode* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = node;
        size++;
    }

    
    void insertFront(ForestEvent e) {
        SLLNode* node = new SLLNode(e);
        node->next = head;
        head = node;
        size++;
    }

    
    void filterNoise(double delta) {
        if (!head || !head->next) return;
        cout << "  Applying noise filter (delta=" << delta << "):\n";
        SLLNode* prev = head;
        SLLNode* cur  = head->next;
        while (cur) {
            if (fabs(cur->data.value - prev->data.value) >= delta) {
                cout << "    [NOISE REMOVED] Zone=" << cur->data.zoneID
                     << "  Value=" << cur->data.value << "\n";
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
                size--;
            } else {
                prev = cur;
                cur  = cur->next;
            }
        }
    }

    
    void display() const {
        cout << "\n[" << listName << "] Singly Linked List  (" << size << " events):\n";
        SLLNode* cur = head;
        int idx = 1;
        while (cur) {
            cout << "  [" << idx++ << "]  Zone=" << cur->data.zoneID
                 << "  Val="  << fixed << setprecision(1) << cur->data.value
                 << "  Type=" << cur->data.eventType
                 << "  ts="   << cur->data.timestamp;
            if (cur->data.value > TEMP_THRESHOLD)
                cout << "  *** HIGH TEMP ***";
            cout << "\n";
            cur = cur->next;
        }
        if (!head) cout << "  (empty)\n";
    }

    ~SinglyLinkedList() {
        SLLNode* cur = head;
        while (cur) { SLLNode* t = cur->next; delete cur; cur = t; }
    }
};

struct DLLNode {
    ForestEvent data;
    DLLNode*    prev;
    DLLNode*    next;
    DLLNode(ForestEvent e) : data(e), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    DLLNode* head;
    DLLNode* tail;
    string   listName;
    int      size;

    DoublyLinkedList(const string& n)
        : head(nullptr), tail(nullptr), listName(n), size(0) {}

    
    void insertBack(ForestEvent e) {
        DLLNode* node = new DLLNode(e);
        if (!tail) { head = tail = node; }
        else { tail->next = node; node->prev = tail; tail = node; }
        size++;
    }

    
    void forwardCorrect(int fromZone, double newVal) {
        DLLNode* cur = head;
        bool     applying = false;
        while (cur) {
            if (!applying && cur->data.zoneID == fromZone) {
                cur->data.value = newVal;
                cout << "    [FWD] Corrected source  Zone=" << fromZone
                     << "  to " << newVal << "\n";
                applying = true;
            } else if (applying) {
                
                cur->data.value += newVal * 0.05;
                cout << "    [FWD] Downstream Zone=" << cur->data.zoneID
                     << "  adjusted to " << fixed << setprecision(2)
                     << cur->data.value << "\n";
            }
            cur = cur->next;
        }
    }

    
    void backwardCorrect(int fromZone, double newVal) {
        DLLNode* cur = tail;
        bool     applying = false;
        while (cur) {
            if (!applying && cur->data.zoneID == fromZone) {
                applying = true;
            } else if (applying) {
                cur->data.value = newVal; 
                cout << "    [BWD] Corrected previous Zone=" << cur->data.zoneID
                     << "  to " << newVal << "\n";
            }
            cur = cur->prev;
        }
    }

    
    void display() const {
        cout << "\n[" << listName << "] Doubly Linked List  (" << size << " events):\n";
        DLLNode* cur = head;
        int idx = 1;
        while (cur) {
            cout << "  [" << idx++ << "]  Zone=" << cur->data.zoneID
                 << "  Val=" << fixed << setprecision(2) << cur->data.value
                 << "  Type=" << cur->data.eventType;
            if (cur->prev) cout << "  <PREV:Z" << cur->prev->data.zoneID << ">";
            if (cur->next) cout << "  <NEXT:Z" << cur->next->data.zoneID << ">";
            cout << "\n";
            cur = cur->next;
        }
        if (!head) cout << "  (empty)\n";
    }

    ~DoublyLinkedList() {
        DLLNode* cur = head;
        while (cur) { DLLNode* t = cur->next; delete cur; cur = t; }
    }
};

struct CLLNode {
    ForestEvent data;
    CLLNode*    next;
    CLLNode(ForestEvent e) : data(e), next(nullptr) {}
};

class CircularLinkedList {
public:
    CLLNode* tail; 
    string   listName;
    int      size;

    CircularLinkedList(const string& n) : tail(nullptr), listName(n), size(0) {}

    
    void insert(ForestEvent e) {
        CLLNode* node = new CLLNode(e);
        if (!tail) {
            tail = node;
            tail->next = tail; 
        } else {
            node->next = tail->next; 
            tail->next = node;       
            tail       = node;       
        }
        size++;
    }

    
    void monitorCycle() const {
        if (!tail) { cout << "  (circular list empty)\n"; return; }
        CLLNode* head = tail->next;
        CLLNode* cur  = head;
        cout << "  Cycle:  ";
        do {
            cout << "Zone" << cur->data.zoneID
                 << "(" << fixed << setprecision(0) << cur->data.value << ")";
            if (cur->data.value > TEMP_THRESHOLD) cout << "[!]";
            cout << " --> ";
            cur = cur->next;
        } while (cur != head);
        cout << "(back to start)\n";
    }

    void display() const {
        cout << "\n[" << listName << "] Circular Linked List  (" << size << " nodes):\n";
        monitorCycle();
    }

    ~CircularLinkedList() {
        if (!tail) return;
        CLLNode* head = tail->next;
        CLLNode* cur  = head;
        do {
            CLLNode* t = cur->next;
            delete cur;
            cur = t;
        } while (cur != head);
    }
};

struct Task {
    string taskID;
    int    zoneID;
    string taskType; 
    double value;
    int    priority; 

    Task(string id="", int z=0, string tt="", double v=0.0, int p=3)
        : taskID(id), zoneID(z), taskType(tt), value(v), priority(p) {}
};

static const int MAX_FQUEUE = 300; 

class ForestQueue {
public:
    MyQueue<Task, MAX_FQUEUE> q; 
    string                    qName;

    ForestQueue(const string& n) : qName(n) {}

    
    void enqueue(const Task& t) {
        q.push(t);
        cout << "  [" << qName << "] Enqueued: " << t.taskID
             << "  Zone=" << t.zoneID
             << "  Type=" << t.taskType << "\n";
    }

    
    Task dequeue() {
        if (q.empty()) {
            cout << "  [" << qName << "] Queue empty!\n";
            return Task();
        }
        Task t = q.pop();
        cout << "  [" << qName << "] Dequeued: " << t.taskID
             << "  Zone=" << t.zoneID
             << "  Type=" << t.taskType << "\n";
        return t;
    }

    void display() const {
        cout << "\n[" << qName << "] FIFO Queue  (" << q.size() << " tasks):\n";
        for (int i = 0; i < q.size(); i++) {
            const Task& t = q.at(i);
            cout << "  [" << i+1 << "]  " << left << setw(12) << t.taskID
                 << "  Zone=" << t.zoneID
                 << "  Type=" << setw(14) << t.taskType
                 << "  Val="  << t.value
                 << "  Pri="  << t.priority << "\n";
        }
        if (q.empty()) cout << "  (empty)\n";
    }

    bool empty() const { return q.empty(); }
    int  count() const { return q.size(); }
};

static const int MAX_HEAP = 150; 

class EmergencyQueue {
    Task heap[MAX_HEAP]; 
    int  heapSz;

    
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent].priority > heap[i].priority) {
                Task tmp = heap[parent]; heap[parent] = heap[i]; heap[i] = tmp;
                i = parent;
            } else break;
        }
    }

    
    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int l = 2*i+1, r = 2*i+2;
            if (l < heapSz && heap[l].priority < heap[smallest].priority) smallest = l;
            if (r < heapSz && heap[r].priority < heap[smallest].priority) smallest = r;
            if (smallest != i) {
                Task tmp = heap[smallest]; heap[smallest] = heap[i]; heap[i] = tmp;
                i = smallest;
            } else break;
        }
    }

public:
    string qName;

    EmergencyQueue(const string& n) : heapSz(0), qName(n) {}

    
    void enqueue(const Task& t) {
        if (heapSz == MAX_HEAP) {
            cout << "  [" << qName << "] Heap FULL!\n"; return;
        }
        heap[heapSz++] = t;
        heapifyUp(heapSz - 1);
        cout << "  [" << qName << "] EMERGENCY enqueued: " << t.taskID
             << "  Zone=" << t.zoneID
             << "  Priority=" << t.priority << "\n";
    }

    
    Task dequeue() {
        if (heapSz == 0) { return Task(); }
        Task top = heap[0];
        heap[0] = heap[--heapSz];
        heapifyDown(0);
        cout << "  [" << qName << "] EMERGENCY dequeued: " << top.taskID
             << "  Zone=" << top.zoneID
             << "  Priority=" << top.priority << "\n";
        return top;
    }

    void display() const {
        cout << "\n[" << qName << "] Emergency Priority Queue  (" << heapSz << " tasks):\n";
        
        Task tmp[MAX_HEAP];
        int  tmpSz = heapSz;
        for (int i = 0; i < heapSz; i++) tmp[i] = heap[i];
        for (int i = 0; i < tmpSz - 1; i++)
            for (int j = 0; j < tmpSz - i - 1; j++)
                if (tmp[j].priority > tmp[j+1].priority) {
                    Task t = tmp[j]; tmp[j] = tmp[j+1]; tmp[j+1] = t;
                }
        for (int i = 0; i < tmpSz; i++)
            cout << "  [" << i+1 << "]  " << left << setw(12) << tmp[i].taskID
                 << "  Zone=" << tmp[i].zoneID
                 << "  Pri="  << tmp[i].priority
                 << "  Val="  << tmp[i].value << "\n";
        if (heapSz == 0) cout << "  (empty)\n";
    }

    bool empty() const { return heapSz == 0; }
    int  count() const { return heapSz; }
};

static const int MAX_TREE_CHILDREN = 15; 

struct TreeNode {
    string            name;
    double            riskScore;
    TreeNode*         children[MAX_TREE_CHILDREN];
    int               numChildren;

    TreeNode(const string& n, double r = 0.0)
        : name(n), riskScore(r), numChildren(0) {
        for (int i = 0; i < MAX_TREE_CHILDREN; i++) children[i] = nullptr;
    }
    ~TreeNode() {
        for (int i = 0; i < numChildren; i++) delete children[i];
    }
};

class ForestDecisionTree {
public:
    TreeNode* root;
    string    treeName;

    ForestDecisionTree(const string& n, const string& rootLabel, double rootRisk = 0.0)
        : treeName(n) {
        root = new TreeNode(rootLabel, rootRisk);
    }

    
    TreeNode* addChild(TreeNode* parent, const string& label, double risk = 0.0) {
        TreeNode* child = new TreeNode(label, risk);
        if (parent->numChildren < MAX_TREE_CHILDREN)
            parent->children[parent->numChildren++] = child;
        else
            cout << "  [Tree] WARNING: MAX_TREE_CHILDREN exceeded for " << parent->name << "\n";
        return child;
    }

    
    void traverse(const TreeNode* node, int depth = 0) const {
        if (!node) return;
        cout << string(depth * 3, ' ') << "|-- "
             << node->name
             << "  (risk=" << fixed << setprecision(2) << node->riskScore << ")\n";
        for (int i = 0; i < node->numChildren; i++)
            traverse(node->children[i], depth + 1);
    }

    
    bool evaluateDecision(double fire, double smoke, double temp,
                          double w1=0.4, double w2=0.3, double w3=0.3,
                          double threshold=0.6) const {
        double score = w1*fire + w2*smoke + w3*temp;
        cout << "  Score = " << w1 << "*" << fire
             << " + " << w2 << "*" << smoke
             << " + " << w3 << "*" << temp
             << " = " << fixed << setprecision(3) << score
             << "  |  threshold=" << threshold
             << "  =>  " << (score > threshold ? "EMERGENCY ACTIVATED" : "Normal")
             << "\n";
        return score > threshold;
    }

    void display() const {
        cout << "\n[" << treeName << "]:\n";
        traverse(root);
    }

    ~ForestDecisionTree() { delete root; }
};

static const int MAX_EDGES_PER_V = 20; 

class AdjListGraph {
public:
    int  V;
    Edge adj[MAX_ZONES][MAX_EDGES_PER_V]; 
    int  adjSize[MAX_ZONES];              

    AdjListGraph(int v) : V(v) {
        for (int i = 0; i < v; i++) adjSize[i] = 0;
    }

    
    void addEdge(int u, int v, double cost = 1.0) {
        if (adjSize[u] < MAX_EDGES_PER_V) { adj[u][adjSize[u]].dest = v; adj[u][adjSize[u]++].cost = cost; }
        if (adjSize[v] < MAX_EDGES_PER_V) { adj[v][adjSize[v]].dest = u; adj[v][adjSize[v]++].cost = cost; }
    }

    
    void BFS(int src) const {
        bool visited[MAX_ZONES] = {};
        MyQueue<int, MAX_ZONES * 2> bfsQ; 
        visited[src] = true;
        bfsQ.push(src);
        int level = 0;

        cout << "  [G1-BFS] Fire spread from Zone" << src << ":\n";
        while (!bfsQ.empty()) {
            int sz = bfsQ.size();
            cout << "    Level " << level++ << ": ";
            while (sz--) {
                int u = bfsQ.pop();
                cout << "Zone" << u << " ";
                for (int j = 0; j < adjSize[u]; j++) {
                    int v = adj[u][j].dest;
                    if (!visited[v]) {
                        visited[v] = true;
                        bfsQ.push(v);
                    }
                }
            }
            cout << "\n";
        }
    }

    
    void dfsHelper(int u, bool visited[], int depth) const {
        visited[u] = true;
        cout << string(depth * 2, ' ') << "-> Zone" << u;
        if (depth > 0) cout << "  [depth=" << depth << "]";
        cout << "\n";
        for (int j = 0; j < adjSize[u]; j++) {
            int v = adj[u][j].dest;
            if (!visited[v])
                dfsHelper(v, visited, depth + 1);
        }
    }

    void runDFS(int src) const {
        bool visited[MAX_ZONES] = {};
        cout << "  [G1-DFS] Path exploration from Zone" << src << ":\n";
        dfsHelper(src, visited, 0);
    }

    
    void updateFireCost(int zone, double fireLevel) {
        cout << "  [G1] Fire-aware update: Zone" << zone
             << "  fireLevel=" << fireLevel << "\n";
        for (int j = 0; j < adjSize[zone]; j++) {
            double newCost = adj[zone][j].cost * (1.0 + fireLevel);
            cout << "    Edge Zone" << zone << "-Zone" << adj[zone][j].dest
                 << ":  " << fixed << setprecision(1)
                 << adj[zone][j].cost << " -> " << newCost << "\n";
            adj[zone][j].cost = newCost;
        }
    }

    void display() const {
        cout << "\n[G1] Adjacency List Graph  (" << V << " zones):\n";
        for (int i = 0; i < V; i++) {
            cout << "  Zone" << i << " : ";
            for (int j = 0; j < adjSize[i]; j++)
                cout << "Zone" << adj[i][j].dest
                     << "(c=" << fixed << setprecision(1) << adj[i][j].cost << ")  ";
            cout << "\n";
        }
    }
};

class AdjMatrixGraph {
public:
    int    V;
    double mat[MAX_ZONES][MAX_ZONES]; 

    AdjMatrixGraph(int v) : V(v) {
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                mat[i][j] = 0.0;
    }

    
    void addEdge(int u, int v, double cost = 1.0) {
        mat[u][v] = cost;
        mat[v][u] = cost;
    }

    
    void BFS(int src) const {
        bool visited[MAX_ZONES] = {};
        MyQueue<int, MAX_ZONES * 2> bfsQ; 
        visited[src] = true;
        bfsQ.push(src);
        cout << "  [G2-BFS] from Zone" << src << ": ";
        while (!bfsQ.empty()) {
            int u = bfsQ.pop();
            cout << "Zone" << u << " ";
            for (int v = 0; v < V; v++)
                if (mat[u][v] > 0 && !visited[v]) {
                    visited[v] = true;
                    bfsQ.push(v);
                }
        }
        cout << "\n";
    }

    void display() const {
        cout << "\n[G2] Adjacency Matrix  (" << V << "x" << V << "):\n  ";
        for (int i = 0; i < V; i++) cout << setw(5) << "Z" + to_string(i);
        cout << "\n";
        for (int i = 0; i < V; i++) {
            cout << "Z" << i << " ";
            for (int j = 0; j < V; j++)
                cout << setw(5) << fixed << setprecision(1) << mat[i][j];
            cout << "\n";
        }
    }
};

struct HashEntry {
    int    key;      
    double temp;
    double smoke;
    double humidity;
    bool   occupied;
    bool   deleted;  

    HashEntry()
        : key(-1), temp(0), smoke(0), humidity(0),
          occupied(false), deleted(false) {}
};

class PrimaryHashTable {
public:
    HashEntry table[HASH_SIZE];
    string    tableName;
    int       count;

    PrimaryHashTable(const string& n) : tableName(n), count(0) {}

    
    int hashFunc(int key) const { return key % HASH_SIZE; }

    
    void insert(int zoneID, double t, double s, double h) {
        int idx   = hashFunc(zoneID);
        int start = idx;
        
        while (table[idx].occupied && !table[idx].deleted) {
            if (table[idx].key == zoneID) break; 
            idx = (idx + 1) % HASH_SIZE;
            if (idx == start) { cout << "  [" << tableName << "] Table full!\n"; return; }
        }
        table[idx].key = zoneID; table[idx].temp = t; table[idx].smoke = s;
        table[idx].humidity = h; table[idx].occupied = true; table[idx].deleted = false;
        count++;
        cout << "  [" << tableName << "] Inserted Zone" << zoneID
             << "  at index=" << idx
             << "  (hash=" << hashFunc(zoneID) << ")\n";
    }

    
    HashEntry* search(int zoneID) {
        int idx   = hashFunc(zoneID);
        int start = idx;
        while (table[idx].occupied || table[idx].deleted) {
            if (table[idx].occupied && table[idx].key == zoneID)
                return &table[idx];
            idx = (idx + 1) % HASH_SIZE;
            if (idx == start) break;
        }
        return nullptr;
    }

    void display() const {
        cout << "\n[" << tableName << "] Primary Hash Table  (size=" << HASH_SIZE << "):\n";
        cout << left << setw(9)  << "Index"
                     << setw(8)  << "Zone"
                     << setw(10) << "Temp"
                     << setw(10) << "Smoke"
                     << "Humidity\n";
        cout << string(47, '-') << "\n";
        for (int i = 0; i < HASH_SIZE; i++) {
            cout << setw(9) << i;
            if (table[i].occupied)
                cout << setw(8)  << table[i].key
                     << setw(10) << table[i].temp
                     << setw(10) << table[i].smoke
                     << table[i].humidity;
            else
                cout << "---";
            cout << "\n";
        }
    }
};

struct ChainNode {
    HashEntry entry;
    ChainNode* next;
    ChainNode(const HashEntry& e) : entry(e), next(nullptr) {}
};

class ChainHashTable {
public:
    ChainNode* buckets[HASH_SIZE];
    string     tableName;

    ChainHashTable(const string& n) : tableName(n) {
        for (int i = 0; i < HASH_SIZE; i++) buckets[i] = nullptr;
    }

    int hashFunc(int key) const { return key % HASH_SIZE; }

    
    void insert(int zoneID, double t, double s, double h) {
        int idx = hashFunc(zoneID);
        HashEntry e;
        e.key = zoneID; e.temp = t; e.smoke = s;
        e.humidity = h; e.occupied = true;
        ChainNode* node = new ChainNode(e);
        node->next   = buckets[idx];
        buckets[idx] = node;
        cout << "  [" << tableName << "] Chained Zone" << zoneID
             << " at bucket[" << idx << "]\n";
    }

    void display() const {
        cout << "\n[" << tableName << "] Chaining Hash Table:\n";
        for (int i = 0; i < HASH_SIZE; i++) {
            cout << "  Bucket[" << i << "]: ";
            ChainNode* cur = buckets[i];
            if (!cur) { cout << "empty\n"; continue; }
            while (cur) {
                cout << "[Z" << cur->entry.key
                     << "|T=" << cur->entry.temp << "] -> ";
                cur = cur->next;
            }
            cout << "NULL\n";
        }
    }

    ~ChainHashTable() {
        for (int i = 0; i < HASH_SIZE; i++) {
            ChainNode* cur = buckets[i];
            while (cur) { ChainNode* t = cur->next; delete cur; cur = t; }
        }
    }
};

class FastCache {
public:
    HashEntry cache[HASH_SIZE];
    int       accessTick[HASH_SIZE]; 
    int       globalTick;
    string    cacheName;

    FastCache(const string& n) : globalTick(0), cacheName(n) {
        
        for (int i = 0; i < HASH_SIZE; i++) accessTick[i] = 0;
    }

    int hashFunc(int key) const { return key % HASH_SIZE; }

    
    void put(int zoneID, double t, double s, double h) {
        int idx = hashFunc(zoneID);
        cache[idx].key = zoneID; cache[idx].temp = t; cache[idx].smoke = s;
        cache[idx].humidity = h; cache[idx].occupied = true; cache[idx].deleted = false;
        accessTick[idx] = ++globalTick;
        cout << "  [" << cacheName << "] Cached Zone" << zoneID
             << " at slot[" << idx << "]\n";
    }

    
    HashEntry* get(int zoneID) {
        int idx = hashFunc(zoneID);
        if (cache[idx].occupied && cache[idx].key == zoneID) {
            accessTick[idx] = ++globalTick;
            cout << "  [" << cacheName << "] Cache HIT  Zone" << zoneID << "\n";
            return &cache[idx];
        }
        cout << "  [" << cacheName << "] Cache MISS Zone" << zoneID << "\n";
        return nullptr;
    }

    void display() const {
        cout << "\n[" << cacheName << "] Fast Retrieval Cache:\n";
        bool any = false;
        for (int i = 0; i < HASH_SIZE; i++) {
            if (cache[i].occupied) {
                cout << "  Slot[" << i << "]  Zone=" << cache[i].key
                     << "  T=" << cache[i].temp
                     << "  S=" << cache[i].smoke
                     << "  H=" << cache[i].humidity
                     << "  last_tick=" << accessTick[i] << "\n";
                any = true;
            }
        }
        if (!any) cout << "  (empty)\n";
    }
};

struct SystemMonitor {
    double latency[6]; 
    double load[6];    
    string modules[6] = { "Arrays", "LinkedLists",
                           "Queues", "Trees",
                           "Graphs", "HashTables" };

    
    void update(int mod, double lat, double ld) {
        if (mod < 0 || mod > 5) return;
        latency[mod] = lat;
        load[mod]    = ld;
    }

    
    void display() const {
        cout << "\n[SYSTEM MONITOR] Real-time Performance Metrics:\n";
        cout << left  << setw(14) << "Module"
                      << setw(14) << "Latency(ms)"
                      << setw(12) << "Load(%)"
                      << "Status\n";
        cout << string(52, '-') << "\n";
        for (int i = 0; i < 6; i++) {
            string status = "Normal";
            if (latency[i] > 8.0  || load[i] > 80.0) status = "WARNING";
            if (latency[i] > 15.0 || load[i] > 95.0) status = "CRITICAL";
            cout << left  << setw(14) << modules[i]
                          << setw(14) << fixed << setprecision(1) << latency[i]
                          << setw(12) << load[i]
                          << status << "\n";
        }
    }
};

struct ExecutionStep {
    int    stepID;
    string stepName;    
    int    zoneID;
    double valueBefore; 
    double valueAfter;  
    double expected;    
    bool   isValid;     
    string action;      

    ExecutionStep(int id=0, string nm="", int z=0,
                  double vb=0, double va=0, double exp=0,
                  bool valid=true, string act="read")
        : stepID(id), stepName(nm), zoneID(z),
          valueBefore(vb), valueAfter(va), expected(exp),
          isValid(valid), action(act) {}
};

struct SystemSnapshot {
    double temperature[MAX_ZONES];
    double humidity[MAX_ZONES];
    double smokeLevel[MAX_ZONES];
    int    fireSignal[MAX_ZONES];
    string label;       
    int    snapTick;    

    SystemSnapshot() : label(""), snapTick(0) {
        
        for (int i = 0; i < MAX_ZONES; i++) temperature[i] = 0.0;
        for (int i = 0; i < MAX_ZONES; i++) humidity[i]    = 0.0;
        for (int i = 0; i < MAX_ZONES; i++) smokeLevel[i]  = 0.0;
        for (int i = 0; i < MAX_ZONES; i++) fireSignal[i]  = 0;
    }
};

class ExecutionControlLayer {
public:
    
    MyStack<SystemSnapshot, 50> checkpointStack;

    
    MyStack<ExecutionStep, 1000> stepLog;

    bool   executionPaused;     
    int    stepCounter;         
    int    inconsistencyCount;  
    string pauseReason;         

    ExecutionControlLayer()
        : executionPaused(false), stepCounter(0),
          inconsistencyCount(0), pauseReason("") {}

    
    
    
    
    
    
    void captureCheckpoint(const DynamicSensorArray& sensorArr,
                           const string& label) {
        SystemSnapshot snap;
        snap.label    = label;
        snap.snapTick = ++stepCounter;
        for (int i = 0; i < MAX_ZONES; i++) {
            snap.temperature[i] = sensorArr.temperature[i];
            snap.humidity[i]    = sensorArr.humidity[i];
            snap.smokeLevel[i]  = sensorArr.smokeLevel[i];
            snap.fireSignal[i]  = sensorArr.fireSignal[i];
        }
        checkpointStack.push(snap);
        cout << "  [ECL] Checkpoint captured: \"" << label
             << "\"  (stack depth=" << checkpointStack.size() << ")\n";
    }

    
    
    
    
    
    
    bool rollback(DynamicSensorArray& sensorArr) {
        if (checkpointStack.empty()) {
            cout << "  [ECL] ROLLBACK FAILED: no checkpoints available.\n";
            return false;
        }
        SystemSnapshot& snap = checkpointStack.peek();
        cout << "  [ECL] Rolling back to: \"" << snap.label
             << "\"  (tick=" << snap.snapTick << ")\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            sensorArr.temperature[i] = snap.temperature[i];
            sensorArr.humidity[i]    = snap.humidity[i];
            sensorArr.smokeLevel[i]  = snap.smokeLevel[i];
            sensorArr.fireSignal[i]  = snap.fireSignal[i];
        }
        checkpointStack.pop();
        
        recordStep("ROLLBACK-RESTORE", -1, 0, 0, 0, true, "rollback");
        executionPaused = false;
        pauseReason     = "";
        cout << "  [ECL] State restored. Execution resumed.\n";
        return true;
    }

    
    
    
    
    
    
    void recordStep(const string& name, int zone,
                    double vBefore, double vAfter,
                    double expected, bool valid,
                    const string& action="read") {
        stepCounter++;
        ExecutionStep s(stepCounter, name, zone,
                        vBefore, vAfter, expected, valid, action);
        stepLog.push(s);
        cout << "  [ECL-Step#" << stepCounter << "] "
             << name << "  Zone=" << zone
             << "  Before=" << fixed << setprecision(1) << vBefore
             << "  After="  << vAfter
             << "  Expect=" << expected
             << "  " << (valid ? "OK" : "*** MISMATCH ***") << "\n";
    }

    
    
    
    
    
    
    
    bool checkConsistency(int zone, double actual,
                          double expected, double tolerance = 15.0) {
        
        if (actual < 0.0 || actual > 200.0) {
            cout << "  [ECL] PHYSICAL LIMIT VIOLATION: Zone" << zone
                 << " value=" << actual << " (outside 0-200 range)\n";
            inconsistencyCount++;
            return false;
        }
        
        if (fabs(actual - expected) > tolerance) {
            cout << "  [ECL] INCONSISTENCY: Zone" << zone
                 << "  actual=" << actual
                 << "  expected=" << expected
                 << "  delta=" << fabs(actual - expected)
                 << " > tolerance=" << tolerance << "\n";
            inconsistencyCount++;
            return false;
        }
        return true;
    }

    
    
    
    
    
    
    void pauseExecution(const string& reason) {
        executionPaused = true;
        pauseReason     = reason;
        cout << "  [ECL] *** EXECUTION PAUSED ***\n";
        cout << "  [ECL] Reason: " << reason << "\n";
        cout << "  [ECL] Last verified state preserved in checkpoint stack.\n";
    }

    
    
    
    
    
    void resumeExecution() {
        executionPaused = false;
        pauseReason     = "";
        cout << "  [ECL] Execution RESUMED from verified stable state.\n";
    }

    
    
    
    
    
    
    
    
    
    void runAlternativePath(DynamicSensorArray& sensorArr,
                            int zone, double safeValue) {
        cout << "  [ECL] Alternative Path: Zone" << zone
             << " replacing faulty=" << sensorArr.temperature[zone]
             << " with interpolated=" << safeValue << "\n";
        double old = sensorArr.temperature[zone];
        sensorArr.temperature[zone] = safeValue;
        sensorArr.fireSignal[zone]  =
            (safeValue > TEMP_THRESHOLD) ? 1 : 0;
        recordStep("ALT_PATH_REPLACE", zone,
                   old, safeValue, safeValue, true, "alt_path");
        cout << "  [ECL] Zone" << zone
             << " is now operating on interpolated safe value.\n";
    }

    
    
    
    
    
    
    void displayStepLog() const {
        cout << "\n[ECL] Execution Step Log  (" << stepLog.size()
             << " recorded steps, newest first):\n";
        cout << left << setw(8)  << "StepID"
                     << setw(26) << "Name"
                     << setw(7)  << "Zone"
                     << setw(10) << "Before"
                     << setw(10) << "After"
                     << setw(10) << "Expected"
                     << "Status\n";
        cout << string(76, '-') << "\n";
        
        for (int i = stepLog.size() - 1; i >= 0; i--) {
            const ExecutionStep& s = stepLog.at(i);
            cout << left << setw(8)  << s.stepID
                         << setw(26) << s.stepName
                         << setw(7)  << s.zoneID
                         << setw(10) << fixed << setprecision(1) << s.valueBefore
                         << setw(10) << s.valueAfter
                         << setw(10) << s.expected
                         << (s.isValid ? "OK" : "MISMATCH") << "\n";
        }
        if (stepLog.empty()) cout << "  (no steps recorded)\n";
    }

    
    
    
    
    
    void displayCheckpoints() const {
        cout << "\n[ECL] Rollback Checkpoint Stack  (depth="
             << checkpointStack.size() << "):\n";
        if (checkpointStack.empty()) {
            cout << "  (no checkpoints stored)\n";
            return;
        }
        
        for (int i = checkpointStack.size() - 1; i >= 0; i--) {
            const SystemSnapshot& s = checkpointStack.at(i);
            int pos = i + 1;
            cout << "  [" << pos << "] \""  << s.label
                 << "\"  tick=" << s.snapTick << "\n";
            cout << "       Sample Zone0: T="  << s.temperature[0]
                 << "  Zone4: T=" << s.temperature[4]
                 << "  Zone9: T=" << s.temperature[9] << "\n";
        }
    }

    
    void displayStatus() const {
        cout << "\n[ECL] Execution Control Status:\n";
        cout << "  Total steps logged   : " << stepLog.size() << "\n";
        cout << "  Checkpoints stored   : " << checkpointStack.size() << "\n";
        cout << "  Inconsistencies found: " << inconsistencyCount << "\n";
        cout << "  Execution paused     : " << (executionPaused ? "YES" : "no") << "\n";
        if (executionPaused)
            cout << "  Pause reason         : " << pauseReason << "\n";
    }
};

class DynamicScheduler {
public:
    int rebalanceCount;     
    int priorityUpgrades;   

    DynamicScheduler() : rebalanceCount(0), priorityUpgrades(0) {}

    
    
    
    
    
    
    
    
    
    
    void adjustPriorities(DynamicSensorArray& sensorArr,
                          ForestQueue& q1, EmergencyQueue& q3) {
        cout << "\n  [DSCH] Scanning Q1 for priority upgrades...\n";
        
        Task retained[MAX_FQUEUE], upgraded[MAX_FQUEUE];
        int  retainedCnt = 0,      upgradedCnt = 0;
        while (!q1.empty()) {
            Task t = q1.q.pop(); 
            int z = t.zoneID;
            if (z >= 0 && z < MAX_ZONES && sensorArr.fireSignal[z]) {
                t.priority  = 1;
                t.taskType  = "emergency_upg";
                if (upgradedCnt < MAX_FQUEUE) upgraded[upgradedCnt++] = t;
                priorityUpgrades++;
                cout << "    [DSCH] Task " << t.taskID
                     << " Zone=" << z << " UPGRADED -> Q3\n";
            } else {
                if (retainedCnt < MAX_FQUEUE) retained[retainedCnt++] = t;
            }
        }
        
        for (int i = 0; i < retainedCnt; i++) q1.q.push(retained[i]);
        
        for (int i = 0; i < upgradedCnt; i++) q3.enqueue(upgraded[i]);
        cout << "  [DSCH] Priority adjustment done: "
             << upgradedCnt << " upgraded, "
             << retainedCnt << " retained.\n";
    }

    
    
    
    
    
    
    
    void rebalanceQueues(ForestQueue& q1, ForestQueue& q2) {
        int c1 = q1.count(), c2 = q2.count();
        cout << "\n  [DSCH] Rebalancing: Q1=" << c1
             << " tasks  Q2=" << c2 << " tasks\n";
        if (c1 <= 2 * c2 + 1) {
            cout << "  [DSCH] Load is balanced, no action needed.\n";
            return;
        }
        int move = (c1 - c2) / 2;
        cout << "  [DSCH] Moving " << move << " tasks from Q1 to Q2:\n";
        for (int i = 0; i < move; i++) {
            Task t = q1.q.pop(); 
            t.taskType = "surveillance_rebal";
            q2.q.push(t);       
            cout << "    Moved: " << t.taskID
                 << " Zone=" << t.zoneID << "\n";
        }
        rebalanceCount++;
        cout << "  [DSCH] Post-balance: Q1=" << q1.count()
             << "  Q2=" << q2.count() << "\n";
    }

    
    
    
    
    
    
    
    void loadBalanceReport(const ForestQueue& q1,
                           const ForestQueue& q2,
                           const EmergencyQueue& q3,
                           const ForestQueue& q4) const {
        cout << "\n[DSCH] Load Balance Report:\n";
        cout << left << setw(30) << "Queue"
                     << setw(10) << "Tasks"
                     << setw(12) << "Util(%)"
                     << "Status\n";
        cout << string(58, '-') << "\n";
        auto row = [&](const string& name, int cnt) {
            double util = (cnt / 20.0) * 100.0;
            string st = util < 50 ? "Light" : (util < 80 ? "Moderate" : "OVERLOADED");
            cout << left << setw(30) << name
                         << setw(10) << cnt
                         << setw(12) << fixed << setprecision(1) << util
                         << st << "\n";
        };
        row("Q1-RoutineMonitoring",  q1.count());
        row("Q2-Surveillance",       q2.count());
        row("Q3-EmergencyResponse",  q3.count());
        row("Q4-MultiFactorDecision",q4.count());
        cout << "  Rebalance operations done: " << rebalanceCount << "\n";
        cout << "  Priority upgrades done   : " << priorityUpgrades << "\n";
    }
};

class AdaptiveMonitor {
public:
    
    double warnLatLimit[6];
    double critLatLimit[6];
    double warnLoadLimit[6];
    
    static const int MAX_TUNE_HIST = 100;
    string tuneHistory[MAX_TUNE_HIST];
    int    histSize;

    AdaptiveMonitor() : histSize(0) {
        
        for (int i = 0; i < 6; i++) {
            warnLatLimit[i]  = 8.0;
            critLatLimit[i]  = 15.0;
            warnLoadLimit[i] = 80.0;
        }
    }

    
    
    
    
    
    
    
    int detectBottleneck(const SystemMonitor& sys) const {
        int    worstIdx   = 0;
        double worstScore = 0.0;
        string names[6] = {"Arrays","LinkedLists","Queues",
                            "Trees","Graphs","HashTables"};
        cout << "\n  [AMON] Bottleneck Analysis:\n";
        for (int i = 0; i < 6; i++) {
            double score = (sys.latency[i] / critLatLimit[i])
                         + (sys.load[i] / 100.0);
            cout << "    " << left << setw(14) << names[i]
                 << "  stress_score=" << fixed << setprecision(3) << score << "\n";
            if (score > worstScore) { worstScore = score; worstIdx = i; }
        }
        cout << "  [AMON] Bottleneck identified: "
             << names[worstIdx]
             << "  (score=" << fixed << setprecision(3) << worstScore << ")\n";
        return worstIdx;
    }

    
    
    
    
    
    
    
    void redistributeLoad(SystemMonitor& sys, int bottleneckIdx) {
        string names[6] = {"Arrays","LinkedLists","Queues",
                            "Trees","Graphs","HashTables"};
        cout << "\n  [AMON] Redistributing load from "
             << names[bottleneckIdx] << "...\n";
        double offload = sys.load[bottleneckIdx] * 0.15;

        
        int   targets[2] = {-1, -1};
        double minLoad[2] = {200.0, 200.0};
        for (int i = 0; i < 6; i++) {
            if (i == bottleneckIdx) continue;
            if (sys.load[i] < minLoad[0]) {
                minLoad[1] = minLoad[0]; targets[1] = targets[0];
                minLoad[0] = sys.load[i]; targets[0] = i;
            } else if (sys.load[i] < minLoad[1]) {
                minLoad[1] = sys.load[i]; targets[1] = i;
            }
        }
        
        sys.load[bottleneckIdx] -= offload;
        sys.latency[bottleneckIdx] *= 0.85;
        for (int k = 0; k < 2 && targets[k] != -1; k++) {
            sys.load[targets[k]] += offload / 2.0;
        }
        cout << "  [AMON] " << names[bottleneckIdx]
             << " load: " << fixed << setprecision(1)
             << sys.load[bottleneckIdx] + offload
             << "% -> " << sys.load[bottleneckIdx] << "%\n";
        string entry = "Redistributed " + to_string((int)offload)
                     + "% from " + names[bottleneckIdx];
        if (histSize < MAX_TUNE_HIST) tuneHistory[histSize++] = entry;
    }

    
    
    
    
    
    
    
    
    
    void tuneThresholds(const SystemMonitor& sys) {
        string names[6] = {"Arrays","LinkedLists","Queues",
                            "Trees","Graphs","HashTables"};
        cout << "\n  [AMON] Dynamic Threshold Tuning:\n";
        for (int i = 0; i < 6; i++) {
            double oldLim = warnLatLimit[i];
            if (sys.load[i] > 90.0) {
                warnLatLimit[i] += 2.0;
                critLatLimit[i] += 2.0;
                cout << "    " << setw(14) << names[i]
                     << "  load=" << sys.load[i]
                     << "%  =>  warnLat: " << oldLim
                     << " -> " << warnLatLimit[i]
                     << " ms  [RELAXED due to high load]\n";
                if (histSize < MAX_TUNE_HIST)
                    tuneHistory[histSize++] = "Relaxed " + names[i]
                        + " threshold to " + to_string((int)warnLatLimit[i]) + "ms";
            } else if (sys.load[i] < 30.0) {
                
                warnLatLimit[i] = (warnLatLimit[i] - 1.0 > 3.0) ? warnLatLimit[i] - 1.0 : 3.0;
                cout << "    " << setw(14) << names[i]
                     << "  load=" << sys.load[i]
                     << "%  =>  warnLat: " << oldLim
                     << " -> " << warnLatLimit[i]
                     << " ms  [TIGHTENED for sensitivity]\n";
                if (histSize < MAX_TUNE_HIST)
                    tuneHistory[histSize++] = "Tightened " + names[i]
                        + " threshold to " + to_string((int)warnLatLimit[i]) + "ms";
            } else {
                cout << "    " << setw(14) << names[i]
                     << "  load=" << sys.load[i]
                     << "%  =>  threshold unchanged (" << oldLim << " ms)\n";
            }
        }
    }

    
    
    
    
    
    
    
    void generateFullReport(const SystemMonitor& sys) const {
        string names[6] = {"Arrays","LinkedLists","Queues",
                            "Trees","Graphs","HashTables"};
        cout << "\n[AMON] === Adaptive Monitor Full Report ===\n";
        cout << left << setw(14) << "Module"
                     << setw(13) << "Lat(ms)"
                     << setw(10) << "Load(%)"
                     << setw(14) << "WarnLat(ms)"
                     << setw(14) << "CritLat(ms)"
                     << "Status\n";
        cout << string(72, '-') << "\n";
        for (int i = 0; i < 6; i++) {
            string status = "NORMAL";
            if (sys.latency[i] > critLatLimit[i] ||
                sys.load[i]    > 95.0)   status = "CRITICAL";
            else if (sys.latency[i] > warnLatLimit[i] ||
                     sys.load[i]    > warnLoadLimit[i]) status = "WARNING";
            cout << left << setw(14) << names[i]
                         << setw(13) << fixed << setprecision(1) << sys.latency[i]
                         << setw(10) << sys.load[i]
                         << setw(14) << warnLatLimit[i]
                         << setw(14) << critLatLimit[i]
                         << status << "\n";
        }
        cout << "\n  [AMON] Tuning History (" << histSize
             << " adjustments):\n";
        if (histSize == 0) {
            cout << "    No adjustments made yet.\n";
        } else {
            for (int i = 0; i < histSize; i++)
                cout << "    [" << i+1 << "] " << tuneHistory[i] << "\n";
        }
    }
};

StaticBaseline       A1;
DynamicSensorArray   A2;
StaticGridMatrix     A3;
DynamicTerrainMatrix A4;

SinglyLinkedList L1("L1-RawEventStream"),
                 L2("L2-VerifiedStream"),
                 L3("L3-AnomalyStream");

DoublyLinkedList L4("L4-ForwardCorrection"),
                 L5("L5-BackwardCorrection"),
                 L6("L6-StateSync");

CircularLinkedList L7("L7-LocalMonitor"),
                   L8("L8-SystemWideMonitor"),
                   L9("L9-EmergencyMonitor"),
                   L10("L10-StabilityMonitor");

ForestQueue    Q1("Q1-RoutineMonitoring"),
               Q2("Q2-Surveillance"),
               Q4("Q4-MultiFactorDecision");
EmergencyQueue Q3("Q3-EmergencyResponse");

ForestDecisionTree* T[13]; 

AdjListGraph   G1(MAX_ZONES);
AdjMatrixGraph G2(MAX_ZONES);

PrimaryHashTable H1("H1-Primary");
ChainHashTable   H2("H2-Chaining");
FastCache        H3("H3-FastCache");

SystemMonitor SYS;

ExecutionControlLayer ECL;

DynamicScheduler DSCH;

AdaptiveMonitor AMON;

void buildTrees() {
    
    T[1] = new ForestDecisionTree("T1-ZoneHierarchy", "Forest", 0.0);
    auto* zA = T[1]->addChild(T[1]->root, "Zone-A", 0.30);
    auto* zA1= T[1]->addChild(zA,  "Zone-A1",   0.40);
               T[1]->addChild(zA1, "Zone-A1-1",  0.50);
    auto* zB = T[1]->addChild(T[1]->root, "Zone-B", 0.60);
               T[1]->addChild(zB,  "Zone-B1",    0.70);
               T[1]->addChild(T[1]->root, "Zone-C", 0.20);

    
    T[2] = new ForestDecisionTree("T2-SubZoneDecomposition", "Zone-A", 0.30);
    T[2]->addChild(T[2]->root, "North-A", 0.40);
    T[2]->addChild(T[2]->root, "South-A", 0.55);
    T[2]->addChild(T[2]->root, "East-A",  0.30);
    T[2]->addChild(T[2]->root, "West-A",  0.65);

    
    T[3] = new ForestDecisionTree("T3-TerrainClassification", "Forest-Terrain", 0.0);
    T[3]->addChild(T[3]->root, "High-Risk  (slope=0.8, dry=0.9, density=0.7)", 0.80);
    T[3]->addChild(T[3]->root, "Medium-Risk(slope=0.5, dry=0.5, density=0.5)", 0.50);
    T[3]->addChild(T[3]->root, "Low-Risk   (slope=0.2, dry=0.2, density=0.3)", 0.23);

    
    T[4] = new ForestDecisionTree("T4-WaterResource", "Water-Sources", 0.0);
    T[4]->addChild(T[4]->root, "River-A  avail=80L  ratio=0.80", 0.80);
    T[4]->addChild(T[4]->root, "Lake-B   avail=60L  ratio=0.60", 0.60);
    T[4]->addChild(T[4]->root, "Tank-C   avail=40L  ratio=0.40", 0.40);

    
    T[5] = new ForestDecisionTree("T5-FireControlResources", "Fire-Resources", 0.0);
    T[5]->addChild(T[5]->root, "Helicopter-1  (aerial water drop)", 0.90);
    T[5]->addChild(T[5]->root, "FireTruck-2   (ground suppression)", 0.70);
    T[5]->addChild(T[5]->root, "ManualCrew-3  (controlled burn)", 0.50);

    
    T[6] = new ForestDecisionTree("T6-EquipmentAllocation", "Allocations", 0.0);
    auto* hi = T[6]->addChild(T[6]->root, "High-Priority  (Risk*Impact=0.72)", 0.72);
               T[6]->addChild(hi, "Deploy Helicopter", 0.90);
    auto* md = T[6]->addChild(T[6]->root, "Medium-Priority(Risk*Impact=0.45)", 0.45);
               T[6]->addChild(md, "Deploy FireTruck",  0.60);
               T[6]->addChild(T[6]->root, "Low-Priority   (Risk*Impact=0.18)", 0.18);

    
    T[7] = new ForestDecisionTree("T7-FireClassification", "Fire-Incidents", 0.0);
    T[7]->addChild(T[7]->root, "Major Fire  T>60 & S>80   alpha*T+beta*S>0.8", 0.95);
    T[7]->addChild(T[7]->root, "Minor Fire  T>45 & S>50   score>0.6",          0.65);
    T[7]->addChild(T[7]->root, "Smoke Alert S>30           score>0.3",          0.35);
    T[7]->addChild(T[7]->root, "Normal      S<=30 & T<=45",                     0.05);

    
    T[8] = new ForestDecisionTree("T8-WildlifeActivity", "Wildlife-Monitor", 0.0);
    T[8]->addChild(T[8]->root, "Large-Animal Movement", 0.30);
    T[8]->addChild(T[8]->root, "Migration Pattern",     0.40);
    T[8]->addChild(T[8]->root, "Unusual Movement",      0.75);

    
    T[9] = new ForestDecisionTree("T9-HumanActivityDetection", "Human-Monitor", 0.0);
    T[9]->addChild(T[9]->root, "Authorized Personnel",        0.10);
    T[9]->addChild(T[9]->root, "Restricted-Zone Entry",       0.80);
    T[9]->addChild(T[9]->root, "Unknown / Unverified Entity", 0.90);

    
    T[10] = new ForestDecisionTree("T10-LocalDecision", "Local-Zone-Decision", 0.0);
    auto* hr = T[10]->addChild(T[10]->root, "Risk > 0.6", 0.70);
               T[10]->addChild(hr, "Activate Local Response",  0.80);
               T[10]->addChild(hr, "Alert Nearby Units",       0.75);
    auto* lr = T[10]->addChild(T[10]->root, "Risk <= 0.6", 0.30);
               T[10]->addChild(lr, "Continue Monitoring",      0.20);

    
    T[11] = new ForestDecisionTree("T11-RegionalEscalation", "Regional-Control", 0.0);
    auto* sp = T[11]->addChild(T[11]->root, "FireSpreadRate > 0.5", 0.80);
               T[11]->addChild(sp, "Escalate to Neighbouring Zones", 0.90);
               T[11]->addChild(sp, "Increase Monitoring Frequency",  0.75);
               T[11]->addChild(T[11]->root, "FireSpreadRate <= 0.5 => Hold", 0.30);

    
    T[12] = new ForestDecisionTree("T12-GlobalEmergency", "GLOBAL-COMMAND", 0.0);
    auto* ga = T[12]->addChild(T[12]->root, "Sum(RiskZones) > Threshold", 0.95);
               T[12]->addChild(ga, "GLOBAL ALERT - All Units Deploy", 1.00);
               T[12]->addChild(ga, "Evacuate Perimeter",               0.95);
               T[12]->addChild(T[12]->root, "Normal Global Condition",  0.10);
}

void initializeSystem() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "   IFAMDS  -  Intelligent Forest Advisory & Multi-Structure\n";
    cout << "              Decision System  [INITIALIZATION]\n";
    cout << string(62, '=') << "\n";

    
    A1.initialize();
    A2.initialize();
    A3.initialize();
    A4.initialize();
    cout << "  [OK] Array Layer      A1 A2 A3 A4\n";

    
    
    for (int i = 0; i < 6; i++)
        L1.insertBack(ForestEvent(25.0 + i*2.5, i, "t"+to_string(i), "raw"));
    
    for (int i = 0; i < 6; i++)
        L2.insertBack(ForestEvent(25.0 + i*1.0, i, "t"+to_string(i), "verified"));
    
    L3.insertBack(ForestEvent(60.0, 2, "t3", "anomaly"));
    L3.insertBack(ForestEvent(75.0, 4, "t4", "anomaly"));
    
    for (int i = 0; i < 5; i++) {
        L4.insertBack(ForestEvent(25.0 + i,   i, "t"+to_string(i), "fwd_chain"));
        L5.insertBack(ForestEvent(25.0 + i*2, i, "t"+to_string(i), "bwd_chain"));
        L6.insertBack(ForestEvent(25.0 + i,   i, "t"+to_string(i), "sync"));
    }
    
    for (int i = 0; i < 4; i++) {
        L7.insert(ForestEvent(25.0 + i, i, "t"+to_string(i), "local"));
        L8.insert(ForestEvent(27.0 + i, i, "t"+to_string(i), "syswide"));
    }
    L9.insert(ForestEvent(65.0, 2, "emg", "emergency"));
    L9.insert(ForestEvent(80.0, 4, "emg", "emergency"));
    for (int i = 0; i < 3; i++)
        L10.insert(ForestEvent(25.0 + i*0.5, i, "t"+to_string(i), "stable"));
    cout << "  [OK] Linked List Layer  L1-L10\n";

    
    Q1.enqueue(Task("T001", 0, "routine",      25.0, 3));
    Q1.enqueue(Task("T002", 1, "routine",      27.0, 3));
    Q2.enqueue(Task("T003", 3, "surveillance", 30.0, 2));
    Q2.enqueue(Task("T004", 5, "surveillance", 32.0, 2));
    Q3.enqueue(Task("T005", 2, "emergency",    60.0, 1));
    Q3.enqueue(Task("T006", 4, "emergency",    75.0, 1));
    Q4.enqueue(Task("T007", 2, "multi",        45.0, 2));
    Q4.enqueue(Task("T008", 4, "multi",        65.0, 1));
    cout << "  [OK] Queue Layer        Q1 Q2 Q3 Q4\n";

    
    buildTrees();
    cout << "  [OK] Tree Layer         T1-T12\n";

    
    
    G1.addEdge(0,1,3.0); G1.addEdge(0,2,5.0);
    G1.addEdge(1,3,2.0); G1.addEdge(1,4,7.0);
    G1.addEdge(2,4,4.0); G1.addEdge(2,5,6.0);
    G1.addEdge(3,6,3.0); G1.addEdge(4,6,5.0);
    G1.addEdge(5,7,2.0); G1.addEdge(6,8,4.0);
    G1.addEdge(7,8,3.0); G1.addEdge(8,9,2.0);
    
    G2.addEdge(0,1,3.0); G2.addEdge(0,2,5.0);
    G2.addEdge(1,3,2.0); G2.addEdge(2,4,4.0);
    G2.addEdge(3,5,6.0); G2.addEdge(4,5,3.0);
    G2.addEdge(5,6,2.0); G2.addEdge(6,7,4.0);
    cout << "  [OK] Graph Layer        G1 G2\n";

    
    for (int i = 0; i < MAX_ZONES; i++) {
        H1.insert(i, A2.temperature[i], A2.smokeLevel[i], A2.humidity[i]);
        H2.insert(i, A2.temperature[i], A2.smokeLevel[i], A2.humidity[i]);
        H3.put(i,    A2.temperature[i], A2.smokeLevel[i], A2.humidity[i]);
    }
    cout << "  [OK] Hash Layer         H1 H2 H3\n";

    
    double initLat[]  = { 1.2, 2.1, 1.8, 3.5, 4.2, 1.5 };
    double initLoad[] = { 20,  30,  25,  40,  50,  18  };
    for (int i = 0; i < 6; i++) SYS.update(i, initLat[i], initLoad[i]);
    cout << "  [OK] System Monitor\n";

    
    
    
    ECL.captureCheckpoint(A2, "SYSTEM_INIT_BASELINE");
    
    for (int i = 0; i < MAX_ZONES; i++) {
        ECL.recordStep("INIT_READ_SENSOR", i,
                       0.0, A2.temperature[i],
                       A1.temperature[i], true, "read");
    }
    cout << "  [OK] Execution Control Layer  (ECL: stack + step log)\n";

    
    
    cout << "  [OK] Dynamic Scheduler        (DSCH)\n";

    
    
    AMON.tuneThresholds(SYS);
    cout << "  [OK] Adaptive Monitor         (AMON)\n";

    cout << string(62, '=') << "\n";
    cout << "   SYSTEM READY\n";
    cout << string(62, '=') << "\n";
}

void scenario1() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  SCENARIO 1: Cascading Fire & Resource Conflict Resolution\n";
    cout << string(62, '=') << "\n";
    cout << "  Fire origin: Zone 3  |  Spreading -> Zone 4, Zone 6\n";

    
    
    
    
    cout << "\n--- Step 1: Pre-Fire Safe State Checkpoint (ECL) ---\n";
    ECL.captureCheckpoint(A2, "SCENARIO1_PRE_FIRE_SAFE");
    cout << "  [Dept3] Safe copy stored on checkpoint stack.\n";
    cout << "  [Dept3] System can recover to this state if instability occurs.\n";

    
    
    
    
    cout << "\n--- Step 2: Continuous Sensor Collection — Fire Spreading (A2) ---\n";
    cout << "  Fire detected in Zone 3. Sensor stream updating...\n";
    A2.updateZone(3,  58.0, 18.0, 74.0); 
    A2.updateZone(4,  47.0, 25.0, 55.0); 
    A2.updateZone(6,  42.0, 32.0, 45.0); 
    A2.updateZone(1,  31.0, 48.0, 12.0); 
    A2.updateZone(5,  29.0, 55.0,  8.0); 
    cout << "\n  Current A2 state after fire propagation readings:\n";
    A2.display();

    
    
    
    
    
    cout << "\n--- Step 3: Reading Validation & Chronological Storage ---\n";
    cout << "  Validating readings against A1 baseline (tolerance=25):\n";
    int    checkZones[] = { 3, 4, 6, 1, 5 };
    double newTemps[]   = { 58.0, 47.0, 42.0, 31.0, 29.0 };
    bool   anyBad = false;
    for (int k = 0; k < 5; k++) {
        int    z = checkZones[k];
        double t = newTemps[k];
        bool   ok = ECL.checkConsistency(z, t, A1.temperature[z], 25.0);
        
        L1.insertBack(ForestEvent(t, z, "s1_fire", ok ? "raw" : "anomaly"));
        ECL.recordStep("FIRE_SPREAD_READ", z,
                       A1.temperature[z], t,
                       A1.temperature[z], ok, "read");
        if (!ok) anyBad = true;
    }
    cout << "\n  [L1] Chronological raw event stream (all readings):\n";
    L1.display();

    
    
    
    
    cout << "\n--- Step 4: Noise Filtering — Removing Unstable Readings (L2) ---\n";
    
    SinglyLinkedList L2fire("L2-S1-Verified");
    for (int k = 0; k < 5; k++)
        L2fire.insertBack(ForestEvent(newTemps[k], checkZones[k],
                                      "s1", "verified"));
    cout << "  Before filtering:\n"; L2fire.display();
    L2fire.filterNoise(NOISE_DELTA);
    cout << "  After filtering (unstable spikes removed):\n";
    L2fire.display();

    
    
    
    
    cout << "\n--- Step 5: Instability Detected — Rollback & Re-read (ECL) ---\n";
    if (anyBad) {
        cout << "  [Dept3] Instability detected in fire zone readings.\n";
        ECL.pauseExecution("Zone3 temperature spike exceeds 25°C tolerance");
        cout << "  [Dept3] Rolling back to last verified state...\n";
        ECL.rollback(A2);
        
        cout << "  [Dept3] Re-applying confirmed fire readings:\n";
        A2.updateZone(3, 56.0, 20.0, 72.0);
        A2.updateZone(4, 46.0, 28.0, 53.0);
        A2.updateZone(6, 40.0, 35.0, 42.0);
        ECL.resumeExecution();
    } else {
        cout << "  [Dept3] All readings stable — no rollback needed.\n";
    }

    
    
    
    
    cout << "\n--- Step 6: Priority Escalation for Dangerous Zones (DSCH) ---\n";
    Q1.enqueue(Task("S1-Z3", 3, "routine", 56.0, 3));
    Q1.enqueue(Task("S1-Z4", 4, "routine", 46.0, 3));
    Q1.enqueue(Task("S1-Z6", 6, "routine", 40.0, 3));
    Q1.enqueue(Task("S1-Z1", 1, "routine", 31.0, 3));
    Q1.enqueue(Task("S1-Z5", 5, "routine", 29.0, 3));
    DSCH.adjustPriorities(A2, Q1, Q3);
    cout << "\n  [Dept4] Critical tasks now in emergency queue:\n";
    Q3.display();

    
    
    
    
    
    
    cout << "\n--- Step 7: Fire Strength Estimation — Zone-Level Decisions ---\n";
    
    struct ZoneRisk { int id; double fire; double smoke; double temp;
                      string response; };
    ZoneRisk zones[] = {
        { 3, 0.95, 0.85, 0.90, "FULL RESPONSE — Zone 3 is fire origin" },
        { 4, 0.65, 0.60, 0.60, "CONTROLLED RESPONSE — Zone 4 spreading" },
        { 6, 0.45, 0.45, 0.50, "MONITORING — Zone 6 approaching" }
    };
    cout << "  [T7] Fire Classification Tree:\n"; T[7]->display();
    cout << "\n  Decision scores (w1=0.40 w2=0.30 w3=0.30, threshold=0.60):\n";
    for (int zi = 0; zi < 3; zi++) {
        cout << "\n  Zone " << zones[zi].id << " — " << zones[zi].response << "\n";
        bool em = T[7]->evaluateDecision(zones[zi].fire, zones[zi].smoke, zones[zi].temp);
        
        cout << "  T10 Local decision: ";
        if (em) {
            cout << "ACTIVATE LOCAL RESPONSE\n";
            Q3.enqueue(Task("FIRE-Z"+to_string(zones[zi].id), zones[zi].id,
                            "fire_response", zones[zi].temp*100, 1));
        } else {
            cout << "CONTINUE MONITORING\n";
        }
    }

    
    
    
    
    cout << "\n--- Step 8: Fire Spread Propagation Prediction (G1 BFS) ---\n";
    cout << "  Predicting spread level-by-level from Zone 3:\n";
    G1.BFS(3);
    cout << "\n  Fire-aware edge cost update for Zone 3 (fireLevel=0.85):\n";
    G1.updateFireCost(3, 0.85);

    
    
    
    cout << "\n--- Step 9: Regional Escalation Check (T11) ---\n";
    T[11]->display();
    double spreadRate = 0.72;
    cout << "\n  Measured fire spread rate = " << spreadRate << "\n";
    bool regional = T[11]->evaluateDecision(spreadRate, 0.60, 0.70);
    if (regional) cout << "  => REGIONAL ESCALATION ACTIVATED\n";

    
    
    
    
    
    cout << "\n--- Step 10: Saving Changes — Hash Update & State Sync ---\n";
    int fireZones136[] = {3, 4, 6};
    for (int fi = 0; fi < 3; fi++) {
        int z = fireZones136[fi];
        H1.insert(z, A2.temperature[z], A2.smokeLevel[z], A2.humidity[z]);
        H3.put(z,    A2.temperature[z], A2.smokeLevel[z], A2.humidity[z]);
        L4.insertBack(ForestEvent(A2.temperature[z], z, "s1_final", "fwd_chain"));
        L6.insertBack(ForestEvent(A2.temperature[z], z, "s1_sync",  "sync"));
    }
    cout << "  [L6] State sync chain for fire zones:\n"; L6.display();
    cout << "  [H1] Hash table for quick retrieval:\n";  H1.display();

    
    
    
    cout << "\n--- Step 11: System-Wide Monitoring Confirmation (L8) ---\n";
    L8.insert(ForestEvent(A2.temperature[3], 3, "s1_final", "syswide"));
    L8.insert(ForestEvent(A2.temperature[4], 4, "s1_final", "syswide"));
    L8.insert(ForestEvent(A2.temperature[6], 6, "s1_final", "syswide"));
    L8.display();
    SYS.update(0, 2.0, 35.0);
    SYS.update(1, 3.5, 45.0);
    SYS.update(2, 7.5, 72.0);
    SYS.update(4, 5.5, 60.0);
    SYS.display();

    cout << "\n  >>> SCENARIO 1 COMPLETE:\n"
            "      Fire tracked Zone3->Zone4->Zone6 | Rollback executed |\n"
            "      Priority escalated | Regional alert | State synchronized.\n";
}

void scenario2() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  SCENARIO 2: Sensor Failure & System Reconstruction\n";
    cout << string(62, '=') << "\n";
    cout << "  Affected zone: Zone 2  |  Sensors sending bad readings\n";

    
    
    
    cout << "\n--- Step 1: Stable Baseline Checkpoint Before Failure (ECL) ---\n";
    ECL.captureCheckpoint(A2, "S2_PRE_FAILURE_ZONE2");
    ECL.captureCheckpoint(A2, "S2_SECONDARY_STABLE"); 
    cout << "  Two-level checkpoint stored for deep recovery capability.\n";
    cout << "  Checkpoint stack depth: " << ECL.checkpointStack.size() << "\n";

    
    
    
    
    cout << "\n--- Step 2: Zone 2 Sensor Failure — Bad Readings Injected ---\n";
    cout << "  Simulating sensor hardware malfunction in Zone 2...\n";
    double badReadings[][3] = {
        { 999.0,  50.0,  70.0 }, 
        {  -8.0,  45.0,  65.0 }, 
        {  28.0, -1.0,   60.0 }, 
        { 250.0, 100.0, 999.0 }  
    };
    string labels[] = {"OOB-temp","neg-temp","neg-humidity","multi-extreme"};
    cout << "\n  Incoming bad readings for Zone 2:\n";
    cout << "  " << left << setw(6) << "Read#"
                         << setw(10) << "Temp"
                         << setw(10) << "Humidity"
                         << setw(10) << "Smoke"
                         << "Verdict\n";
    cout << "  " << string(46, '-') << "\n";
    for (int i = 0; i < 4; i++) {
        bool tempOk  = (badReadings[i][0] >= 0 && badReadings[i][0] <= 200);
        bool humOk   = (badReadings[i][1] >= 0 && badReadings[i][1] <= 100);
        bool smokeOk = (badReadings[i][2] >= 0 && badReadings[i][2] <= 200);
        bool allOk   = tempOk && humOk && smokeOk;
        cout << "  " << setw(6) << i+1
                     << setw(10) << badReadings[i][0]
                     << setw(10) << badReadings[i][1]
                     << setw(10) << badReadings[i][2]
                     << (allOk ? "ACCEPTED" : "REJECTED ["+labels[i]+"]") << "\n";
    }

    
    
    
    
    cout << "\n--- Step 3: Noise Filtering & Physical Limit Rejection (L2) ---\n";
    SinglyLinkedList rawStream("S2-L1-Raw");
    SinglyLinkedList verStream("S2-L2-Verified");
    
    for (int i = 0; i < 4; i++)
        rawStream.insertBack(ForestEvent(badReadings[i][0], 2,
                             "fail_"+to_string(i), "raw"));
    rawStream.display();
    cout << "\n  ECL physical-limit + delta validation:\n";
    for (int i = 0; i < 4; i++) {
        bool ok = ECL.checkConsistency(2, badReadings[i][0],
                                       A1.temperature[2], 20.0);
        if (ok) verStream.insertBack(ForestEvent(badReadings[i][0], 2,
                                     "accepted", "verified"));
    }
    cout << "\n  L2 verified stream (only safe readings pass):\n";
    verStream.display();
    if (verStream.head == nullptr)
        cout << "  [ALL READINGS REJECTED] Verified stream empty.\n";

    
    
    
    
    cout << "\n--- Step 4: Reviewing Execution History via Step Log (ECL Stack) ---\n";
    cout << "  [Dept3] Scanning step log for last valid Zone 2 entry...\n";
    int   lastGoodStep = -1;
    double lastGoodVal = A1.temperature[2]; 
    int   scanned = 0;
    
    for (int si = ECL.stepLog.size() - 1; si >= 0 && scanned < 10; si--, scanned++) {
        const ExecutionStep& s = ECL.stepLog.at(si);
        if (s.zoneID == 2 && s.isValid) {
            lastGoodStep = s.stepID;
            lastGoodVal  = s.valueAfter;
            break;
        }
    }
    cout << "  Last valid Zone 2 entry in step log:\n";
    if (lastGoodStep >= 0)
        cout << "    StepID=" << lastGoodStep
             << "  Value=" << lastGoodVal << "C\n";
    else
        cout << "    No recent valid reading found. Using A1 baseline="
             << A1.temperature[2] << "C\n";

    
    
    
    
    cout << "\n--- Step 5: Rollback to Last Stable State (ECL Checkpoint) ---\n";
    cout << "  [Dept3] Popping checkpoint stack...\n";
    bool rb1 = ECL.rollback(A2);
    if (rb1) cout << "  Zone 2 restored: T=" << A2.temperature[2]
                  << "  S=" << A2.smokeLevel[2]
                  << "  H=" << A2.humidity[2] << "\n";

    
    
    
    
    
    cout << "\n--- Step 6: Estimating Missing Values (Spatial Interpolation) ---\n";
    cout << "  Zone 2 is in grid position (0,2) — computing neighbour average:\n";
    double interpVal = A3.interpolate(0, 2);
    cout << "  Interpolated temperature = " << fixed << setprecision(1)
         << interpVal << "C\n";
    cout << "  Past pattern estimate from step log = " << lastGoodVal << "C\n";
    double combinedEstimate = (interpVal + lastGoodVal) / 2.0;
    cout << "  Combined estimate (interpolated+history)/2 = "
         << combinedEstimate << "C\n";
    ECL.runAlternativePath(A2, 2, combinedEstimate);

    
    
    
    
    cout << "\n--- Step 7: Verify Reconstructed Value (Second Rollback if Needed) ---\n";
    bool rebuilt_ok = ECL.checkConsistency(2, A2.temperature[2],
                                           A1.temperature[2], 15.0);
    if (!rebuilt_ok) {
        cout << "  [Dept3] Rebuilt value still inconsistent.\n";
        cout << "  [Dept3] Performing second rollback to earlier checkpoint...\n";
        ECL.rollback(A2);
        
        ECL.runAlternativePath(A2, 2, A1.temperature[2]);
        cout << "  Zone 2 set to safe baseline: T=" << A1.temperature[2] << "C\n";
    } else {
        cout << "  [Dept3] Rebuilt value verified OK. No second rollback needed.\n";
    }

    
    
    
    
    
    cout << "\n--- Step 8: Zone 2 Restored — Back to Normal Operation ---\n";
    double finalVal = A2.temperature[2];
    cout << "  Zone 2 final restored temperature: " << finalVal << "C\n";
    
    DoublyLinkedList L5restore("S2-L5-Correction");
    L5restore.insertBack(ForestEvent(55.0, 2, "bad_1", "bwd"));
    L5restore.insertBack(ForestEvent(-8.0, 2, "bad_2", "bwd"));
    L5restore.insertBack(ForestEvent(finalVal, 2, "restored", "bwd"));
    cout << "  Before backward correction:\n"; L5restore.display();
    L5restore.backwardCorrect(2, finalVal);
    cout << "  After backward correction (history corrected):\n";
    L5restore.display();
    H1.insert(2, finalVal, A2.smokeLevel[2], A2.humidity[2]);
    H3.put(2,    finalVal, A2.smokeLevel[2], A2.humidity[2]);
    cout << "\n  Zone 2 hash updated. Now under normal monitoring (L10 stability loop):\n";
    L10.insert(ForestEvent(finalVal, 2, "restored", "stable"));
    L10.display();
    ECL.recordStep("ZONE2_RESTORED", 2, 55.0, finalVal,
                   A1.temperature[2], true, "correct");
    SYS.update(3, 2.5, 28.0);
    SYS.display();

    cout << "\n  >>> SCENARIO 2 COMPLETE:\n"
            "      All bad readings rejected | Step log traced |\n"
            "      Two-level rollback executed | Spatial reconstruction done |\n"
            "      Zone 2 fully restored and operating normally.\n";
}

void scenario3() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  SCENARIO 3: Multi-Factor Anomaly Escalation System\n";
    cout << string(62, '=') << "\n";
    cout << "  Simultaneous events: Wildlife | Fire Risk | Human Movement\n";

    
    
    
    
    cout << "\n--- Step 1: Combined Forest View — All Zones (A2) ---\n";
    
    A2.updateZone(0, 26.0, 58.0, 5.0);   
    A2.updateZone(1, 44.0, 30.0, 35.0);  
    A2.updateZone(2, 29.0, 52.0, 10.0);  
    A2.updateZone(5, 50.0, 22.0, 68.0);  
    A2.updateZone(7, 31.0, 45.0, 20.0);  
    A2.updateZone(8, 27.0, 55.0,  6.0);  
    A2.display();

    
    
    
    
    cout << "\n--- Step 2: Pattern Comparison — Current vs Historical (L1 vs A2) ---\n";
    cout << "  " << left << setw(7)  << "Zone"
                          << setw(14) << "Historic(L1)"
                          << setw(14) << "Current(A2)"
                          << setw(12) << "Delta"
                          << "Trend\n";
    cout << "  " << string(55, '-') << "\n";
    SLLNode* cur = L1.head;
    while (cur) {
        int z = cur->data.zoneID;
        if (z < MAX_ZONES) {
            double hist  = cur->data.value;
            double live  = A2.temperature[z];
            double delta = live - hist;
            string trend = (delta > 5.0)  ? "RISING" :
                           (delta < -5.0) ? "FALLING" : "Stable";
            cout << "  " << setw(7)  << z
                         << setw(14) << hist
                         << setw(14) << live
                         << setw(12) << fixed << setprecision(1) << delta
                         << trend << "\n";
        }
        cur = cur->next;
    }

    
    
    
    
    cout << "\n--- Step 3: Independent Anomaly Classification ---\n";
    cout << "\n  [T8] Wildlife Activity Assessment:\n";
    T[8]->display();
    cout << "  Zone 8 shows unusual migration pattern:\n";
    T[8]->evaluateDecision(0.45, 0.40, 0.40, 0.4, 0.3, 0.3, 0.6);

    cout << "\n  [T7] Fire Risk Assessment:\n";
    T[7]->display();
    cout << "  Zone 1 elevated readings (fire=0.60, smoke=0.50, temp=0.58):\n";
    (void)T[7]->evaluateDecision(0.60, 0.50, 0.58); 
    cout << "  Zone 5 critical readings (fire=0.85, smoke=0.80, temp=0.75):\n";
    bool fireRisk5 = T[7]->evaluateDecision(0.85, 0.80, 0.75);

    cout << "\n  [T9] Human Activity Assessment:\n";
    T[9]->display();
    cout << "  Zone 7 unknown entity detected (risk=0.80, restricted=0.90):\n";
    T[9]->evaluateDecision(0.80, 0.90, 0.75, 0.4, 0.35, 0.25, 0.6);

    
    
    
    
    cout << "\n--- Step 4: Multi-Factor Combined Danger Assessment ---\n";
    cout << "  Combined scoring across all three anomaly types:\n";
    struct MultiZone { int z; double fw; double ww; double hw;
                       double fire; double wild; double human; };
    MultiZone mz[] = {
        { 1, 0.5, 0.2, 0.3, 0.60, 0.20, 0.10 },
        { 5, 0.5, 0.2, 0.3, 0.85, 0.30, 0.15 },
        { 7, 0.3, 0.3, 0.4, 0.20, 0.50, 0.85 },
        { 8, 0.2, 0.5, 0.3, 0.10, 0.75, 0.20 }
    };
    cout << "  " << left << setw(7)  << "Zone"
                          << setw(12) << "FireW"
                          << setw(12) << "WildlifeW"
                          << setw(12) << "HumanW"
                          << setw(12) << "Score"
                          << "Decision\n";
    cout << "  " << string(60, '-') << "\n";
    for (int mi = 0; mi < 4; mi++) {
        double score = mz[mi].fw*mz[mi].fire + mz[mi].ww*mz[mi].wild + mz[mi].hw*mz[mi].human;
        string dec   = score > 0.6 ? "URGENT ATTENTION" : "Normal Observation";
        cout << "  " << setw(7)  << mz[mi].z
                     << setw(12) << mz[mi].fw
                     << setw(12) << mz[mi].ww
                     << setw(12) << mz[mi].hw
                     << setw(12) << fixed << setprecision(3) << score
                     << dec << "\n";
        if (score > 0.6) {
            L3.insertBack(ForestEvent(A2.temperature[mz[mi].z], mz[mi].z,
                                      "multi_factor", "anomaly"));
            Q3.enqueue(Task("MFA-Z"+to_string(mz[mi].z), mz[mi].z,
                            "multi_anomaly", score, 1));
        } else {
            Q1.enqueue(Task("NRM-Z"+to_string(mz[mi].z), mz[mi].z,
                            "normal_obs", score, 3));
            L7.insert(ForestEvent(A2.temperature[mz[mi].z], mz[mi].z,
                                  "normal", "local"));
        }
    }

    
    
    
    
    cout << "\n--- Step 5: Propagation Check — Effect on Nearby Zones (G1 BFS) ---\n";
    if (fireRisk5) {
        cout << "  Zone 5 fire risk confirmed — checking spread path:\n";
        G1.BFS(5);
    }
    cout << "\n  Zone 7 human activity — checking adjacent zones:\n";
    G1.BFS(7);

    
    
    
    
    cout << "\n--- Step 6: Anomaly Stream & Monitoring Loops ---\n";
    cout << "  [L3] All anomalies logged in anomaly stream:\n";
    L3.display();
    cout << "\n  [L7] Normal zones in local monitoring loop:\n";
    L7.display();
    cout << "\n  [L9] Emergency loop activated for high-risk zones:\n";
    for (int mi = 0; mi < 4; mi++) {
        double score = mz[mi].fw*mz[mi].fire + mz[mi].ww*mz[mi].wild + mz[mi].hw*mz[mi].human;
        if (score > 0.6)
            L9.insert(ForestEvent(A2.temperature[mz[mi].z], mz[mi].z,
                                  "s3_emg", "emergency"));
    }
    L9.display();

    
    
    
    cout << "\n--- Step 7: Global Risk Evaluation (T12) ---\n";
    T[12]->display();
    cout << "\n  Global state: fire=0.72, wildlife=0.65, human=0.80\n";
    bool globalRisk = T[12]->evaluateDecision(0.72, 0.65, 0.80,
                                              0.4, 0.3, 0.3, 0.75);
    if (globalRisk)
        cout << "  => MULTI-FACTOR GLOBAL ALERT ACTIVATED\n";
    else
        cout << "  => System risk contained at zone level.\n";
    SYS.update(2, 6.0, 65.0);
    SYS.update(3, 8.0, 78.0);
    SYS.display();

    cout << "\n  >>> SCENARIO 3 COMPLETE:\n"
            "      Three simultaneous anomaly types identified |\n"
            "      Multi-factor scoring applied | Urgent vs normal separated |\n"
            "      Propagation paths computed | Global risk evaluated.\n";
}

void scenario4() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  SCENARIO 4: System Overload & Load Redistribution\n";
    cout << string(62, '=') << "\n";
    cout << "  Simulating high-volume simultaneous incoming updates\n";

    
    
    
    
    cout << "\n--- Step 1: Pre-Overload Safe State Checkpoint (ECL) ---\n";
    ECL.captureCheckpoint(A2, "S4_PRE_OVERLOAD_STABLE");
    cout << "  [Dept3] Safe copy saved. Overload handling can begin safely.\n";

    
    
    
    
    cout << "\n--- Step 2: High-Volume Update Flood — All Queues Loaded ---\n";
    cout << "  Injecting 20 simultaneous incoming sensor updates:\n";
    for (int i = 0; i < 6; i++) {
        Q1.enqueue(Task("OVL-R"+to_string(i), i%MAX_ZONES, "routine", 25.0+i, 3));
    }
    for (int i = 0; i < 5; i++) {
        Q2.enqueue(Task("OVL-S"+to_string(i), (i+3)%MAX_ZONES,
                        "surveillance", 30.0+i, 2));
    }
    
    Q3.enqueue(Task("OVL-E1", 3, "emergency", 56.0, 1));
    Q3.enqueue(Task("OVL-E2", 5, "emergency", 50.0, 1));
    Q3.enqueue(Task("OVL-E3", 1, "emergency", 44.0, 2));
    for (int i = 0; i < 3; i++) {
        Q4.enqueue(Task("OVL-M"+to_string(i), i%MAX_ZONES,
                        "multi", 40.0+i, 2));
    }
    cout << "\n  Load after flood:\n";
    DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);

    
    SYS.update(0,  4.0, 70.0);
    SYS.update(1,  5.5, 75.0);
    SYS.update(2, 14.5, 94.0); 
    SYS.update(3, 10.0, 88.0); 
    SYS.update(4, 17.5, 97.0); 
    SYS.update(5,  2.0, 25.0);
    cout << "\n  System performance under overload:\n";
    SYS.display();

    
    
    
    
    cout << "\n--- Step 3: Separating Critical from Non-Critical (DSCH) ---\n";
    cout << "  [Dept4] Scanning Q1 for fire-zone tasks to upgrade...\n";
    DSCH.adjustPriorities(A2, Q1, Q3);
    cout << "\n  Post-separation queue state:\n";
    DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);

    
    
    
    
    cout << "\n--- Step 4: Process Critical First, Pause Low Priority ---\n";
    cout << "  [Q3] Processing ALL emergency tasks immediately:\n";
    int emergCount = 0;
    while (!Q3.empty()) { Q3.dequeue(); emergCount++; }
    cout << "  " << emergCount << " critical tasks processed.\n";
    cout << "\n  [Q4] Processing multi-factor tasks:\n";
    while (!Q4.empty()) Q4.dequeue();
    cout << "  Low-priority Q1/Q2 tasks PAUSED — holding for rebalance.\n";
    cout << "  Q1 pending: " << Q1.count()
         << "  |  Q2 pending: " << Q2.count() << "\n";

    
    
    
    
    cout << "\n--- Step 5: Workload Rebalancing Across Resources (DSCH) ---\n";
    DSCH.rebalanceQueues(Q1, Q2);
    cout << "\n  Post-rebalance distribution:\n";
    DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);

    
    
    
    
    cout << "\n--- Step 6: Caching Frequently Needed Data (H3) ---\n";
    cout << "  Pre-loading hot zones into fast retrieval cache:\n";
    int hotZones[] = { 3, 4, 5, 1, 9 };
    for (int hz = 0; hz < 5; hz++) {
        H3.put(hotZones[hz], A2.temperature[hotZones[hz]], A2.smokeLevel[hotZones[hz]], A2.humidity[hotZones[hz]]);
    }
    cout << "\n  Verifying cache hits for repeated queries:\n";
    for (int hz = 0; hz < 5; hz++) H3.get(hotZones[hz]);
    H3.display();

    
    
    
    
    cout << "\n--- Step 7: Gradual Restoration of Paused Updates (Batch Processing) ---\n";
    const int BATCH = 3;
    int round = 1;
    while (!Q1.empty() || !Q2.empty()) {
        cout << "  -- Batch " << round++ << " --\n";
        for (int b = 0; b < BATCH && !Q1.empty(); b++) Q1.dequeue();
        for (int b = 0; b < BATCH && !Q2.empty(); b++) Q2.dequeue();
    }
    cout << "  All paused updates processed. Queues clear.\n";

    
    
    
    
    cout << "\n--- Step 8: Adaptive Monitor — System Recovery (AMON) ---\n";
    int bn = AMON.detectBottleneck(SYS);
    AMON.redistributeLoad(SYS, bn);
    AMON.tuneThresholds(SYS);
    
    SYS.update(2, 5.5, 48.0);
    SYS.update(3, 4.5, 42.0);
    SYS.update(4, 6.0, 52.0);
    cout << "\n  System metrics after load redistribution:\n";
    SYS.display();
    AMON.generateFullReport(SYS);

    
    
    
    
    cout << "\n--- Step 9: Stability Confirmation — System Back to Normal ---\n";
    for (int i = 0; i < MAX_ZONES; i++) {
        if (fabs(A2.temperature[i] - A1.temperature[i]) < 10.0)
            L10.insert(ForestEvent(A2.temperature[i], i, "s4_stable", "stable"));
    }
    cout << "  [L10] Stability monitoring loop confirms normal zones:\n";
    L10.display();

    cout << "\n  >>> SCENARIO 4 COMPLETE:\n"
            "      Overload handled | Critical processed first |\n"
            "      Workload rebalanced | Cache warmed | Batched restore |\n"
            "      Adaptive tuning applied | System returned to normal.\n";
}

void scenario5() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  SCENARIO 5: Global Multi-Zone Emergency Synchronization\n";
    cout << string(62, '=') << "\n";
    cout << "  Simultaneous emergencies across all regions of the forest\n";

    
    
    
    
    cout << "\n--- Step 1: Multi-Zone Emergency Update — All Regions (A2) ---\n";
    cout << "  Asynchronous updates from all forest regions arriving:\n";
    
    A2.updateZone(0, 62.0, 12.0, 78.0);  
    A2.updateZone(1, 28.0, 50.0, 12.0);  
    A2.updateZone(2, 70.0, 10.0, 85.0);  
    A2.updateZone(3, 25.0, 55.0,  8.0);  
    A2.updateZone(4, 68.0, 11.0, 82.0);  
    A2.updateZone(5, 29.0, 58.0,  9.0);  
    A2.updateZone(6, 55.0, 22.0, 65.0);  
    A2.updateZone(7, 31.0, 50.0, 15.0);  
    A2.updateZone(8, 60.0, 15.0, 70.0);  
    A2.updateZone(9, 26.0, 54.0,  7.0);  
    cout << "\n  Current global state (conflicts evident between region pairs):\n";
    A2.display();

    
    
    
    
    cout << "\n--- Step 2: Global Inconsistency Detection (ECL) ---\n";
    cout << "  Checking each zone against A1 baseline + spatial neighbours:\n";
    ECL.captureCheckpoint(A2, "S5_PRE_CONFLICT_STATE");
    
    int conflictZones[MAX_ZONES], conflictCnt = 0;
    int cleanZones[MAX_ZONES],    cleanCnt    = 0;
    for (int i = 0; i < MAX_ZONES; i++) {
        bool ok = ECL.checkConsistency(i, A2.temperature[i],
                                       A1.temperature[i], 20.0);
        ECL.recordStep("GLOBAL_SCAN", i,
                       A1.temperature[i], A2.temperature[i],
                       A1.temperature[i], ok, "read");
        if (!ok) {
            conflictZones[conflictCnt++] = i;
            L3.insertBack(ForestEvent(A2.temperature[i], i,
                                      "s5_conflict", "anomaly"));
        } else {
            cleanZones[cleanCnt++] = i;
        }
    }
    cout << "\n  Conflicting zones: ";
    for (int i = 0; i < conflictCnt; i++) cout << "Zone" << conflictZones[i] << " ";
    cout << "\n  Clean zones     : ";
    for (int i = 0; i < cleanCnt; i++)    cout << "Zone" << cleanZones[i]    << " ";
    cout << "\n";

    
    
    
    
    
    cout << "\n--- Step 3: Revisiting Validated History (L5 + ECL StepLog) ---\n";
    cout << "  [L5] Building backward correction chain from history:\n";
    DoublyLinkedList L5global("S5-L5-GlobalCorrect");
    
    for (int i = 0; i < MAX_ZONES; i++)
        L5global.insertBack(ForestEvent(A2.temperature[i], i,
                                        "s5_current", "bwd"));
    
    cout << "  Correcting conflicting zones to last known clean values:\n";
    for (int ci = 0; ci < conflictCnt; ci++)
        L5global.backwardCorrect(conflictZones[ci], A1.temperature[conflictZones[ci]]);
    L5global.display();

    
    
    
    
    cout << "\n--- Step 4: Rollback to Globally Consistent State (ECL) ---\n";
    cout << "  [Dept3] Popping to last confirmed consistent global snapshot...\n";
    ECL.rollback(A2);
    cout << "  Globally consistent state restored.\n";
    cout << "  Conflict zones will be reconstructed with verified data.\n";

    
    
    
    
    cout << "\n--- Step 5: Data Isolation — Consistent Segments Only ---\n";
    cout << "  [L3] Isolated conflicting zone data:\n";
    L3.display();
    cout << "\n  [Dept2] Rebuilding verified stream from consistent zones only:\n";
    SinglyLinkedList verGlobal("S5-L2-GlobalVerified");
    for (int ci = 0; ci < cleanCnt; ci++)
        verGlobal.insertBack(ForestEvent(A2.temperature[cleanZones[ci]], cleanZones[ci],
                                         "s5_verified", "verified"));
    verGlobal.display();

    
    
    
    
    
    cout << "\n--- Step 6: Correction State Construction (L4 + L6) ---\n";
    cout << "  [L4] Forward correction: propagating verified values forward:\n";
    DoublyLinkedList L4global("S5-L4-GlobalFwd");
    
    for (int ci = 0; ci < conflictCnt; ci++) {
        int z = conflictZones[ci];
        double corrected = (A1.temperature[z] + A3.interpolate(z/GRID_COLS,
                                                               z%GRID_COLS)) / 2.0;
        A2.updateZone(z, corrected,
                      A2.humidity[z],
                      A2.smokeLevel[z]);
        L4global.insertBack(ForestEvent(corrected, z, "s5_corrected", "fwd_chain"));
        cout << "    Zone " << z << " corrected to T=" << fixed
             << setprecision(1) << corrected << "C\n";
    }
    L4global.forwardCorrect(-1, 0); 
    cout << "\n  [L6] State synchronization — all modules get same values:\n";
    DoublyLinkedList L6global("S5-L6-GlobalSync");
    for (int i = 0; i < MAX_ZONES; i++)
        L6global.insertBack(ForestEvent(A2.temperature[i], i,
                                        "s5_sync", "sync"));
    L6global.display();

    
    
    
    
    cout << "\n--- Step 7: Regional Conflict Resolution (T11 + T12) ---\n";
    double globalFireSum = 0;
    for (int i = 0; i < MAX_ZONES; i++)
        globalFireSum += (A2.temperature[i] > TEMP_THRESHOLD ? 1.0 : 0.0);
    double globalRisk = globalFireSum / MAX_ZONES;

    cout << "  Fire zones count = " << (int)globalFireSum
         << " / " << MAX_ZONES
         << "  => Global risk ratio = " << globalRisk << "\n";

    cout << "\n  [T11] Regional Escalation:\n"; T[11]->display();
    cout << "\n  Regional decision (spreadRate=0.68, smoke=0.70, temp=0.72):\n";
    T[11]->evaluateDecision(0.68, 0.70, 0.72);

    cout << "\n  [T12] Global Emergency Command:\n"; T[12]->display();
    cout << "\n  Global decision (risk=" << globalRisk << ", smoke=0.78, temp=0.80):\n";
    bool globalAlert = T[12]->evaluateDecision(globalRisk, 0.78, 0.80,
                                               0.4, 0.3, 0.3, 0.75);
    if (globalAlert) {
        cout << "\n  ╔══════════════════════════════════════════════╗\n";
        cout << "  ║  *** GLOBAL SYNCHRONIZATION ALERT ***        ║\n";
        cout << "  ║  Unified emergency response strategy active  ║\n";
        cout << "  ╚══════════════════════════════════════════════╝\n";
    }

    
    
    
    
    cout << "\n--- Step 8: Synchronized Response — Multi-Origin BFS (G2) ---\n";
    cout << "  G2 adjacency matrix BFS from each emergency zone:\n";
    G2.display();
    for (int ci = 0; ci < conflictCnt; ci++) {
        int z = conflictZones[ci];
        if (A2.temperature[z] > TEMP_THRESHOLD) {
            cout << "\n  Emergency origin Zone" << z << ":\n";
            G2.BFS(z);
        }
    }

    
    
    
    
    cout << "\n--- Step 9: Synchronized Emergency Dispatch (Q3 Burst) ---\n";
    int dispatchCount = 0;
    for (int i = 0; i < MAX_ZONES; i++) {
        if (A2.temperature[i] > TEMP_THRESHOLD ||
            A2.smokeLevel[i]  > SMOKE_THRESHOLD) {
            Q3.enqueue(Task("SYNC-Z"+to_string(i), i,
                            "global_sync_emg",
                            A2.temperature[i], 1));
            dispatchCount++;
        }
    }
    cout << "  Total synchronized tasks dispatched: " << dispatchCount << "\n";
    Q3.display();
    cout << "\n  Processing all synchronized emergency responses:\n";
    while (!Q3.empty()) Q3.dequeue();

    
    
    
    
    
    cout << "\n--- Step 10: Continuous Validation — All Zones (L8 + AMON) ---\n";
    cout << "  [L8] System-wide monitoring loop confirming synchronized state:\n";
    for (int i = 0; i < MAX_ZONES; i++)
        L8.insert(ForestEvent(A2.temperature[i], i, "s5_validate", "syswide"));
    L8.display();

    SYS.update(0,  3.5, 55.0);
    SYS.update(1,  4.0, 60.0);
    SYS.update(2,  7.5, 70.0);
    SYS.update(3,  8.5, 78.0);
    SYS.update(4, 12.0, 88.0);
    SYS.update(5,  2.0, 30.0);
    AMON.generateFullReport(SYS);

    
    ECL.displayStatus();

    cout << "\n  ╔═════════════════════════════════════════════════════╗\n";
    cout << "  ║  SCENARIO 5 COMPLETE                                ║\n";
    cout << "  ║  Global inconsistencies detected & resolved         ║\n";
    cout << "  ║  Rollback + L4/L5/L6 correction applied             ║\n";
    cout << "  ║  T11/T12 regional+global decisions executed         ║\n";
    cout << "  ║  Synchronized multi-origin BFS + Q3 burst done      ║\n";
    cout << "  ║  Continuous validation via L8 loop + AMON active    ║\n";
    cout << "  ╚═════════════════════════════════════════════════════╝\n";
    cout << "\n  >>> SCENARIO 5 COMPLETE: Global emergency fully synchronized.\n";
}

void scenario6() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  SCENARIO 6: Execution Control & State Recovery\n";
    cout << "  (Dept3: ExecControl | Dept4: DynScheduler |"
            " Dept8: AdaptiveMonitor)\n";
    cout << string(62, '=') << "\n";

    
    
    
    cout << "\n--- Step 1: Pre-Scenario Checkpoint Capture (ECL) ---\n";
    ECL.captureCheckpoint(A2, "PRE_SCENARIO6_STABLE");
    cout << "  Checkpoint stack depth: "
         << ECL.checkpointStack.size() << "\n";
    cout << "  [Dept3] Stack-based checkpoint ensures full rollback"
            " capability.\n";

    
    
    
    cout << "\n--- Step 2: Normal Execution Steps (ECL Step Log) ---\n";
    for (int i = 0; i < 5; i++) {
        bool ok = ECL.checkConsistency(i, A2.temperature[i],
                                       A1.temperature[i], 20.0);
        ECL.recordStep("NORMAL_SCAN", i,
                       A1.temperature[i], A2.temperature[i],
                       A1.temperature[i], ok, "read");
    }
    cout << "  [Dept3] Execution continuity maintained. "
            "5 steps logged.\n";

    
    
    
    cout << "\n--- Step 3: Injecting Faulty Sensor Readings ---\n";
    cout << "  Simulating sensor hardware faults...\n";
    cout << "  Injecting Zone 1: temp=999.0 (out-of-range)\n";
    cout << "  Injecting Zone 3: temp=-5.0  (below-zero invalid)\n";
    cout << "  Injecting Zone 6: temp=180.0 (extreme spike)\n";
    (void)A2.temperature[1]; (void)A2.temperature[3]; (void)A2.temperature[6];
    A2.temperature[1] = 999.0;
    A2.temperature[3] = -5.0;
    A2.temperature[6] = 180.0;
    cout << "  Faulty readings injected into A2 sensor array.\n";

    
    
    
    cout << "\n--- Step 4: Consistency Checking (ECL) ---\n";
    cout << "  Running physical limit & delta checks on all zones:\n";
    bool allOk = true;
    for (int i = 0; i < MAX_ZONES; i++) {
        bool ok = ECL.checkConsistency(i, A2.temperature[i],
                                       A1.temperature[i], 20.0);
        if (!ok) {
            ECL.recordStep("FAULT_DETECTED", i,
                           A1.temperature[i], A2.temperature[i],
                           A1.temperature[i], false, "read");
            allOk = false;
        }
    }
    if (!allOk) cout << "  [Dept3] INCONSISTENCIES DETECTED in sensor stream.\n";
    else        cout << "  [Dept3] All readings consistent.\n";

    
    
    
    cout << "\n--- Step 5: Execution Pause (ECL) ---\n";
    if (!allOk) {
        ECL.pauseExecution(
            "Multiple sensor readings violated physical limits"
            " (values outside 0-200 range)");
        ECL.displayStatus();
    }

    
    
    
    cout << "\n--- Step 6: Rollback to Last Valid State (ECL Stack) ---\n";
    cout << "  [Dept3] Initiating stack pop + state restoration...\n";
    bool rbOk = ECL.rollback(A2);
    if (rbOk) {
        cout << "  A2 restored to clean state:\n";
        cout << "    Zone1 T=" << A2.temperature[1]
             << "  Zone3 T=" << A2.temperature[3]
             << "  Zone6 T=" << A2.temperature[6] << "\n";
        ECL.recordStep("ROLLBACK_COMPLETE", -1, 0, 0, 0, true, "rollback");
    }

    
    
    
    cout << "\n--- Step 7: Alternative Path Processing (ECL) ---\n";
    cout << "  Checking for spatial outliers after rollback...\n";
    for (int i = 0; i < MAX_ZONES; i++) {
        if (A2.temperature[i] < 0.0 || A2.temperature[i] > 200.0) {
            int r = i / GRID_COLS, c = i % GRID_COLS;
            double safe = A3.interpolate(r, c);
            ECL.runAlternativePath(A2, i, safe);
        }
    }
    cout << "  Simulating marginal spike in Zone 7 (T=62, exp=29)...\n";
    bool z7ok = ECL.checkConsistency(7, 62.0, 29.0, 20.0);
    if (!z7ok) {
        double safe7 = A3.interpolate(1, 3);
        ECL.runAlternativePath(A2, 7, safe7);
    }
    cout << "  [Dept3] All zones now operating on verified values.\n";

    
    
    
    cout << "\n--- Step 8: Priority Adjustment Post-Recovery (DSCH) ---\n";
    cout << "  [Dept4] Fire zones re-identified; upgrading tasks...\n";
    Q1.enqueue(Task("POST-R01", 2, "routine", 55.0, 3));
    Q1.enqueue(Task("POST-R02", 4, "routine", 65.0, 3));
    Q1.enqueue(Task("POST-R03", 0, "routine", 27.0, 3));
    Q1.enqueue(Task("POST-R04", 8, "routine", 25.0, 3));
    DSCH.adjustPriorities(A2, Q1, Q3);

    
    
    
    cout << "\n--- Step 9: Scheduler Load Balance Report (DSCH) ---\n";
    for (int i = 0; i < 5; i++)
        Q1.enqueue(Task("LOAD-Q1-"+to_string(i), i, "routine", 27.0, 3));
    Q2.enqueue(Task("LOAD-Q2-1", 3, "surveillance", 30.0, 2));
    DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);
    cout << "\n  [Dept4] Rebalancing Q1 -> Q2 if needed:\n";
    DSCH.rebalanceQueues(Q1, Q2);
    DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);

    
    
    
    cout << "\n--- Step 10: Bottleneck Detection (AMON) ---\n";
    SYS.update(2, 14.0, 93.0);
    SYS.update(4, 16.5, 96.0);
    SYS.update(3,  9.5, 85.0);
    int bn = AMON.detectBottleneck(SYS);
    cout << "  [Dept8] Bottleneck found at module index " << bn << "\n";

    
    
    
    cout << "\n--- Step 11: Dynamic Threshold Tuning (AMON) ---\n";
    AMON.tuneThresholds(SYS);

    
    
    
    cout << "\n--- Step 12: Adaptive Load Redistribution (AMON) ---\n";
    AMON.redistributeLoad(SYS, bn);
    cout << "  [Dept8] Post-redistribution metrics:\n";
    SYS.display();

    
    
    
    cout << "\n--- Step 13: Full Adaptive Health Report (AMON) ---\n";
    AMON.generateFullReport(SYS);

    
    
    
    cout << "\n--- Step 14: Execution Step Log & Checkpoint Summary (ECL) ---\n";
    ECL.displayStepLog();
    ECL.displayCheckpoints();
    ECL.displayStatus();

    cout << "\n  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║  SCENARIO 6 COMPLETE                             ║\n";
    cout << "  ║  State recovery successful via stack rollback    ║\n";
    cout << "  ║  Dynamic scheduler rebalanced all task queues    ║\n";
    cout << "  ║  Adaptive monitor tuned thresholds & load        ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
}

static void sec6Separator() {
    cout << string(62, '-') << "\n";
}

static void sec6Header(const string& title) {
    cout << "\n" << string(62, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(62, '=') << "\n";
}

static int readChoice() {
    int c = -1;
    if (!(cin >> c)) { cin.clear(); cin.ignore(1000, '\n'); }
    return c;
}

void handleMenu1() {
    sec6Header("1. INPUT ENVIRONMENTAL DATA");
    cout << "   1.1  Add Sensor Reading (Temperature, Smoke, Wind)\n";
    cout << "   1.2  Store Data in Dynamic Array\n";
    cout << "   1.3  Compare with Static Baseline\n";
    cout << "   1.4  Validate and Filter Noise\n";
    sec6Separator();
    cout << "   Enter sub-option (1-4): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("1.1 | Add Sensor Reading");
        int z; double t, h, s, w;
        cout << "  Zone (0-" << MAX_ZONES-1 << ")  : "; cin >> z;
        cout << "  Temperature (°C)  : "; cin >> t;
        cout << "  Humidity    (%)   : "; cin >> h;
        cout << "  Smoke Level       : "; cin >> s;
        cout << "  Wind Speed (km/h) : "; cin >> w;
        
        ECL.captureCheckpoint(A2, "PRE_INPUT_Z"+to_string(z));
        
        A2.updateZone(z, t, h, s);
        
        L1.insertBack(ForestEvent(t, z, "manual_input", "raw"));
        
        bool ok = ECL.checkConsistency(z, t, A1.temperature[z], 25.0);
        ECL.recordStep("SENSOR_INPUT", z, A1.temperature[z], t,
                       A1.temperature[z], ok, "update");
        
        H1.insert(z, t, s, h);
        H3.put(z, t, s, h);
        cout << "\n  [1.1] Reading recorded. "
             << (ok ? "Value within expected range." : "WARNING: value outside baseline range.") << "\n";
        cout << "  Wind=" << w << " km/h stored as auxiliary parameter.\n";
        break;
    }
    case 2: {
        
        sec6Header("1.2 | Store Data in Dynamic Array (A2)");
        cout << "  A2 is a DYNAMIC array — values update continuously at runtime.\n";
        cout << "  Each cell stores: Temperature, Humidity, Smoke, FireSignal.\n";
        cout << "  Time Complexity: O(1) per update | O(n) full scan\n\n";
        A2.display();
        cout << "\n  A4 Dynamic Terrain Risk Matrix (also updated at runtime):\n";
        A4.display();
        break;
    }
    case 3: {
        
        sec6Header("1.3 | Compare with Static Baseline (A1 vs A2)");
        cout << "  A1 = STATIC reference (fixed normal values)\n";
        cout << "  A2 = DYNAMIC live readings\n";
        cout << "  Delta = A2 - A1  |  Status: >10°C difference = FIRE RISK\n\n";
        A1.display();
        cout << "\n";
        cout << left << setw(8)  << "Zone"
                     << setw(12) << "Baseline"
                     << setw(12) << "Live"
                     << setw(10) << "Delta"
                     << setw(14) << "Smoke-Live"
                     << "Status\n";
        cout << string(62, '-') << "\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            double dT = A2.temperature[i] - A1.temperature[i];
            double dS = A2.smokeLevel[i]  - A1.smokeLevel[i];
            string st = "Normal";
            if (dT > 20 || dS > 50)       st = "*** CRITICAL ***";
            else if (dT > 10 || dS > 20)  st = "* WARNING *";
            cout << setw(8)  << i
                 << setw(12) << fixed << setprecision(1) << A1.temperature[i]
                 << setw(12) << A2.temperature[i]
                 << setw(10) << dT
                 << setw(14) << A2.smokeLevel[i]
                 << st << "\n";
        }
        break;
    }
    case 4: {
        
        sec6Header("1.4 | Validate and Filter Noise");
        cout << "  Step A — ECL Physical Limit Checks (0 <= T <= 200):\n";
        int flagged = 0;
        for (int i = 0; i < MAX_ZONES; i++) {
            bool ok = ECL.checkConsistency(i, A2.temperature[i],
                                           A1.temperature[i], 25.0);
            if (!ok) flagged++;
        }
        cout << "  Zones flagged by ECL: " << flagged << "\n\n";
        cout << "  Step B — L2 Singly-Linked Noise Filter (delta=" << NOISE_DELTA << "):\n";
        cout << "  Rule: |val_i - val_{i-1}| >= delta => noise removed\n";
        
        SinglyLinkedList demoStream("1.4-NoiseDemo");
        for (int i = 0; i < MAX_ZONES; i++)
            demoStream.insertBack(ForestEvent(A2.temperature[i], i,
                                             "live", "raw"));
        cout << "  Before filter:\n"; demoStream.display();
        demoStream.filterNoise(NOISE_DELTA);
        cout << "  After filter:\n";  demoStream.display();
        cout << "\n  Step C — A3 Grid Boundary Detection:\n";
        A3.detectBoundaries();
        A3.detectAnomalies();
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu2() {
    sec6Header("2. VIEW FOREST GRID STATUS");
    cout << "   2.1  Display 1D Time Series Data\n";
    cout << "   2.2  Display 2D Forest Zone Matrix\n";
    cout << "   2.3  View Zone-wise Conditions\n";
    sec6Separator();
    cout << "   Enter sub-option (1-3): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("2.1 | 1D Time Series Data (L1 Raw Stream)");
        cout << "  L1 is a SINGLY LINKED LIST storing sensor readings in time order.\n";
        cout << "  Each node: { value, zoneID, timestamp, eventType }\n";
        cout << "  Traversal: forward only  O(n)  |  Insert-back: O(n)\n\n";
        L1.display();
        cout << "\n  L2 Verified Stream (noise removed):\n";
        L2.display();
        cout << "\n  L3 Anomaly Stream (threshold violations):\n";
        L3.display();
        break;
    }
    case 2: {
        
        sec6Header("2.2 | 2D Forest Zone Matrix (A3 Static Grid)");
        cout << "  A3 is a 2D STATIC ARRAY (4x4 grid).\n";
        cout << "  Each cell stores baseline temperature for that grid zone.\n";
        cout << "  Access: O(1) by (row,col)  |  Full scan: O(n*m)\n\n";
        A3.display();
        cout << "\n  A4 Dynamic Terrain Risk Matrix (updated at runtime):\n";
        cout << "  Each cell = (slope + dryness + density) / 3  [0.0 - 1.0]\n\n";
        A4.display();
        cout << "\n  Spatial Interpolation demo — estimate cell (1,2):\n";
        cout << "  Formula: (top + bottom + left + right) / count\n";
        double iv = A3.interpolate(1, 2);
        cout << "  Interpolated value at (1,2) = " << fixed
             << setprecision(1) << iv << " °C\n";
        break;
    }
    case 3: {
        
        sec6Header("2.3 | Zone-wise Conditions — Complete Status");
        cout << left << setw(7)  << "Zone"
                     << setw(11) << "Temp(°C)"
                     << setw(12) << "Humidity(%)"
                     << setw(10) << "Smoke"
                     << setw(12) << "FireSignal"
                     << "Condition\n";
        cout << string(62, '-') << "\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            string cond = "SAFE";
            if (A2.fireSignal[i])                          cond = "*** FIRE ***";
            else if (A2.smokeLevel[i]  > SMOKE_THRESHOLD)  cond = "SMOKE ALERT";
            else if (A2.temperature[i] > TEMP_THRESHOLD)   cond = "HIGH TEMP";
            else if (A2.humidity[i]    < HUMID_THRESHOLD)   cond = "DRY";
            cout << setw(7)  << i
                 << setw(11) << fixed << setprecision(1) << A2.temperature[i]
                 << setw(12) << A2.humidity[i]
                 << setw(10) << A2.smokeLevel[i]
                 << setw(12) << A2.fireSignal[i]
                 << cond << "\n";
        }
        int fireCnt = 0;
        for (int i = 0; i < MAX_ZONES; i++) fireCnt += A2.fireSignal[i];
        cout << "\n  Active fire zones: " << fireCnt
             << " / " << MAX_ZONES << "\n";
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu3() {
    sec6Header("3. EVENT MEMORY SYSTEM");
    cout << "   3.1  Store Event (Linked List)\n";
    cout << "   3.2  Traverse Event History Forward\n";
    cout << "   3.3  Traverse Event History Backward\n";
    cout << "   3.4  Circular Event Monitoring\n";
    cout << "   3.5  Restore Last Stable State\n";
    sec6Separator();
    cout << "   Enter sub-option (1-5): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("3.1 | Store Event in Linked List");
        int z; double v; string ts, et;
        cout << "  Zone (0-" << MAX_ZONES-1 << ")   : "; cin >> z;
        cout << "  Value (temp)  : "; cin >> v;
        cout << "  Timestamp     : "; cin >> ts;
        cout << "  Type (raw/verified/anomaly/emergency): "; cin >> et;

        ForestEvent ev(v, z, ts, et);
        if (et == "anomaly" || v > TEMP_THRESHOLD) {
            L3.insertBack(ev);
            cout << "  Stored in L3-AnomalyStream (anomaly/high value).\n";
        } else {
            L1.insertBack(ev);
            cout << "  Stored in L1-RawEventStream.\n";
        }
        
        L4.insertBack(ForestEvent(v, z, ts, "fwd_chain"));
        cout << "  Also stored in L4-ForwardCorrectionChain.\n\n";
        cout << "  L1 current state (time-ordered, O(1) front insert / O(n) back):\n";
        L1.display();
        break;
    }
    case 2: {
        
        sec6Header("3.2 | Traverse Event History Forward (L4)");
        cout << "  L4 is a DOUBLY LINKED LIST — forward traversal shows events\n";
        cout << "  in the order they were corrected/updated.\n";
        cout << "  Navigation rule: Event_i -> Event_{i+1}  O(n)\n\n";
        L4.display();
        cout << "\n  L1 Singly-linked forward traversal:\n";
        L1.display();
        cout << "\n  L2 Verified stream forward:\n";
        L2.display();
        break;
    }
    case 3: {
        
        sec6Header("3.3 | Traverse Event History Backward (L5)");
        cout << "  L5 is a DOUBLY LINKED LIST — backward traversal allows\n";
        cout << "  revisiting and correcting past readings.\n";
        cout << "  Navigation rule: Event_i -> Event_{i-1}  O(n)\n\n";
        cout << "  L5 Backward Correction Chain:\n";
        L5.display();
        cout << "\n  L6 State Synchronization Chain:\n";
        L6.display();
        
        cout << "\n  Demonstration: Applying backward correction to Zone 3\n";
        cout << "  (if history has Zone 3 entries, they get corrected to 30.0):\n";
        L5.backwardCorrect(3, 30.0);
        L5.display();
        break;
    }
    case 4: {
        
        sec6Header("3.4 | Circular Event Monitoring (L7-L10)");
        cout << "  Circular Linked Lists loop continuously — the last node\n";
        cout << "  points back to the first: Event_n -> Event_1\n";
        cout << "  One complete cycle: O(n)  |  Insert: O(1)\n\n";
        cout << "  [L7] LOCAL monitoring loop (single zone cycle):\n";
        L7.display();
        cout << "\n  [L8] SYSTEM-WIDE monitoring loop (all zones):\n";
        L8.display();
        cout << "\n  [L9] EMERGENCY monitoring loop (active danger zones):\n";
        L9.display();
        cout << "\n  [L10] STABILITY monitoring loop (normal/stable zones):\n";
        L10.display();
        break;
    }
    case 5: {
        
        sec6Header("3.5 | Restore Last Stable State (ECL Rollback)");
        cout << "  The Execution Control Layer (ECL) maintains a STACK of\n";
        cout << "  full system snapshots.\n";
        cout << "  Rollback = pop top snapshot and restore A2 state.  O(n)\n\n";
        ECL.displayCheckpoints();
        cout << "\n  Initiating rollback to last checkpoint...\n";
        bool ok = ECL.rollback(A2);
        if (ok) {
            cout << "\n  Restored A2 state:\n";
            A2.display();
        } else {
            cout << "  No checkpoints available. Capture one first via option 34.\n";
        }
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu4() {
    sec6Header("4. FIRE DETECTION AND CONTROL");
    cout << "   4.1  Detect Fire Risk (Threshold Check)\n";
    cout << "   4.2  Trigger Emergency Alert\n";
    cout << "   4.3  Priority-Based Fire Response\n";
    cout << "   4.4  Simulate Fire Spread (Graph BFS)\n";
    cout << "   4.5  Allocate Firefighting Resources\n";
    sec6Separator();
    cout << "   Enter sub-option (1-5): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("4.1 | Detect Fire Risk — Threshold Check");
        cout << "  Thresholds: T>" << TEMP_THRESHOLD
             << "°C  |  S>" << SMOKE_THRESHOLD
             << "  |  H<" << HUMID_THRESHOLD << "%\n\n";
        cout << left << setw(7)  << "Zone"
                     << setw(12) << "Temp(°C)"
                     << setw(10) << "Smoke"
                     << setw(12) << "Humid(%)"
                     << "Risk Level\n";
        cout << string(55, '-') << "\n";
        int totalRisk = 0;
        for (int i = 0; i < MAX_ZONES; i++) {
            bool tFire = A2.temperature[i] > TEMP_THRESHOLD;
            bool sFire = A2.smokeLevel[i]  > SMOKE_THRESHOLD;
            bool hDry  = A2.humidity[i]    < HUMID_THRESHOLD;
            string risk = "SAFE";
            if      (tFire && sFire)  { risk = "MAJOR FIRE";  totalRisk += 3; }
            else if (tFire || sFire)  { risk = "FIRE RISK";   totalRisk += 2; }
            else if (hDry)            { risk = "DRY/CAUTION"; totalRisk += 1; }
            cout << setw(7)  << i
                 << setw(12) << fixed << setprecision(1) << A2.temperature[i]
                 << setw(10) << A2.smokeLevel[i]
                 << setw(12) << A2.humidity[i]
                 << risk << "\n";
        }
        cout << "\n  Overall Forest Risk Score: " << totalRisk
             << " / " << (MAX_ZONES * 3) << "\n";
        
        cout << "\n  A3 Grid Anomaly Detection:\n";
        A3.detectAnomalies();
        break;
    }
    case 2: {
        
        sec6Header("4.2 | Trigger Emergency Alert");
        int z; double t, s;
        cout << "  Zone to alert (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "  Current temperature : "; cin >> t;
        cout << "  Current smoke level : "; cin >> s;
        
        A2.updateZone(z, t, A2.humidity[z], s);
        
        L3.insertBack(ForestEvent(t, z, "alert_trigger", "anomaly"));
        
        Q3.enqueue(Task("ALERT-Z"+to_string(z), z, "emergency", t, 1));
        
        L9.insert(ForestEvent(t, z, "emg_trigger", "emergency"));
        
        H1.insert(z, t, s, A2.humidity[z]);
        cout << "\n  [4.2] EMERGENCY ALERT TRIGGERED for Zone " << z << "\n";
        cout << "  Added to: L3-AnomalyStream, Q3-EmergencyQueue, L9-EmergencyLoop, H1\n";
        L3.display();
        Q3.display();
        break;
    }
    case 3: {
        
        sec6Header("4.3 | Priority-Based Fire Response (Q3 + DSCH)");
        cout << "  Q3 is a MIN-HEAP priority queue — lowest priority number\n";
        cout << "  is processed first.  Enqueue: O(log n)  Dequeue: O(log n)\n\n";
        cout << "  Step 1: Scan Q1 for fire-zone tasks and upgrade to Q3:\n";
        DSCH.adjustPriorities(A2, Q1, Q3);
        cout << "\n  Step 2: Current Emergency Queue (Q3):\n";
        Q3.display();
        cout << "\n  Step 3: Processing emergency tasks (priority order):\n";
        int cnt = 0;
        while (!Q3.empty()) { Q3.dequeue(); cnt++; }
        cout << "  " << cnt << " emergency tasks processed.\n";
        cout << "\n  Step 4: DSCH Load Balance Report:\n";
        DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);
        break;
    }
    case 4: {
        
        sec6Header("4.4 | Simulate Fire Spread — Graph BFS");
        int z;
        cout << "  Enter fire origin zone (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "\n  [G1] Adjacency List BFS — Time Complexity: O(V+E)\n";
        cout << "  Shows level-by-level fire spread from Zone " << z << ":\n\n";
        G1.BFS(z);
        cout << "\n  [G2] Adjacency Matrix BFS — Time Complexity: O(V²)\n";
        G2.BFS(z);
        cout << "\n  Fire-aware edge cost update (fireLevel=0.80):\n";
        cout << "  Formula: updatedCost = distance × (1 + fireLevel)\n";
        G1.updateFireCost(z, 0.80);
        cout << "\n  A3 boundary detection (shows fire spread boundaries):\n";
        A3.detectBoundaries();
        break;
    }
    case 5: {
        
        sec6Header("4.5 | Allocate Firefighting Resources");
        cout << "  Resource allocation uses Tree-based priority decisions.\n";
        cout << "  Priority = Risk × Impact  — higher score = more resources\n\n";
        cout << "  [T4] Water Resources:\n"; T[4]->display();
        cout << "\n  [T5] Fire Control Equipment:\n"; T[5]->display();
        cout << "\n  [T6] Equipment Allocation by Priority:\n"; T[6]->display();
        cout << "\n  Zone allocation summary:\n";
        struct AllocZone { int z; double risk; double impact; string resource; };
        AllocZone allocs[] = {
            { 3, 0.90, 0.85, "Helicopter (aerial water drop)" },
            { 4, 0.70, 0.80, "FireTruck  (ground suppression)" },
            { 6, 0.45, 0.50, "ManualCrew (controlled burn)"   }
        };
        cout << left << setw(7) << "Zone" << setw(10) << "Risk"
             << setw(10) << "Impact" << setw(12) << "Score" << "Resource\n";
        cout << string(55, '-') << "\n";
        for (int ai = 0; ai < 3; ai++) {
            double score = allocs[ai].risk * allocs[ai].impact;
            cout << setw(7) << allocs[ai].z << setw(10) << allocs[ai].risk
                 << setw(10) << allocs[ai].impact
                 << setw(12) << fixed << setprecision(2) << score
                 << allocs[ai].resource << "\n";
        }
        
        Q4.enqueue(Task("RES-Z3", 3, "resource_alloc", 0.77, 1));
        Q4.enqueue(Task("RES-Z4", 4, "resource_alloc", 0.56, 2));
        cout << "\n  Resource tasks added to Q4-MultiFactorDecision.\n";
        Q4.display();
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu5() {
    sec6Header("5. TASK SCHEDULING SYSTEM");
    cout << "   5.1  Add Routine Task (Queue)\n";
    cout << "   5.2  Add Surveillance Task\n";
    cout << "   5.3  Add Emergency Task (Priority Queue)\n";
    cout << "   5.4  Process Tasks (FIFO / Priority)\n";
    cout << "   5.5  Pause and Resume Tasks\n";
    sec6Separator();
    cout << "   Enter sub-option (1-5): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("5.1 | Add Routine Task — Q1 (FIFO)");
        cout << "  Q1 is a standard FIFO queue.\n";
        cout << "  Enqueue: O(1)  |  Dequeue: O(1)\n\n";
        int z; double v;
        cout << "  Zone (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "  Value (sensor reading): "; cin >> v;
        Q1.enqueue(Task("RTN-Z"+to_string(z), z, "routine", v, 3));
        cout << "\n  Q1 current state:\n";
        Q1.display();
        break;
    }
    case 2: {
        
        sec6Header("5.2 | Add Surveillance Task — Q2");
        cout << "  Q2 handles high-frequency surveillance zone updates.\n";
        cout << "  Enqueue: O(1)  |  Dequeue: O(1)\n\n";
        int z; double v;
        cout << "  Zone (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "  Surveillance reading : "; cin >> v;
        Q2.enqueue(Task("SRV-Z"+to_string(z), z, "surveillance", v, 2));
        cout << "\n  Q2 current state:\n";
        Q2.display();
        break;
    }
    case 3: {
        
        sec6Header("5.3 | Add Emergency Task — Q3 (Priority Queue)");
        cout << "  Q3 is a MIN-HEAP priority queue.\n";
        cout << "  Lower priority number = processed FIRST.\n";
        cout << "  Enqueue: O(log n)  |  Dequeue: O(log n)\n\n";
        int z, p; double v;
        cout << "  Zone (0-" << MAX_ZONES-1 << ")        : "; cin >> z;
        cout << "  Value (sensor reading)  : "; cin >> v;
        cout << "  Priority (1=highest, 3=lowest): "; cin >> p;
        Q3.enqueue(Task("EMG-Z"+to_string(z), z, "emergency", v, p));
        cout << "\n  Q3 current state (priority order):\n";
        Q3.display();
        break;
    }
    case 4: {
        
        sec6Header("5.4 | Process Tasks (FIFO / Priority Dequeue)");
        cout << "  Which queue to process?\n";
        cout << "  [1] Q1-Routine (FIFO)    [2] Q2-Surveillance (FIFO)\n";
        cout << "  [3] Q3-Emergency (PQ)    [4] Q4-MultiDecision (FIFO)\n";
        cout << "  [5] Process ALL queues\n";
        cout << "  Choice: ";
        int qc = readChoice();
        auto processQ = [](ForestQueue& q) {
            if (q.empty()) { cout << "  Queue empty.\n"; return; }
            int cnt = 0;
            while (!q.empty()) { q.dequeue(); cnt++; }
            cout << "  Processed " << cnt << " tasks.\n";
        };
        auto processEQ = [](EmergencyQueue& q) {
            if (q.empty()) { cout << "  Queue empty.\n"; return; }
            int cnt = 0;
            while (!q.empty()) { q.dequeue(); cnt++; }
            cout << "  Processed " << cnt << " emergency tasks.\n";
        };
        switch (qc) {
            case 1: cout << "\n  Processing Q1 (FIFO):\n"; processQ(Q1); break;
            case 2: cout << "\n  Processing Q2 (FIFO):\n"; processQ(Q2); break;
            case 3: cout << "\n  Processing Q3 (Priority):\n"; processEQ(Q3); break;
            case 4: cout << "\n  Processing Q4 (FIFO):\n"; processQ(Q4); break;
            case 5:
                cout << "\n  Processing ALL queues:\n";
                processEQ(Q3);
                processQ(Q1);
                processQ(Q2);
                processQ(Q4);
                break;
            default: cout << "  Invalid.\n";
        }
        cout << "\n  Post-process load report:\n";
        DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);
        break;
    }
    case 5: {
        
        sec6Header("5.5 | Pause and Resume Task Execution (ECL)");
        cout << "  The Execution Control Layer manages pause/resume.\n";
        cout << "  When paused: critical Q3 tasks can still be dispatched;\n";
        cout << "  low-priority Q1/Q2 tasks are held.\n\n";
        cout << "  Current ECL status:\n";
        ECL.displayStatus();
        cout << "\n  [1] Pause execution   [2] Resume execution\n";
        cout << "  Choice: ";
        int pc = readChoice();
        if (pc == 1) {
            ECL.pauseExecution("Manual pause via menu 5.5");
            cout << "\n  Execution paused. Q3 still accepts emergency tasks.\n";
            cout << "  Low-priority Q1/Q2 are held until resume.\n";
        } else if (pc == 2) {
            ECL.resumeExecution();
            cout << "\n  Execution resumed. All queues active.\n";
        } else {
            cout << "  Invalid choice.\n";
        }
        cout << "\n  Updated ECL status:\n";
        ECL.displayStatus();
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu6() {
    sec6Header("6. DECISION SYSTEM");
    cout << "   6.1  Compute Risk Score\n";
    cout << "   6.2  Zone-Level Decision Tree\n";
    cout << "   6.3  Regional Decision Processing\n";
    cout << "   6.4  Global Emergency Decision\n";
    cout << "   6.5  Execute Final Action\n";
    sec6Separator();
    cout << "   Enter sub-option (1-5): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("6.1 | Compute Risk Score");
        cout << "  Formula: Score = w1*fire + w2*smoke + w3*temp\n";
        cout << "  If Score > threshold => Emergency Activated\n";
        cout << "  Time Complexity: O(1)\n\n";
        double fire, smoke, temp, w1, w2, w3, thr;
        cout << "  fire  (0.0-1.0): "; cin >> fire;
        cout << "  smoke (0.0-1.0): "; cin >> smoke;
        cout << "  temp  (0.0-1.0): "; cin >> temp;
        cout << "  w1 (fire weight)  : "; cin >> w1;
        cout << "  w2 (smoke weight) : "; cin >> w2;
        cout << "  w3 (temp weight)  : "; cin >> w3;
        cout << "  threshold          : "; cin >> thr;
        cout << "\n  Computing...\n";
        bool em = T[7]->evaluateDecision(fire, smoke, temp, w1, w2, w3, thr);
        cout << "  Result: " << (em ? "EMERGENCY ACTIVATED" : "Normal — continue monitoring") << "\n";
        break;
    }
    case 2: {
        
        sec6Header("6.2 | Zone-Level Decision Tree (T10)");
        cout << "  T10 handles LOCAL zone decisions.\n";
        cout << "  Rule: Risk > 0.6 => Activate Local Response\n";
        cout << "  Tree traversal: O(n) pre-order\n\n";
        T[10]->display();
        cout << "\n  Evaluating current zone conditions from A2:\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            if (A2.fireSignal[i]) {
                double nT = A2.temperature[i] / 100.0;
                double nS = A2.smokeLevel[i]  / 100.0;
                cout << "  Zone " << i << ": ";
                T[10]->evaluateDecision(nT, nS, nT, 0.4, 0.3, 0.3, 0.6);
            }
        }
        break;
    }
    case 3: {
        
        sec6Header("6.3 | Regional Decision Processing (T11)");
        cout << "  T11 handles REGIONAL escalation decisions.\n";
        cout << "  Rule: FireSpreadRate > 0.5 => Escalate to neighbouring zones\n\n";
        T[11]->display();
        cout << "\n  Enter measured fire spread rate (0.0-1.0): ";
        double sr; cin >> sr;
        cout << "\n  Evaluating regional decision (spreadRate=" << sr << "):\n";
        bool reg = T[11]->evaluateDecision(sr, 0.65, 0.70, 0.4, 0.3, 0.3, 0.6);
        if (reg) {
            cout << "  => REGIONAL ESCALATION: alerting neighbouring zones.\n";
            Q3.enqueue(Task("REG-ESC", -1, "regional", sr, 1));
        } else {
            cout << "  => Fire spread contained at local level.\n";
        }
        break;
    }
    case 4: {
        
        sec6Header("6.4 | Global Emergency Decision (T12)");
        cout << "  T12 is the GLOBAL COMMAND tree.\n";
        cout << "  Rule: Sum(RiskZones) > Threshold => GLOBAL ALERT\n\n";
        T[12]->display();
        
        double globalFire = 0, globalSmoke = 0, globalTemp = 0;
        for (int i = 0; i < MAX_ZONES; i++) {
            globalFire  += (A2.fireSignal[i] ? 1.0 : 0.0);
            globalSmoke += A2.smokeLevel[i] / 100.0;
            globalTemp  += A2.temperature[i] / 100.0;
        }
        globalFire  /= MAX_ZONES;
        globalSmoke /= MAX_ZONES;
        globalTemp  /= MAX_ZONES;
        cout << "\n  Computed global averages from A2:\n";
        cout << "  fireRatio=" << fixed << setprecision(2) << globalFire
             << "  avgSmoke=" << globalSmoke
             << "  avgTemp=" << globalTemp << "\n\n";
        bool ga = T[12]->evaluateDecision(globalFire, globalSmoke, globalTemp,
                                          0.4, 0.3, 0.3, 0.5);
        if (ga) {
            cout << "\n  ╔══════════════════════════════════════╗\n";
            cout << "  ║  *** GLOBAL EMERGENCY ACTIVATED ***  ║\n";
            cout << "  ╚══════════════════════════════════════╝\n";
        } else {
            cout << "  Global conditions within manageable limits.\n";
        }
        break;
    }
    case 5: {
        
        sec6Header("6.5 | Execute Final Action");
        cout << "  Final action pipeline:\n";
        cout << "  (1) Process all pending emergency tasks from Q3\n";
        cout << "  (2) Update H1 hash table with latest confirmed data\n";
        cout << "  (3) Synchronize L6 state chain\n";
        cout << "  (4) Run AMON full health report\n\n";
        
        cout << "  Step 1 — Dispatching emergency tasks:\n";
        int cnt = 0;
        while (!Q3.empty()) { Q3.dequeue(); cnt++; }
        cout << "  " << cnt << " tasks dispatched.\n";
        
        cout << "\n  Step 2 — Updating H1 hash table:\n";
        for (int i = 0; i < MAX_ZONES; i++)
            if (A2.fireSignal[i])
                H1.insert(i, A2.temperature[i],
                          A2.smokeLevel[i], A2.humidity[i]);
        
        cout << "\n  Step 3 — L6 State Synchronization:\n";
        for (int i = 0; i < MAX_ZONES; i++)
            L6.insertBack(ForestEvent(A2.temperature[i], i,
                                     "final_action", "sync"));
        L6.display();
        
        cout << "\n  Step 4 — Adaptive Monitor Report:\n";
        AMON.generateFullReport(SYS);
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu7() {
    sec6Header("7. SPATIAL ROUTING SYSTEM");
    cout << "   7.1  Load Graph (Adjacency List)\n";
    cout << "   7.2  Load Graph (Adjacency Matrix)\n";
    cout << "   7.3  BFS Traversal (Fire Spread)\n";
    cout << "   7.4  DFS Traversal (Deep Analysis)\n";
    cout << "   7.5  Compute Safe Path\n";
    cout << "   7.6  Update Blocked Routes\n";
    sec6Separator();
    cout << "   Enter sub-option (1-6): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("7.1 | Load & Display Graph (Adjacency List — G1)");
        cout << "  G1 stores connections as per-node neighbour lists.\n";
        cout << "  Space: O(V+E)  |  Edge lookup: O(degree)  |  BFS/DFS: O(V+E)\n\n";
        G1.display();
        break;
    }
    case 2: {
        
        sec6Header("7.2 | Load & Display Graph (Adjacency Matrix — G2)");
        cout << "  G2 stores connections in a V×V matrix.\n";
        cout << "  Space: O(V²)  |  Edge lookup: O(1)  |  BFS: O(V²)\n\n";
        G2.display();
        break;
    }
    case 3: {
        
        sec6Header("7.3 | BFS Traversal — Fire Spread Simulation");
        int z;
        cout << "  Fire origin zone (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "\n  [G1] Adjacency List BFS  Time Complexity: O(V+E)\n";
        cout << "  Shows level-by-level spread (each level = 1 time step):\n\n";
        G1.BFS(z);
        cout << "\n  [G2] Adjacency Matrix BFS  Time Complexity: O(V²)\n";
        G2.BFS(z);
        break;
    }
    case 4: {
        
        sec6Header("7.4 | DFS Traversal — Deep Path Analysis");
        int z;
        cout << "  Start zone (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "\n  [G1] Adjacency List DFS  Time Complexity: O(V+E)\n";
        cout << "  Explores one path deeply before backtracking:\n\n";
        G1.runDFS(z);
        break;
    }
    case 5: {
        
        sec6Header("7.5 | Compute Safe Path Costs");
        cout << "  Path cost formula: Distance + Danger\n";
        cout << "  Fire-aware cost:   Distance × (1 + fireLevel)\n\n";
        cout << "  Current adjacency list with edge costs:\n";
        G1.display();
        cout << "\n  Path cost analysis from each zone (G1 DFS edge costs):\n";
        cout << "  Zones with high fire levels have increased edge costs.\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            if (A2.fireSignal[i]) {
                cout << "\n  Zone" << i << " is a fire zone — its edges are blocked:\n";
                
                for (int ej = 0; ej < G1.adjSize[i]; ej++)
                    cout << "    Zone" << i << "-Zone" << G1.adj[i][ej].dest
                         << " cost=" << fixed << setprecision(1) << G1.adj[i][ej].cost << "\n";
            }
        }
        break;
    }
    case 6: {
        
        sec6Header("7.6 | Update Blocked Routes (Fire-Aware Cost Update)");
        int z; double fl;
        cout << "  Zone with fire (0-" << MAX_ZONES-1 << "): "; cin >> z;
        cout << "  Fire level (0.0-1.0)              : "; cin >> fl;
        cout << "\n  Updating edge costs for Zone " << z
             << " (fireLevel=" << fl << "):\n";
        cout << "  Formula: newCost = oldCost × (1 + fireLevel)\n\n";
        G1.updateFireCost(z, fl);
        cout << "\n  Updated G1 adjacency list:\n";
        G1.display();
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu8() {
    sec6Header("8. HASH-BASED FAST ACCESS SYSTEM");
    cout << "   8.1  Insert Data (Hash Table)\n";
    cout << "   8.2  Retrieve Data (O(1) Access)\n";
    cout << "   8.3  Handle Collisions\n";
    cout << "   8.4  Update Cache\n";
    cout << "   8.5  View Index Table\n";
    sec6Separator();
    cout << "   Enter sub-option (1-5): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("8.1 | Insert Data — H1 Primary Hash Table");
        cout << "  Hash Function: index = ZoneID mod " << HASH_SIZE << "\n";
        cout << "  Collision: Linear probing  |  Avg: O(1)  |  Worst: O(n)\n\n";
        int z; double t, s, h;
        cout << "  Zone ID (key)        : "; cin >> z;
        cout << "  Temperature          : "; cin >> t;
        cout << "  Smoke Level          : "; cin >> s;
        cout << "  Humidity             : "; cin >> h;
        cout << "\n  Computing hash: " << z << " mod " << HASH_SIZE
             << " = " << (z % HASH_SIZE) << "\n\n";
        H1.insert(z, t, s, h);
        H2.insert(z, t, s, h);
        cout << "\n  H1 state after insert:\n";
        H1.display();
        break;
    }
    case 2: {
        
        sec6Header("8.2 | Retrieve Data — O(1) Average Access");
        int z;
        cout << "  Zone ID to retrieve: "; cin >> z;
        cout << "\n  Hash index = " << z << " mod " << HASH_SIZE
             << " = " << (z % HASH_SIZE) << "\n";
        cout << "\n  [H1] Primary hash lookup (open addressing):\n";
        HashEntry* e1 = H1.search(z);
        if (e1)
            cout << "  FOUND — Zone=" << e1->key
                 << "  T=" << e1->temp
                 << "  S=" << e1->smoke
                 << "  H=" << e1->humidity << "\n";
        else
            cout << "  NOT FOUND in H1.\n";
        cout << "\n  [H3] Fast cache lookup (O(1)):\n";
        H3.get(z);
        break;
    }
    case 3: {
        
        sec6Header("8.3 | Collision Handling — H2 Separate Chaining");
        cout << "  H2 uses SEPARATE CHAINING: each bucket holds a linked list\n";
        cout << "  of all entries that hash to the same index.\n";
        cout << "  Avg: O(1)  |  Worst (all in one bucket): O(n)\n\n";
        cout << "  Demonstrating collision: Zones 0 and 11 both map to bucket 0\n";
        H2.insert(0,  25.0, 5.0,  60.0);   
        H2.insert(11, 30.0, 12.0, 55.0);   
        cout << "\n  H2 chaining table (collision in bucket 0):\n";
        H2.display();
        break;
    }
    case 4: {
        
        sec6Header("8.4 | Update Cache — H3 Fast Retrieval Cache");
        cout << "  H3 stores recently accessed zone data for repeated queries.\n";
        cout << "  Put: O(1)  |  Get: O(1)  |  Uses recency tick for tracking\n\n";
        cout << "  Caching all currently fire-active zones:\n";
        for (int i = 0; i < MAX_ZONES; i++) {
            if (A2.fireSignal[i] || A2.temperature[i] > TEMP_THRESHOLD) {
                H3.put(i, A2.temperature[i],
                       A2.smokeLevel[i], A2.humidity[i]);
            }
        }
        cout << "\n  Verifying cache with repeated access:\n";
        for (int i = 0; i < MAX_ZONES; i++)
            if (A2.fireSignal[i]) H3.get(i);
        cout << "\n  H3 cache state:\n";
        H3.display();
        break;
    }
    case 5: {
        
        sec6Header("8.5 | View Index Table — All Hash Structures");
        cout << "  H1 — Primary Hash Table (open addressing, linear probing):\n";
        H1.display();
        cout << "\n  H2 — Collision Handling Table (separate chaining):\n";
        H2.display();
        cout << "\n  H3 — Fast Retrieval Cache (recency-based):\n";
        H3.display();
        cout << "\n  Summary:\n";
        cout << "  H1 table size: " << HASH_SIZE
             << "  |  entries: " << H1.count << "\n";
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu9() {
    sec6Header("9. SYSTEM MONITORING");
    cout << "   9.1  Monitor System Load\n";
    cout << "   9.2  Track Execution Time\n";
    cout << "   9.3  Detect Bottlenecks\n";
    cout << "   9.4  Optimize Performance\n";
    cout << "   9.5  View System Health\n";
    sec6Separator();
    cout << "   Enter sub-option (1-5): ";
    int sub = readChoice();

    switch (sub) {
    case 1: {
        
        sec6Header("9.1 | Monitor System Load (SYS + DSCH)");
        cout << "  Base system module loads:\n";
        SYS.display();
        cout << "\n  Queue load distribution (DSCH):\n";
        DSCH.loadBalanceReport(Q1, Q2, Q3, Q4);
        cout << "\n  Update load metrics? [1=Yes 2=No]: ";
        if (readChoice() == 1) {
            cout << "  Enter new latency and load for each module (ms, %):\n";
            string names[6] = {"Arrays","LinkedLists","Queues",
                               "Trees","Graphs","HashTables"};
            for (int i = 0; i < 6; i++) {
                double lat, ld;
                cout << "  " << names[i] << " — latency(ms): "; cin >> lat;
                cout << "  " << names[i] << " — load(%):     "; cin >> ld;
                SYS.update(i, lat, ld);
            }
            cout << "\n  Updated metrics:\n";
            SYS.display();
        }
        break;
    }
    case 2: {
        
        sec6Header("9.2 | Track Execution Time — ECL Step Log");
        cout << "  The ECL step log records every processing step with\n";
        cout << "  before/after values enabling full audit of execution.\n";
        cout << "  Latency formula: FinishTime - StartTime\n\n";
        ECL.displayStepLog();
        cout << "\n  ECL summary:\n";
        ECL.displayStatus();
        break;
    }
    case 3: {
        
        sec6Header("9.3 | Detect Bottlenecks (AMON)");
        cout << "  Stress score = (latency / critLimit) + (load / 100)\n";
        cout << "  Highest stress score = bottleneck module\n\n";
        int bn = AMON.detectBottleneck(SYS);
        cout << "\n  Bottleneck module index: " << bn << "\n";
        string names[6] = {"Arrays","LinkedLists","Queues",
                            "Trees","Graphs","HashTables"};
        cout << "  Bottleneck module name : " << names[bn] << "\n";
        cout << "  Latency: " << SYS.latency[bn]
             << " ms  |  Load: " << SYS.load[bn] << "%\n";
        break;
    }
    case 4: {
        
        sec6Header("9.4 | Optimize Performance (AMON)");
        cout << "  Step 1 — Detect bottleneck:\n";
        int bn = AMON.detectBottleneck(SYS);
        cout << "\n  Step 2 — Redistribute load (offload 15% from bottleneck):\n";
        AMON.redistributeLoad(SYS, bn);
        cout << "\n  Step 3 — Tune thresholds dynamically:\n";
        AMON.tuneThresholds(SYS);
        cout << "\n  Step 4 — Post-optimization metrics:\n";
        SYS.display();
        cout << "\n  Step 5 — Rebalance task queues (DSCH):\n";
        DSCH.rebalanceQueues(Q1, Q2);
        break;
    }
    case 5: {
        
        sec6Header("9.5 | View System Health — Full AMON Report");
        cout << "  Comprehensive health report with adaptive thresholds,\n";
        cout << "  bottleneck analysis, and full tuning history.\n\n";
        AMON.generateFullReport(SYS);
        cout << "\n  ECL execution health:\n";
        ECL.displayStatus();
        cout << "\n  Dynamic Scheduler health:\n";
        cout << "  Rebalance operations performed: "
             << DSCH.rebalanceCount << "\n";
        cout << "  Priority upgrades performed   : "
             << DSCH.priorityUpgrades << "\n";
        break;
    }
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void handleMenu10() {
    sec6Header("10. SCENARIO SIMULATION");
    cout << "   10.1  Cascading Fire Scenario\n";
    cout << "   10.2  Sensor Failure & Reconstruction Scenario\n";
    cout << "   10.3  Multi-Factor Anomaly Escalation Scenario\n";
    cout << "   10.4  System Overload & Load Redistribution Scenario\n";
    cout << "   10.5  Global Multi-Zone Emergency Synchronization\n";
    cout << "   10.6  Run Full System Simulation (All 6 Scenarios)\n";
    sec6Separator();
    cout << "   Enter sub-option (1-6): ";
    int sub = readChoice();

    switch (sub) {
    case 1:
        cout << "\n  Launching Scenario 1: Cascading Fire & "
                "Resource Conflict Resolution\n";
        scenario1();
        break;
    case 2:
        cout << "\n  Launching Scenario 2: Sensor Failure & "
                "System Reconstruction\n";
        scenario2();
        break;
    case 3:
        cout << "\n  Launching Scenario 3: Multi-Factor Anomaly "
                "Escalation System\n";
        scenario3();
        break;
    case 4:
        cout << "\n  Launching Scenario 4: System Overload & "
                "Load Redistribution\n";
        scenario4();
        break;
    case 5:
        cout << "\n  Launching Scenario 5: Global Multi-Zone "
                "Emergency Synchronization\n";
        scenario5();
        break;
    case 6:
        cout << "\n  Launching Full System Simulation (All 6 Scenarios):\n";
        cout << string(62, '=') << "\n";
        scenario1();
        scenario2();
        scenario3();
        scenario4();
        scenario5();
        scenario6();
        cout << "\n" << string(62, '=') << "\n";
        cout << "  FULL SYSTEM SIMULATION COMPLETE\n";
        cout << string(62, '=') << "\n";
        break;
    default:
        cout << "  Invalid sub-option.\n";
    }
}

void displayMainMenu() {
    cout << "\n" << string(62, '=') << "\n";
    cout << "   IFAMDS  |  Intelligent Forest Advisory & Multi-Structure\n";
    cout << "            |  Decision System  [MAIN MENU]\n";
    cout << string(62, '=') << "\n";
    cout << "   1.  Input Environmental Data\n";
    cout << "   2.  View Forest Grid Status\n";
    cout << "   3.  Event Memory System\n";
    cout << "   4.  Fire Detection and Control\n";
    cout << "   5.  Task Scheduling System\n";
    cout << "   6.  Decision System\n";
    cout << "   7.  Spatial Routing System\n";
    cout << "   8.  Hash-Based Fast Access System\n";
    cout << "   9.  System Monitoring\n";
    cout << "   10. Scenario Simulation\n";
    cout << string(62, '-') << "\n";
    cout << "   0.  Exit System\n";
    cout << string(62, '=') << "\n";
    cout << "   Enter choice: ";
}

void displaySplash() {
    cout << "\nInitializing all data structures...\n";
}

int main() {
    
    displaySplash();

    
    initializeSystem();

    
    int sessMenuOps    = 0;  
    int sessScenarios  = 0;  

    
    int choice = -1;
    while (choice != 0) {
        displayMainMenu();
        choice = readChoice();

        switch (choice) {
            case 1:  handleMenu1();  sessMenuOps++; break;
            case 2:  handleMenu2();  sessMenuOps++; break;
            case 3:  handleMenu3();  sessMenuOps++; break;
            case 4:  handleMenu4();  sessMenuOps++; break;
            case 5:  handleMenu5();  sessMenuOps++; break;
            case 6:  handleMenu6();  sessMenuOps++; break;
            case 7:  handleMenu7();  sessMenuOps++; break;
            case 8:  handleMenu8();  sessMenuOps++; break;
            case 9:  handleMenu9();  sessMenuOps++; break;
            case 10:
                handleMenu10();
                sessMenuOps++;
                sessScenarios++;
                break;
            case 0:
                
                cout << "\n" << string(62, '=') << "\n";
                cout << "  IFAMDS SESSION SUMMARY\n";
                cout << string(62, '-') << "\n";
                cout << "  Menu operations performed  : " << sessMenuOps  << "\n";
                cout << "  Scenario runs triggered    : " << sessScenarios << "\n";
                cout << "  ECL steps logged           : " << ECL.stepLog.size() << "\n";
                cout << "  ECL checkpoints remaining  : " << ECL.checkpointStack.size() << "\n";
                cout << "  DSCH priority upgrades     : " << DSCH.priorityUpgrades << "\n";
                cout << "  DSCH rebalance ops         : " << DSCH.rebalanceCount << "\n";
                cout << "  AMON tuning adjustments    : " << AMON.histSize << "\n";
                cout << "  H1 hash entries            : " << H1.count << "\n";
                cout << string(62, '-') << "\n";
                cout << "  Final system health:\n";
                SYS.display();
                cout << string(62, '=') << "\n";
                cout << "  IFAMDS shutdown complete. Goodbye.\n";
                cout << string(62, '=') << "\n";
                break;
            default:
                cout << "\n  Invalid choice. Please enter 0-10.\n";
        }
    }

    
    for (int i = 1; i <= 12; i++) delete T[i];
    return 0;
}
