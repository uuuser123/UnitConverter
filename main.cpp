#include<bits/stdc++.h>
using namespace std;

class Unit{
	public:
		int show() const;
		Unit(double _val,string _symbol):val(_val),symbol(_symbol){}
		~Unit(){}
		Unit operator + (const Unit &add){}
		Unit operator - (const Unit &add){}
		Unit operator * (const Unit &add){}
		Unit operator / (const Unit &add){}
		Unit operator > (const Unit &add){}
		Unit operator < (const Unit &add){}
		Unit operator == (const Unit &add){}
	private:
		double val;
		string symbol;
};

class Weight:public Unit{
	public:
		Weight(int _val,string _symbol,double _coefficient):Unit(_val,_symbol),coefficient(_coefficient){}
		~Weight(){}
		
	private:
		double coefficient;
};


int main(){
	Weight a(1,"1",1);
	Weight b(2,"2",2);
	Weight c = a+b;
	return 0;
}

