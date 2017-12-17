#pragma once
class StringTable
{
private:
	static int i;
public:
	static vector<string> names;
	static vector<string> contents;
	StringTable(void);
	~StringTable(void);
	static void init();//½«0ºÅÖÃÎª string_0 "\n"
	/**	
	 *	@param	content
	 *	@return content's name
	 */
	static string add(string content);
	/**	
	 *	@param	content's name
	 *	@return content
	 */
	static string look_up(string name);
	static void print(char *path);
	static void print(ofstream out);
};

