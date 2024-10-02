#include<iostream>
#include <stdexcept>

class Queue {
    private:
        int* arr;
        size_t capacity;
        size_t hd;
        size_t tl;
        const float scale_factor = 1.5;

    public:
        size_t size;

        // Constructor
        Queue() {
            capacity = 4;
            arr = new int[capacity];
            hd = 0;
            tl = 0;
            size = 0;
        }

        //Destructor
        ~Queue() {
            delete[] arr;
        }

        void resize() {
            size_t new_capacity = capacity * scale_factor;
            int* new_arr = new int[new_capacity];
            for (size_t new_ix = 0; new_ix < capacity; new_ix++) {
                size_t ix = (hd + new_ix) % capacity;
                new_arr[new_ix] = arr[ix];
            }
            hd = 0;
            tl = capacity - 1;
            capacity = new_capacity;
            delete[] arr;
            arr = new_arr;
        }

        void push(int val) {
            if (size == 0) {
                arr[tl] = val;
                size = 1;
                return;
            }
            if ((tl + 1) % capacity == hd) {
                resize();
            }
            tl = (tl + 1) % capacity;
            arr[tl] = val;   
            size += 1;
        }

        int pop() {
            if (size == 0) {
                std::runtime_error("queue is empty, cannot pop");
            }
            int val = arr[hd];
            if (hd != tl) {
                hd = (hd + 1) % capacity;
            }
            size -= 1;
            return val;
        }

        bool empty() {
            return (size > 0);
        }

        void debug() {
            std::cout << "hd=" << hd << "|tl=" << tl << "|cap=" << capacity << "|size=" << size << "\n";
        }

        friend std::ostream& operator<<(std::ostream& os, const Queue& obj);
};

std::ostream& operator<<(std::ostream& os, const Queue& obj)
{
    if (obj.size == 0) {
        std::cout << "[]";
        return os;
    }
    std::cout << "[";
    for (size_t i = 0; i < obj.size - 1; i++) {
        size_t ix = (obj.hd + i) % obj.capacity;
        std::cout << obj.arr[ix] << ",";
    }
    std::cout << obj.arr[obj.tl] << "]";
    return os;
}

int main() {
    Queue queue = Queue();
    queue.debug();
    for (int i = 0; i < 5; i++) {
        queue.push(i);
        std::cout << queue << "\n";
    }
    queue.debug();
    for (int i = 0; i < 5; i++) {
        queue.pop();
        std::cout << queue << "\n";
    }
    queue.debug();
    for (int i = 0; i < 5; i++) {
        queue.push(i);
        std::cout << queue << "\n";
    }
    queue.debug();
    return 0;
}
