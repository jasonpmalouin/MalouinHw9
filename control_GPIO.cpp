/** A program that accepts two GPIO pin numbers, the first for output, and the second for input
 * Sets the output to a specified value, and reads the value of the input pin
 * Usage: ./control_gpio <output GPIO #> <value: 0 or 1> <input GPIO #>
 * Ex: ./control_gpio 60 1 46
 *
 *Felt that it made more sense for values to be 0 and 1 to maintain logical format
 *
 * By: Jason Malouin
 * 11-8-22
 * */

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define GPIO_PATH "/sys/class/gpio/gpio"

string readGPIO(string path)
{
 fstream reads;
 stringstream ss;
 string line;
 string readPath = path + "/value";
 reads.open((readPath).c_str(), fstream::in);
 while(getline(reads, line))
 {
     ss << line << endl;
 }

 reads.close();
 string value = string(ss.str());
 return value;
}

void writeGPIO(string path, string value)
{
fstream writes;

string writePath = path + "/direction";
writes.open((writePath).c_str(), fstream::out);
writes << "out" << endl;
writes.close();

writePath = path + "/value";
writes.open((writePath).c_str(), fstream::out);
writes << value << endl;
writes.close();
}


int main(int argc, char* argv[]){
	if(argc!=4){
		cout << endl;
		cout << "Usage is: ./control_GPIO <output GPIO #> <1 or 0> <input GPIO #> " << endl;
		return 2;
	}
	ostringstream ss; 
	string outputGPIO(argv[1]);
	string inputGPIO(argv[3]);
	string outputValue(argv[2]);
	ss << GPIO_PATH << outputGPIO;
	string outputGPIOPath = string(ss.str());
	ss.str("");
	ss << GPIO_PATH << inputGPIO;
	string inputGPIOPath = string(ss.str());

	cout << "Starting the control_GPIO program" << endl;
	cout << "The GPIO Output Path Is:  " << outputGPIOPath << endl;
	cout << "The GPIO Output Value Is:  " << outputValue << endl;
	cout << "The GPIO Input Path Is: " << inputGPIOPath << endl;
        cout << endl;
	 writeGPIO(outputGPIOPath, outputValue);
	 string inputValue = readGPIO(inputGPIOPath);
	 cout << "GPIO " << outputGPIO << " Value Set To: " << outputValue << endl; 
	 cout << "GPIO " << inputGPIO << " Value Is: " << inputValue  << endl;
	 return 0;
}
