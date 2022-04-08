#include <bits/stdc++.h>
using namespace std;

// this is basically the node of each block.
// This is the data structure for the basic block of a CFG.

struct Node
{
  int id;
  vector<string> store;
  int left;
  int right;
  // constructor
  Node(int x)
  {
    id = x;
    left = -1;
    right = -1;
  }
};

void dfs(int node, vector<string> local, vector<int> checknode, vector<vector<string> > &all_paths,map<int, Node *> &mapper)
{
  if (node == -1)
    return;

  // checking if the node had already been travelled once in this particular traversal.
  
  if (count(checknode.begin(), checknode.end(), node))
  {   checknode.push_back(node);
    
    for(auto p:mapper[node]->store)
      {local.push_back(p);}
    
    
     all_paths.push_back(local);
    
    return;
  }

  // visited
  checknode.push_back(node);

  // leaf node
  if (mapper[node]->left == -1 && mapper[node]->right == -1)
  { for(auto p:mapper[node]->store)
      {local.push_back(p);}
    all_paths.push_back(local);  
    return;
  }

 
 for(auto p:mapper[node]->store)
      {local.push_back(p);}

  dfs(mapper[node]->left, local, checknode, all_paths,mapper);
  dfs(mapper[node]->right, local, checknode, all_paths,mapper);
}

int main()
{
  vector<vector<string> > all_paths;
  // code for extracting CFG.
  //***
  ifstream inFile;
  inFile.open("blocks.txt");

  vector<string> orderdata;
  map<int, Node *> mapper;

  while (true)
  {
    string str;
    inFile >> str;
    if (inFile.eof())
      break;
    orderdata.push_back(str);
  }

  int n = orderdata.size();
  for (int i = 0; i < n; i++)
  {
    if (orderdata[i][0] >= '0' && orderdata[i][0] <= '9')
    {
      int blocknumber = stoi(orderdata[i]);
      int j = i + 1;
      vector<string> blockopcodes;

      while (j<n && (orderdata[j][0] < '0' || orderdata[j][0] > '9'))
      {
        blockopcodes.push_back(orderdata[j]);
        j++;
      }

      Node *newnode = new Node(blocknumber);

     
      

    for(auto &x : blockopcodes)
      {
        newnode->store.push_back(x);
      }

      mapper[blocknumber] = newnode;
    }
    else
    {
      continue;
    }
  }
inFile.close();
  
  ifstream inFilew;
  string first,second;
  inFilew.open("order.txt");

  while(inFilew >> first>> second)
  { 
    int x,y;
    x=stoi(first);
    y=stoi(second);
    cout<<x<<" "<<y<<endl;
    if(mapper[x]->left==-1)
    {mapper[x]->left=y;}
    else
    {
      mapper[x]->right=y;
    }
    
  }
  inFilew.close();

  
  //***

  vector<int> checknodelocal;
  vector<string> opcodesofeachloop;

   dfs(0,opcodesofeachloop,checknodelocal,all_paths,mapper);



  int i;
int count=0;
  cout<<"the total number of paths are :" <<all_paths.size()<<endl;
   for(auto &each_path : all_paths)
  {
    cout<<"this is the path number : "<<count<<endl;
    cout<<"The number of instructions on this path are : "<<each_path.size()<<endl;
    
   for(i=0;i<each_path.size()-2;i++)
 {
  
  cout<<each_path[i]<<" "<<each_path[i+1]<<" "<<each_path[i+1]<<" "<<endl;
}
    printf("\n");
    count++;
  } 

  /* for(auto x:mapper)
      {
        cout<<x.first<<endl;
        cout<<x.second->left<<endl;
        cout<<x.second->right<<endl;
        for(auto p:x.second->store)
          {
           cout<<p<<endl;
          }
      } */
}
