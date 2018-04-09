/**************************************************************************//**
 * @file	zztest.cc
 * @brief	測試用專案
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-24
 * @note	none
 *****************************************************************************/
#include "acore\acore.hh"

using namespace std;

class Base
{
public:
	Base() {}
	virtual ~Base() {}

	virtual void func1() { printf("this is base - func1 \n"); }
	virtual void func2() { printf("this is base - func2 \n"); }
	virtual void func3() { printf("this is base - func3 \n"); }
	virtual void func4() { printf("this is base - func4 \n"); }
	void func5() { printf("this is base - func5 \n"); }
};

class Father : public Base
{
public:
	Father() : Base() {}
	virtual ~Father() {}

	virtual void func1() { printf("this is father - func1 \n"); }
	virtual void func2() { printf("this is father - func2 \n"); Base::func2(); }
	virtual void func3() { printf("this is father - func3 \n"); }
	virtual void func4() { printf("this is father - func4 \n"); }
	void func5() { printf("this is father - func5 \n"); }
};

class Child : public Father
{
public:
	Child() : Father() {}
	virtual ~Child() {}

	virtual void func1() { printf("this is child - func1 \n"); }
	virtual void func2() { printf("this is child - func2 \n"); Father::func2(); }
	virtual void func3() { printf("this is child - func3 \n"); }
	virtual void func4() { printf("this is child - func4 \n"); }
	void func5() { printf("this is child - func5 \n"); }
};





int main(int argc, char *argv)
{
	Base*	baseObj = new (std::nothrow) Base();
	Father* fathObj = new (std::nothrow) Father();
	Child*	chldObj = new (std::nothrow) Child();

	Base*	punkObj;

	printf("Base*	baseObj:\n");
	baseObj->func1();
	baseObj->func2();
	baseObj->func5();

	printf("\n\n");
	printf("Father* fathObj:\n");
	fathObj->func1();
	fathObj->func2();
	fathObj->func5();

	printf("\n\n");
	printf("Child* chldObj:\n");
	chldObj->func1();
	chldObj->func2();
	chldObj->func5();

	printf("\n\n");
	printf("Father* fathObj Pass to : Base*	punkObj:\n");
	punkObj = (Base*)fathObj;
	punkObj->func1();
	punkObj->func2();
	punkObj->func5();

	printf("\n\n");
	printf("Child* chldObj Pass to : Base*	punkObj:\n");
	punkObj = (Base*)chldObj;
	punkObj->func1();
	punkObj->func2();
	punkObj->func5();

	printf("\n\n");
	SAFE_DELETE(chldObj);
	SAFE_DELETE(fathObj);
	SAFE_DELETE(baseObj);
	system("pause");
	return 0;
}
