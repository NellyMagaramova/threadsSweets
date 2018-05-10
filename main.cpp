#include "Header.h"


using namespace std;

int main(int argc, char* argv[])


{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");


	cout << argv[0] << endl;

	if (argc == 1) {
		cout << "Expected two arguments : path to file with data and path to save file. Example: C:\\Users\\..\\text1.txt" "C:\\Users\\..\\result.txt" ;
		return 0;
	}


	cout << argv[1] << endl;
	cout << argv[2] << endl;

	string fileopen(argv[1]);
	string fileclose(argv[2]);
	
	


	thread func_read(readFile,fileopen);
	func_read.join();
	thread func_write(writeToFile,fileclose);
	func_write.join();
	thread func_revizor(revizor);
	func_revizor.join();

	
	
	

	cout << "\n open the file";
	
	

	
//	wcout << L"файл  ";
	

	system("pause");
	return 0;


}
