#include "Header.h"
#include "veriables.h"
#include <windows.h>

std::mutex mut;
std::condition_variable data_cond;
std::queue<std::string>buf;
std::queue<std::string>buf2;
int halva, marmelad , zefir , condensedMilk , pastila , pechenie , waffle , jam, eclair,pie, sweets;
using namespace std;

void revizor() {
	halva = 0, marmelad=0, zefir=0, condensedMilk=0, pastila=0, pechenie=0, waffle =0, jam=0, eclair=0, pie=0,sweets=0;
	

	while (!buf2.empty()) {
		string dataToCount;
		std::unique_lock<std::mutex>lk(mut);

		while (buf2.empty())
		{
			data_cond.wait(lk);
		}

		dataToCount = buf2.front();
	

		
		if (dataToCount.find("Halva") != std::string::npos)halva = halva + 1;
		if (dataToCount.find("Jujube") != std::string::npos)marmelad = marmelad + 1;
		if (dataToCount.find("Zefir") != std::string::npos)zefir = zefir + 1;
		if (dataToCount.find("Condensed Milk") != std::string::npos) condensedMilk = condensedMilk + 1;
		if (dataToCount.find("Pastila") != std::string::npos) pastila = pastila + 1;
		if (dataToCount.find("Waffle") != std::string::npos) waffle = waffle + 1;
		if (dataToCount.find("Cookie") != std::string::npos) pechenie = pechenie + 1;
		if (dataToCount.find("Jam") != std::string::npos) jam = jam + 1;
		if (dataToCount.find("Eclair") != std::string::npos) eclair = eclair + 1;
		if (dataToCount.find("Sweets") != std::string::npos) sweets = sweets + 1;

		dataToCount.erase();
		
		buf2.pop();
		lk.unlock();
	


	
	}
	cout << "\n Halva" << "  " << halva<<endl;
	cout << "\n Jujube" << "  " << marmelad << endl;
	cout << "\n Zefir" << "  " << zefir << endl;
	cout << "\n Condensed Milk" << "  " << condensedMilk << endl;
	cout << "\n Pastila" << "  " << pastila << endl;
	cout << "\n Waffle" << "  " << waffle << endl;
	cout << "\n Cookie" << "  " << pechenie << endl;
	cout << "\n Jam" << "  " << jam << endl;
	cout << "\n Eclair" << "  " << eclair << endl;
	cout << "\n Sweets" << "  " << sweets << endl;




}






void writeToFile(std::string& filepath)
{
	ofstream result(filepath);
	
	while (!buf.empty()) 
	{

		std::string dataToFile;
		std::unique_lock<std::mutex>lk(mut);

		while (buf.empty()) 
		{
			data_cond.wait(lk);
			
		}

		dataToFile = buf.front();

		
		

	

		buf2.push(dataToFile);
		

	
			if (result.is_open())
			{
				if ((dataToFile.find("Sweets") != std::string::npos)||(dataToFile.find("Marmelad")!=std::string::npos)|| (dataToFile.find("Zefir") != std::string::npos)|| (dataToFile.find("Condensed milk") != std::string::npos)|| (dataToFile.find("Cookie") != std::string::npos))
				{
					if (dataToFile.find("Marmelad") != std::string::npos)
					{
						dataToFile.replace(dataToFile.begin(), dataToFile.end() - 1, "Zefir");
					}
						result << dataToFile;
				}
				
			}

			buf.pop();
			
			
			dataToFile.erase();
						
			lk.unlock();
			data_cond.notify_one();
		
	}
	result.close();

}

void readFile(std::string& filepath)
{
	cout << "filepath    " <<filepath<<std::endl;


	std::ifstream stream(filepath);
		
	char ff;

	string file_buffer;

	if (!stream.is_open())
	{
		cout << "eror openning";
	}

	else
	{
		std::lock_guard<std::mutex>lk(mut);

		while (!stream.eof())
		{
			ff = stream.get();
			
			file_buffer += ff;

			if (ff == '\n')
			{
			
				
			
				
				buf.push(file_buffer);
				

				file_buffer.clear();

				data_cond.notify_one();
			}
		}
	}


}