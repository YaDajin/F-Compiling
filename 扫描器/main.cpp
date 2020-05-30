#include "main.h"
#include "Lexical.h"//词法分析器
int main()
{
	int maxLen;//字符串最大长度
	wordList *words=new wordList[1000];
	FILE *fpoint;
	fpoint = fopen("1.txt", "rt");
	maxLen = cifa_analysis(fpoint,words);
	cout << endl;
	std::cout << "hello world" << std::endl;
	delete[] words;
	return 0;
}