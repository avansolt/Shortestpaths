#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include <map>
#include<sstream>
#include <list>
#include <queue> 
#define pp pair<char,int>
using namespace std;

map<char, int> final;
map<char, bool> picked;
 
class Prioritize
{
public:
    int operator() ( const pair<char, int>& p1, const pair<char, int>& p2 )
    {
        return p1.second > p2.second;
    }
};


struct directed{
  char node1;  //from
  char node2;  //to
  int weight;
};

//Functions
void d_Dijkstra(directed d_edges[], int edges_num,char S,int k);
void ud_Dijkstra(directed ud_edges[], int edges_num, char S, int k);


int main()
{
        char filename[20];
        int max =0;        
        int edges_num=0;
        cout << "Please enter file name\n";
        cin >> filename;
  
      
 //create file stream
   ifstream inFile( filename );

   if( ! inFile.good() )
      return -1;

   //Create the filestream with pointer at the end
   inFile.seekg( 0, ios::end);
   string input, input2;                    //string to hold the entire file

   input.resize( inFile.tellg() );  //Resize string to size of file
   input2.resize( inFile.tellg() );

   inFile.seekg( 0 , ios::beg );    //Set stream pointer back to begin
   inFile.read( &input[0], input.size() ); //Read the file into string

   inFile.seekg( 0 , ios::beg );    //Set stream pointer back to begin
   inFile.read( &input2[0], input2.size() ); //Read the file into string
  
    inFile.close();                  //Close the file
     char comments[256];
   
    stringstream ss(input);
    string hold;
    ss  >> hold;
	
	if(hold[0] == '#')
    { ss.getline(comments,256);
    	ss >> hold;  }
	
	
	//Get the amount of edges and total value for all edges put together
    while(!ss.eof())     
  	{
           char node1, node2;
           int val;
           ss >> node1 >> node2 >> val;
           if(ss.eof()){break;}
             max+=val;
            edges_num++;   
        } 
    stringstream sa(input2);

   //store values in this struct 
   directed d_edges[edges_num]; 
    int i=0;
   string type;
   sa >> type;     

   if(type[0] == '#')
   {  sa.getline(comments,256);
      sa >> type;  }
     
	 while(!sa.eof())
        {
           char node1, node2;
           int val;
           sa >> node1 >> node2 >> val;
           
          if(sa.eof()){break;}
          
          if( i < edges_num){
           d_edges[i].node1 = node1;
           d_edges[i].node2 = node2;
           d_edges[i].weight =val;
          
		  //initialize values in final map and boolean map
          if(final.find(node1) == final.end())
          { final[node1] = max; 
            picked[node1] = false;  }
          if(final.find(node2) == final.end())
          { final[node2] = max;  
            picked[node2] = false;}
           i++;           }
        }

  char S;
 
  cout<< "Please enter the source node "<<endl;
  cin >> S;

  cout<<"Dijkstra\n"<<"Source : " << S<< endl;
  
        if(type== "D")
          {d_Dijkstra(d_edges,edges_num, S, max);}
        else{ud_Dijkstra(d_edges,edges_num, S, max);}

  map<char,int>::iterator it;

   //print nodes shortest path
   for (it=final.begin(); it!=final.end(); ++it)
   { 
	 if(it->second == max)
	  {cout <<"Node: " <<it->first << " = Unreachable\n";}
	 else{
      cout <<"Node: " <<it->first << " = " << it->second << '\n';}
      it->second = max;
   }

  int k;
  cout<<"Please plug in k: \n";
  cin >> k;
  cout<<"Please plug inthe Source node:\n";
  cin >> S;

  map<char,bool>::iterator itr;
  //reset picked to false
  for (itr=picked.begin(); itr!=picked.end(); ++itr)
        itr->second = false;

  if(type== "D")
  { d_Dijkstra(d_edges,edges_num, S, k);}
  else{ud_Dijkstra(d_edges,edges_num, S, k);}

  for (it=final.begin(); it!=final.end(); ++it)
  {
     if(it->second == max)
	 {cout <<"Node: " <<it->first << " = Unreachable\n";}
	 else{
     cout <<"Node: " <<it->first << " = " << it->second << '\n';}
     it->second = max; }


  return 0;
}//end main
void d_Dijkstra(directed d_edges[], int edges_num, char S, int k)
{
    priority_queue<pp, vector<pp> , Prioritize > Q;
    int counter=0;   //Edges from the source node
    char u, node; 
   
    final[S] = 0;
    Q.push(pp(S,0));
   
   while(!Q.empty())
   {
      u = Q.top().first;
      Q.pop();

     if(picked.find(u)->second == false )
      { picked[u] = true;}
      else
        {continue;}

     //check all edges
      for(int i=0; i < edges_num ; i++)
      { 
	       //check the edges that are from or start from node u
           if(d_edges[i].node1 == u && picked.find(i)->second == false )
           {             
             node = d_edges[i].node2; //node it that gets the weight
			 
             // check node weight and make sure it is the smallest possible value
             if(final.find(node)->second > d_edges[i].weight + final.find(u)->second)
 		     {
	           if(counter < k){
                    final[node] = d_edges[i].weight + final.find(u)->second;
                    Q.push(pp(node, final.find(node)->second));
	            }
             }
           }
      }
	  counter++; //increment the distance from the source
   }
}//end of directed
void ud_Dijkstra(directed ud_edges[], int edges_num, char S, int k)
{
    priority_queue<pp, vector<pp> , Prioritize > Q;
    int counter = 0;
    char u, node,node_;
   
    final[S] = 0;
    Q.push(pp(S,0));

   while(!Q.empty())
   {
      u = Q.top().first;
      Q.pop();

     if(picked.find(u)->second == false )
      { picked[u] = true;}
      else
        {continue;}

      for(int i=0; i < edges_num ; i++)
      {
           if(ud_edges[i].node1 == u || ud_edges[i].node2 == u)
             {
                 node = ud_edges[i].node2; //node it that gets the weight
                 node_ = ud_edges[i].node1;

                 //if node2 != u and has not been used
                 if(node != u &&  picked.find(node)->second == false)
                 {
                    if(final.find(node)->second > ud_edges[i].weight + final.find(u)->second)
                    {
					  if(counter < k){
                        final[node] = ud_edges[i].weight + final.find(u)->second;;
                        Q.push(pp(node, final.find(node)->second));
					  }
                    }//end if
                 }//end if
                 
                   //if node1 != u and has not been used
                 if(node_ != u &&  picked.find(node_)->second == false)
                 {
                    if(final.find(node_)->second >ud_edges[i].weight + final.find(u)->second)
                    {
					  if(counter < k){
                        final[node_] = ud_edges[i].weight + final.find(u)->second;;
                        Q.push(pp(node_, final.find(node_)->second));
                      }
					}//end if
                 }//end if
                         
              }//end if
        }//end for
		counter++;
      }//end while

}//end of undirected 
