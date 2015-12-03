#include <iostream>
#include <string>

class MyClass
{
	public:
		std::string s = "Hello world!";
};

int main()
{
	MyClass obj;
	std::cout<<obj.s<<std::endl;
	return 0;
}

