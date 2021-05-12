#pragma once
#include <memory>
#include <mutex>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>
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
	virtual std::shared_ptr<base> clone() = 0;
};
class object :public base {
public:
	object(int a, int *b): A(a),B(b){}
	virtual std::shared_ptr<base> clone(){ 
		int *b = new int;
		*b = *B;
		std::shared_ptr<base> p(new object(A, b));
		return p;
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
//44444444444444444444444444444**********解释器模式**********4444444444444444444444444444444444444444444444444//
//******************************************************************************//

/*(a+(b+c))的调用形式为AndTerminalExpress(terminalExpress,AndTerminalExpress(terminalExpress,terminalExpress))*/
class Context {
private:
	std::unordered_map<terminalExpress*, int> m_mapTeminalValue;
public:
	int lookUp(terminalExpress* key) {
		try {
			auto it = m_mapTeminalValue.find(key);
			if (it != m_mapTeminalValue.end()) {
				return it->second;
			}
			throw("don't find the value.");
		}
		catch (const char* str) {
			printf("%s", str);
		}
		return 0;
	}
};
class express {
public:
	virtual int interpret(Context context) = 0;
};
//终端命令
class terminalExpress :public express {
public:
	terminalExpress() = delete;
	terminalExpress(string str) {
		key = str;
	}
	virtual int interpret(Context context) {
		context.lookUp(this);
	}
private:
	string key;
};
//非终端命令
class AndTerminalExpress :public express {
public:
	AndTerminalExpress() = delete;
	AndTerminalExpress(express* l, express* r) {
		left = l;
		right = r;
	}
	virtual int interpret(Context context) {
		return left->interpret(context) + right->interpret(context);
	}
private:
	express* left;
	express* right;
};
//****************************************行为型模式******************************************************************************//
//5555555555555555555555555555555**********命令模式**********5555555555555555555555555555//
//666666666666666666666666666666**********观察者模式**********666666666666666666666666666666666//
//******************************************************************************//
//此处运用了命令模式和观察者结合

//同一个command能注册多个receive，同一个receive也可以注册到多个command中
class command {
public:
	virtual void call() {
		for (auto m : m_listRecv) {
			m->run();
		}
	}
	virtual ~command() {
		for (auto c : m_listRecv) {
			if (c)
				c->noReCurRemoveCommand(this);
		}
	}
private:
	/////////////////此处仅允许receive使用////////////////////////

	virtual void add(receive* recv) final{
		if (recv) 
		{
			try {
				for (auto &n : m_listRecv) {
					if (n == recv)
						throw 0;
				}
			}
			catch (int n) {
				printf("命令中已有该接受者:%s,%s", __FILE__, __LINE__);
				return;
			}
			m_listRecv.push_back(recv);
		}

	}
	virtual void remove(receive* recv) final{
		if (recv) {
			auto it = m_listRecv.begin();
			for (; it != m_listRecv.end(); it++) {
				if (*it == recv)
				{
					m_listRecv.erase(it);
					return;
				}
			}
		}
	}
	friend class receive;
protected:
	std::list<receive*> m_listRecv;
};
class receive {
private:
	std::list<command*> m_listComm;
public: 
	virtual ~receive() {
		for (auto c: m_listComm) {
			if(c)
				c->remove(this);
			}
	}
	virtual void setCommand(command* c) final {
		if (c) {
			try {
				for (auto &n : m_listComm) {
					if (n == c)
						throw 0;
				}
			}
			catch (int n) {
				printf("命令中已有该接受者:%s,%s", __FILE__, __LINE__);
				return;
			}
			m_listComm.push_back(c);
			c->add(this);
		}
	}
	virtual void removeCommand(command* c) final {
		if (c)
		{
			auto it = m_listComm.begin();
			for (; it != m_listComm.end(); it++) {
				if (*it == c)
				{
					m_listComm.erase(it);
					c->remove(this);
					return;
				}
			}
		}
	}
	virtual void run() = 0;
protected:
	virtual void noReCurRemoveCommand(command* c) final {
		if (c)
		{
			auto it = m_listComm.begin();
			for (; it != m_listComm.end(); it++) {
				if (*it == c)
				{
					m_listComm.erase(it);
					return;
				}
			}
		}
	}
	friend class command;
};
class receive1 {
public:
	virtual void run() {}
};
class invoke {
public:
	invoke() = delete;
	invoke(command* c) {m_c = c;}
	void setCommand(command* c) { m_c = c; }
	void call() { 
		if(m_c)
			m_c->call();
	}
private:
	command* m_c;
};

//*************************行为型模式******************************************************************************//
//777777777777777777777777777777777**********中介者模式**********77777777777777777777777777777777777777777777777//
//******************************************************************************//
//与观察者类似，不过消息的发送者为接收者中的一个
//代码参考观察者


//*************************行为型模式******************************************************************************//
//8888888888888888888888888888888888888888**********访问者模式**********888888888888888888888888888888888888888//
//******************************************************************************//
//与观察者类似，不过消息的发送者为接收者中的一个
class medium {
public:
	void accept(BaseVisit *v) {
		if (v) {
			for (auto e : m_listElement) {
				if (e)
					e->accept(v);
			}
		}
	}
	void add(BaseElement* e) {
		m_listElement.push_back(e);
	}
	void remove(BaseElement* e) {
		m_listElement.remove(e);
	}
private:
	std::list<BaseElement*> m_listElement;
};
class BaseElement {
public:
	virtual void accept(BaseVisit* v) = 0;
};
class element1 :public BaseElement {
public:
	void accept(BaseVisit* v) {
		if (v)
			v->visit(this);
	}
};
class element2 :public BaseElement {
public:
	void accept(BaseVisit* v) {
		if (v)
			v->visit(this);
	}
};
class BaseVisit {
public:
	virtual void visit(BaseElement* e) = 0;
};
class visit1 {
public:
	virtual void visit(BaseElement* e) {}
};
class visit2 {
public:
	virtual void visit(BaseElement* e) {}
};
//*************************行为型模式******************************************************************************//
//9999999999999999999999999999999999**********备忘录模式**********999999999999999999999999999999999999999//
//******************************************************************************//
//运用克隆相结合
class memoryManage {
public:
	memoryManage() = delete;
	memoryManage(BaseMemory* pMomery):m_pMomery(pMomery){
		try {
			if (pMomery == nullptr)
				throw 0;
		}
		catch (int) {
			printf("传入了空值：%s-%s", __FILE__, __LINE__);
		}
	}
	void saveMemory() {
		if(m_pMomery)
			m_store.push(m_pMomery);
	}
	void movePre() {
		BaseMemory* p = m_store.pop();
		if (p) {
			delete m_pMomery;
			m_pMomery = p;
		}			
	}
private:
	BaseMemory* m_pMomery;
	store m_store;
};

class BaseMemory {
public:
	virtual BaseMemory* clone() = 0;
};
class memory:public BaseMemory {
public:
	virtual BaseMemory* clone() { 
		return new memory(*this); //默认浅拷贝，深拷贝需要自己实现，具体参考上面的原型模式
	}
private:
	int a;
};

class store {
public:
	void push(BaseMemory* o) {
		if(o)
			m_stackMemory.push(o);
	}
	BaseMemory* pop() {
		BaseMemory* res = m_stackMemory.top();
		m_stackMemory.pop();
		return res;
	}
private:
	stack<BaseMemory*> m_stackMemory;
};
//*************************行为型模式******************************************************************************//
//10 10 10 10 10 10 10**********责任链模式**********10 10 10 10 10 10 10// 
//******************************************************************************//
class handle {
public:
	void setNext(handle* p) { next = p; }
	handle* getNext()const { return next; }
	virtual void handleRequest(int n) = 0;
protected:
	int m_v;
private:
	handle* next;
};
class handle1 :public handle {
public:
	virtual void handleRequest(int n){
		if (n == m_v) {
			//Todo
		}
		else {
			if (getNext()) {
				getNext()->handleRequest(n);
				
			}
			else {
				printf("no one handle the request.");
			}
		}

	}
};
//*************************行为型模式******************************************************************************//
//11 11 11 11 11 11 11**********迭代器模式**********11 11 11 11 11 11 11//
//******************************************************************************//
class Object{};

class agregate {
public:
	virtual void add(Object*) = 0;
	virtual void remove(Object*) = 0;
	virtual Iterator* getIterator() = 0;
};
class agregate1 {
public:
	virtual void add(Object* o) {
		if(o)
			m_listData->push_back(o);
	}
	virtual void remove(Object* o) {
		if (o)
			m_listData->remove(o);
	}
	virtual Iterator* getIterator() {
		return dynamic_cast<Iterator *>(new Iterator1(m_listData));
	}
private:
	list<Object*> *m_listData = new list<Object*>;
};

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual void first() = 0;
	virtual agregate* next() = 0;
};
class Iterator1 {
public:
	Iterator1(list<Object*> *p){
		m_listData = p;
		i = -1;
	}
	virtual bool hasNext() {
		if (i < m_listData->size() - 1) {
			return true;
		}
		else {
			return false;
		}
	}
	virtual Object* first() {
		return m_listData->front();
	}
	virtual Object* next() {
		Object* o = nullptr;
		if (hasNext()) {
			int k = ++i;
			auto it = m_listData->begin();
			while (k--) {
				++it;
			}
			o = *it;
		}
		return o;
	}
private:
	list<Object*> *m_listData = nullptr;
	int i;
};