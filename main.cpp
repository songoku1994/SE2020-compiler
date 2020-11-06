#include<stdio.h>
#include<stack>
#include<iostream>
#include<utility>
#include<string>

#define PLUS 0
#define MUL 1
#define I 2
#define LEFTPAREN 3
#define RIGHTPAREN 4
#define WELL 5
#define N 6
#define END -1
#define STATUTE_TRUE 1
#define STATUTE_FALSE 0
using namespace std;
int priority_table[6][6]={
    {2,1,1,1,2,2},
    {2,2,1,1,2,2},
    {2,2,-1,-1,2,2},
    {1,1,1,1,0,-1},
    {2,2,-1,-1,2,2},
    {1,1,1,1,-1,-1}
};
int statute(stack<char>& st){
    if(st.top() == 'i'){
        st.pop();
        st.push('N');
        return STATUTE_TRUE;
    }
    else if(st.top() == 'N'){
        st.pop();
        if(st.top()=='+'||st.top()=='*'){
            st.pop();
            if(st.top()=='N'){
                return STATUTE_TRUE;
            }
            else{
                return STATUTE_FALSE;
            }
        }
        else{
            return STATUTE_FALSE;
        }
    }
    else if(st.top() == ')'){
        st.pop();
        if(st.top()=='N'){
            st.pop();
            if(st.top() == '('){
                st.pop();
                st.push('N');
                return STATUTE_TRUE;
            }
            else{
                return STATUTE_FALSE;
            }
        }
        else{
            return STATUTE_FALSE;
        }
    }
    else{
        return STATUTE_FALSE;
    }
}

int getIndex(char c){
    switch (c){
    case '+':{
        return PLUS;
        break;
    }
    case '*':{
        return MUL;
        break;
    }
    case 'i':{
        return I;
        break;
    }
    case '(':{
        return LEFTPAREN;
        break;
    }
    case ')':{
        return RIGHTPAREN;
        break;
    }
    case '#':{
        return WELL;
        break;
    }
    default:
        return -1;
        break;
    }
}
char get_vt(stack<char> st){
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
int main(int argc,char* argv[]){
    FILE* fp = NULL;
    std::stack<char> st;
    st.push('#');
    char s_temp[1005]={'\0'};
    fp = fopen(argv[1],"r");
    fscanf(fp,"%s",s_temp);
    std::string s = s_temp;
    s += '#';
    int index_y;
    int index_x;
    char c;
    int i = 0;
    while(i < s.length()){
        index_y = getIndex(s[i]);
        if(index_y != -1 ){
            if(i!=s.length()-1 && s[i]=='#'){
                printf("E\n");
                return 0;
            }
            c = get_vt(st);
            index_x = getIndex(c);
            switch (priority_table[index_x][index_y]){
            case 2:{
                int status = statute(st);
                if( status == STATUTE_TRUE){
                    printf("R\n");
                }
                else if(status == STATUTE_FALSE){
                    printf("RE\n");
                    return 0;
                }
                break;
            }
            case 1:{
                printf("I%c\n",s[i]);
                st.push(s[i]);
                i++;
                break;
            }
            case 0:{
                printf("I%c\n",s[i]);
                st.push(s[i]);
                i++;
                break;
            }
            default:{
                if(c == '#' && s[i] == '#'){
                    return 0;
                }
                printf("E\n");
                return 0;
                break;
            }
            }
        }
        else{
            printf("E\n");
            return 0;
        }
    }
    fclose(fp);
    return 0;
}
