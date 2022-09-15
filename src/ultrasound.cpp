#include <CppLinuxSerial/SerialPort.hpp>
#include<iostream>
#include<string>
#include <unistd.h>
#include <algorithm>

using namespace mn::CppLinuxSerial;
using std::cout; using std::endl;
using std::string; using std::hex;
using std::stringstream;

void showInfo(){

}

float front(){
	SerialPort serialPort1("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	int i;
	string readData;
        unsigned char F_data[4]={0};
        float F_distance ;
	serialPort1.Open();
	serialPort1.Read(readData); 
        do{
            for(i=0;i<4;i++){
                F_data[i]=readData[i];
            }
        }while(readData[i]==0xff);

        if(F_data[0]==0xff){
        int sum;
        sum=(F_data[0]+F_data[1]+F_data[2])&0x00FF;
	cout <<  "Front:"  << endl;
            if(sum==F_data[3]){
                F_distance=(F_data[1]<<8)+F_data[2];
                if(F_distance>30){
                cout << "distance=" << F_distance/10 << "cm" <<endl;
                }else{cout << "Below the lower limit"<<endl;}
            }
            else cout << "ERROR"<<endl;;
        }
	return F_distance/10;
        usleep(100*1000);
}
float front_right(){
	SerialPort serialPort2("/dev/ttyUSB1", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	int i;
	string readData;
        unsigned char FR_data[4]={0};
        float FR_distance ;
	serialPort2.Open();
	serialPort2.Read(readData); 
        do{
            for(i=0;i<4;i++){
                FR_data[i]=readData[i];
            }
        }while(readData[i]==0xff);

        if(FR_data[0]==0xff){
        int sum;
        sum=(FR_data[0]+FR_data[1]+FR_data[2])&0x00FF;
	cout <<  "Front Right:"  << endl;
            if(sum==FR_data[3]){
                FR_distance=(FR_data[1]<<8)+FR_data[2];
                if(FR_distance>30){
                cout << "distance=" << FR_distance/10 << "cm" <<endl;
                }else{cout << "Below the lower limit"<<endl;}
            }
            else cout << "ERROR"<<endl;;
        }
	return FR_distance/10;
        usleep(100*1000);
}
float front_left(){
	SerialPort serialPort3("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	int i;
	string readData;
        unsigned char FL_data[4]={0};
        float FL_distance ;
	serialPort3.Open();
	serialPort3.Read(readData); 
        do{
            for(i=0;i<4;i++){
                FL_data[i]=readData[i];
            }
        }while(readData[i]==0xff);

        if(FL_data[0]==0xff){
        int sum;
        sum=(FL_data[0]+FL_data[1]+FL_data[2])&0x00FF;
	cout <<  "Front Left:"  << endl;
            if(sum==FL_data[3]){
                FL_distance=(FL_data[1]<<8)+FL_data[2];
                if(FL_distance>30){
                cout << "distance=" << FL_distance/10 << "cm" <<endl;
                }else{cout << "Below the lower limit"<<endl;}
            }
            else cout << "ERROR"<<endl;;
        }
	return FL_distance/10;
        usleep(100*1000);
}
float back(){
	SerialPort serialPort4("/dev/ttyUSB3", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	int i;
        string readData;
        unsigned char B_data[4]={0};
        float B_distance ;
	serialPort4.Open();
	serialPort4.Read(readData); 
        do{
            for(i=0;i<4;i++){
                B_data[i]=readData[i];
            }
        }while(readData[i]==0xff);

        if(B_data[0]==0xff){
        int sum;
        sum=(B_data[0]+B_data[1]+B_data[2])&0x00FF;
	cout <<  "Back:"  << endl;
            if(sum==B_data[3]){
                B_distance=(B_data[1]<<8)+B_data[2];
                if(B_distance>30){
                cout << "distance=" << B_distance/10 << "cm" <<endl;
                }else{cout << "Below the lower limit"<<endl;}
            }
            else cout << "ERROR"<<endl;;
        }
	return B_distance/10;
        usleep(100*1000);
}

int main(){
    //Serial 1
    SerialPort serialPort1("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort1.SetTimeout(-1); 
	serialPort1.Open();
    cout <<  "Open serial port for ultrasound Serial-1"  << endl;
    //Serial 2
    SerialPort serialPort2("/dev/ttyUSB1", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort2.SetTimeout(-1); 
	serialPort2.Open();
    cout <<  "Open serial port for ultrasound Serial-2"  << endl;
   //Serial 3
    SerialPort serialPort3("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort3.SetTimeout(-1); 
	serialPort3.Open();
    cout <<  "Open serial port for ultrasound Serial-3"  << endl;
    //Serial 4
    SerialPort serialPort4("/dev/ttyUSB3", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort4.SetTimeout(-1); 
	serialPort4.Open();
    cout <<  "Open serial port for ultrasound Serial-4"  << endl;

    
    int i;
    int sensor = 4;
    float Distance[sensor]={};
    float minVal;
    float distance;    

    while(1 == true ) {
        Distance[0] = front();
	Distance[1] = front_right();
	Distance[2] = front_left();
	Distance[3] = back();
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

