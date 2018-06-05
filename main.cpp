#include<bits/stdc++.h>

using namespace std;

string unitName[0][0]={};
double coefficient[0][0]={};

class unit{
	public:
		unit(){}
		~unit(){}
		double convert(string newUnit);//change the unit and return coefficient(if the unit type is different return -1)
		int set(string newUnit);//change the unit and return 0 if suceed(only use if the unit type is diffierent)
		string showUnit();//return the unit name
	private:
		int unitId;
		int unitType;
};

class unitNum:unit{
	public:
		int showVal();//return the value of the unitNum
		int change(string A);//change the val and the unit
		bool operator ==(const unitNum &A);//return true if both unit and val equal
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

