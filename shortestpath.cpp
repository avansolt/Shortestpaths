#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include <map>
#include<sstream>
#include <list>
#include <queue> 
using namespace std;

map<char, int> final;

struct directed{
  char node1;  //from
  char node2;  //to
  int weight;
  bool picked;
};

//Functions
void d_Dijkstra(directed d_edges[], int edges_num);



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
           d_edges[i].picked = false;
     cout <<d_edges[i].node1<<" " <<  d_edges[i].node2 <<  d_edges[i].weight << endl;
           i++;           }
        }

  cout << "edges: "<< edges_num << " " <<i<<endl;

        if(type== 'D')
          d_Dijkstra(d_edges,edges_num);



  return 0;
}//end main
void d_Dijkstra(directed d_edges[], int edges_num)
{


} 
