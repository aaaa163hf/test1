#pragma once
#include <memory>
#include <mutex>
#include <map>
#include <unordered_map>
#include <vector>
#include <random>
using namespace std;
//*************************������ģʽ******************************************************************************//
//111111111111111111111111111111111**********����ģʽ**********11111111111111111111111111111111111111//
//******************************************************************************//
/*1�û�ֻ��Ҫ֪�����幤�������ƾͿɵõ���Ҫ�Ĳ�Ʒ������֪����Ʒ�ľ��崴�����̡�
2�������ǿ�������²�Ʒ�Ĵ�����ֻ���дһ����Ӧ�Ĺ����ࡣ
3���͵Ľ����ܡ��߲�ģ��ֻ��Ҫ֪����Ʒ�ĳ����࣬�����������ʵ���࣬��������ط�����������ԭ��������滻ԭ��*/

/*��ĸ������׹��࣬���Ӹ��Ӷ�
������ϵͳ�ĳ����Ժ�����Ѷ�
�����Ʒֻ������һ�ֲ�Ʒ���˱׶˿�ʹ�ó��󹤳�ģʽ���*/
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
//*************************������ģʽ******************************************************************************//
//22222222222222222222222222222**********����ģʽ**********22222222222222222222222222222//
/*������һ�����д���һ����Ʒ��Ĳ�ͬ�ȼ��Ĳ�Ʒ�������������µ��࣬�ͻ����ڵ���һ����Ʒ��Ĳ�ͬ��Ʒʱ�����Ա�ֻ֤����һ����Ʒ��Ĺ�������*/

/*��Ʒ���д���һ���²�Ʒ��ʱ�����й�����Ҫ���ģ������˳������Լ�����Ѷ�*/

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
//*************************������ģʽ******************************************************************************//
//3333333333333333333333333333333**********������ģʽ**********3333333333333333333333333333333333//
/*��������װ���룬�ͻ��˲���Ҫ�˽⹹��ϸ�ڣ������߿��Զ��Ӳ�������װ���̽���ϸ��*/
/*�ڲ��������ӣ�һ����Ʒ�����ı䣬������Ҳ�øı䣬����ά���ɱ��ϴ�*/
//���˸о�buildɾȥ���ã�����һ���޸Ĳ�Ʒ��������ôbuild��Ҫ�޸ģ����۾޴�
//��Ʒ��
template<class T>
class product {
public:
	void setPartA(T a) { this->partA = a; }
	void setPartB(T b) { this->partB = b; }
private:
	T partA;
	T partB;
};
//������
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
//��װ��
class director {
	std::shared_ptr<product<int>> getProduct() {
		m_build.buildA(1);
		m_build.buildB(2);
		return m_build.getProtect();
	}
private:
	concreteBuild<int> m_build;
};
//*************************������ģʽ******************************************************************************//
//44444444444444444444444444444444444**********����ģʽ**********444444444444444444444444444444444444444444444//
/*��֤�ڴ���ֻ��һ��ʵ�����Ż�����Դ���ġ�����������Ϊȫ��ģʽ�������ʵ����Դ�Ĺ���*/
/*��Ҫ��չ���ܵĻ���ֻ���޸��౾��Υ������ԭ�򣻸߲����¹�����Դ���ٴ���δִ������������Ҫ�Ӷ�����ܵĻ�����Υ���˵�һԭ��*/
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
//*************************������ģʽ******************************************************************************//
//55555555555555555555555555555555**********ԭ��ģʽ**********55555555555555555555555555555555555555//
/*���Կ��ٵ�ʵ��һ��ʵ���Ŀ�¡��������new����һ��ʵ�������ٽ������Ը�ֵ*/
/*�޸�������ҲҪ�޸�clone������Υ���˿���ԭ�򣻶���֮����ڶ���Ƕ������ʱ��Ϊ��ʵ�����¡��ÿһ������Ӧ���඼����֧�����¡*/
/*��������������ڶ�̬��ԭ�򣬿���ͨ����ָ���¡һ��ʵ�������������*/
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
//************************�ṹ��ģʽ******************************************************************************//
//111111111111111111111111111111111**********����ģʽ**********11111111111111111111111111111111111111//
//******************************************************************************//
/*����ģʽ��װ�����Լ�������ģʽ�ṹ���ƣ���ͬ���Ǵ����װ����ģʽ��ҵ����ʹ������ǹ�����ϵ�����������Ǽ̳й�ϵ*/
/*װ���ߵ��ص�����չҵ���๦�ܣ����������ص���ƥ��ӿ�*/
/*
����װ�Ρ�������
���-���
�ۺ�-��ۡ��Žӡ���Ԫ
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
//************************�ṹ��ģʽ******************************************************************************//
//222222222222222222222222222222*********������ģʽ***********22222222222222222222222222222222//
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
//************************�ṹ��ģʽ******************************************************************************//
//33333333333333333**********װ����ģʽ**********333333333333333333333333333333333//
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
//************************�ṹ��ģʽ******************************************************************************//
//444444444444444444444**********���ģʽ**********44444444444444444444444444444444444444//
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
//************************�ṹ��ģʽ******************************************************************************//
//555555555555555555555555555555555**********����ģʽ**********55555555555555555555555555555555//
//******************************************************************************//
class abstractShared {
public:
	virtual void work() = 0;
};
class shared :public abstractShared {
public:
	virtual void work()override{}
private:
	//ADD���˴������Ҫ����ĳ�Ա
};
class sharedFactory {
public:
	void pushShared(int nkey/*...��ӹ������*/){
		abstractShared* s = new shared(/*...��ӹ������*/);
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
//************************�ṹ��ģʽ******************************************************************************//
//666666666666666666666666666666666666666**********�Ž�ģʽ**********666666666666666666666666666666666//
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
//************************�ṹ��ģʽ******************************************************************************//
//77777777777777777777777777777777777777777**********���ģʽ**********77777777777777777777777777777777//
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
//*************************��Ϊ��ģʽ******************************************************************************//
//111111111111111111111111111111111**********ģ��ģʽ**********11111111111111111111111111111111111111//
//******************************************************************************//
/*��ͬ������������������ǲ���ľ���ʵ�������൱�У���ȡ�˹������֣���ͬ����������ʵ��*/

/*��ĸ������׹��࣬���Ӹ��Ӷȣ��������ӹ��ܣ����඼Ҫ��д*/
/*
��ѡһ��1����   2���ҵ����Ϊ�����ߣ�  3״̬����״̬����ҵ��   4ģ�壨ҵ�����ﴦ��ֲ��账��ҵ�񣬻������ҵ��ӿڣ�
һѡ�ࣺͨ�ţ�1�۲��ߣ�����-��������    2�н��ࣨҵ���෢��-���н��෢��-������ҵ������գ�3�����ߣ��ⲿ������ֱ��ͨ���н��ഫ��ҵ���ࣩ
		������������Ϣ�����߷ֱ�Ϊ�н顢ҵ���ⲿ��
		������1������     2������
һ��һ������¼
����һ��������ģʽ
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
//*************************��Ϊ��ģʽ******************************************************************************//
//22222222222222222222222**********״̬ģʽ**********22222222222222222222222222222//
//******************************************************************************//
/*��std::map����ʹ�ý��if-else��switch-case�������������*/

/*��ĸ������׹��࣬���Ӹ��Ӷȣ�������ɴ������*/

//״̬ģʽ��ģ��ģʽ�����𣺶�����ִ��ʱ���ڶ�����໹���ڻ��൱��
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
//*************************��Ϊ��ģʽ******************************************************************************//
//3333333333333333333333333333**********����ģʽ**********33333333333333333333333333//
//******************************************************************************//

//��״̬ģʽ���ƣ����Ǹ���ע�ز��ԣ�������Ϊ��ʵ����ͬ��Ŀ�ĵ���ʹ�ò�ͬ���㷨��������״̬���л�
//��std::map����ʹ�ã����Խ��if-else��switch-case�������������
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
//*************************��Ϊ��ģʽ******************************************************************************//
//44444444444444444444444444444**********����ģʽ**********444444444444444444444444444444444//
//******************************************************************************//

//*************************��Ϊ��ģʽ******************************************************************************//
//55555555555555555555555555555555555**********����ģʽ**********55555555555555555555555555555555555555//
//******************************************************************************//y
��