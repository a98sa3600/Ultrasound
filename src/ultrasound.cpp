//g++ -o ultrasound ultrasound.cpp -lCppLinuxSerial
#include <CppLinuxSerial/SerialPort.hpp>
#include<iostream>
#include<string>
#include <unistd.h>
#include <algorithm>

using namespace mn::CppLinuxSerial;
using std::cout; using std::endl;
using std::string; using std::stringstream;

//distance measurement
float showInfo(SerialPort *serialPort){
	int i;
	string readData;
    unsigned char s_data[4]={0};
    float s_distance ;
	serialPort->Open();
	serialPort->Read(readData); 
        do{
            for(i=0;i<4;i++){
                s_data[i]=readData[i];
            }
        }while(readData[i]==0xff);

        if(s_data[0]==0xff){
        	int sum;
        	sum=(s_data[0]+s_data[1]+s_data[2])&0x00FF;
            if(sum==s_data[3]){
                s_distance=(s_data[1]<<8)+s_data[2];
                if(s_distance>30){
					return s_distance;
                }else{return -1;}
            }else{return -2;}
        }	
}

float front(){
	SerialPort serialPort1("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	float F_distance ;
	float state ;
	state = showInfo (&serialPort1);
	if(state==-2){
		cout << "ERROR"<<endl;	
	}else if(state==-1){
		cout << "Out of Range"<<endl;
	}else{	
		F_distance = state;
		cout <<  "Front:"  << endl;
		cout << "distance=" << F_distance/10 << "cm" <<endl;		
	}
	return F_distance/10;
        usleep(100*1000);
}
float front_right(){
	SerialPort serialPort2("/dev/ttyUSB1", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	float F_distance ;
	float state ;
	state = showInfo(&serialPort2);
	if(state==-2){
		cout << "ERROR"<<endl;	
	}else if(state==-1){
		cout << "Out of Range"<<endl;
	}else{	
		F_distance = state;
		cout <<  "Front Right:"  << endl;
		cout << "distance=" << F_distance/10 << "cm" <<endl;		
	}
	return F_distance/10;
        usleep(100*1000);
}
float front_left(){
	SerialPort serialPort3("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	float F_distance ;
	float state ;
	state = showInfo(&serialPort3);
	if(state==-2){
		cout << "ERROR"<<endl;	
	}else if(state==-1){
		cout << "Out of Range"<<endl;
	}else{	
		F_distance = state;
		cout <<  "Front Left:"  << endl;
		cout << "distance=" << F_distance/10 << "cm" <<endl;		
	}
	return F_distance/10;
    usleep(100*1000);
}
float back(){
	SerialPort serialPort4("/dev/ttyUSB3", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	float F_distance ;
	float state ;
	state = showInfo(&serialPort4);
	if(state==-2){
		cout << "ERROR"<<endl;	
	}else if(state==-1){
		cout << "Out of Range"<<endl;
	}else{	
		F_distance = state;
		cout <<  "Back:"  << endl;
		cout << "distance=" << F_distance/10 << "cm" <<endl;		
	}
	return F_distance/10;
        usleep(100*1000);
}
float back_right(){
	SerialPort serialPort5("/dev/ttyUSB4", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	float F_distance ;
	float state ;
	state = showInfo(&serialPort5);
	if(state==-2){
		cout << "ERROR"<<endl;	
	}else if(state==-1){
		cout << "Out of Range"<<endl;
	}else{	
		F_distance = state;
		cout <<  "Back Right:"  << endl;
		cout << "distance=" << F_distance/10 << "cm" <<endl;		
	}
	return F_distance/10;
        usleep(100*1000);
}
float back_left(){
	SerialPort serialPort6("/dev/ttyUSB5", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	float F_distance ;
	float state ;
	state = showInfo(&serialPort6);
	if(state==-2){
		cout << "ERROR"<<endl;	
	}else if(state==-1){
		cout << "Out of Range"<<endl;
	}else{	
		F_distance = state;
		cout <<  "Back Left:"  << endl;
		cout << "distance=" << F_distance/10 << "cm" <<endl;		
	}
	return F_distance/10;
        usleep(100*1000);
}
int main(){
    int i;
    int sensor = 6;
    float Distance[sensor]={};
    float minVal;
    float distance;


    while(1) {
		Distance[0] = front();
		Distance[1] = front_right();
		Distance[2] = front_left();
		Distance[3] = back();
		Distance[4] = back_right();
		Distance[5] = back_left();
		cout <<  ""  << endl;
		minVal=Distance[0];
			for(int i=0; i<sensor; i++){
				minVal=std::min(Distance[i],minVal);
			}
			distance = minVal;
		cout << "Min Distance=" << distance << "cm" <<endl;
		cout <<  ""  << endl;   
		cout <<  ""  << endl;     
    }
    return 0;
}
