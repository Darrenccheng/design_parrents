/******************************
*  -------简单工厂模式-----------
*******************************/
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
class SheepSmile final : public AbstractSmile {
public:
    void transform() override {
        cout << "Sheep 的 transform" << endl;
    }

    void ability() override {
        cout << "Sheep 的 ability" << endl;
    }
};

class LionSmile final : public AbstractSmile {
public:
    void transform() override {
        cout << "Lion 的 transform" << endl;
    }

    void ability() override {
        cout << "Lion 的 ability" << endl;
    }
};

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

// 工厂类
class SmileFactory {
public:
    AbstractSmile* createSmile(Type type) {
        AbstractSmile* ptr = nullptr;
        switch (type) {
            case Type::Sheep:
                ptr = new SheepSmile;
                break;
            case Type::Lion:
                ptr = new LionSmile;
                break;
            case Type::Bat:
                ptr = new BatSmile;
                break;
            default:
                break;
        }

        return ptr;
    }
};

int main() {
    // 定义一个工厂类对象
    SmileFactory* factory = new SmileFactory;

    // 使用抽象类指针指向子类对象。根据传入的类型产生对应的产品对象
    AbstractSmile* obj = factory->createSmile(Type::Sheep);
    obj->transform();
    obj->ability();

    delete obj;
    delete factory;

    return 0;
}
