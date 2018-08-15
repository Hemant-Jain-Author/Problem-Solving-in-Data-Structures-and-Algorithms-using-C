#include "stdafx.h"
#include "Stringclass.h"

Stringclass::Stringclass()
{
	std::string str1 = "hello";
	std::string str2 = "hello";
	std::string str3 = "Hello";

	std::cout << "str1 equals str2 :" << str1.compare(str2);
	std::cout << "str1 equals str3 :" << str1.compare(str3);

}

void main()
{
	std::string str1 = "hello";
	std::string str2 = "hello";
	std::string str3 = "Hello";

	std::cout << "str1 equals str2 :" << (str1 == str2) << std::endl;
	std::cout << "str1 equals str3 :" << (str1 == str3) << std::endl;

}


void main22222()
{
	std::string str;
	std::string text = "Hello, World!";
	const char* ptr = text.c_str();

	text[7];

	char arr[] = { 'H','e','l','l','o', ',' ,' ','W','o','r','l','d','!','\0' };
	std::string hello(arr);

	int len = hello.length();
	std::string first = "Hello, ";
	std::string second = "World!";
	std::cout << first.compare(first);
	std::cout << (first == first);
	std::string helloworld = first + second;
	first.append(second);
}

