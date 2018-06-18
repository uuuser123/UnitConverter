#include<bits/stdc++.h>
#include<QApplication>
#include<QMainWindow>
#include<QLayout>
#include<QLabel>
#include<QPushButton>
#include<QWidget>
#include<QTextCodec>
#include<QLineEdit>
#include<QMessageBox>

using namespace std;

const int maxUnitNum=100,maxUnitType=8;
string unitTypeName[maxUnitType]={"Err","length","area","volume","mass","time","current","pressure"};
string unitName[maxUnitType][maxUnitNum]={{"Err"},{"mm","cm","m","km","inch","feet"},{"mm^2","cm^2","m^2","km^2"},{"mm^3","mL","L","m^3"},{"mg","g","kg","t"},{"ms","s","min","h"},{"mA","A","kA"},{"atm","Pa","hPa","kPa"}};

double coefficient[maxUnitType][maxUnitNum]={{},{1e-3,1e-2,1,1e3,0.0254,0.3048},{1e-6,1e-4,1,1e6},{1e-3,1,1e3,1e6},{1e-3,1,1e3,1e6},{1e-3,1,60,3600},{1e-3,1,1e3},{98692327*1e-13,1,1e2,1e3}}; 
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
	for(int i=1;i<maxUnitType;i++)
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
	unitType=0;
	unitId=0;
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

class unitNum:public unit{
	public:
		int parse(string unitNumStr);//parse the value
		unitNum(string unitNumStr):unit(){parse(unitNumStr);}
		double showVal();//return the value of the unitNum
		int convertUnit(string newUnit);
		//support the operator
		bool operator == (unitNum A);//return true if both unit and val equal
		bool operator < (unitNum A);
		bool operator > (unitNum A);
		bool operator <= (unitNum A);
		bool operator >= (unitNum A);
		unitNum operator + (unitNum A);
		unitNum operator - (unitNum A);
	private:
		double val;
};

double unitNum::showVal()
{
	return val;
}

int unitNum::convertUnit(string newUnit)
{
	double ret=convert(newUnit);
	if(ret==-1)
		return -1;
	val*=ret;
	return 0;
}

int unitNum::parse(string unitNumStr){
	double integer = 0,decimal = 0;
	int d_cnt = 0;
	int dot = 0;
	for(int i = 0;i < (int)unitNumStr.length();i++){
		char tmp = unitNumStr[i];
		if(tmp == ' ') continue;
		if(tmp == '.'){
			dot = 1;
			continue;
		}
		if(!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' &&
		tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) break;
		if((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')){
			set(unitNumStr.substr(i));
			while(d_cnt--){
				decimal *= 0.1;
			}
			val = integer + decimal;
			return 0;
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

bool unitNum::operator == (unitNum A){
	A.convertUnit(showUnit());
	return val == A.val && A.showUnit()==showUnit();
}

bool unitNum::operator >= (unitNum A){
	A.convertUnit(showUnit());
	return val >= A.val && A.showUnit()==showUnit();
}

bool unitNum::operator <= (unitNum A){
	A.convertUnit(showUnit());
	return val <= A.val && A.showUnit()==showUnit();
}

bool unitNum::operator > (unitNum A){
	A.convertUnit(showUnit());
	return val > A.val && A.showUnit()==showUnit();
}

bool unitNum::operator < (unitNum A){
	A.convertUnit(showUnit());
	return val < A.val && A.showUnit()==showUnit();
}

unitNum unitNum::operator + (unitNum A){
	A.convertUnit(showUnit());
	A.val = val + A.val;
	return A;
}

unitNum unitNum::operator - (unitNum A){
	A.convertUnit(showUnit());
	A.val = val - A.val;
	return A;
}

class mainWin:public QMainWindow{
	Q_OBJECT
	private:
		QPushButton *button1;
		QPushButton *button2;
		QPushButton *button3;
		QLineEdit *edit1,*edit2,*edit3,*edit4,*edit5,*edit6;
	private slots:  
		void convert(){
			string unitNumStr=(edit1->text()+edit2->text()).toStdString();
			unitNum a=unitNum(unitNumStr);
			int ret=a.convertUnit(edit4->text().toStdString());
			if(ret==0)
				edit3->setText(QString::fromStdString(to_string(a.showVal())));
			else
				edit3->setText("Err");
		}
		int calculate(){
			string expression=(edit5->text()).toStdString()+"$";
			int lastPos=0;
			unitNum ans=unitNum("");
			bool first=true;
			for(int i=0;i<(int)expression.length();i++)
			{
				if(expression[i]=='+' || expression[i]=='-' || expression[i]=='$')
				{
					if(first){
						ans=unitNum(expression.substr(0,i));
						lastPos=i;
						first=false;
						continue;
					}
					unitNum tmp=unitNum(expression.substr(lastPos+1,i-lastPos-1));
					if(tmp.showUnitTypeName()!=ans.showUnitTypeName()){
						edit6->setText("Err");
						return 0;
					}
					if(expression[lastPos]=='+'){
						ans=ans+tmp;
					}
					else if(expression[lastPos]=='-'){
						ans=ans-tmp;
					}
					lastPos=i;
				}
			}
			edit6->setText(QString::fromStdString(to_string(ans.showVal())+ans.showUnit()));
			return 0;
		}
		void unitMenu(){
			string totstr;
			for(int i = 1;i < maxUnitType;i++){
				totstr+=unitTypeName[i];
				totstr+=":\t";
				int ct = 0;
				while(unitName[i][ct]!=""){
					totstr+=' ';
					totstr+=unitName[i][ct++];				
				}
				totstr+="\n";
			}
			QMessageBox::information(NULL, "All Units", QString::fromStdString(totstr), "confirm");
		}
	public:
		mainWin(){
			this->resize(QSize(600,300));
			this->setWindowTitle("Unit Converter");
			QGridLayout *layout=new QGridLayout;
			for(int i=0;i<8;i++)
				layout->setColumnStretch(i,1);
			for(int i=0;i<5;i++)
				layout->setRowStretch(i,1);
			QWidget *mywidget=new QWidget;
			mywidget->setLayout(layout);
			this->setCentralWidget(mywidget);
			//add button1&button2
			button1=new QPushButton("-->");
			button2=new QPushButton("=");
			button3=new QPushButton("Press");
			layout->addWidget(button1,1,3,1,1);
			layout->addWidget(button2,3,4,1,1);
			layout->addWidget(button3,5,4,1,1);
			//add label1
			QLabel *label1= new QLabel("单位转换器");
			layout->addWidget(label1,0,2,1,4,Qt::AlignCenter);
			QLabel *labelt= new QLabel("Show All Available Units");
			layout->addWidget(labelt,5,1,1,3);
			//add lineedit
			edit1=new QLineEdit;
			layout->addWidget(edit1,1,1,1,1);
			//add lineedit
			edit2=new QLineEdit("Unit");
			layout->addWidget(edit2,1,2,1,1);
			//add lineedit
			edit3=new QLineEdit();
			layout->addWidget(edit3,1,4,1,1);
			//add lineedit
			edit4=new QLineEdit("NewUnit");	
			layout->addWidget(edit4,1,5,1,2);
			edit5=new QLineEdit("e.g. 1km+3m");
			layout->addWidget(edit5,3,1,1,3);
			edit6=new QLineEdit("Ans & Unit");
			layout->addWidget(edit6,3,5,1,2);
			edit6->setFocusPolicy(Qt::NoFocus);
			edit3->setFocusPolicy(Qt::NoFocus);
			connect(button1, SIGNAL(clicked()), this, SLOT(convert())); 
			connect(button2, SIGNAL(clicked()), this, SLOT(calculate())); 
			connect(button3, SIGNAL(clicked()), this, SLOT(unitMenu())); 
		} 
};

int main(int argc,char *argv[]){
	//解决中文乱码
	QTextCodec *codec=QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QApplication app(argc,argv);
	mainWin *win=new mainWin;
	win->show();
	app.exec();
	return 0;
}

#include"main.moc"
//因qt导致bug，不能识别cpp文件中的Q_OBJECT宏定义
//使用MOC生成文件并在最后包含

