#include<bits/stdc++.h>

using namespace std;

const int maxUnitNum=100,maxUnitType=10;
string unitTypeName[maxUnitType]={"length","mass","time","electric current","thermodynamic temperature","amount of substance","luminous intensity"};
string unitName[maxUnitType][maxUnitNum]={{"mm","cm","m","km","inch","feet"},{"mg","g","kg","t"}};
double coefficient[maxUnitType][maxUnitNum]={{1e-3,1e-2,1,1e3,0.0254,0.3048},{1e-3,1,1e3,1e6}};

class unit{
	public:
		unit(){}
		~unit(){}
		double convert(string newUnit);//change the unit and return coefficient(if the unit type is different return -1)
		int set(string newUnit);//change the unit and return 0 if suceed(only use if the unit type is diffierent)
		string showUnit();//return the unit name
		string showUnitTypeName();//return the unit type name
	private:
		int unitId;
		int unitType;
};

double unit::convert(string newUnit)
{
	for(int i=0;i<maxUnitType;i++)
	{
		for(int j=0;j<maxUnitNum;j++)
		{
			if(newUnit==unitName[i][j])
			{
				if(i!=unitType)
				{
					return -1;
				}
				double ret=coefficient[unitType][unitId]/coefficient[unitType][j];
				unitId=j;
				unitType=i;
				return ret;
			}
		}
	}
	return -1;
}

int unit::set(string newUnit)
{
	for(int i=0;i<maxUnitType;i++)
	{
		for(int j=0;j<maxUnitNum;j++)
		{
			if(newUnit==unitName[i][j])
			{
				unitId=j;
				unitType=i;
				return 0;
			}
		}
	}
	return 1;
}

string unit::showUnit()
{
	return unitName[unitType][unitId];
}

string unit::showUnitTypeName()
{
	return unitTypeName[unitType];
}

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

