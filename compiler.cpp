#include<cstdio>
#include<iostream>
#include<fstream>
#include<cstring>
#include<stdio.h>
using namespace std;
char ch=' ';
char token[20];
char *keyin[6]={"BEGIN","END","FOR","IF","THEN","ELSE"};
char *keyout[6]={"Begin","End","For","If","Then","Else"};
char sepin[6]={':','+','*',',','(',')'};
char *sepout[6]={"Colon","Plus","Star","Comma","LParenthesis","RParenthesis"};
//判断关键字(不是为0)
int iskey(char *token){
	for(int i=0;i<=5;i++)
	    if(strcmp(keyin[i],token)==0)
	        return ++i;
	return 0;
} 
//判断字母 
bool isletter(char letter){
	if((letter>='a'&&letter<='z')||(letter>='A'&&letter<='Z'))
	    return true;
	else 
	    return false;
}
//判断数字 
bool isdigit(char digit){
	if(digit>='0'&&digit<='9')
	    return true;
	else
	    return false;
}
//判断分界符
int isseprator(char token){
	for(int i=0;i<=5;i++)
	    if(token==sepin[i])
	        return ++i;
	return 0;
} 
int stoi(char *token,int l){
	int t=0;
	for(int i=0;i<=l;i++){
		t=t*10+token[i]-'0';
	}
	return t;
}
//词法分析函数 
void analyze(FILE *file){
    while((ch=fgetc(file))!=EOF){
    	if(ch==' '||ch=='\t'||ch=='\n'){}
    	else if(isletter(ch)){
    		char token[20]={'\0'};
    		int i=0;
    		while(isletter(ch)||isdigit(ch)){
    			token[i]=ch;
    			i++;
    			ch=fgetc(file);
			}
			int k=iskey(token);
			if(k>0) cout<<keyout[k-1]<<endl;
			else{
				cout<<"Ident("<<token<<")"<<endl;
			}
			memset(token,'\0',i+1);
			fseek(file,-1L,SEEK_CUR);
			if(ch==EOF) return;
		}
		else if(isdigit(ch)){
			int i=0;
			while(isdigit(ch)){
				token[i]=ch;
				i++;
				ch=fgetc(file);
			}
			if(i==1) cout<<"Int("<<token<<")"<<endl;
			else cout<<"Int("<<stoi(token,i-1)<<")"<<endl;
			memset(token,'\0',i+1);
			fseek(file,-1L,SEEK_CUR);
			if(ch==EOF) return;
		}
		else if(isseprator(ch)){
			int s=isseprator(ch);
			char t=fgetc(file);
			if(s==1&&t=='='){
				cout<<"Assign"<<endl;
				continue;
			} 
			else{
				cout<<sepout[s-1]<<endl;
			}
			fseek(file,-1L,SEEK_CUR);
			if(ch==EOF) return;
		}
		else{
			cout<<"Unknown"<<endl;
			return;
		} 
	}
}
int main(int argc,char *argv[]){
	FILE *file=fopen(argv[1],"r");
	//FILE *file=fopen("test.txt","r"); 
	analyze(file);
	fclose(file);
	return 0;
} 
