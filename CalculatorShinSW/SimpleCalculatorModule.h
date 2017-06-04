#include "stdafx.h"
#include "vector"
#include "string"
#define MAX_CHATTING_SIZE 1000
#pragma once
#pragma warning(disable:4996)
using namespace std;
class SimpleCalculatorModule{
private:
	CString decTobi(int number);
	CString decTohd(int number);	
	vector<int> v;
	
public:
	SimpleCalculatorModule();

	int a;
	int b;
	int status;
	int add();
	int sub();
	int mul();
	double mod();
	void reset();

	void save(int number);
	int getSize();

	void InsertionSort();
	void SelectionSort();
	void BubbleSort();

	CString getIndexof(int number);
	CString calAndOrXor(CString s1,CString s2,int K);
	CString intConverter(CString number,int K,int TARGET_K);
	CString CAtoHA(char* carray,int length);
	
};