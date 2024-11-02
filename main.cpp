#include<bitset>
#include"HuffmanTree.h"
void encode(std::string filename){
    std::string passage;
    WordList wordlist;
    freopen(filename.data(),"rb",stdin);
    freopen((filename+".huff").data(),"wb",stdout);
    char c;
    std::map<char,int>pos;
    while(scanf("%c",&c)!=EOF){
        passage+=c;
        if(pos[c]){
            wordlist.list[pos[c]-1].val++;
        }
        else{
            pos[c]=wordlist.list.size()+1;
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
    for(auto &i:tree.list){
        std::bitset<8>firstToBin(i.first[0]);
        compressionFile+=firstToBin.to_string();
        std::bitset<5>lengthToBin(i.second.length());
        compressionFile+=lengthToBin.to_string();
        compressionFile+=i.second;
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
void decode(const std::string &filename){
    freopen((filename+".huff").data(),"rb",stdin);
    freopen(("decoded-"+filename).data(),"wb",stdout);
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
        c=0;
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
        if(!map[codeNow].empty()){
            std::cout<<map[codeNow];
            codeNow="";
        }
    }
}
void encodeWithWord(std::string filename){
    std::string passage;
    WordList wordlist;
    freopen(filename.data(),"rb",stdin);
    freopen((filename+".huffWithWord").data(),"wb",stdout);
    char c;
    std::string word;
    std::map<char,int>pos;
    std::map<std::string,int>wordCnt;
    std::vector<std::string>wordToHuffman;
    while(scanf("%c",&c)!=EOF){
        passage+=c;
        if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
            word+=c;
        else{
            wordCnt[word]++;
            if(wordCnt[word]==30)
                wordToHuffman.push_back(word);
            word="";
        }
        if(pos[c]){
            wordlist.list[pos[c]-1].val++;
        }
        else{
            pos[c]=wordlist.list.size()+1;
            std::string s;
            s+=c;
            wordlist.list.push_back(Word(s,1));
        }
    }
    for(auto &wordInList:wordToHuffman){
        wordlist.list.push_back(Word(wordInList,wordCnt[wordInList]));
    }
    HuffmanTree tree(wordlist);
    tree.buildList(tree.root,"");
    std::string compressionFile;
    std::bitset<8>sizeToBin(tree.list.size()-1);//0到255
    compressionFile+=sizeToBin.to_string();
    for(auto &i:tree.list){
        std::bitset<4>lengthOfWordToBin(i.first.length());
        compressionFile+=lengthOfWordToBin.to_string();
        for(int j=0;j<i.first.length();j++){
            std::bitset<8>firstToBin(i.first[j]);
            compressionFile+=firstToBin.to_string();
        }
        std::bitset<5>lengthToBin(i.second.length());
        compressionFile+=lengthToBin.to_string();
        compressionFile+=i.second;
    }
    int length=passage.length();
    for(int i=0;i<length;i++){
        std::string s;
        c=passage[i];
        word="";
        int j=i;
        while((c>='A'&&c<='Z')||(c>='a'&&c<='z')){
            word+=c;
            c=passage[++j];
        }
        if(!tree.map[word].empty()){
            s=word;
            i=j-1;
        }
        else
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
void decodeWithWord(const std::string &filename){
    freopen((filename+".huffWithWord").data(),"rb",stdin);
    freopen(("decodedWithWord-"+filename).data(),"wb",stdout);
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
        int wordLength=0;
        for(int j=1;j<=4;j++){
            wordLength=wordLength*2+compressionFile[cnt++]-'0';
        }
        std::string text;
        for(int pos=1;pos<=wordLength;pos++){
            c=0;
            for(int j=1;j<=8;j++){
                c=c*2+compressionFile[cnt++]-'0';
            }
            text+=c;
        }
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
        if(!map[codeNow].empty()){
            std::cout<<map[codeNow];
            codeNow="";
        }
    }
}
int main(){
    encode("1.MIT-license.txt");
    encode("2.hamlet.txt");
    encode("3.USTC-logo.bmp");
    encode("4.USTC-logo.png");
    encode("5.data-structure.pdf");
    encode("6.MV.mp4");
    decode("1.MIT-license.txt");
    decode("2.hamlet.txt");
    decode("3.USTC-logo.bmp");
    decode("4.USTC-logo.png");
    decode("5.data-structure.pdf");
    decode("6.MV.mp4");
    encodeWithWord("2.hamlet.txt");
    decodeWithWord("2.hamlet.txt");
    return 0;
}
