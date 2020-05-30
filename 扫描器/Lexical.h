#pragma once
#ifndef LEXICAL_H
#define LEXICAL_H

#include <iostream>
using namespace std;

#define	 BEGIN              1  /* begin */
#define	 END                2  /* end */
#define	 VAR                3  /* var */
#define	 INTEGER            4  /* integer */
#define	 WHILE              5  /* while */
#define	 DO                 6  /* do */
#define	 THEN               7  /* then */
#define	 IF                 8  /* if */
#define	 ELSE               9  /* else */
#define	 EQUAL              10 /* = */
#define	 ASSIGNMENT         11 /* == */
#define	 ADD                12 /* + */
#define	 MULTIPLY           13 /* * */
#define	 SMALLER            14 /* < */
#define	 BIGER              15 /* > */
#define	 SMALLER_EQUAL      16 /* <= */
#define	 BIGER_EQUAL        17 /* >= */
#define	 LEFT_BRACKET       18 /* [ */
#define	 RIGHT_BRACKET      19 /* ] */
#define	 NOT_EQUAL          20 /* != */
#define	 POINT              21 /* . */
#define	 BEAN               22 /* , */
#define	 BUBBLE             23 /* : */
#define	 SPLIT              24 /* ; */
#define  ID                 25 /* a-z */
#define  INT                26 /* 0-9 */
#define  SUB                27 /* - */

/*单词结构体*/
typedef struct 
{
	int num;
	string type;//类型
	string name;//类型名
}wordList;

int cifa_analysis(FILE *f, wordList *w);
int lookup(char *arrays);
std::string relook_up(int c);
void out(int flag, char *strings, std::string name);
void report(FILE *fpoint, char ch);
void scan(wordList *words, int &max_len, FILE *fpoint);


#endif // !LEXICAL_H
