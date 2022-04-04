#include <bits/stdc++.h>
using namespace std;

//this is basically the node of each block.
//This is the data structure for the basic block of a CFG.


struct Node{
int id;
vector<string> store;
Node* left;
Node* right;
//constructor
Node(int x){
  id=x;  
  left=NULL;
  right=NULL;
  }
};




void dfs(Node* node,vector<string>local,vector<int>checknode,vector<vector<string>> &all_paths)
{
  if(node==NULL)
  { return;}

 //checking if the node had already been travelled once in this particular traversal.
      if(count(checknode.begin(),checknode.end(),node->id))
      {
          return;
      }
  
     if(node->left==NULL && node->right==NULL)
     {
           checknode.push_back(node->id);
           for(auto &x : node->store)
          {local.push_back(x);}
           all_paths.push_back(local);
           return;
     }

    checknode.push_back(node->id);
  
    for(auto &x : node->store)
      {
          local.push_back(x);
      }

      dfs(node->left,local,checknode,all_paths);
      dfs(node->right,local,checknode,all_paths);

}


int main() {
  vector<vector<string>>all_paths;
//code for extracting CFG. 
//*****************************
ifstream inFile;
inFile.open("blocks.txt");

vector<string> orderdata;
map<int,Node*> mapper;
  
while(true)
  {
   string str;
    inFile>>str;
     if(inFile.eof()) 
       break;
   orderdata.push_back(str);
  }

 

for(int i=0;i<orderdata.size();i++)
  {
    if(orderdata[i][0]>='0' && orderdata[i][0]<='9')
    {
      int blocknumber=stoi(orderdata[i]);
      int j=i+1;
      vector<string> blockopcodes;
      while(orderdata[j][0]<'0'||orderdata[j][0]>'9')
        {
          blockopcodes.push_back(orderdata[j]);
          j++;
        }
      

      Node* newnode=new Node(blocknumber);

      for(auto &x:blockopcodes)
        {
          newnode->store.push_back(x);
        }

      mapper[blocknumber]=newnode;
      
    }
    else
    { continue;}
  }
 


  
//*****************************

  
vector<int> checknodelocal;
  vector<string> opcodesofeachloop;

/*
  for(auto x:mapper)
    {
      cout<<x.first<<endl;
      for(auto p:x.second->store)
        {
         cout<<p<<endl; 
        }
    }*/
  
//dfs(node,opcodesofeachloop,checknodelocal);

map<pair<string,pair<string,string>>,int> frequency;

int i;
  
  //for(auto &each_path : all_paths)
    //{
     //for(i=0;i<each_path.size()-2;i++)
       //{
          //to store the frequency of each 3 - gram
         //frequency[make_pair(each_path[i],make_pair(each_path[i+1],each_path[i+1]))]++; 
       //}      
    //}
    
  //further write code to extract uniquee/most occuring trigrams.
  
}




//     SVC(kernel='linear', C = 1)
