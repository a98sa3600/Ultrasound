#include <CppLinuxSerial/SerialPort.hpp>
#include<iostream>
#include<string>
#include <unistd.h>
#include <algorithm>
#include <pthread.h>  

using namespace mn :: CppLinuxSerial;
using std::cout; using std::endl;
using std::string;
using std::stringstream;

#define ultrasound_number 6
#define ultrasound_limit 3


 void * calculateInfo(void *args){
	string readData;
	int i; //for do-while func to use
    unsigned char data[4]={0};
    float *distance;
	SerialPort *serialPort = (SerialPort *) args;
	serialPort->Read(readData); 
    do{
        for(i=0;i<4;i++){
            data[i]=readData[i];
        }
    }while(readData[i]==0xff);

    if(data[0]==0xff){
    int sum;
    sum=(data[0]+data[1]+data[2])&0x00FF;
        if(sum==data[3]){
            *distance=((data[1]<<8)+data[2])/10;
			return (void *)distance;
		}
	}
}

int main(){
	//Open SerialPort
	//Serial 1
    SerialPort serialPort1("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort1.SetTimeout(-1); 
	serialPort1.Open();
    //Serial 2
    SerialPort serialPort2("/dev/ttyUSB1", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort2.SetTimeout(-1); 
	serialPort2.Open();
    //Serial 3
    SerialPort serialPort3("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort3.SetTimeout(-1); 
	serialPort3.Open();
    //Serial 4
    SerialPort serialPort4("/dev/ttyUSB3", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort4.SetTimeout(-1); 
	serialPort4.Open();
    //Serial 5
    SerialPort serialPort5("/dev/ttyUSB4", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort5.SetTimeout(-1); 
	serialPort5.Open();
    //Serial 6
    SerialPort serialPort6("/dev/ttyUSB5", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    serialPort6.SetTimeout(-1); 
	serialPort6.Open();
	cout <<  "Open serial port for ultrasound Serial"  << endl;


		//create pthread_t ;
		pthread_t ultrasound_reader1,ultrasound_reader2,ultrasound_reader3,ultrasound_reader4,ultrasound_reader5,ultrasound_reader6;
		if (pthread_create(&ultrasound_reader1, NULL, calculateInfo, (void *)&serialPort1) !=0) {
		perror("could not create thread for ultrasound_reader");
		return -1;
		}
		if (pthread_create(&ultrasound_reader2, NULL, calculateInfo, (void *)&serialPort2) !=0) {
		perror("could not create thread for ultrasound_reader");
		return -1;
		}
		if (pthread_create(&ultrasound_reader3, NULL, calculateInfo, (void *)&serialPort3) !=0) {
		perror("could not create thread for ultrasound_reader");
		return -1;
		}
		if (pthread_create(&ultrasound_reader4, NULL, calculateInfo, (void *)&serialPort4) !=0) {
		perror("could not create thread for ultrasound_reader");
		return -1;
		}
		if (pthread_create(&ultrasound_reader5, NULL, calculateInfo, (void *)&serialPort5) !=0) {
		perror("could not create thread for ultrasound_reader");
		return -1;
		}
		if (pthread_create(&ultrasound_reader6, NULL, calculateInfo, (void *)&serialPort6) !=0) {
		perror("could not create thread for ultrasound_reader");
		return -1;
		}
		
		//End pthread and Save callBack_value
		void *Distance[ultrasound_number];
		if (pthread_join(ultrasound_reader1, &Distance[0]) != 0) {
			perror("Error: pthread_join");
			return -1;
		} 

		if (pthread_join(ultrasound_reader2, &Distance[1]) != 0) {
			perror("Error: pthread_join");
			return -1;
		} 
		if (pthread_join(ultrasound_reader3, &Distance[2]) != 0) {
			perror("Error: pthread_join");
			return -1;
		} 
		if (pthread_join(ultrasound_reader4, &Distance[3]) != 0) {
			perror("Error: pthread_join");
			return -1;
		} 
		if (pthread_join(ultrasound_reader5, &Distance[4]) != 0) {
			perror("Error: pthread_join");
			return -1;
		} 
		if (pthread_join(ultrasound_reader6, &Distance[5]) != 0) {
			perror("Error: pthread_join");
			return -1;
		} 

		float result[ultrasound_number];
		for(int i=0; i < ultrasound_number; i++){
			result[i]=*(float *)Distance[i];
			if(result[i]>ultrasound_limit){
			cout << "Distance=" << (float *)Distance << "cm" <<endl;
			}else{cout << "Below the lower limit"<<endl;}
		} 
		

	
	usleep(100*1000);
	pthread_exit(NULL);
    
    return 0;
}

