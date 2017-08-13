#pragma once
extern "C" void lock_mutex(void *);
extern "C" void unlock_mutex(void *);
template<typename T>
class mutex {
    public:
        int lock;
        T value;
        mutex(): lock(0) {}
        mutex(T value): lock(0), value(value) {}
        mutex(T &value): lock(0), value(value) {}

        void operator++(int) {
            lock_mutex(&lock);
        }
        void operator--(int) {
            unlock_mutex(&lock);
        }
        T &operator*() {
            return value;
        }
        T *operator->() {
            return &value;
        }
        ~mutex() {}
};
