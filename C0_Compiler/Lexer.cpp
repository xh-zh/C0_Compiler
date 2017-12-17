#include "StdAfx.h"

/***********DEBUG*************/
bool showToken = false;
bool showC = false;
/***********DEBUG*************/

int Lexer::savePointer[NUM];
string Lexer::saveToken[NUM];
int Lexer::saveNum[NUM];
enum kinds Lexer::saveSymbol[NUM];
int Lexer::saveLine[NUM];
int Lexer::line;
FILE* Lexer::input;
char Lexer::c;

string Lexer::token;
int Lexer::num;
enum kinds Lexer::symbol;

//Lexer::Lexer(const char *path)
//{
//	fopen_s(&input, path, "r");	
//	Error e;
//	error = e;
//	c = 0;
//}
Lexer::Lexer() {
	
}

Lexer::~Lexer(void)
{
	fclose(input);
}

void Lexer::init(const char* path) {
	fopen_s(&input, path, "r");
	line = 1;
	token = "";
	num = 0;
	symbol = kinds::null;
	c = 0;
}

int Lexer::getChar() {
	c = fgetc(input);
	if (c == EOF) {
		//cout << "In Lexer::getChar:\tEnd in getChar" << endl;
		return 1;
	}
	if (showC) cout << c << endl;
	return 0;
}

int Lexer::retract() {
	if (c == EOF)
		return 1;
	return fseek(input, -1, SEEK_CUR);
}
int Lexer::isSpace()	{	return c == ' ';}
int Lexer::isNewLine()	{	return c == '\n';}
int Lexer::isTab()		{	return c == '\t';}
int Lexer::isPlussy()	{	return c == '+';}
int Lexer::isMinussy()	{	return c == '-';}
int Lexer::isStarsy()	{	return c == '*';}
int Lexer::isLessy()	{	return c == '<';}
int Lexer::isMorsy()	{	return c == '>';}
int Lexer::isDivisy()	{	return c == '/';}
int Lexer::isLParsy()	{	return c == '(';}
int Lexer::isRParsy()	{	return c == ')';}
int Lexer::isLBracsy()	{	return c == '[';}
int Lexer::isRBracsy()	{	return c == ']';}
int Lexer::isLCBracsy()	{	return c == '{';}
int Lexer::isRCBracsy()	{	return c == '}';}
int Lexer::isCommasy()	{	return c == ',';}//����
int Lexer::isSemisy()	{	return c == ';';}//�ֺ�
int Lexer::isColonsy()	{	return c == ':';}//ð��
int Lexer::isEqusy()	{	return c == '=';}//�Ⱥ�
int Lexer::isExcsy()	{	return c == '!';}//��̾��
int	Lexer::isULine()	{	return c == '_';}//�»���
int Lexer::isAposy()	{	return c == '\'';}//������
int Lexer::isQuotesy()	{	return c == '"';}//˫����
int Lexer::isAlpha()	{	return isalpha(c) || c=='_';}
int Lexer::isDigit()	{	return '0'<=c && c<='9';}
int Lexer::isPartOfStr(){	return (35<=c && c<=126) || c==32 || c==33;}

int Lexer::reserver() {
	if		(token == "const")	symbol = kinds::CONST;
	else if (token == "int")	symbol = kinds::INT;
	else if (token == "char")	symbol = kinds::CHAR;
	else if (token == "void")	symbol = kinds::VOID;
	else if (token == "main")	symbol = kinds::MAIN;
	else if (token == "if")		symbol = kinds::IF;
	else if (token == "else")	symbol = kinds::ELSE;
	else if (token == "for")	symbol = kinds::FOR;
	else if (token == "switch")	symbol = kinds::SWITCH;
	else if (token == "case")	symbol = kinds::CASE;
	else if (token == "default")symbol = kinds::DEFAULT;
	else if (token == "scanf")	symbol = kinds::SCANF;
	else if (token == "printf")	symbol = kinds::PRINTF;
	else if (token == "return")	symbol = kinds::RETURN;
	else return 0;//�Ǳ�����
	return 1;//������
}



/**	ȫ�ֱ���
 *
 */

//�кż�����

//return 1 in δʶ�� return 0 in ʶ��return -1 in EOF
int Lexer::getToken(){
	c = 0;
	token = "";
	num = 0;
	getChar();
	while (isSpace() || isNewLine() || isTab()) {
		if (isNewLine()) line++;
		getChar();//�ն�
	}
	if (isAlpha()) {			//������/��ʶ��
		do {
			token += c;
			getChar();
		} while (isAlpha() || isDigit());
		retract();
		if (0 == reserver()) {
			symbol = kinds::IDSY;
		}
	} else if (isDigit()) {		//�޷�������
		if (c != '0') {
			do {
				token += c;
				num = 10 * num + c - '0';
				getChar();
			} while (isDigit());
			retract();
			symbol = kinds::USINTSY;
		} else {
			num = 0;
			token += c;
			symbol = kinds::USINTSY;
		}
	} else if (isLessy()) {		//<
		token += c;
		getChar();
		if (isEqusy()) {		//<=
			symbol = kinds::NMORSY;
			token += c;
		} else {				//<
			symbol = kinds::LESSY;
			retract();
		}
	} else if (isMorsy()) {		//>
		token += c;
		getChar();
		if(isEqusy()) {			//>=
			symbol = kinds::NLESSY;
			token += c;
		} else {				//>
			symbol = kinds::MORSY;
			retract();
		}
	} else if (isAposy()) {		//'
		getChar();
		if (isDigit() ||isAlpha() ||isPlussy() ||
			isMinussy() ||isStarsy() || isDivisy()) {
			symbol = kinds::CHARSY;
			token += c;
			num = c;//��num����ַ���ASSICֵ
			getChar();
			if (!isAposy()) {//δƥ���ҵ�����
				retract();
				Error::addError("'"+token, line, UNDEFINED_INPUT);
				return 1;
			}
		}
		else {//�����ŵĺ��δ����
			retract();
			Error::addError("'", line, UNDEFINED_INPUT);
			return 1;
		}
	} else if (isQuotesy()) {	//"
		getChar();
		while (32==c ||33==c ||(35<=c && c<=126)) {//������ַ���
			token += c;
			getChar();
		}
		//δƥ����˫���ţ����ﻹ��һЩ����ֲ��������⣺token�����ݿ��ܿ���ƥ��������ʶ��
		//ֵ��ע����ǣ�')'��';'�ȶ����ַ����ĺϷ��ַ������ָ�������������鷳
		if (!isQuotesy()) {
			retract();
			Error::addError("\""+token, line, UNDEFINED_INPUT);
			return 1;
		}
		//����������е����⣺�޷�ʶ��˫�����ﺬ��δ�����ַ��Ĵ��󣬳�������������¼Ϊ���δ���
		symbol = kinds::STRSY;
	}else if (isEqusy()) {		//=
		token += c;
		getChar();
		if (isEqusy()) {		//��ϵ�����==
			symbol = kinds::EQUSY;
			token += c;
		} else {				//��ֵ��=
			retract();
			symbol = kinds::ASINSY;
		}
	} else if (isPlussy()) {	//+
		symbol = kinds::PLUSSY;
		token += c;
	} else if (isMinussy()) {	//-
		symbol = kinds::MINUSSY;
		token += c;
	} else if (isStarsy()) {	//*
		symbol = kinds::STARSY;
		token += c;
	} else if (isDivisy()) {	///
		symbol = kinds::DIVISY;
		token += c;
	} else if (isExcsy()) {		//!
		token += c;
		getChar();
		if (isEqusy()) {		//!=
			token += c;
			symbol = kinds::NEQUSY;
		} else {				//ֻ��!��δʶ��
			retract();
			Error::addError("!", line, UNDEFINED_INPUT);
			return 1;
		}
	} else if (isULine()) {		//_
		symbol = kinds::ULINE;
		token += c;
	} else if (isCommasy()) {	//,
		symbol = kinds::COMMASY;
		token += c;
	} else if (isSemisy()) {	//;
		symbol = kinds::SEMISY;
		token += c;
	} else if (isColonsy()) {	//:
		symbol = kinds::COLONSY;
		token += c;
	}  else if (isLParsy()) {	//(
		symbol = kinds::LPARSY;
		token += c;
	} else if (isRParsy()) {	//)
		symbol = kinds::RPARSY;
		token += c;
	} else if (isLBracsy()) {	//[
		symbol = kinds::LBRACSY;
		token += c;
	} else if (isRBracsy()) {	//]
		symbol = kinds::RBRACSY;
		token += c;
	} else if (isLCBracsy()) {	//{
		symbol = kinds::LCBRACSY;
		token += c;
	} else if (isRCBracsy()) {	//}
		symbol = kinds::RCBRACSY;
		token += c;
	} else if (EOF == c) {
		return -1;
	}
	else {					//δʶ��
		Error::addError(""+c, line,UNDEFINED_INPUT);
		return 1;
	}
	if (showToken) cout << token << endl;
	return 0;
}

void Lexer::save(const int i) {
	savePointer[i] = ftell(input);
	saveNum[i] = num;
	saveSymbol[i] = symbol;
	saveToken[i] = token;
	saveLine[i] = line;
}

void Lexer::recover(const int i) {
	fseek(input, savePointer[i], 0);
	num = saveNum[i];
	symbol = saveSymbol[i];
	token = saveToken[i];
	line = saveLine[i];
}




