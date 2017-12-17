#pragma once
#define NUM 100000
class Lexer
{
private:
	static int savePointer[NUM];
	static string saveToken[NUM];
	static int saveNum[NUM];
	static enum kinds saveSymbol[NUM];
	static int saveLine[NUM];
	static FILE* input;
	static char c;
	static int getChar();
	static int retract();
	static int isSpace();
	static int isNewLine();
	static int isTab();
	static int isPlussy();
	static int isMinussy();
	static int isStarsy();
	static int isLessy();
	static int isMorsy();
	static int isDivisy();
	static int isLParsy();
	static int isRParsy();
	static int isLBracsy();
	static int isRBracsy();
	static int isLCBracsy();
	static int isRCBracsy();
	static int isCommasy();
	static int isSemisy();
	static int isColonsy();
	static int isEqusy();
	static int isExcsy();
	static int isULine();
	static int isAposy();
	static int isQuotesy();
	static int isAlpha();
	static int isDigit();
	static int isPartOfStr();
	static int reserver();
public:
	static string token;
	static int num;
	static enum kinds symbol;
	static int line;
//	Lexer(const char* path);
	Lexer();
	~Lexer();
	static void init(const char* path);
	static int getToken();
	static void save(int i);
	static void recover(int i);
};

