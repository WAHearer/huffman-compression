#include<iostream>
#include<map>
#include<bitset>
#include"HuffmanTree.h"
std::map<char,int>map;
void encode(){
    std::string passage;
    WordList wordlist;
    freopen("4.USTC-logo.png","rb",stdin);
    freopen("4.USTC-logo.png.huff","wb",stdout);
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
    std::string compressionFile;
    std::bitset<8>sizeToBin(tree.list.size()-1);//0到255
    compressionFile+=sizeToBin.to_string();
    for(int i=0;i<tree.list.size();i++){
        std::bitset<8>firstToBin(tree.list[i].first[0]);
        compressionFile+=firstToBin.to_string();
        std::bitset<5>lengthToBin(tree.list[i].second.length());
        compressionFile+=lengthToBin.to_string();
        compressionFile+=tree.list[i].second;
    }
    int length=passage.length();
    for(int i=0;i<length;i++){
        std::string s;
        s+=passage[i];
        compressionFile+=tree.map[s];
    }
    for(int i=0;i<compressionFile.length();i+=8){
        char code=0;
        for(int j=0;j<8;j++){
            if(i+j>=compressionFile.length())
                code=code*2+1;
            else
                code=code*2+compressionFile[i+j]-'0';
        }
        std::cout<<code;
    }
    fclose(stdin);
    fclose(stdout);
}
void decode(){
    freopen("4.USTC-logo.png.huff","rb",stdin);
    freopen("4.USTC-logo.png.decode","wb",stdout);
    std::map<std::string,std::string>map;
    int listLength=0;
    std::string compressionFile;
    char c;
    while(scanf("%c",&c)!=EOF){
        std::bitset<8>charToBin(c);
        compressionFile+=charToBin.to_string();
    }
    int cnt=0;
    for(int i=1;i<=8;i++){
        listLength=listLength*2+compressionFile[cnt++]-'0';
    }
    listLength++;
    for(int i=1;i<=listLength;i++){
        char c=0;
        for(int j=1;j<=8;j++){
            c=c*2+compressionFile[cnt++]-'0';
        }
        std::string text;
        text+=c;
        int codeLength=0;
        for(int j=1;j<=5;j++){
            codeLength=codeLength*2+compressionFile[cnt++]-'0';
        }
        std::string code;
        for(int j=1;j<=codeLength;j++){
            code+=compressionFile[cnt++];
        }
        map[code]=text;
    }
    std::string codeNow;
    while(cnt<compressionFile.length()){
        codeNow+=compressionFile[cnt++];
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
