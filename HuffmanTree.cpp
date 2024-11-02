#include"HuffmanTree.h"
TreeNode::TreeNode(int val):val(val),father(nullptr),left(nullptr),right(nullptr){}
TreeNode::TreeNode(std::string &s,int val):s(s),val(val),father(nullptr),left(nullptr),right(nullptr){}
HuffmanTree::HuffmanTree(WordList wordlist){
    std::vector<TreeNode*>nodelist;
    for(auto &i:wordlist.list){
        TreeNode *node=new TreeNode(i.s,i.val);
        nodelist.push_back(node);
    }
    std::deque<int>q;
    std::vector<int>defeat[nodelist.size()];//val,pos
    while(nodelist.size()>1){
        q.clear();
        for(int i=0;i<nodelist.size();i+=2){
            defeat[i].clear();
            if(i+1<nodelist.size())
                defeat[i+1].clear();
            if(i+1==nodelist.size())
                q.push_back(i);
            else{
                if(nodelist[i]->val<nodelist[i+1]->val){
                    defeat[i].push_back(i+1);
                    q.push_back(i);
                }
                else{
                    defeat[i+1].push_back(i);
                    q.push_back(i+1);
                }
            }
        }
        while(q.size()>1){
            unsigned long long size=q.size();
            for(int i=0;i<size/2;i++){
                int pos1=q.front();
                q.pop_front();
                int pos2=q.front();
                q.pop_front();
                if(nodelist[pos1]->val<nodelist[pos2]->val){
                    defeat[pos1].push_back(pos2);
                    q.push_back(pos1);
                }
                else{
                    defeat[pos2].push_back(pos1);
                    q.push_back(pos2);
                }
            }
        }
        int pos1=q.front(),pos2,minn=0x7fffffff;
        for(int &i:defeat[pos1]){
            if(nodelist[i]->val<minn){
                pos2=i;
                minn=nodelist[i]->val;
            }
        }
        TreeNode *node=new TreeNode(nodelist[pos1]->val+nodelist[pos2]->val);
        nodelist[pos1]->father=node;
        nodelist[pos2]->father=node;
        node->left=nodelist[pos1];
        node->right=nodelist[pos2];
        nodelist.erase(nodelist.begin()+std::max(pos1,pos2));
        nodelist.erase(nodelist.begin()+std::min(pos1,pos2));
        nodelist.push_back(node);
    }
    root=nodelist[0];
}
void HuffmanTree::buildList(TreeNode *node,const std::string &s){
    if(!node->s.empty()){
        list.emplace_back(node->s,s);
        map[node->s]=s;
    }
    if(node->left)
        buildList(node->left,s+"0");
    if(node->right)
        buildList(node->right,s+"1");
}
void HuffmanTree::print(){
    for(auto &i:list){
        std::cout<<i.first<<" "<<i.second<<std::endl;
    }
}
