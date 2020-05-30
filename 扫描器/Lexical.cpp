#include "main.h"
char token[30];
int Max_len = 10;
char nullarray[30];
int rows = 1;
int lookup(char *arrays)//查找
{
	int c;
	if (!strcmp(arrays, "begin"))
	{
		c = 1;
	}
	else if (!strcmp(arrays, "end"))
	{
		c = 2;
	}
	else if (!strcmp(arrays, "var"))
	{
		c = 3;
	}
	else if (!strcmp(arrays, "integer"))
	{
		c = 4;
	}
	else if (!strcmp(arrays, "while"))
	{
		c = 5;
	}
	else if (!strcmp(arrays, "do"))
	{
		c = 6;
	}
	else if (!strcmp(arrays, "then"))
	{
		c = 7;
	}
	else if (!strcmp(arrays, "if"))
	{
		c = 8;
	}
	else if (!strcmp(arrays, "else"))
	{
		c = 9;
	}
	else
	{
		c = 0;
	}

	return c;
}
std::string relook_up(int c)
{
	char ch = c + '0';
	switch (ch)
	{
	case '1':
		return "begin";
	case '2':
		return "end";
	case '3':
		return"var";
	case '4':
		return"integer";
	case '5':
		return"while";
	case '6':
		return"do";
	case '7':
		return"then";
	case '8':
		return"if";
	case '9':
		return"else";
	default:
		return "error";
	}
}
void out(int flag, char *strings, std::string name)
{
	char str[20];
	sprintf(str, "%d", flag);
	int temp, maxlen = strlen(str);
	for (temp = 0; temp < maxlen; ++temp)
	{
		strings[temp] = str[temp];
	}
	strings[temp] = '\0';
	std::cout << "<" << strings << "," << name << "> ";
}
void report(FILE *fpoint, char ch)
{
	char temp_array[100];
	if (ch == '\n')
	{
		rows++;
		if (getc(fpoint) != EOF)
		{
			fseek(fpoint, -1, 1);
			std::cout << "\n" << rows << ":";
		}
		else
		{
			std::cout << "[code]Analysis is End";
		}
	}

	if (ch != ' ' && ch != '\n' && ch != '\t')
	{
		//单行注释
		if (ch == '/' && fgetc(fpoint) == '/')
		{
			fgets(temp_array, 100, fpoint);
			rows++;
			std::cout << "<注释>";
			std::cout << "\n" << rows << ":";

			return;
		}
		//花括号注释
		else if (ch == '{')
		{
			while ((ch = fgetc(fpoint)) != EOF)
			{
				if (ch == '\n')
				{
					rows++;
					if (getc(fpoint) != EOF)
					{
						fseek(fpoint, -1, 1);
						std::cout << "<注释>" ;
						std::cout <<"\n"<< rows << ":" ;
					}
					else
					{
						std::cout << "[error by annotation]Annotation is error,the program is end." << std::endl;
						std::cin.get();
						exit(0);
					}
				}
				else if (ch == '}')
				{
					std::cout << "<注释>" ;
					return;
				}
			}
			std::cout << "[error by annotation]Annotation is error,the program is end." << std::endl;
			std::cin.get();
			exit(0);
		}
		else
		{
			std::cout << "[error by annotation]Annotation is error,the program is end." << std::endl;
			exit(0);
		}
	}
}
void scan(wordList *words, int &max_len, FILE *fpoint)
{
	char ch;
	int i, c;
	ch = fgetc(fpoint);

	if (isalpha(ch))//检查所传的字符是否是字母
	{
		token[0] = ch;
		ch = fgetc(fpoint);
		i = 1;
		while (isalnum(ch))//检查所传的字符是否是字母和数字
		{
			token[i] = ch;
			i++;
			ch = fgetc(fpoint);
		}
		token[i] = '\0';
		fseek(fpoint, -1, 1);//回退一个字符
		c = lookup(token);
		if (c == 0)
		{
			words[max_len].type = token;
			out(ID, token, words[max_len].type);
			words[max_len].num = ID;

			++max_len;
		}
		else
		{
			words[max_len].type = relook_up(c);
			out(c, nullarray, words[max_len].type);
			words[max_len].num = c;
			++max_len;
		}
	}
	else
	{
		if (isdigit(ch))//检查所传的字符是否是十进制数字字符
		{
			token[0] = ch;
			ch = fgetc(fpoint);
			i = 1;
			if (isalpha(ch))
			{
				std::cout << "[4]Raise Error,please concert" << std::endl;
				std::cin.get();
				exit(0);
			}
			while (isdigit(ch))
			{
				token[i] = ch;
				i++;
				ch = fgetc(fpoint);
			}
			token[i] = '\0';
			fseek(fpoint, -1, 1);

			words[max_len].type = token;
			out(INT, token, words[max_len].type);
			words[max_len].num = INT;
			++max_len;
		}
		else
		{
			switch (ch)
			{
			case '<':
				ch = fgetc(fpoint);
				if (ch == '=')
				{
					words[max_len].type = "<=";
					out(SMALLER_EQUAL, nullarray, words[max_len].type);
					words[max_len].num = SMALLER_EQUAL;
					++max_len;
				}
				else if (ch == '>')
				{
					words[max_len].type = "!=";
					out(NOT_EQUAL, nullarray, words[max_len].type);
					words[max_len].num = NOT_EQUAL;
					++max_len;
				}
				else
				{
					fseek(fpoint, -1, 1);
					words[max_len].type = "<";
					out(SMALLER, nullarray, words[max_len].type);
					words[max_len].num = SMALLER;
					++max_len;
				}
				break;
			case '=':
				words[max_len].type = "=";
				out(EQUAL, nullarray, words[max_len].type);
				words[max_len].num = EQUAL;
				++max_len;
				break;
			case '>':
				ch = fgetc(fpoint);
				if (ch == '=')
				{
					words[max_len].type = ">=";
					out(BIGER_EQUAL, nullarray, words[max_len].type);
					words[max_len].num = BIGER_EQUAL;
					++max_len;
				}
				else
				{
					fseek(fpoint, -1, 1);
					words[max_len].type = ">";
					out(BIGER, nullarray, words[max_len].type);
					words[max_len].num = BIGER;
					++max_len;
				}
				break;
			case ':':
				ch = fgetc(fpoint);
				if (ch == '=')
				{
					words[max_len].type = ":=";
					out(ASSIGNMENT, nullarray, words[max_len].type);
					words[max_len].num = ASSIGNMENT;
					++max_len;
				}
				else
				{
					fseek(fpoint, -1, 1);
					words[max_len].type = ":";
					out(BUBBLE, nullarray, words[max_len].type);
					words[max_len].num = BUBBLE;
					++max_len;
				}
				break;
			case '+':
				words[max_len].type = "+";
				out(ADD, nullarray, words[max_len].type);
				words[max_len].num = ADD;
				++max_len;
				break;
			case '-':
				words[max_len].type = "-";
				out(ADD, nullarray, words[max_len].type);
				words[max_len].num = SUB;
				++max_len;
				break;
			case '*':
				words[max_len].type = "*";
				out(MULTIPLY, nullarray, words[max_len].type);
				words[max_len].num = MULTIPLY;
				++max_len;
				break;
			case '(':
				words[max_len].type = "(";
				out(LEFT_BRACKET, nullarray, words[max_len].type);
				words[max_len].num = LEFT_BRACKET;
				++max_len;
				break;
			case ')':
				words[max_len].type = ")";
				out(RIGHT_BRACKET, nullarray, words[max_len].type);
				words[max_len].num = RIGHT_BRACKET;
				++max_len;
				break;
			case '.':
				words[max_len].type = ".";
				out(POINT, nullarray, words[max_len].type);
				words[max_len].num = POINT;
				++max_len;
				break;
			case ',':
				words[max_len].type = ",";
				out(BEAN, nullarray, words[max_len].type);
				words[max_len].num = BEAN;
				++max_len;
				break;
			case ';':
				words[max_len].type = ";";
				out(SPLIT, nullarray, words[max_len].type);
				words[max_len].num = SPLIT;
				++max_len;
				break;
			default:report(fpoint, ch);
				break;
			}

			return;
		}
	}
}
int cifa_analysis(FILE *f, wordList *w)
{
	int max_len = 0;
	std::cout << rows << ":" ;//第一行
	while (fgetc(f)!=EOF)
	{
		fseek(f, -1, 1);
		scan(w,max_len,f);
	}
	fclose(f);
	return max_len;
}