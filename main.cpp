#include<bits/stdc++.h>

using namespace std;

class Unit{
	public:
		int Show() const;
		Unit(double _val, string _symbol):val(_val),symbol(_symbol){}
		~Unit(){}
	protected:
		double val;
		string symbol;
};

int Unit::Show() const
{
	printf("%lf%s\n",val,&symbol[0]);
	return 0;
}

class Weight:public Unit{
	public:
		Weight(int _val,string _symbol):Unit(_val,_symbol){coefficient=0.1;}
		~Weight(){}
		Weight operator + (const Weight &add){return Weight(val+add.val,symbol);}
	private:
		double coefficient;
};


int main(){
	Weight a(1,"kg");
	Weight b(2,"kg");
	Weight c = a+b;
	c.Show();
	return 0;
}

