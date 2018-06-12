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

const int maxUnitNum=100,maxUnitType=4;
/*string unitTypeName[maxUnitType]={"length","mass","time","electric current","thermodynamic temperature","amount of substance","luminous intensity"};
*/
string unitTypeName[maxUnitType]={"length","mass","time","electric current"};
string unitName[maxUnitType][maxUnitNum]={{"mm","cm","m","km","inch","feet"},{"mg","g","kg","t"},{"ms","s","min","h"},{"mA","A","kA"}};

double coefficient[maxUnitType][maxUnitNum]={{1e-3,1e-2,1,1e3,0.0254,0.3048},{1e-3,1,1e3,1e6},{1e-3,1,60,3600},{1e-3,1,1e3}}; 
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
		unitNum operator * (unitNum A);
		unitNum operator / (unitNum A);
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
		QLineEdit *edit1,*edit2,*edit3,*edit4;
	private slots:  
		void OnClicked()
		{
			QString str;
			str = tr("You press button\n")+tr("num1:")+edit1->text()+edit2->text()+tr("\nnum2:")+edit3->text()+edit4->text();
			QMessageBox::information(this, tr("Information"), str);
		}
	public:
		mainWin(){
			this->resize(QSize(600,300));
			this->setWindowTitle("Unit Converter");
			QGridLayout *layout=new QGridLayout;
			layout->setColumnStretch(0,1);
			layout->setColumnStretch(1,2);
			layout->setColumnStretch(2,2);
			layout->setColumnStretch(3,1);
			layout->setColumnStretch(4,2);
			layout->setColumnStretch(5,2);
			layout->setColumnStretch(6,2);
			layout->setRowStretch(0,1);
			layout->setRowStretch(1,1);
			layout->setRowStretch(2,1);
			layout->setRowStretch(3,1);
			QWidget *mywidget=new QWidget;
			mywidget->setLayout(layout);
			this->setCentralWidget(mywidget);
			//add button1
			button1=new QPushButton("转换");
			layout->addWidget(button1,2,2,1,3);
			//add label1
			QLabel *label1= new QLabel("单位转换器");
			layout->addWidget(label1,0,2,1,3,Qt::AlignCenter);
			//add label2
			QLabel *label2= new QLabel("-->");
			layout->addWidget(label2,1,3,1,1,Qt::AlignCenter);
			//add lineedit
			edit1=new QLineEdit;
			layout->addWidget(edit1,1,1,1,1,Qt::AlignCenter);
			//add lineedit
			edit2=new QLineEdit("Unit");
			layout->addWidget(edit2,1,2,1,1,Qt::AlignCenter);
			//add lineedit
			edit3=new QLineEdit;
			layout->addWidget(edit3,1,4,1,1,Qt::AlignCenter);
			//add lineedit
			edit4=new QLineEdit("NewUnit");
			layout->addWidget(edit4,1,5,1,1,Qt::AlignCenter);
			connect(button1, SIGNAL(clicked()), this, SLOT(OnClicked())); 
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
