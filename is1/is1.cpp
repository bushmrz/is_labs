#include <iostream>
#include <fstream>


using namespace std;
// 1 
string decode(string code) 
{
	return code.substr(code.size() - 3, code.size()) + code.substr(0, code.size() - 3);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string buff;
	string decoded;
	ifstream fin("encoded.txt");
	ofstream fout("decoded1.txt");
	
	while (!fin.eof()) {
		fin >> buff;
		decoded = decode(buff);
		fout << decoded << " ";
	}

	fin.close();
	fout.close();

	cout << "Done" << endl;

}



// 3 
string revDecode(string code) {
	int n = code.length();
	for (int i = 0; i < n / 2; i++) {
		swap(code[i], code[n - i - 1]);
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string buff;
	string decoded;
	ifstream fin("encoded.txt");
	ofstream fout("decoded1.txt");

	while (!fin.eof()) {
		fin >> buff;
		decoded = revDecode(buff);
		fout << decoded << " ";
	}

	fin.close();
	fout.close();

	cout << "Done" << endl;
}


