// ObjParser.cpp //
#include "stdafx.h"
#include "ObjParser.h"
#include "Mesh.h"
#include "RenderSystemPrereq.h"
namespace helper {
	bool is_whitespace(char c) {
		if(c==' '||c=='\t') {return true;};
		return false;
	};
	bool is_newline(char c) {
		if(c=='\r'||c=='\n'||c=='\0') {return true;};
		return false;
	};
	bool is_comment(char c) {
		if(c=='#') {return true;};
		return false;
	};
	bool is_numeric(char c) {
		if((c>='0'&&c<='9')||c=='+'||c=='-') {return true;};
		return false;
	};
	bool is_number(char c) {
		if(is_numeric(c)||c=='.'||c==',') {return true;};
		return false;
	};
	bool is_character(char c) {
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z')) {return true;};
		return false;
	};
	bool is_float(char *str,int len) {
		for(int i=0;i<len;i++) {
			if(str[i]==','||str[i]=='.') {
				return true;
			};
		};
		return false;
	};
	void set(EToken type,Token &token) {
		token.type=type;
		token.index=0;
		for(int k=0;k<4;k++) {
			token.f[k]=0.0f;
		};
		for(int k=0;k<12;k++) {
			token.i[k]=-1;
		};
	};
}; // helper

namespace obj {
	static int size=0;
	static FILE *file;
	static char buffer[128];
	static int pos=0;
	static int len=0;

	static bool is_eof() {return len==0;}; // End of line
	struct _index {_index(s32 a,s32 b,s32 c) {i[0]=a;i[1]=b;i[2]=c;}; s32 i[3];};
	bool construct(const std::vector<Token> &stream,Mesh *&mesh) {
		std::vector<Vector3> vertex;
		std::vector<Vector3> normal;
		std::vector<Vector2> texcoord;
		std::vector<_index> indices;

		u32 count=stream.size();
		for(u32 k=0;k<count;k++) {
			if(stream[k].type == TT_Vertex) {
				vertex.push_back(Vector3(stream[k].f[0],stream[k].f[1],stream[k].f[2]));
			}
			else if(stream[k].type == TT_Normal) {
				normal.push_back(Vector3(stream[k].f[0],stream[k].f[1],stream[k].f[2]));
			}
			else if(stream[k].type == TT_Texcoord) {
				texcoord.push_back(Vector2(stream[k].f[0],stream[k].f[1]));
			}
			else if(stream[k].type == TT_Face) {
				indices.push_back(_index(stream[k].i[0]-1,stream[k].i[1]-1,stream[k].i[2]-1));
				indices.push_back(_index(stream[k].i[3]-1,stream[k].i[4]-1,stream[k].i[5]-1));
				indices.push_back(_index(stream[k].i[6]-1,stream[k].i[7]-1,stream[k].i[8]-1));
			};
		};
		vertex_s *vertices=new vertex_s[indices.size()];
		u16 *index=new u16[indices.size()];

		for(u32 i=0;i<indices.size();i++) {
			vertices[i].position=vertex[indices[i].i[0]];
			vertices[i].normal=normal[indices[i].i[2]];
			vertices[i].texcoord=texcoord[indices[i].i[1]];
			vertices[i].color=0xffffffff;

			index[i]=i;
		};

		bool success=true;
		
		if(!mesh->Init(sizeof(vertex_s),indices.size(),vertices,indices.size(),index,true)) {
			success=false;
		};
		delete [] vertices;
		delete [] index;
		return success;
	};
	bool parse(const char *filename,std::vector<Token> &stream) {
		fopen_s(&file,filename,"r");
		if(file==NULL) {return false;};

		fseek(file,0,SEEK_END);
		size=ftell(file);
		rewind(file);

		EToken curr_token=TT_Invalid;
		int index=0;
		char c=-1,t[2]={0},n[12]={0};

		fill_buffer();
		while(!is_eof()) {
			get_next(c);
			if(curr_token==TT_Invalid) {
				if(helper::is_whitespace(c)||helper::is_newline(c)) {
					continue;
				}
				else if(helper::is_comment(c)) {
					consume_line();
				}
				else if(helper::is_numeric(c)) {
					curr_token=TT_Numeric;
					step_back();
				}
				else if(helper::is_character(c)) {
					curr_token=TT_Character;
					step_back();
				};
			}
			else {
				if(curr_token==TT_Numeric) {
					
					if(!helper::is_number(c)) {
						if(helper::is_float(n,sizeof(n))) {
							Token &token=stream[index];
							token.f[token.index++]=(f32)atof(n);
						}
						else {
							Token &token=stream[index];
							token.i[token.index++]=(s32)atoi(n);
						};
						
						curr_token=TT_Invalid;
						for(int k=0;k<sizeof(n);k++) {
							n[k]=0;
						};
					}
					else {
						for(int k=0;k<sizeof(n);k++) {
							if(n[k]==0) {
								n[k]=c;

								break;
							};
						};
					};
				}
				else if(curr_token==TT_Character) {
					if(!helper::is_character(c)) {
						if(t[0]=='v'&&t[1]==0) {
							Token token;
							helper::set(TT_Vertex,token);
							stream.push_back(token);
							index=stream.size()-1;
						}
						else if(t[0]=='v'&&t[1]=='t') {
							Token token;
							helper::set(TT_Texcoord,token);
							stream.push_back(token);
							index=stream.size()-1;
						}
						else if(t[0]=='v'&&t[1]=='n') {
							Token token;
							helper::set(TT_Normal,token);
							stream.push_back(token);
							index=stream.size()-1;
						}
						else if(t[0]=='f'&&t[1]==0) {
							Token token;
							helper::set(TT_Face,token);
							stream.push_back(token);
							index=stream.size()-1;
						};

						curr_token=TT_Invalid;
						for(int k=0;k<sizeof(t);k++) {
							t[k]=0;
						};
						step_back();
					}
					else {
						for(int k=0;k<sizeof(t);k++) {
							if(t[k]==0) {
								t[k]=c;
								break;
							};
						};
					};	
				};
			};
		};
		fclose(file);
		return true;
	};
	void get_next(char &c) {
		if(pos<len) {
			c=buffer[pos++];
		}
		else {
			fill_buffer();
			if(len==0) {
				c=0;
			};
		};
	};
	void fill_buffer() {
		len=fread(buffer,1,sizeof(buffer),file);
		pos=0;
	};
	void step_back() {
		pos--;
	};
	void consume_line() {
		char c=0;
		while(true) {
			get_next(c);
			if(helper::is_newline(c)) {
				break;
			};
		};
	};
}; // obj
