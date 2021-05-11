#pragma once
#include <memory>
#include <mutex>
#include <map>
#include <unordered_map>
#include <vector>
#include <random>
using namespace std;
//*************************创建者模式******************************************************************************//
//111111111111111111111111111111111**********工厂模式**********11111111111111111111111111111111111111//
//******************************************************************************//
/*1用户只需要知道具体工厂的名称就可得到所要的产品，无须知道产品的具体创建过程。
2灵活性增强，对于新产品的创建，只需多写一个相应的工厂类。
3典型的解耦框架。高层模块只需要知道产品的抽象类，无须关心其他实现类，满足迪米特法则、依赖倒置原则和里氏替换原则*/

/*类的个数容易过多，增加复杂度
增加了系统的抽象性和理解难度
抽象产品只能生产一种产品，此弊端可使用抽象工厂模式解决*/
class car {
public:
	virtual void drive()=0;
};
class bmwCar :public car {
public:
	virtual void drive() {};
};
class benzCar :public car {
public:
	virtual void drive() {};
};
class carFactory{
public:
	virtual car* createCar() = 0;
};
class bmwCarFactory :public carFactory {
public:
	virtual car* createCar() {
		return new bmwCar;
	};
};
class BenzCarFactory:public carFactory {
public:
	virtual car* createCar() {
		return new benzCar;
	};
};
//*************************创建者模式******************************************************************************//
//22222222222222222222222222222**********工厂模式**********22222222222222222222222222222//
/*可以在一个类中创建一个产品族的不同等级的产品，而不用引进新的类，客户端在调用一个产品族的不同产品时，可以保证只调用一个产品组的工厂即可*/

/*产品族中创建一个新产品的时候。所有工厂都要更改，增加了抽象性以及理解难度*/

class car {
public:
	virtual void drive() = 0;
};
class bmwCar :public car {
public:
	virtual void drive() {};
};
class benzCar :public car {
public:
	virtual void drive() {};
};

class phone {
public:
	virtual void call() = 0;
};
class bmwPhone :public phone {
public:
	virtual void call() {};
};
class benzPhone :public phone {
public:
	virtual void call() {};
};

class Factory {
public:
	virtual car* createCar() = 0;
	virtual phone* createPhone() = 0;
};
class bmwFactory :public Factory {
public:
	virtual car* createCar() {
		return new bmwCar;
	};
	virtual phone* createPhone() {
		return new bmwPhone;
	};
};
class BenzFactory :public Factory {
public:
	virtual car* createCar() {
		return new benzCar;
	};
	virtual phone* createPhone() {
		return new benzPhone;
	};
};
//*************************创建者模式******************************************************************************//
//3333333333333333333333333333333**********建造者模式**********3333333333333333333333333333333333//
/*构建与组装分离，客户端不需要了解构建细节，构建者可以对子部件的组装过程进行细化*/
/*内部构建复杂，一旦产品发生改变，构建类也得改变，后期维护成本较大*/
//个人感觉build删去更好，否则一旦修改产品部件，那么build都要修改，代价巨大
//产品类
template<class T>
class product {
public:
	void setPartA(T a) { this->partA = a; }
	void setPartB(T b) { this->partB = b; }
private:
	T partA;
	T partB;
};
//构建类
template<class T>
class Build {
public:
	build() {m_pProtect = std::make_shared<product<T>>();}
	virtual void buildA(T a) = 0;
	virtual void buildB(T b) = 0;
	auto getProtect()->decltype(m_pProtect){
		return m_pProtect;
	}
private:
	std::shared_ptr<product<T>> m_pProtect;
};
template<class T>
class concreteBuild:public Build<T>{
public:
	virtual void buildA(T a) {
		getProtect()->setPartA(a);
	}
	virtual void buildB(T b) {
		getProtect()->setPartB(b);
	}
};
//组装类
class director {
	std::shared_ptr<product<int>> getProduct() {
		m_build.buildA(1);
		m_build.buildB(2);
		return m_build.getProtect();
	}
private:
	concreteBuild<int> m_build;
};
//*************************创建者模式******************************************************************************//
//44444444444444444444444444444444444**********单例模式**********444444444444444444444444444444444444444444444//
/*保证内存中只有一个实例，优化了资源消耗。若将单例设为全局模式，则可以实现资源的共享*/
/*若要拓展功能的话，只能修改类本身，违反开闭原则；高并发下共享资源面临代码未执行完的情况；若要加多个功能的话，则违反了单一原则*/
class singleton {
public:
	virtual ~singleton(){}

	singleton* getInstance(){
		std::lock_guard<mutex> lock(m_mutex);
		if (m_pInstance == nullptr) {
			m_pInstance = new singleton();
		}
		return m_pInstance;
	}
	void unInstance() {
		if (m_pInstance) {
			delete m_pInstance;
		}
		m_pInstance = nullptr;
	}
private:
	singleton() = default;
private:
	std::mutex m_mutex;
	static singleton* m_pInstance;
};
singleton* m_pInstance(nullptr);
//*************************创建者模式******************************************************************************//
//55555555555555555555555555555555**********原型模式**********55555555555555555555555555555555555555//
/*可以快速的实现一个实例的克隆，而不必new出来一个实例进行再进行属性赋值*/
/*修改类属性也要修改clone方法，违反了开闭原则；对象之间存在多重嵌套引用时，为了实现深克隆，每一层对象对应的类都必须支持深克隆*/
/*与深拷贝的区别：由于多态的原因，可以通过父指针克隆一个实例，而深拷贝不行*/
class base {
public:
	virtual std::shared_ptr<base> Clone() = 0;
};
class object :public base {
public:
	object(int a, int *b): A(a),B(b){}
	virtual std::shared_ptr<base> Clone() override{ 
		int *b = new int;
		*b = *B;
		return std::make_shared<object>(A, b);
	}
private:
	int A;
	int *B;
};
//************************结构型模式******************************************************************************//
//111111111111111111111111111111111**********代理模式**********11111111111111111111111111111111111111//
//******************************************************************************//
/*代理模式与装饰者以及适配器模式结构类似，不同的是代理和装饰者模式中业务类和代理类是关联关系，而适配器是继承关系*/
/*装饰者的重点在扩展业务类功能，而适配器重点在匹配接口*/
/*
代理、装饰、适配器
组合-组合
聚合-外观、桥接、享元
*/
class machine{
public:
	virtual void run() = 0;
};
class realmachine:public machine{
public:
	virtual void run() override{}
};
class degatemachine :public machine {
public:
	void beforeRun(){}
	void afterRun(){}
	virtual void run() override {
		if (!m_pMachine)
			m_pMachine = new realmachine;
		beforeRun();
		if(m_pMachine)
			m_pMachine->run();
		afterRun();
	}
	virtual ~degatemachine() {
		if (m_pMachine) {
			delete m_pMachine;
			m_pMachine = nullptr;
		}
			
	}
private:
	realmachine *m_pMachine=nullptr;
};
//************************结构型模式******************************************************************************//
//222222222222222222222222222222*********适配器模式***********22222222222222222222222222222222//
//******************************************************************************//
class abstractAdapter {
	virtual void request()=0;
};
class adaptee:public abstractAdapter {
public:
	void specificRequest() {};
};
class adapter :public adaptee {
public:
	virtual void request() override {
		specificRequest();
	};
};
//************************结构型模式******************************************************************************//
//33333333333333333**********装饰者模式**********333333333333333333333333333333333//
//******************************************************************************//
class machin {
public:
	virtual void run() = 0;
};
class realmachin :public machin {
public:
	virtual void run() override {}
};
class degatemachin :public machin {
public:
	void addfunction() {}
	virtual void run() override {
		if (!m_pMachine)
			m_pMachine = new realmachin;
		if (m_pMachine)
			m_pMachine->run();
		addfunction();
	}
	virtual ~degatemachin() {
		if (m_pMachine) {
			delete m_pMachine;
			m_pMachine = nullptr;
		}

	}
private:
	realmachin *m_pMachine = nullptr;
};
//************************结构型模式******************************************************************************//
//444444444444444444444**********外观模式**********44444444444444444444444444444444444444//
//******************************************************************************//
class subSytem1 {
public:
	void work1(){}
};
class subSytem2 {
public:
	void work2() {}
};
class subSytem3 {
public:
	void work3() {}
};
class system {
public:
	void work() {
		s1.work1();
		s2.work2();
		s3.work3();
	}
private:
	subSytem1 s1;
	subSytem2 s2;
	subSytem3 s3;
};
//************************结构型模式******************************************************************************//
//555555555555555555555555555555555**********共享模式**********55555555555555555555555555555555//
//******************************************************************************//
class abstractShared {
public:
	virtual void work() = 0;
};
class shared :public abstractShared {
public:
	virtual void work()override{}
private:
	//ADD：此处添加需要共享的成员
};
class sharedFactory {
public:
	void pushShared(int nkey/*...添加共享参数*/){
		abstractShared* s = new shared(/*...添加共享参数*/);
		if(s)
			m_mapShared[nkey] = s;
	}
	abstractShared* getShared(int nkey) {
		auto it = m_mapShared.find(nkey);
		if (it != m_mapShared.end()) {
			return it->second;
		}
		return nullptr;
	}
private:
	map<int, abstractShared*> m_mapShared;
};
//************************结构型模式******************************************************************************//
//666666666666666666666666666666666666666**********桥接模式**********666666666666666666666666666666666//
//******************************************************************************//
class brand {
public:
	virtual void level() = 0;
};
class RollsRoyce :public brand {
public:
	virtual void level() {
		printf("level 1");
	}
};
class BMW :public brand {
public:
	virtual void level() {
		printf("level 2");
	}
};
class Car {
protected:
	brand* m_brand;
public:
	virtual void setBrand(brand *pBrand) = 0;
	virtual void carinfo() = 0;
};
class saloon : public Car{
public:
	void setBrand(brand *pBrand) { m_brand = pBrand; }
	virtual void carinfo() {
		printf("this a saloon---");
		if (m_brand)
			m_brand->level();
	}
};
class suv : public Car {
public:
	void setBrand(brand *pBrand) { m_brand = pBrand; }
	virtual void carinfo() {
		printf("this a suv---");
		if (m_brand)
			m_brand->level();
	}
};
//************************结构型模式******************************************************************************//
//77777777777777777777777777777777777777777**********组合模式**********77777777777777777777777777777777//
//******************************************************************************//
class area {
public:
	virtual int nums() = 0;
};
class province :public area {
public:
	virtual int nums() {
		int num = 0;
		for (auto n : citys) {
			num += n->nums();
		}
		return num;
	}
private:
	std::vector<area*> citys;
};
class city :public area {
public:
	virtual int nums() {
		return rand();
	}
};
//*************************行为型模式******************************************************************************//
//111111111111111111111111111111111**********模板模式**********11111111111111111111111111111111111111//
//******************************************************************************//
/*对同类型事情拆步骤解决，但是步骤的具体实现在子类当中，提取了公共部分，不同部分由子类实现*/

/*类的个数容易过多，增加复杂度，父类增加功能，子类都要改写*/
/*
多选一：1策略   2命令（业务处理为接收者）  3状态（按状态调用业务）   4模板（业务类里处理分步骤处理业务，基类调用业务接口）
一选多：通信：1观察者（订阅-》发布）    2中介类（业务类发布-》中介类发布-》所有业务类接收）3访问者（外部访问者直接通过中介类传给业务类）
		（三者区别：信息发布者分别为中介、业务、外部）
		迭代：1责任链     2迭代器
一对一：备忘录
二对一：解释者模式
*/

class cook {
public:
	virtual void step1() = 0;
	virtual void step2() = 0;
	void cooking() {
		step1();
		step2();
	}
};
class cookRice:public cook {
public:
	virtual void step1() override{}
	virtual void step2() override {}
};
class cookCorn :public cook {
public:
	virtual void step1() override {}
	virtual void step2() override {}
};
//*************************行为型模式******************************************************************************//
//22222222222222222222222**********状态模式**********22222222222222222222222222222//
//******************************************************************************//
/*与std::map联合使用解决if-else，switch-case等冗余语句问题*/

/*类的个数容易过多，增加复杂度，容易造成代码混乱*/

//状态模式和模板模式的区别：动作的执行时放在额外的类还是在基类当中
class state {
public:
	virtual void say() = 0;
};
class happyState :public state {
public:
	virtual void say() override{};
};
class angryState :public state {
public:
	virtual void say() override {};
};
class context {
private:
	state* m_state=nullptr;
public:
	void changeState(state* pstate) {
		m_state = pstate;
	}
	void doSomething() {
		if (m_state) {
			m_state->say();
		}
	}
};
//*************************行为型模式******************************************************************************//
//3333333333333333333333333333**********策略模式**********33333333333333333333333333//
//******************************************************************************//

//与状态模式相似，但是更加注重策略，策略是为了实现相同的目的但是使用不同的算法，而不是状态的切换
//与std::map联合使用，可以解决if-else，switch-case等冗余语句问题
class order {
public:
	virtual void work() = 0;
};
class sheerOrder :public order {
public:
	virtual void work() override {};
};
class stackOrder :public order {
public:
	virtual void work() override {};
};
class context {
public:
	void run(order* porder) {
		porder->work();
	}
};
//*************************行为型模式******************************************************************************//
//44444444444444444444444444444**********命令模式**********444444444444444444444444444444444//
//******************************************************************************//

//*************************行为型模式******************************************************************************//
//55555555555555555555555555555555555**********命令模式**********55555555555555555555555555555555555555//
//******************************************************************************//y
对