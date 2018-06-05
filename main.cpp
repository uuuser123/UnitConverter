#include<bits/stdc++.h>

using namespace std;

string unitTypeName[0]={};
string unitName[0][0]={};
double coefficient[0][0]={};

class unit{
	public:
		unit(){}//parse the unitId and the unitType
		~unit(){}
		double convert(string newUnit);//change the unit and return coefficient(if the unit type is different return -1)
		int set(string newUnit);//change the unit and return 0 if suceed(only use if the unit type is diffierent)
		string showUnit();//return the unit name
		string showUnitTypeName();//return the unit type name
	private:
		int unitId;
		int unitType;
};

class unitNum:unit{
	public:
		unitNum(string unitNumStr):unit(){set("");}//parse the value
		int showVal();//return the value of the unitNum
		int change(string A);//change the val and the unit
		//support the operator
		bool operator ==(const unitNum &A);//return true if both unit and val equal
		bool operator <(const unitNum &A);
		bool operator >(const unitNum &A);
		bool operator <=(const unitNum &A);
		bool operator >=(const unitNum &A);
		unitNum operator + (const unitNum &A);
		unitNum operator - (const unitNum &A);
		unitNum operator * (const unitNum &A);
		unitNum operator / (const unitNum &A);
	private:
		double val;
};

class console{
	public:
		console(){}
		~console(){}
		int startConsole();
	private:
		
};

int console::startConsole(){
	while(true){
		//deal with the instruction
	}
	return 0;
}


int main(){
	
	return 0;
}

