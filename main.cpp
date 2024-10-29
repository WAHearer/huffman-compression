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
void decode(std::string filename){
    freopen((filename+".huff").data(),"rb",stdin);
    freopen((filename+".decode").data(),"wb",stdout);
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
    int cnt=0;
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
    for(int i=0;i<wordToHuffman.size();i++){
        std::string word=wordToHuffman[i];
        wordlist.list.push_back(Word(word,wordCnt[word]));
    }
    HuffmanTree tree(wordlist);
    tree.buildList(tree.root,"");
    std::string compressionFile;
    std::bitset<8>sizeToBin(tree.list.size()-1);//0到255
    compressionFile+=sizeToBin.to_string();
    for(int i=0;i<tree.list.size();i++){
        std::bitset<4>lengthOfWordToBin(tree.list[i].first.length());
        compressionFile+=lengthOfWordToBin.to_string();
        for(int j=0;j<tree.list[i].first.length();j++){
            std::bitset<8>firstToBin(tree.list[i].first[j]);
            compressionFile+=firstToBin.to_string();
        }
        std::bitset<5>lengthToBin(tree.list[i].second.length());
        compressionFile+=lengthToBin.to_string();
        compressionFile+=tree.list[i].second;
    }
    int length=passage.length();
    for(int i=0;i<length;i++){
        std::string s;
        char c=passage[i];
        std::string word;
        int j=i;
        while((c>='A'&&c<='Z')||(c>='a'&&c<='z')){
            word+=c;
            c=passage[++j];
        }
        if(tree.map[word]!=""){
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
void decodeWithWord(std::string filename){
    freopen((filename+".huffWithWord").data(),"rb",stdin);
    freopen((filename+".decodeWithWord").data(),"wb",stdout);
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
            char c=0;
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
        if(map[codeNow]!=""){
            std::cout<<map[codeNow];
            codeNow="";
        }
    }
}
int main(){
    encode("6.MV.mp4");
    decode("6.MV.mp4");
    encodeWithWord("2.hamlet.txt");
    decodeWithWord("2.hamlet.txt");
    return 0;
}
