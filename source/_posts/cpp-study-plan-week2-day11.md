---
title: C++ 学习计划 - 第11天：虚函数与多态
date: 2025-09-16 10:21:00
categories: Cpp
tags:
    - C++ 
    - Study Plan
    - Week2
    - Day11
layout: page
menu_id: plan
permalink: /plan/week2/day11/
---

# 第11天：虚函数与多态

## 学习目标
深入理解多态机制，掌握虚函数的概念和使用，学会设计支持多态的类体系。

## 学习资源链接

### 📚 官方文档和教程
- [C++ Reference - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual) - C++官方虚函数文档
- [LearnCpp - Virtual Functions](https://www.learncpp.com/cpp-tutorial/introduction-to-virtual-functions/) - 虚函数详解教程
- [GeeksforGeeks - Polymorphism](https://www.geeksforgeeks.org/polymorphism-in-c/) - 多态性详解

### 🎥 视频教程
- [The Cherno C++ Virtual Functions](https://www.youtube.com/watch?v=oIV2KchSyGQ) - 虚函数深入讲解
- [C++ Polymorphism Explained](https://www.youtube.com/watch?v=4NPOIaLfq2s) - 多态概念详解

### 📖 深入阅读
- [C++ Primer 第5版 - 第15.2-15.3节](https://www.amazon.com/Primer-5th-Stanley-Lippman/dp/0321714113) - 虚函数和抽象基类
- [Effective C++ - 条款7](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) - 为多态基类声明虚析构函数
- [More Effective C++ - 条款24](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X) - 理解虚函数、多重继承、虚基类和RTTI的开销

## 学习内容

### 1. 多态基础概念
- 编译时多态 vs 运行时多态
- 静态绑定 vs 动态绑定
- 多态的实现机制
- 多态的优势

### 2. 虚函数机制
- 虚函数的声明和定义
- 虚函数表（vtable）
- 虚函数指针（vptr）
- 动态绑定过程

### 3. 纯虚函数和抽象类
- 纯虚函数的语法
- 抽象类的概念
- 接口设计
- 抽象类的使用场景

### 4. 虚析构函数
- 虚析构函数的必要性
- 基类指针删除派生类对象
- 析构函数的调用顺序
- 虚析构函数的开销

### 5. 高级多态技巧
- 虚函数的重写规则
- 协变返回类型
- 虚函数的默认参数
- 构造函数中调用虚函数

## 重点概念和代码示例

### 多态基础演示
```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// 基类：媒体文件
class MediaFile {
protected:
    string filename;
    size_t fileSize;
    
public:
    MediaFile(const string& name, size_t size) 
        : filename(name), fileSize(size) {
        cout << "MediaFile构造: " << filename << endl;
    }
    
    // 虚析构函数 - 非常重要！
    virtual ~MediaFile() {
        cout << "MediaFile析构: " << filename << endl;
    }
    
    // 纯虚函数 - 派生类必须实现
    virtual void play() const = 0;
    virtual void stop() const = 0;
    virtual string getFormat() const = 0;
    
    // 虚函数 - 派生类可以重写
    virtual void displayInfo() const {
        cout << "文件: " << filename << ", 大小: " << fileSize << " bytes" << endl;
    }
    
    virtual double getDuration() const {
        return 0.0;  // 默认实现
    }
    
    // 非虚函数 - 不能被重写
    string getFilename() const { return filename; }
    size_t getFileSize() const { return fileSize; }
    
    // 模板方法模式 - 定义算法骨架
    void processFile() const {
        cout << "开始处理文件: " << filename << endl;
        loadFile();
        play();
        cout << "文件处理完成" << endl;
    }
    
private:
    void loadFile() const {
        cout << "加载文件: " << filename << endl;
    }
};

// 音频文件类
class AudioFile : public MediaFile {
private:
    int sampleRate;
    int bitRate;
    
public:
    AudioFile(const string& name, size_t size, int sample, int bit) 
        : MediaFile(name, size), sampleRate(sample), bitRate(bit) {
        cout << "AudioFile构造: " << filename << endl;
    }
    
    ~AudioFile() {
        cout << "AudioFile析构: " << filename << endl;
    }
    
    // 实现纯虚函数
    void play() const override {
        cout << "播放音频: " << filename << " (" << sampleRate << "Hz, " 
             << bitRate << "kbps)" << endl;
    }
    
    void stop() const override {
        cout << "停止音频播放: " << filename << endl;
    }
    
    string getFormat() const override {
        return "Audio";
    }
    
    // 重写虚函数
    void displayInfo() const override {
        MediaFile::displayInfo();  // 调用基类实现
        cout << "格式: 音频, 采样率: " << sampleRate 
             << "Hz, 比特率: " << bitRate << "kbps" << endl;
    }
    
    double getDuration() const override {
        // 简化计算：文件大小 / (比特率 * 1024 / 8)
        return static_cast<double>(fileSize) / (bitRate * 128);
    }
    
    // 音频特有方法
    void adjustVolume(int level) const {
        cout << "调整音量到 " << level << "%" << endl;
    }
    
    int getSampleRate() const { return sampleRate; }
    int getBitRate() const { return bitRate; }
};

// 视频文件类
class VideoFile : public MediaFile {
private:
    int width, height;
    int frameRate;
    
public:
    VideoFile(const string& name, size_t size, int w, int h, int fps) 
        : MediaFile(name, size), width(w), height(h), frameRate(fps) {
        cout << "VideoFile构造: " << filename << endl;
    }
    
    ~VideoFile() {
        cout << "VideoFile析构: " << filename << endl;
    }
    
    void play() const override {
        cout << "播放视频: " << filename << " (" << width << "x" << height 
             << ", " << frameRate << "fps)" << endl;
    }
    
    void stop() const override {
        cout << "停止视频播放: " << filename << endl;
    }
    
    string getFormat() const override {
        return "Video";
    }
    
    void displayInfo() const override {
        MediaFile::displayInfo();
        cout << "格式: 视频, 分辨率: " << width << "x" << height 
             << ", 帧率: " << frameRate << "fps" << endl;
    }
    
    double getDuration() const override {
        // 简化计算：假设每秒需要1MB数据
        return static_cast<double>(fileSize) / (1024 * 1024);
    }
    
    // 视频特有方法
    void changeResolution(int w, int h) {
        width = w;
        height = h;
        cout << "分辨率改为 " << width << "x" << height << endl;
    }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getFrameRate() const { return frameRate; }
};

void polymorphismDemo() {
    cout << "=== 多态基础演示 ===" << endl;
    
    // 创建不同类型的媒体文件
    AudioFile audio("song.mp3", 5242880, 44100, 320);
    VideoFile video("movie.mp4", 104857600, 1920, 1080, 30);
    
    cout << "\n=== 直接调用 ===" << endl;
    audio.displayInfo();
    audio.play();
    
    video.displayInfo();
    video.play();
    
    cout << "\n=== 多态调用 ===" << endl;
    // 使用基类指针 - 这是多态的关键
    MediaFile* mediaPtr;
    
    mediaPtr = &audio;
    cout << "通过基类指针调用音频:" << endl;
    mediaPtr->displayInfo();  // 动态绑定到AudioFile::displayInfo
    mediaPtr->play();         // 动态绑定到AudioFile::play
    cout << "时长: " << mediaPtr->getDuration() << " 秒" << endl;
    
    mediaPtr = &video;
    cout << "\n通过基类指针调用视频:" << endl;
    mediaPtr->displayInfo();  // 动态绑定到VideoFile::displayInfo
    mediaPtr->play();         // 动态绑定到VideoFile::play
    cout << "时长: " << mediaPtr->getDuration() << " 秒" << endl;
    
    cout << "\n=== 模板方法模式 ===" << endl;
    mediaPtr = &audio;
    mediaPtr->processFile();
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 虚函数表机制演示
```cpp
// 演示虚函数表的工作原理
class VTableDemo {
public:
    VTableDemo() { 
        cout << "VTableDemo构造，this指针: " << this << endl;
        // 注意：在构造函数中调用虚函数，调用的是当前类的版本
        virtualFunction();  
    }
    
    virtual ~VTableDemo() { 
        cout << "VTableDemo析构" << endl; 
    }
    
    virtual void virtualFunction() const {
        cout << "VTableDemo::virtualFunction() 被调用" << endl;
    }
    
    virtual void pureVirtualFunction() const = 0;
    
    void nonVirtualFunction() const {
        cout << "VTableDemo::nonVirtualFunction() 被调用" << endl;
    }
    
    // 显示对象的内存布局（仅用于演示）
    void showMemoryLayout() const {
        cout << "对象地址: " << this << endl;
        cout << "对象大小: " << sizeof(*this) << " bytes" << endl;
        // 第一个指针通常是虚函数表指针
        cout << "虚函数表指针: " << *reinterpret_cast<const void**>(this) << endl;
    }
};

class DerivedVTable : public VTableDemo {
private:
    int data;
    
public:
    DerivedVTable(int value) : data(value) {
        cout << "DerivedVTable构造，值: " << data << endl;
        virtualFunction();  // 现在调用的是派生类版本
    }
    
    ~DerivedVTable() {
        cout << "DerivedVTable析构" << endl;
    }
    
    // 重写虚函数
    void virtualFunction() const override {
        cout << "DerivedVTable::virtualFunction() 被调用，data = " << data << endl;
    }
    
    // 实现纯虚函数
    void pureVirtualFunction() const override {
        cout << "DerivedVTable::pureVirtualFunction() 被调用" << endl;
    }
    
    // 新增虚函数
    virtual void newVirtualFunction() const {
        cout << "DerivedVTable::newVirtualFunction() 被调用" << endl;
    }
    
    int getData() const { return data; }
};

void vtableDemo() {
    cout << "\n=== 虚函数表机制演示 ===" << endl;
    
    DerivedVTable derived(42);
    
    cout << "\n=== 内存布局 ===" << endl;
    derived.showMemoryLayout();
    
    cout << "\n=== 多态调用 ===" << endl;
    VTableDemo* basePtr = &derived;
    
    // 这些调用会通过虚函数表进行动态绑定
    basePtr->virtualFunction();      // 调用DerivedVTable版本
    basePtr->pureVirtualFunction();  // 调用DerivedVTable版本
    basePtr->nonVirtualFunction();   // 调用VTableDemo版本（静态绑定）
    
    cout << "\n=== 类型转换 ===" << endl;
    // 向下转换需要小心
    DerivedVTable* derivedPtr = static_cast<DerivedVTable*>(basePtr);
    derivedPtr->newVirtualFunction();
    cout << "数据值: " << derivedPtr->getData() << endl;
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

## 实践练习

### 练习1：图形渲染系统
```cpp
#include <cmath>

// 抽象渲染器接口
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void drawLine(double x1, double y1, double x2, double y2) const = 0;
    virtual void drawCircle(double x, double y, double radius) const = 0;
    virtual void drawRectangle(double x, double y, double width, double height) const = 0;
    virtual void setColor(const string& color) const = 0;
};

// 控制台渲染器
class ConsoleRenderer : public Renderer {
private:
    mutable string currentColor = "黑色";
    
public:
    void drawLine(double x1, double y1, double x2, double y2) const override {
        cout << "[控制台] 绘制" << currentColor << "线段: (" << x1 << "," << y1 
             << ") -> (" << x2 << "," << y2 << ")" << endl;
    }
    
    void drawCircle(double x, double y, double radius) const override {
        cout << "[控制台] 绘制" << currentColor << "圆形: 中心(" << x << "," << y 
             << "), 半径=" << radius << endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) const override {
        cout << "[控制台] 绘制" << currentColor << "矩形: 位置(" << x << "," << y 
             << "), 大小=" << width << "x" << height << endl;
    }
    
    void setColor(const string& color) const override {
        currentColor = color;
        cout << "[控制台] 设置颜色为: " << color << endl;
    }
};

// SVG渲染器
class SVGRenderer : public Renderer {
private:
    mutable string currentColor = "black";
    mutable vector<string> svgElements;
    
public:
    void drawLine(double x1, double y1, double x2, double y2) const override {
        string element = "<line x1=\"" + to_string(x1) + "\" y1=\"" + to_string(y1) +
                        "\" x2=\"" + to_string(x2) + "\" y2=\"" + to_string(y2) +
                        "\" stroke=\"" + currentColor + "\" />";
        svgElements.push_back(element);
        cout << "[SVG] 添加线段元素" << endl;
    }
    
    void drawCircle(double x, double y, double radius) const override {
        string element = "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) +
                        "\" r=\"" + to_string(radius) + "\" fill=\"none\" stroke=\"" + 
                        currentColor + "\" />";
        svgElements.push_back(element);
        cout << "[SVG] 添加圆形元素" << endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) const override {
        string element = "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y) +
                        "\" width=\"" + to_string(width) + "\" height=\"" + to_string(height) +
                        "\" fill=\"none\" stroke=\"" + currentColor + "\" />";
        svgElements.push_back(element);
        cout << "[SVG] 添加矩形元素" << endl;
    }
    
    void setColor(const string& color) const override {
        currentColor = color;
        cout << "[SVG] 设置颜色为: " << color << endl;
    }
    
    void exportSVG(const string& filename) const {
        cout << "\n导出SVG文件: " << filename << endl;
        cout << "<svg xmlns=\"http://www.w3.org/2000/svg\">" << endl;
        for (const auto& element : svgElements) {
            cout << "  " << element << endl;
        }
        cout << "</svg>" << endl;
    }
    
    void clearElements() const {
        svgElements.clear();
        cout << "[SVG] 清空所有元素" << endl;
    }
};

// 抽象图形类
class Drawable {
protected:
    double x, y;
    string color;
    
public:
    Drawable(double x, double y, const string& c) : x(x), y(y), color(c) {}
    virtual ~Drawable() = default;
    
    // 纯虚函数：子类必须实现
    virtual void draw(const Renderer& renderer) const = 0;
    virtual double getArea() const = 0;
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
    }
    
    // 虚函数：子类可以重写
    virtual void displayInfo() const {
        cout << "位置: (" << x << "," << y << "), 颜色: " << color << endl;
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    string getColor() const { return color; }
    void setColor(const string& c) { color = c; }
};

// 具体图形类
class DrawableCircle : public Drawable {
private:
    double radius;
    
public:
    DrawableCircle(double x, double y, double r, const string& c) 
        : Drawable(x, y, c), radius(r) {}
    
    void draw(const Renderer& renderer) const override {
        renderer.setColor(color);
        renderer.drawCircle(x, y, radius);
    }
    
    double getArea() const override {
        return M_PI * radius * radius;
    }
    
    void displayInfo() const override {
        cout << "圆形 - ";
        Drawable::displayInfo();
        cout << "半径: " << radius << ", 面积: " << getArea() << endl;
    }
    
    double getRadius() const { return radius; }
    void setRadius(double r) { if (r > 0) radius = r; }
};

class DrawableRectangle : public Drawable {
private:
    double width, height;
    
public:
    DrawableRectangle(double x, double y, double w, double h, const string& c) 
        : Drawable(x, y, c), width(w), height(h) {}
    
    void draw(const Renderer& renderer) const override {
        renderer.setColor(color);
        renderer.drawRectangle(x, y, width, height);
    }
    
    double getArea() const override {
        return width * height;
    }
    
    void displayInfo() const override {
        cout << "矩形 - ";
        Drawable::displayInfo();
        cout << "尺寸: " << width << "x" << height << ", 面积: " << getArea() << endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

// 复合图形
class DrawingCanvas {
private:
    vector<unique_ptr<Drawable>> shapes;
    
public:
    void addShape(unique_ptr<Drawable> shape) {
        shapes.push_back(move(shape));
    }
    
    void drawAll(const Renderer& renderer) const {
        cout << "\n绘制画布上的所有图形:" << endl;
        for (const auto& shape : shapes) {
            shape->draw(renderer);
        }
    }
    
    void displayAllInfo() const {
        cout << "\n画布上的图形信息:" << endl;
        for (size_t i = 0; i < shapes.size(); ++i) {
            cout << (i + 1) << ". ";
            shapes[i]->displayInfo();
        }
    }
    
    double getTotalArea() const {
        double total = 0;
        for (const auto& shape : shapes) {
            total += shape->getArea();
        }
        return total;
    }
    
    void moveAll(double dx, double dy) {
        cout << "\n移动所有图形 (" << dx << "," << dy << ")" << endl;
        for (auto& shape : shapes) {
            shape->move(dx, dy);
        }
    }
    
    size_t getShapeCount() const { return shapes.size(); }
};

void exercise1() {
    cout << "\n=== 练习1：图形渲染系统 ===" << endl;
    
    // 创建不同的渲染器
    ConsoleRenderer consoleRenderer;
    SVGRenderer svgRenderer;
    
    // 创建画布和图形
    DrawingCanvas canvas;
    
    canvas.addShape(make_unique<DrawableCircle>(100, 100, 50, "红色"));
    canvas.addShape(make_unique<DrawableRectangle>(200, 150, 80, 60, "蓝色"));
    canvas.addShape(make_unique<DrawableCircle>(300, 200, 30, "绿色"));
    
    // 显示图形信息
    canvas.displayAllInfo();
    cout << "总面积: " << canvas.getTotalArea() << endl;
    
    // 使用不同渲染器绘制
    cout << "\n=== 控制台渲染 ===" << endl;
    canvas.drawAll(consoleRenderer);
    
    cout << "\n=== SVG渲染 ===" << endl;
    canvas.drawAll(svgRenderer);
    
    // 导出SVG
    const SVGRenderer* svgPtr = &svgRenderer;
    svgPtr->exportSVG("drawing.svg");
    
    // 移动所有图形
    canvas.moveAll(10, -5);
    
    cout << "\n移动后的图形信息:" << endl;
    canvas.displayAllInfo();
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

### 练习2：游戏角色系统
```cpp
// 游戏角色基类
class GameCharacter {
protected:
    string name;
    int level;
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    
public:
    GameCharacter(const string& n, int lvl) 
        : name(n), level(lvl), health(100 * lvl), maxHealth(100 * lvl),
          mana(50 * lvl), maxMana(50 * lvl) {
        cout << "角色创建: " << name << " (等级 " << level << ")" << endl;
    }
    
    virtual ~GameCharacter() {
        cout << "角色销毁: " << name << endl;
    }
    
    // 纯虚函数：战斗相关
    virtual void attack(GameCharacter& target) = 0;
    virtual void useSpecialAbility(GameCharacter& target) = 0;
    virtual string getCharacterClass() const = 0;
    
    // 虚函数：可以被重写
    virtual void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        cout << name << " 受到 " << damage << " 点伤害，剩余生命: " << health << endl;
        
        if (health == 0) {
            onDeath();
        }
    }
    
    virtual void heal(int amount) {
        health += amount;
        if (health > maxHealth) health = maxHealth;
        cout << name << " 恢复 " << amount << " 点生命，当前生命: " << health << endl;
    }
    
    virtual void levelUp() {
        level++;
        int healthIncrease = 100;
        int manaIncrease = 50;
        
        maxHealth += healthIncrease;
        maxMana += manaIncrease;
        health = maxHealth;  // 升级时恢复满血
        mana = maxMana;      // 升级时恢复满蓝
        
        cout << name << " 升级到 " << level << " 级！生命+" << healthIncrease 
             << ", 法力+" << manaIncrease << endl;
    }
    
    virtual void displayStatus() const {
        cout << "\n=== " << name << " (" << getCharacterClass() << ") ===" << endl;
        cout << "等级: " << level << endl;
        cout << "生命: " << health << "/" << maxHealth << endl;
        cout << "法力: " << mana << "/" << maxMana << endl;
        cout << "状态: " << (isAlive() ? "存活" : "死亡") << endl;
    }
    
protected:
    virtual void onDeath() {
        cout << name << " 已死亡！" << endl;
    }
    
    bool consumeMana(int cost) {
        if (mana >= cost) {
            mana -= cost;
            return true;
        }
        cout << name << " 法力不足！" << endl;
        return false;
    }
    
public:
    // 状态查询
    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getLevel() const { return level; }
    int getHealth() const { return health; }
    int getMana() const { return mana; }
};

// 战士类
class Warrior : public GameCharacter {
private:
    int armor;
    int rage;
    
public:
    Warrior(const string& n, int lvl) 
        : GameCharacter(n, lvl), armor(lvl * 5), rage(0) {
        cout << "战士就职: " << name << endl;
    }
    
    ~Warrior() {
        cout << "战士退役: " << name << endl;
    }
    
    void attack(GameCharacter& target) override {
        if (!isAlive()) return;
        
        int damage = 20 + level * 5 + rage;
        rage += 10;  // 攻击增加怒气
        if (rage > 100) rage = 100;
        
        cout << name << " 用剑攻击 " << target.getName() << "!" << endl;
        target.takeDamage(damage);
    }
    
    void useSpecialAbility(GameCharacter& target) override {
        if (!isAlive() || rage < 50) {
            cout << name << " 怒气不足，无法使用狂暴攻击！" << endl;
            return;
        }
        
        rage -= 50;
        int damage = 40 + level * 10;
        
        cout << name << " 使用狂暴攻击！" << endl;
        target.takeDamage(damage);
    }
    
    string getCharacterClass() const override {
        return "战士";
    }
    
    void takeDamage(int damage) override {
        int actualDamage = damage - armor / 2;
        if (actualDamage < 1) actualDamage = 1;
        
        cout << name << " 的护甲减少了 " << (damage - actualDamage) << " 点伤害" << endl;
        GameCharacter::takeDamage(actualDamage);
        
        rage += 5;  // 受伤增加怒气
        if (rage > 100) rage = 100;
    }
    
    void displayStatus() const override {
        GameCharacter::displayStatus();
        cout << "护甲: " << armor << endl;
        cout << "怒气: " << rage << "/100" << endl;
    }
    
    // 战士特有技能
    void defend() {
        cout << name << " 进入防御姿态，护甲临时增加！" << endl;
        armor += 10;
    }
    
    int getArmor() const { return armor; }
    int getRage() const { return rage; }
};

// 法师类
class Mage : public GameCharacter {
private:
    int spellPower;
    
public:
    Mage(const string& n, int lvl) 
        : GameCharacter(n, lvl), spellPower(lvl * 8) {
        cout << "法师就职: " << name << endl;
    }
    
    ~Mage() {
        cout << "法师隐退: " << name << endl;
    }
    
    void attack(GameCharacter& target) override {
        if (!isAlive() || !consumeMana(10)) return;
        
        int damage = 15 + spellPower;
        
        cout << name << " 释放魔法飞弹攻击 " << target.getName() << "!" << endl;
        target.takeDamage(damage);
    }
    
    void useSpecialAbility(GameCharacter& target) override {
        if (!isAlive() || !consumeMana(30)) return;
        
        int damage = 30 + spellPower * 2;
        
        cout << name << " 释放火球术！" << endl;
        target.takeDamage(damage);
    }
    
    string getCharacterClass() const override {
        return "法师";
    }
    
    void heal(int amount) override {
        GameCharacter::heal(amount);
        mana += 20;  // 法师治疗时恢复一些法力
        if (mana > maxMana) mana = maxMana;
    }
    
    void displayStatus() const override {
        GameCharacter::displayStatus();
        cout << "法术强度: " << spellPower << endl;
    }
    
    // 法师特有技能
    void meditate() {
        if (!isAlive()) return;
        
        int manaRestore = maxMana / 4;
        mana += manaRestore;
        if (mana > maxMana) mana = maxMana;
        
        cout << name << " 冥想恢复法力: " << manaRestore << endl;
    }
    
    void castShield() {
        if (!consumeMana(25)) return;
        
        cout << name << " 释放魔法护盾！" << endl;
        // 简化实现：临时增加生命值
        heal(50);
    }
    
    int getSpellPower() const { return spellPower; }
};

// 游戏战斗系统
class BattleSystem {
public:
    static void battle(GameCharacter& char1, GameCharacter& char2) {
        cout << "\n=== 战斗开始：" << char1.getName() << " VS " << char2.getName() << " ===" << endl;
        
        int round = 1;
        while (char1.isAlive() && char2.isAlive() && round <= 10) {
            cout << "\n--- 第 " << round << " 回合 ---" << endl;
            
            // 角色1攻击
            if (char1.isAlive()) {
                if (round % 3 == 0) {
                    char1.useSpecialAbility(char2);
                } else {
                    char1.attack(char2);
                }
            }
            
            // 角色2反击
            if (char2.isAlive()) {
                if (round % 4 == 0) {
                    char2.useSpecialAbility(char1);
                } else {
                    char2.attack(char1);
                }
            }
            
            round++;
        }
        
        cout << "\n=== 战斗结束 ===" << endl;
        if (char1.isAlive() && char2.isAlive()) {
            cout << "战斗平局！" << endl;
        } else if (char1.isAlive()) {
            cout << char1.getName() << " 获胜！" << endl;
        } else if (char2.isAlive()) {
            cout << char2.getName() << " 获胜！" << endl;
        } else {
            cout << "同归于尽！" << endl;
        }
    }
    
    static void displayBattleStatus(const GameCharacter& char1, const GameCharacter& char2) {
        char1.displayStatus();
        char2.displayStatus();
    }
};

void exercise2() {
    cout << "\n=== 练习2：游戏角色系统 ===" << endl;
    
    // 创建不同类型的角色
    Warrior warrior("亚瑟王", 5);
    Mage mage("梅林", 4);
    
    cout << "\n=== 初始状态 ===" << endl;
    BattleSystem::displayBattleStatus(warrior, mage);
    
    // 角色升级
    cout << "\n=== 角色升级 ===" << endl;
    mage.levelUp();
    
    // 使用特殊技能
    cout << "\n=== 技能演示 ===" << endl;
    warrior.defend();
    mage.meditate();
    mage.castShield();
    
    BattleSystem::displayBattleStatus(warrior, mage);
    
    // 进行战斗
    BattleSystem::battle(warrior, mage);
    
    // 最终状态
    cout << "\n=== 最终状态 ===" << endl;
    BattleSystem::displayBattleStatus(warrior, mage);
    
    // 多态演示
    cout << "\n=== 多态演示 ===" << endl;
    vector<unique_ptr<GameCharacter>> party;
    party.push_back(make_unique<Warrior>("兰斯洛特", 3));
    party.push_back(make_unique<Mage>("甘道夫", 6));
    party.push_back(make_unique<Warrior>("罗兰", 4));
    
    cout << "冒险队伍成员:" << endl;
    for (const auto& member : party) {
        cout << "- " << member->getName() << " (" << member->getCharacterClass() << ")" << endl;
    }
    
    cout << "\n队伍升级!" << endl;
    for (auto& member : party) {
        member->levelUp();
    }
    
    cout << "\n函数结束，开始析构..." << endl;
}
```

## 学习检查点

- [ ] 理解多态的基本概念和实现机制
- [ ] 掌握虚函数的声明和使用
- [ ] 理解虚函数表的工作原理
- [ ] 掌握纯虚函数和抽象类的设计
- [ ] 了解虚析构函数的重要性
- [ ] 能够设计支持多态的类体系
- [ ] 理解动态绑定和静态绑定的区别
- [ ] 掌握多态在设计模式中的应用

## 完整示例程序

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

int main() {
    cout << "=== C++ 虚函数与多态学习 ===" << endl;
    
    try {
        // 运行所有示例和练习
        polymorphismDemo();
        vtableDemo();
        
        exercise1();
        exercise2();
        
    } catch (const exception& e) {
        cout << "程序异常: " << e.what() << endl;
    }
    
    cout << "\n程序结束" << endl;
    return 0;
}
```

[返回第二周](/plan/week2/) | [上一天：继承](/plan/week2/day10/) | [下一天：运算符重载](/plan/week2/day12/)
