#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include<stdio.h>
#include<string> 
 
using namespace std;

string str; //存储输入文法
stack <char> st;//栈 
string str_b; // 剩余输入串
//符号索引
char key[6] = {'+','*','i','(',')','#'};
// 算符优先关系表
int table[6][6] = {
    {2,1,1,1,2,2},
    {2,2,1,1,2,2},
    {2,2,-1,-1,2,2},
    {1,1,1,1,0,-1},
    {2,2,-1,-1,2,2},
    {1,1,1,1,-1,-1}
};
void set_stack(){
	st.push('#');
}

//寻找字符a在算符优先关系表中的位置
int find(char a){
	for (int i = 0; i <= 5; ++i){
		if (key[i] == a){
			return i;
		}
	}
	return -1;
}

// 删除字符串的第一个元素
void init_string(string &a) {
	for (int i = 1; i <= a.length(); ++i){
		a[i - 1] = a[i];
	}
}

//获取终结符a，b的优先关系
int get_relationship(char a, char b) {
	int x = find(a);
	int y = find(b);
	if(x<0||y<0) return -2;
	return table[x][y];
}

bool is_reduce(){
	if(st.top() == 'i'){
		st.pop();
		st.push('N');
		return true;
	}
	else if(st.top() == 'N'){
		st.pop();
		if(st.top() == '+'||st.top() == '*'){ 
		    st.pop();
		    if(st.top() == 'N'){
		    	return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
    }
	else if(st.top() == ')'){
		st.pop();
		if(st.top() == 'N'){
			st.pop();
			if(st.top() == '('){
				st.pop();
				st.push('N');
				return true;
			}
			else{
			 	return false;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
char get_t(){
	char c;
    if(st.top()=='N'){
        st.pop();
        c = st.top();
        st.push('N');
    }
    else{
        c = st.top();
    }
    return c;
}
// 生成算符优先文法的分析过程
void analyze(){
    int i = 0;
	while(i < str.length()){
		char c = get_t();
		int ret = get_relationship(c,str[i]);
		if(ret == -2){
			printf("E\n");
            return;
		}
		else if(ret == 2){
			int is_re = is_reduce();
			if(is_re == 1){
				printf("R\n");
			}
			else{
				printf("RE\n");
				return;
			}
		}
		else if(ret == 1|| ret == 0){
			printf("I%c\n",str[i]);
            st.push(str[i]);
            i++;
		}
		else{
			if(str[i]=='#'&&c=='#'){
				return;
			}
			else{
				printf("E\n");
                return;
			}
		}
	}
	
}

int main(int argc, char* argv[]){
	FILE* fp = NULL;
	set_stack();
	char s_temp[1010]={'\0'};
    fp = fopen(argv[1],"r");
    fscanf(fp,"%s",s_temp);
    std::string s = s_temp;
	str += '#'; 
	analyze();
	fclose(fp);
	return 0;
}
