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

void d_Dijkstra(directed d_edges[], int edges_num,char S);
void ud_Dijkstra(directed ud_edges[], int edges_num, char S);


int main()
{
        char filename[20];
        
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


    stringstream ss(input);
    char hold;
    ss  >> hold;

        while(!ss.eof())     
  	{
           char node1, node2;
           int val;
           ss >> node1 >> node2 >> val;
           if(ss.eof()){break;}
           edges_num++;   
       } 
    stringstream sa(input2);

    directed d_edges[edges_num], ud_edges[edges_num]; 
    int i=0;
   char type;

     sa >> type;     

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
          
          if(final.find(node1) == final.end())
          { final[node1] = 999;
            picked[node1] = false;  }
          if(final.find(node2) == final.end())
          { final[node2] = 999;  
            picked[node2] = false;}
   

  cout <<d_edges[i].node1<<" " <<  d_edges[i].node2 <<  d_edges[i].weight << endl;
           i++;           }
        }

  cout << "edges: "<< edges_num << " " <<i<<endl;
  char S;
 
  cout<< "Please enter the source node "<<endl;
  cin >> S;

        if(type== 'D')
          d_Dijkstra(d_edges,edges_num, S);



  return 0;
}//end main
void d_Dijkstra(directed d_edges[], int edges_num, char S)
{
    priority_queue<pp, vector<pp> , Prioritize > Q;
   
    char u, node; 
   
    final[S] = 0;
    Q.push(pp(S,0));
   
   while(!Q.empty())
   {
      u = Q.top().first;
      Q.pop();

     if(picked.find(u)->second == false )
      { picked[u] = true;
       cout<<"picked: "<< u << " " << picked.find(u)->second <<endl;
      }
      else
        {continue;}


     cout<<"u: "<<u <<endl;

      for(int i=0; i < edges_num ; i++)
      { 
           if(d_edges[i].node1 == u && picked.find(i)->second == false )
             {
                 
                node = d_edges[i].node2; //node it that gets the weight
     cout<< "node2: "<<node <<endl;

                if(final.find(node)->second > d_edges[i].weight + final.find(u)->second)
 		{
		    	
                    final[node] = d_edges[i].weight + final.find(u)->second;;
                  cout <<"node2 weight: "<< final.find(node)->second<<endl;            
        
                   Q.push(pp(node, final.find(node)->second));
                   
		}

           }

      }
 
   }


  

} 
