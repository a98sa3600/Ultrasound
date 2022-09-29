//g++ -o ultrasound1 ultrasound1.cpp -lCppLinuxSerial -pthread

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

pthread_mutex_t mutex ;

void * getInfo(void *args){
	pthread_mutex_lock(&mutex);
	int i; //for the following do-while function to use
	string readData={0};
    unsigned char data[4]={0};
    float * distance;
	SerialPort * serialPort = (SerialPort *) args;
	serialPort->Open();
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
		}else { *distance =-1; }
	}
	pthread_mutex_unlock(&mutex);
	return (void *)distance;
	usleep(100*1000);
}

int main(){
	//Define SerialPort 
    SerialPort serialPort0("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    SerialPort serialPort1("/dev/ttyUSB1", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    SerialPort serialPort2("/dev/ttyUSB2", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    SerialPort serialPort3("/dev/ttyUSB3", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    SerialPort serialPort4("/dev/ttyUSB4", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    SerialPort serialPort5("/dev/ttyUSB5", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	cout <<  " serialPort for ultrasound Serial"  << endl;

	SerialPort serialPort[ultrasound_number] = {serialPort0, serialPort1,serialPort2,serialPort3,serialPort4,serialPort5};


	while(1){
		//create pthread_t ;
		pthread_t ultrasound_reader[ultrasound_number];

		for(int i=0;i<ultrasound_number;i++){
			if (pthread_create(&ultrasound_reader[i], NULL, getInfo , (void *) (serialPort+i) ) !=0) {
			perror("could not create thread for ultrasound_reader");
			return -1;
			}
		}
		
		//End pthread and Save callBack_value
		void * Distance[ultrasound_number];	
		for(int i=0;i<ultrasound_number;i++){
			if (pthread_join(ultrasound_reader[i],(Distance+i)) !=0) {
			perror("pthread_join error for ultrasound_reader");
			return -1;
			}
		}	

		string serialState[ultrasound_number]={"Front","Front_Right","Front_Left","Back","Back_Right","Back_Left"};
		for(int i=0; i < ultrasound_number; i++){
			float result[i]={0};
			result[i]= *(float *)Distance[i];
			cout << serialState[i] << "\t" ;
			if(result[i]>ultrasound_limit){
				cout << "Distance" << i << "=" << result[i] << "cm" <<endl;
			}
			else if(result[i] == -1 ){
				cout << "ERROR"<<endl;
			}
			else{
				cout << "Over Range" << endl;
			}
		}
		
	}

	
	pthread_mutex_destroy(&mutex);
    return 0;
}