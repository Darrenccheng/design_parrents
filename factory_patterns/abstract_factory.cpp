/*****************************************
 * =============抽象工厂模式================
 *****************************************/

/***************************************************************************
 * 场景：制造三种类型的船，船有三个组成部分，不同类型的船，每部分的材质不一样。
 *          基础型	标准型	  旗舰型
     船体	木头	    钢铁	     合成金属
     动力	手动	    内燃机	   核能
     武器	枪	    速射炮	   激光
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iostream>

using namespace std;

// 抽象船体类
class ShipBody {
public:
    virtual string getShipBody() = 0;
    virtual ~ShipBody() { }
};

// 木头船体
class WoodBody : public ShipBody {
public:
    string getShipBody() override {
        return string("用<木材>制作轮船船体...");
    }
};

// 钢铁船体
class SteelBody : public ShipBody {
public:
    string getShipBody() override {
        return string("用<钢铁>制作轮船船体...");
    }
};

// 金属船体
class MetalBody : public ShipBody {
public:
    string getShipBody() override {
        return string("用<合成金属>制作轮船船体...");
    }
};

// 抽象动力部分类
class Engine {
public:
    virtual string getEngine() = 0;
    virtual ~Engine() { }
};

// 手动发动机
class manualEngine : public Engine {
public:
    string getEngine() override {
        return string("用<人工驱动>的发动机 ...");
    }
};

// 内燃机
class DieselEngine : public Engine {
public:
    string getEngine() override {
        return string("用<内燃机驱动>的发动机 ...");
    }
};

// 核能驱动
class nuclearEngine : public Engine {
public:
    string getEngine() override {
        return string("用<核能驱动>的发动机 ...");
    }
};

// 抽象的武器部分
class Arms {
public:
    virtual string getArms() = 0;
    virtual ~Arms() { }
};

// 枪
class GunArm : public Arms {
public:
    string getArms() override {
        return string("配备的武器是<枪>...");
    }
};

// 速射炮
class CannoArm : public Arms {
public:
    string getArms() override {
        return string("配备的武器是<速射炮>...");
    }
};

// 激光
class LaserArm : public Arms {
public:
    string getArms() override {
        return string("配备的武器是<激光>...");
    }
};

// 船类
class Ship {
public:
    Ship(ShipBody* body, Engine* engine, Arms* arm) :
        body_(body),
        engine_(engine),
        arm_(arm) {

    }

    string getShip() {
        string info = body_->getShipBody() + engine_->getEngine() + arm_->getArms();
        return info;
    }

    ~Ship() {
        delete body_;
        delete engine_;
        delete arm_;
    }
private:
    ShipBody* body_ = nullptr;
    Engine* engine_ = nullptr;
    Arms* arm_ = nullptr;
};

// 抽象工厂类
class AbatractFactory {
public:
    virtual Ship* createShip() = 0;
    virtual ~AbatractFactory() {}
};

// 基础型船厂
class BasicalFactory : public AbatractFactory {
public:
    Ship* createShip() override {
        Ship* ship = new Ship(new WoodBody, new manualEngine, new GunArm);
        cout << "<基础型>战船生产完毕, 可以下水啦..." << endl;
        return ship;
    }
};

// 标准型船厂
class StandalFactory : public AbatractFactory {
public:
    Ship* createShip() override {
        Ship* ship = new Ship(new SteelBody, new DieselEngine, new CannoArm);
        cout << "<标准型>战船生产完毕, 可以下水啦..." << endl;
        return ship;
    }
};

// 旗舰型船厂
class UltimateFactory  : public AbatractFactory {
public:
    Ship* createShip() override {
        Ship* ship = new Ship(new MetalBody, new nuclearEngine, new LaserArm);
        cout << "<旗舰型>战船生产完毕, 可以下水啦..." << endl;
        return ship;
    }
};

int main() {
    // 定义一个抽象工厂指针指向具体的工厂
    AbatractFactory* factory = new UltimateFactory;
    // 定义一个船类
    Ship* ship = factory->createShip();
    cout << ship->getShip() << endl;

    delete ship;
    delete factory;

    return 0;
}