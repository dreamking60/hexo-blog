# 第17天：智能指针复习

## 学习目标
掌握C++11引入的智能指针，理解现代C++的内存管理方式，学会使用RAII原则避免内存泄漏。

## 学习内容

### 1. 智能指针概述

智能指针是C++11引入的自动内存管理工具，它们基于RAII（Resource Acquisition Is Initialization）原则，在对象销毁时自动释放资源。

#### 为什么需要智能指针？
- **避免内存泄漏**：自动释放内存
- **异常安全**：即使发生异常也能正确释放资源
- **简化代码**：减少手动内存管理
- **避免悬空指针**：防止访问已释放的内存

### 2. unique_ptr

`unique_ptr`是独占所有权的智能指针，同一时间只能有一个`unique_ptr`拥有对象。

#### 基本使用
```cpp
#include <memory>
#include <iostream>

void uniquePtrBasic() {
    // 创建unique_ptr
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::cout << "值: " << *ptr1 << std::endl;
    
    // 检查是否为空
    if (ptr1) {
        std::cout << "指针不为空" << std::endl;
    }
    
    // 获取原始指针
    int* rawPtr = ptr1.get();
    std::cout << "原始指针值: " << *rawPtr << std::endl;
    
    // 释放所有权
    int* releasedPtr = ptr1.release();
    std::cout << "释放后的值: " << *releasedPtr << std::endl;
    delete releasedPtr;  // 需要手动删除
    
    // 重置指针
    ptr1.reset(new int(100));
    std::cout << "重置后的值: " << *ptr1 << std::endl;
}
```

#### 移动语义
```cpp
#include <memory>
#include <iostream>

void uniquePtrMove() {
    // 创建unique_ptr
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    
    // 移动所有权（ptr1变为空）
    std::unique_ptr<int> ptr2 = std::move(ptr1);
    
    std::cout << "ptr1是否为空: " << (ptr1 == nullptr) << std::endl;
    std::cout << "ptr2的值: " << *ptr2 << std::endl;
    
    // 不能复制，只能移动
    // std::unique_ptr<int> ptr3 = ptr2;  // 编译错误
    std::unique_ptr<int> ptr3 = std::move(ptr2);  // 正确
}
```

#### 自定义删除器
```cpp
#include <memory>
#include <iostream>

void customDeleter() {
    // 使用Lambda作为删除器
    auto deleter = [](int* ptr) {
        std::cout << "自定义删除器被调用" << std::endl;
        delete ptr;
    };
    
    std::unique_ptr<int, decltype(deleter)> ptr(new int(42), deleter);
    
    // 使用函数作为删除器
    auto fileDeleter = [](FILE* f) {
        if (f) {
            std::cout << "关闭文件" << std::endl;
            fclose(f);
        }
    };
    
    std::unique_ptr<FILE, decltype(fileDeleter)> file(fopen("test.txt", "w"), fileDeleter);
}
```

### 3. shared_ptr

`shared_ptr`是共享所有权的智能指针，多个`shared_ptr`可以共享同一个对象。

#### 基本使用
```cpp
#include <memory>
#include <iostream>

void sharedPtrBasic() {
    // 创建shared_ptr
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::cout << "引用计数: " << ptr1.use_count() << std::endl;
    
    // 复制shared_ptr
    std::shared_ptr<int> ptr2 = ptr1;
    std::cout << "引用计数: " << ptr1.use_count() << std::endl;
    
    // 获取原始指针
    int* rawPtr = ptr1.get();
    std::cout << "原始指针值: " << *rawPtr << std::endl;
    
    // 检查是否唯一
    std::cout << "是否唯一: " << ptr1.unique() << std::endl;
    
    // 重置指针
    ptr1.reset();
    std::cout << "ptr1重置后，ptr2引用计数: " << ptr2.use_count() << std::endl;
}
```

#### 循环引用问题
```cpp
#include <memory>
#include <iostream>

struct Node {
    int value;
    std::shared_ptr<Node> next;
    
    Node(int v) : value(v) {}
    
    ~Node() {
        std::cout << "Node " << value << " 被销毁" << std::endl;
    }
};

void circularReferenceProblem() {
    // 创建循环引用
    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);
    
    node1->next = node2;
    node2->next = node1;  // 循环引用！
    
    std::cout << "node1引用计数: " << node1.use_count() << std::endl;
    std::cout << "node2引用计数: " << node2.use_count() << std::endl;
    
    // 即使离开作用域，对象也不会被销毁
    // 因为存在循环引用
}
```

### 4. weak_ptr

`weak_ptr`是弱引用智能指针，用于解决循环引用问题。

#### 基本使用
```cpp
#include <memory>
#include <iostream>

struct Node {
    int value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // 使用weak_ptr避免循环引用
    
    Node(int v) : value(v) {}
    
    ~Node() {
        std::cout << "Node " << value << " 被销毁" << std::endl;
    }
};

void weakPtrExample() {
    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);
    
    node1->next = node2;
    node2->prev = node1;  // 使用weak_ptr
    
    std::cout << "node1引用计数: " << node1.use_count() << std::endl;
    std::cout << "node2引用计数: " << node2.use_count() << std::endl;
    
    // 使用weak_ptr
    if (auto locked = node2->prev.lock()) {
        std::cout << "通过weak_ptr访问: " << locked->value << std::endl;
    }
    
    // 检查weak_ptr是否有效
    std::cout << "weak_ptr是否过期: " << node2->prev.expired() << std::endl;
}
```

### 5. make_unique 和 make_shared

#### make_unique (C++14)
```cpp
#include <memory>
#include <iostream>

void makeUniqueExample() {
    // 推荐使用make_unique
    auto ptr1 = std::make_unique<int>(42);
    auto ptr2 = std::make_unique<std::string>("Hello");
    
    // 创建数组
    auto arr = std::make_unique<int[]>(10);
    for (int i = 0; i < 10; ++i) {
        arr[i] = i * i;
    }
    
    // 创建对象
    struct Point {
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
    };
    
    auto point = std::make_unique<Point>(3, 4);
    std::cout << "Point: (" << point->x << ", " << point->y << ")" << std::endl;
}
```

#### make_shared
```cpp
#include <memory>
#include <iostream>

void makeSharedExample() {
    // 推荐使用make_shared
    auto ptr1 = std::make_shared<int>(42);
    auto ptr2 = std::make_shared<std::string>("World");
    
    // 创建对象
    struct Person {
        std::string name;
        int age;
        Person(const std::string& n, int a) : name(n), age(a) {}
    };
    
    auto person = std::make_shared<Person>("Alice", 25);
    std::cout << "Person: " << person->name << ", " << person->age << std::endl;
    
    // 复制shared_ptr
    auto person2 = person;
    std::cout << "引用计数: " << person.use_count() << std::endl;
}
```

### 6. 智能指针与容器

```cpp
#include <memory>
#include <vector>
#include <iostream>

void smartPtrWithContainers() {
    // 容器存储智能指针
    std::vector<std::unique_ptr<int>> vec;
    
    // 添加元素
    for (int i = 0; i < 5; ++i) {
        vec.push_back(std::make_unique<int>(i * i));
    }
    
    // 遍历
    for (const auto& ptr : vec) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;
    
    // 使用shared_ptr
    std::vector<std::shared_ptr<int>> sharedVec;
    for (int i = 0; i < 3; ++i) {
        sharedVec.push_back(std::make_shared<int>(i * 10));
    }
    
    // 复制shared_ptr
    std::vector<std::shared_ptr<int>> sharedVec2 = sharedVec;
    std::cout << "引用计数: " << sharedVec[0].use_count() << std::endl;
}
```

### 7. 智能指针与多态

```cpp
#include <memory>
#include <iostream>
#include <vector>

class Animal {
public:
    virtual void makeSound() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void makeSound() const override {
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Meow!" << std::endl;
    }
};

void polymorphismExample() {
    // 使用智能指针实现多态
    std::vector<std::unique_ptr<Animal>> animals;
    
    animals.push_back(std::make_unique<Dog>());
    animals.push_back(std::make_unique<Cat>());
    animals.push_back(std::make_unique<Dog>());
    
    for (const auto& animal : animals) {
        animal->makeSound();
    }
    
    // 使用shared_ptr
    std::shared_ptr<Animal> pet = std::make_shared<Dog>();
    pet->makeSound();
}
```

## 实践练习

### 练习1：资源管理器
```cpp
#include <memory>
#include <iostream>
#include <vector>

class Resource {
private:
    int id;
    std::string name;
    
public:
    Resource(int i, const std::string& n) : id(i), name(n) {
        std::cout << "创建资源: " << name << " (ID: " << id << ")" << std::endl;
    }
    
    ~Resource() {
        std::cout << "销毁资源: " << name << " (ID: " << id << ")" << std::endl;
    }
    
    int getId() const { return id; }
    const std::string& getName() const { return name; }
};

class ResourceManager {
private:
    std::vector<std::unique_ptr<Resource>> resources;
    
public:
    void addResource(int id, const std::string& name) {
        resources.push_back(std::make_unique<Resource>(id, name));
    }
    
    Resource* findResource(int id) const {
        for (const auto& resource : resources) {
            if (resource->getId() == id) {
                return resource.get();
            }
        }
        return nullptr;
    }
    
    void removeResource(int id) {
        resources.erase(
            std::remove_if(resources.begin(), resources.end(),
                          [id](const std::unique_ptr<Resource>& resource) {
                              return resource->getId() == id;
                          }),
            resources.end()
        );
    }
    
    void printAllResources() const {
        std::cout << "所有资源:" << std::endl;
        for (const auto& resource : resources) {
            std::cout << "  " << resource->getName() 
                      << " (ID: " << resource->getId() << ")" << std::endl;
        }
    }
};
```

### 练习2：观察者模式
```cpp
#include <memory>
#include <vector>
#include <iostream>
#include <string>

class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<std::weak_ptr<Observer>> observers;
    
public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    
    void notifyObservers(const std::string& message) {
        // 清理过期的weak_ptr
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                          [](const std::weak_ptr<Observer>& weak_obs) {
                              return weak_obs.expired();
                          }),
            observers.end()
        );
        
        // 通知所有观察者
        for (const auto& weak_obs : observers) {
            if (auto obs = weak_obs.lock()) {
                obs->update(message);
            }
        }
    }
};

class ConcreteObserver : public Observer {
private:
    std::string name;
    
public:
    ConcreteObserver(const std::string& n) : name(n) {}
    
    void update(const std::string& message) override {
        std::cout << name << " 收到消息: " << message << std::endl;
    }
};

void observerPatternExample() {
    Subject subject;
    
    // 创建观察者
    auto observer1 = std::make_shared<ConcreteObserver>("观察者1");
    auto observer2 = std::make_shared<ConcreteObserver>("观察者2");
    
    // 添加观察者
    subject.addObserver(observer1);
    subject.addObserver(observer2);
    
    // 发送通知
    subject.notifyObservers("Hello World!");
    
    // 移除一个观察者
    observer1.reset();
    
    // 再次发送通知
    subject.notifyObservers("Second message");
}
```

### 练习3：树结构
```cpp
#include <memory>
#include <iostream>
#include <vector>

template<typename T>
class TreeNode {
private:
    T value;
    std::vector<std::shared_ptr<TreeNode<T>>> children;
    std::weak_ptr<TreeNode<T>> parent;
    
public:
    TreeNode(T val) : value(val) {}
    
    void addChild(std::shared_ptr<TreeNode<T>> child) {
        child->parent = shared_from_this();
        children.push_back(child);
    }
    
    void removeChild(std::shared_ptr<TreeNode<T>> child) {
        children.erase(
            std::remove(children.begin(), children.end(), child),
            children.end()
        );
    }
    
    T getValue() const { return value; }
    
    const std::vector<std::shared_ptr<TreeNode<T>>>& getChildren() const {
        return children;
    }
    
    std::shared_ptr<TreeNode<T>> getParent() const {
        return parent.lock();
    }
    
    void printTree(int depth = 0) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << value << std::endl;
        
        for (const auto& child : children) {
            child->printTree(depth + 1);
        }
    }
};

void treeExample() {
    // 创建树节点
    auto root = std::make_shared<TreeNode<int>>(1);
    auto child1 = std::make_shared<TreeNode<int>>(2);
    auto child2 = std::make_shared<TreeNode<int>>(3);
    auto grandchild1 = std::make_shared<TreeNode<int>>(4);
    auto grandchild2 = std::make_shared<TreeNode<int>>(5);
    
    // 构建树结构
    root->addChild(child1);
    root->addChild(child2);
    child1->addChild(grandchild1);
    child1->addChild(grandchild2);
    
    // 打印树
    root->printTree();
}
```

## 学习要点总结

1. **RAII原则**：资源获取即初始化，自动管理资源生命周期
2. **所有权语义**：unique_ptr独占，shared_ptr共享，weak_ptr弱引用
3. **循环引用**：使用weak_ptr避免循环引用导致的内存泄漏
4. **异常安全**：智能指针确保异常情况下也能正确释放资源
5. **性能考虑**：make_shared比new + shared_ptr更高效

## 今日算法题

完成以下4道LeetCode题目，巩固智能指针的使用：

1. [LeetCode 138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) - 使用智能指针管理链表节点
2. [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/) - 使用智能指针实现LRU缓存
3. [LeetCode 208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) - 使用智能指针实现字典树
4. [LeetCode 341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/) - 使用智能指针实现迭代器

每道题目都涉及智能指针的使用，是很好的实践机会！
