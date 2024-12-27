/**********************************
 * =============工厂模式=============
 **********************************/
#include <iostream>

using namespace std;

// 产品的抽象类
class AbstractSmile {
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {}
};

// 具体的产品类
// 山羊恶魔果实
class SheepSmile final : public AbstractSmile {
public:
    void transform() override {
        cout << "Sheep 的 transform" << endl;
    }

    void ability() override {
        cout << "Sheep 的 ability" << endl;
    }
};

// 狮子恶魔果实
class LionSmile final : public AbstractSmile {
public:
    void transform() override {
        cout << "Lion 的 transform" << endl;
    }

    void ability() override {
        cout << "Lion 的 ability" << endl;
    }
};

// 蝙蝠恶魔果实
class BatSmile final : public AbstractSmile {
public:
    void transform() override {
        cout << "Bat 的 transform" << endl;
    }

    void ability() override {
        cout << "Bat 的 ability" << endl;
    }
};

enum class Type : char { Sheep, Lion, Bat };

// 抽象工厂类
class SmileFactory {
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~SmileFactory() {}
};

// SheepSmile的工厂
class SheepFactory final : public SmileFactory {
public:
    AbstractSmile* createSmile() override {
        return new SheepSmile;
    }

    ~SheepFactory() {
        cout << "sheepFactory 析构了" << endl;
    }
};

// LionSmile的工厂
class LionFactory final : public SmileFactory {
public:
    AbstractSmile* createSmile() override {
        return new LionSmile;
    }

    ~LionFactory() {
        cout << "LionFactory 析构了" << endl;
    }
};

// BatSmile的工厂
class BatFactory final : public SmileFactory {
public:
    AbstractSmile* createSmile() override {
        return new BatSmile;
    }

    ~BatFactory() {
        cout << "BatFactory 析构了" << endl;
    }
};

int main() {
    // 定义一个具体的工厂类对象
    SmileFactory* factory = new SheepFactory;

    // 使用抽象类指针指向子类对象。根据传入的类型产生对应的产品对象
    AbstractSmile* obj = factory->createSmile();
    obj->transform();
    obj->ability();

    delete obj;
    delete factory;

    return 0;
}
