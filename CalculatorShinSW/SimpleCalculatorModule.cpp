#include "stdafx.h"
#include "iostream"
#include "SimpleCalculatorModule.h"
using namespace std;
// +
SimpleCalculatorModule::SimpleCalculatorModule(){
	a=-1;
	b=-1;
	status=0;
}

int SimpleCalculatorModule :: add(){
	return a+b;
}

// -
int SimpleCalculatorModule :: sub(){
	return a-b;
}

// *
int SimpleCalculatorModule :: mul(){
	return a*b;
}

// /
double SimpleCalculatorModule :: mod(){
	return (double)a/(double)b;
}
// reset value
void SimpleCalculatorModule :: reset(){
	a=-1;
	b=-1;
	status=0;
}
//save value
void SimpleCalculatorModule :: save(int number){
	v.push_back(number);
}
int SimpleCalculatorModule :: getSize(){
	return v.size();
}
CString SimpleCalculatorModule :: getIndexof(int number){
	CString result;
	result.Format(_T("%d"),v[number]);
	return result;
}

// decimal ->binary
CString SimpleCalculatorModule :: decTobi(int number){
	int count =1;
	int numbertemp=number;
	
	while(number>1){
		number/=2;
		count++;
	}	
	
	int* boxes=(int*)malloc(count*sizeof(int));
	
	for(int i=count-1;i>=0;i--){
		boxes[i]=numbertemp%2;
		numbertemp/=2;						
	}

	CString msg;

	for(int i=0;i<count;i++){
		if(boxes[i]==0)
			msg+="0";
		else
			msg+="1";		
	}	
	return msg;
}

//decimal->hexadecimal
CString SimpleCalculatorModule :: decTohd(int number){
	int count =0;
	int numbertemp=number;
	
	while(number>0){
		number/=16;
		count++;
	}	
	int* boxes=(int*)malloc(count*sizeof(int));
	
	for(int i=count-1;i>=0;i--){
		boxes[i]=numbertemp%16;
		numbertemp/=16;						
	}

	CString msg;
	for(int i=0;i<count;i++){
		if(boxes[i]>=0&&boxes[i]<10)			
			msg+=(char)(boxes[i]+48);		
		else
			msg+=(char)(boxes[i]+55);		
	}
	
	return msg;	
}

// 진법 변환
CString SimpleCalculatorModule :: intConverter(CString number, int K, int TARGET_K){
	
	if((K!=2&&K!=10&&K!=16)||(TARGET_K!=2&&TARGET_K!=10&&TARGET_K!=16))
		return NULL;
	
	if(K==TARGET_K)
		return number;

	int size=number.GetLength();
	char *number_char=(char*)malloc(sizeof(char)*number.GetLength());

	for(int i=0;i<number.GetLength();i++)
		number_char[i]=number[i];
	
	int decNumber=0;	

	if(K==2){
		for(int i=0;i<size;i++){
			if(number_char[i]!='0'&&number_char[i]!='1')
				return NULL;

			decNumber+=(int)(number_char[i]-'0')*pow(K,size-i-1);				
		}
	}else if(K==16){
		for(int i=0;i<size;i++){
			int temp;
			if((int)number_char[i]>47&&(int)number_char[i]<58)
				temp=(int)number_char[i]-48;
			else if((int)number_char[i]>64&&(int)number_char[i]<71)
				temp=(int)number_char[i]-55;
			else				
				return NULL;
			
			decNumber+=temp*pow(K,size-i-1);			
		}
	}else
		decNumber = atoi(number_char);			
		CString x;
		x.Format(_T("%d"),decNumber);
		
	if(TARGET_K==2)
		return decTobi(decNumber);
	else if(TARGET_K==10)
		return x;
	else
		return decTohd(decNumber);
}

// and or xor 연산
CString SimpleCalculatorModule :: calAndOrXor(CString s1,CString s2,int K){
	if(s1.GetLength()!=s2.GetLength())
		return CString("Length doesn't match");

	int length=s1.GetLength();
	CString result;
	if(K==1){
		for(int i=0;i<length;i++){
			int x=((int)(s1[i]-'0'))&((int)(s2[i]-'0'));
			CString temp;
			temp.Format(_T("%d"),x);
			result+=temp;
		}
	}else if(K==2){
		for(int i=0;i<length;i++){
			int x=((int)(s1[i]-'0'))|((int)(s2[i]-'0'));
			CString temp;
			temp.Format(_T("%d"),x);
			result+=temp;
		}
	}else if(K==3){
		for(int i=0;i<length;i++){
			int x=((int)(s1[i]-'0'))^((int)(s2[i]-'0'));
			CString temp;
			temp.Format(_T("%d"),x);
			result+=temp;
		}
	}else
		return CString("Internal Error!\n");

	return result;
}
//삽입정렬
void SimpleCalculatorModule :: InsertionSort(){
	for(int i=1;i<v.size();i++){
		int key=v[i],j=i-1;
		while(j>=0 && key<v[j]){
			swap(v[j],v[j+1]);
			j--;
		}
		v[j+1]=key;
	}
}
//선택정렬
void SimpleCalculatorModule :: SelectionSort(){
	for(int i=0;i<v.size()-1;i++){
		for(int j=i+1;j<v.size();j++)
			if(v[i]>v[j]) swap(v[i],v[j]);
	}
}
//버블정렬
void SimpleCalculatorModule :: BubbleSort(){
	for(int i=0;i<v.size()-1;i++){
		for(int j=1;j<v.size()-i;j++)
			if(v[j-1]>v[j])
				swap(v[j-1],v[j]);
	}
}



CString SimpleCalculatorModule::CAtoHA(char* carray,int length){//carray -> 일반 문자열,1자씩 끊어서16진수화

	CString sum("");
	CString pre("0x");
	CString post(" ");

	for(int i=0;i<length;i++)		
		sum=sum+pre+decTohd((int)carray[i])+post;		
	
	return sum;
}