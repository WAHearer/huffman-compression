#include<iostream>
#include<map>
#include<bitset>
#include"HuffmanTree.h"
std::map<char,int>map;
void encode(){
    std::string passage;
    WordList wordlist;
    freopen("1.MIT-license.txt","rb",stdin);
    freopen("1.MIT-license.txt.huff","wb",stdout);
    char c;
    while(scanf("%c",&c)!=EOF){
        passage+=c;
        if(map[c]){
            wordlist.list[map[c]-1].val++;
        }
        else{
            map[c]=wordlist.list.size()+1;
            std::string s;
            s+=c;
            wordlist.list.push_back(Word(s,1));
        }
    }
    HuffmanTree tree(wordlist);
    tree.buildList(tree.root,"");
    std::bitset<8>sizeToBin(tree.list.size()-1);//0到255
    std::cout<<sizeToBin.to_string();
    for(int i=0;i<tree.list.size();i++){
        std::bitset<8>firstToBin(tree.list[i].first[0]);
        std::cout<<firstToBin.to_string();
        std::bitset<5>lengthToBin(tree.list[i].second.length());
        std::cout<<lengthToBin.to_string();
        std::cout<<tree.list[i].second;
    }
    int length=passage.length();
    for(int i=0;i<length;i++){
        std::string s;
        s+=passage[i];
        std::cout<<tree.map[s];
    }
    fclose(stdin);
    fclose(stdout);
}
void decode(){
    freopen("1.MIT-license.txt.huff","rb",stdin);
    freopen("1.MIT-license.txt.decode","wb",stdout);
    std::map<std::string,std::string>map;
    int listLength=0;
    for(int i=1;i<=8;i++){
        listLength=listLength*2+getchar()-'0';
    }
    listLength++;
    for(int i=1;i<=listLength;i++){
        char c=0;
        for(int j=1;j<=8;j++){
            c=c*2+getchar()-'0';
        }
        std::string text;
        text+=c;
        int codeLength=0;
        for(int j=1;j<=5;j++){
            codeLength=codeLength*2+getchar()-'0';
        }
        std::string code;
        for(int j=1;j<=codeLength;j++){
            code+=getchar();
        }
        map[code]=text;
    }
    std::string codeNow;
    char c;
    while(scanf("%c",&c)!=EOF){
        codeNow+=c;
        if(map[codeNow]!=""){
            std::cout<<map[codeNow];
            codeNow="";
        }
    }
}
int main(){
    encode();
    decode();
    return 0;
}
