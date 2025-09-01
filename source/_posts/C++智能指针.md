# C++智能指针
## 种类
三种。
1. unique_ptr<>
    1. 不能复制，只能移动
    2. 独占资源管理
    3. make_unique<T>(args…)创建
2. shared_ptr<>
    1. 引用计数，多个shared_ptr共享同一对象，最后一个销毁时释放资源
    2. 存在循环引用风险，需要weak_ptr
    3. make_unique<T>(args…)创建
3. weak_ptr<>
    1. 依赖share_ptr，不会增加技术
    2. 解决循环引用的问题
    3. 可通过lock()获取shared_ptr，判断object是否有效

## Make_shared的优势
make_shared相比shared_ptr<T>(new)有什么好处？
1. 避免额外的内存分配，make_shared会在一次内存分配中同时分配对象本体和引用计数，而后者需要两次分配，一次给T，一次给shared_ptr控制块。
2. 减少异常安全问题，两个是独立的操作，new可能抛出异常，而shared_ptr还未构造，造成内存泄露。make_shared进行的是原子操作，不存在问题
3. 更高效的引用计数管理，减少cache mis，提高运行效率。
4. 代码更简洁。



## 自定义实现shared_ptr
```cpp
#include <iostream>
using namespace std;

// Operations for reference counting
template<typename T>
class ShareCount {
    private:
        T * ptr; // Point to the actual object
        int count; // Reference count

        // Forbid copy constructor and assignment operator
        ShareCount(const ShareCount&) = delete;
        ShareCount& operator=(const ShareCount&) = delete;

    public:
        ShareCount(T *p) : ptr(p), count(1) {}
       ~ShareCount() {
            delete ptr;
        }
         
        // Increment reference count
        void increment() {count++;}

        // Decrement reference count and delete if it reaches zero
        void decrement() {
            if(--count == 0) {
                delete this;
            }
        }

        // Get the ptr
        T* get() const {
            return ptr;
        }
};

template<typename T>
class SharePtr {
    private:
        T *ptr; // Point to the actual object
        ShareCount<T> *countPtr; // Organize the reference count

    public:
        SharePtr(T *p = nullptr) : ptr(p) {
            if(p) {
                countPtr = new ShareCount<T>(p);
            } else {
                p = nullptr;
            }
        }
        
        // Copy constructor
        SharePtr(const SharePtr &other) : ptr(other.ptr), countPtr(other.countPtr) {
            if(countPtr) {
                countPtr->increment();
            }
        }

        // Move constructor
        SharePtr(SharePtr && other) : ptr(other.ptr), countPtr(other.countPtr) {
            other.ptr = nullptr;
            other.countPtr = nullptr;
        }

        // Destructor
        ~SharePtr() {
            if(countPtr) {
                countPtr->decrement();
            }
        }

        T* operator->() const {
            return ptr;
        }

        T& operator*() const {
            return *ptr;
        }

        // Reset
        void reset(T* p = nullptr) {
            if(p != ptr) {
                if(countPtr) {
                    countPtr->decrement();
                }
            }

            ptr = p;
            if(p) {
                countPtr = new ShareCount<T>(p);
            } else {
                countPtr = nullptr;
            }

        }

        // Get the original ptr
        T* get() const {
            return ptr;
        }
};

int main() {
    SharePtr<int> p1(new int(10));
    SharePtr<int> p2 = p1; // Copy constructor

    cout << "p1: " << *p1 << endl; // Output: 10
    cout << "p2: " << *p2 << endl; // Output: 10

    p1.reset();
    cout << "p2 after p1 reset: " << *p2 << endl; // Output: 10

    SharePtr<int> p3 = std::move(p2);
    cout << "p3 after move: " << *p3 << endl; // Output: 10
    //cout << "p2 after move: " << *p2 << endl; // Undefined behavior

    return 0;
}
```