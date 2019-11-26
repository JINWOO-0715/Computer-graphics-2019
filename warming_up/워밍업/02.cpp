#include <iostream>
#include<fstream>
#include<string>


using namespace std;

int main()
{

	ifstream in("text.txt");
	string s;

	if (in.is_open())
	{
		in.seekg(0, ios::end);

		int size = in.tellg();
		s.resize(size);
		in.seekg(0, ios::beg);
		in.read(&s[0], size);
		cout << s <<endl
;
		char *c = new char[s.length() + 1];
		strcpy(c, s.c_str());
		
		cout <<c;
	
	}
}