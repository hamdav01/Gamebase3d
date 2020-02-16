// ObjParser.h //

#ifndef OBJPARSER_H_INCLUDED
#define OBJPARSER_H_INCLUDED

class Mesh;

enum EToken {TT_Invalid,TT_Numeric,TT_Character,TT_Vertex,TT_Texcoord,TT_Normal,TT_Face};

struct Token {
	EToken type;
	s32 index;
	f32 f[4];
	s32 i[12];
};

namespace helper {
	bool is_whitespace(char c);
	bool is_newline(char c);
	bool is_comment(char c);
	bool is_numeric(char c);
	bool is_number(char c);
	bool is_character(char c);
	bool is_float(char *str,int len);
	void set(EToken type,Token &token);
}; // helper

namespace obj {
	bool construct(const std::vector<Token> &stream,Mesh *&mesh);
	bool parse(const char *filename,std::vector<Token> &stream);
	void get_next(char &c);
	void fill_buffer();
	void step_back();
	void consume_line();
};
#endif // OBJPARSER_H_INCLUDED