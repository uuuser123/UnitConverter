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
		double showVal();//return the value of the unitNum
		int change(string A);//change the val and the unit
		//support the operator
		bool operator == (const unitNum &A);//return true if both unit and val equal
		bool operator < (const unitNum &A);
		bool operator > (const unitNum &A);
		bool operator <= (const unitNum &A);
		bool operator >= (const unitNum &A);
		unitNum operator + (const unitNum &A);
		unitNum operator - (const unitNum &A);
		unitNum operator * (const unitNum &A);
		unitNum operator / (const unitNum &A);
	private:
		double val;
};

double unitNum::showVal(){
	double integer = 0,decimal = 0;
	int d_cnt = 0;
	int dot = 0;
	for(int i = 0;i < unitNumStr.length();i++){
		char tmp = unitNum[i];
		if(tmp == ' ') continue;
		if(!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' &&
		tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) return -1;
		if((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')){
			set(unitNumStr.substr(i));
			while(d_cnt--){
				decimal *= 0.1;
			}
			return integer + decimal;
		}
		if(tmp == '.'){
			dot = 1;
			continue;
		}
		if(!dot){
			integer *= 10;
			integer += tmp - '0';
		}
		else{
			decimal *= 10;
			decimal += tmp - '0';
			d_cnt++;
		}
	}
	return 0;
}
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

