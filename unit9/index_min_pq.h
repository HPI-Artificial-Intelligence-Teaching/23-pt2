/******************************************************************************
 *
 * Min oriented indexed priority queue implementation using a binary heap
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __INDEX_MIN_PQ_H__
#define __INDEX_MIN_PQ_H__

#include <stdexcept>

using namespace std;

// Implements a min oriented indexed priority queue using a binary heap
template <typename T>
class IndexMinPQ {
    int n;         // number of items on priority queue
    int capacity;  // total capacity of the heap
    int* pq;       // binary heap using 1-based indexing
    int* qp;       // inverse of pq such that qp[pq[i]] = pq[qp[i]] = i
    T* keys;       // keys[i] = priority of i

    // swims up from index pq[k] in the heap
    void swim(int k) {
        while (k > 1 && keys[pq[k / 2]] > keys[pq[k]]) {
            exch(k / 2, k);
            k = k / 2;
        }
        return;
    }

    // sinks down from index pq[k] in the heap
    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && keys[pq[j]] > keys[pq[j + 1]]) j++;
            if (!(keys[pq[k]] > keys[pq[j]])) break;
            exch(k, j);
            k = j;
        }
        return;
    }

    // swaps the priority entry at level pq[i] and pq[j]
    void exch(const int i, const int j) {
        int swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
        return;
    }

   public:
    // constructor
    IndexMinPQ(const int _capacity = 1) : capacity(_capacity),
                                          n(0) {
        keys = new T[capacity + 1];
        pq = new int[capacity + 1];
        qp = new int[capacity + 1];
        for (auto i = 0; i <= capacity; i++) qp[i] = -1;
    }

    // copy constructor
    IndexMinPQ(const IndexMinPQ& mq) : capacity(mq.capacity),
                                       n(mq.n) {
        keys = new T[capacity + 1];
        pq = new int[capacity + 1];
        qp = new int[capacity + 1];
        for (auto i = 0; i <= capacity; i++) {
            keys[i] = mq.keys[i];
            pq[i] = mq.pq[i];
            qp[i] = mq.qp[i];
        }
    }

    // move constructor
    IndexMinPQ(IndexMinPQ&& mq) : capacity(mq.capacity),
                        n(mq.n),
                        keys(mq.keys),
                        pq(mq.pq),
                        qp(mq.qp) {
        mq.capacity = 0;
        mq.n = 0;
        mq.keys = nullptr;
        mq.pq = nullptr;
        mq.qp = nullptr;
    }

    // copy assignment
    IndexMinPQ& operator=(const IndexMinPQ& mq) {
        // free the existing indexed priority queue
        delete[] keys;
        delete[] pq;
        delete[] qp;

        // copy the indexed priority queue passed in
        capacity = mq.capacity;
        n = mq.n;
        keys = new T[capacity + 1];
        pq = new int[capacity + 1];
        qp = new int[capacity + 1];
        for (auto i = 0; i <= capacity; i++) {
            keys[i] = mq.keys[i];
            pq[i] = mq.pq[i];
            qp[i] = mq.qp[i];
        }

        return (*this);
    }

    // move assignment
    IndexMinPQ& operator=(IndexMinPQ&& mq) {
        // free the existing indexed priority queue
        delete[] keys;
        delete[] pq;
        delete[] qp;

        // shallow copy of priority queue
        capacity = mq.capacity;
        n = mq.n;
        keys = mq.keys;
        pq = mq.pq;
        qp = mq.qp;

        // remove the priority queue passed in
        mq.capacity = 0;
        mq.n = 0;
        mq.keys = nullptr;
        mq.pq = nullptr;
        mq.qp = nullptr;

        return (*this);
    }

    // destructor
    ~IndexMinPQ() {
        delete[] keys;
        delete[] pq;
        delete[] qp;
    }

    // returns true if this indexed priority queue is empty
    bool is_empty() const {
        return (n == 0);
    }

    // returns whether i is an index on this priority queue
    bool contains(const int i) const {
        return (qp[i] != -1);
    }

    // returns the number of keys on this priority queue
    int size() const {
        return (n);
    }

    // returns the key associated with index i
    const T& key_of(const int i) const {
        if (!contains(i)) 
            throw logic_error("index is not in the priority queue");
        else 
            return keys[i];
    }

    // returns the index associated with the minimum key
    int min_index() const {
        if (is_empty()) throw logic_error("Priority queue underflow");
        return (pq[1]);
    }

    // returns the minimum key
    const T& min_key() const {
        if (is_empty()) throw logic_error("Priority queue underflow");
        return (keys[pq[1]]);
    }

    // associates key with index i
    void insert(const int i, const T& key) {
        if (contains(i)) throw logic_error("index is already in the priority queue");

        // add x, and percolate it up to maintain heap invariant
        n++;
        qp[i] = n;
        pq[n] = i;
        keys[i] = key;
        swim(n);

        return;
    }

    // change the key associated with index i to the specified value
    void change_key(const int i, const T& key) {
        if (!contains(i)) throw logic_error("index is not in the priority queue");

        keys[i] = key;
        swim(qp[i]);
        sink(qp[i]);

        return;
    }

    // decrease the key associated with index i to the specified value
    void decrease_key(const int i, const T& key) {
        if (!contains(i)) throw logic_error("index is not in the priority queue");
        if (keys[i] == key) throw logic_error("calling decrease_key() with a key equal to the key in the priority queue");
        if (keys[i] < key) throw logic_error("calling decrease_key() with a key strictly greater than the key in the priority queue");

        keys[i] = key;
        swim(qp[i]);

        return;
    }

    // increase the key associated with index i to the specified value
    void increase_key(const int i, const T& key) {
        if (!contains(i)) throw logic_error("index is not in the priority queue");
        if (keys[i] == key) throw logic_error("calling increase_key() with a key equal to the key in the priority queue");
        if (keys[i] > key) throw logic_error("calling increase_key() with a key strictly less than the key in the priority queue");

        keys[i] = key;
        sink(qp[i]);

        return;
    }

    // removes a minimum key and returns its associated index
    int del_min() {
        if (is_empty()) throw logic_error("Priority queue underflow");
        int min = pq[1];
        exch(1, n--);
        sink(1);
        qp[min] = -1;
        pq[n+1] = -1;

        return min;
    }

    // removes the key associated with index i
    void del(const int i) {
        if (!contains(i)) throw logic_error("index is not in the priority queue");
        int index = qp[i];
        exch(index, n--);
        swim(index);
        sink(index);
        qp[i] = -1;

        return;
    }
};

#endif