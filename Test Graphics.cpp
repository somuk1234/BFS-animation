#include<graphics.h>
#include<dos.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
   initwindow(600,600); //initialise a graphics window of size 600 x 600
   rectangle(20,20,580,580); //grid boundry
   int n;
   cout<<"Enter Number Of Row or Column of n x n grid(between 2 to 20) : ";
   cin>>n;
   int gap=560/n;
   for(int i=1;i<n;i++){
   	line(20,20+(gap*i),580,20+(gap*i));
   	line(20+(gap*i),20,20+(gap*i),580);
   }
int base_x=(20+gap)/2;
int base_y=(20+gap)/2;
int s_x,s_y;
cout<<"Enter The Source Coordinate as X Y :";
cin>>s_x>>s_y;
int source_x=(base_x)+(gap*s_x);
int source_y=(base_y)+(gap*s_y);
setfillstyle(1,2);                    //pattern for highlighting source 
floodfill(source_x,source_y,15);       //with green color 
int d_x,d_y;
cout<<"Enter The Destination Coordinate as X Y :";
cin>>d_x>>d_y;
int destination_x=(base_x)+(gap*d_x);  
int destination_y=(base_y)+(gap*d_y);   
setfillstyle(1,2);                       //pattern for highlighting destination 
floodfill(destination_x,destination_y,15);//with green color
int num_enemy;
cout<<"Enter Number Of Enemy : ";
cin>>num_enemy;
//pair<int,int> p[n];
map<pair<int,int> ,bool>enemy;
cout<<"Enter the coordinates of Enemies :"<<endl;
for(int i=0;i<num_enemy;i++){
	int a, b;
	cin>>a>>b;
	//p[i].first=a;
	//p[i].second=b;
	enemy[make_pair(a,b)]=true;
	setfillstyle(1,4);                         //pattern for highlighting enemies 
   floodfill((base_x+gap*a),(base_y+gap*b),15); //with red color
}  
//////////////////////////  BFS  to find shortest distance  ////////////////////////////////////////
  int arr[5]={1,0,-1,0,1};
  map < pair<int,int> , bool> visited;
  map<pair<int ,int> ,pair<int ,int> >parent;
  map<pair<int,int>, int>distance;
  queue<pair<int,int> > q; 
  q.push(make_pair(s_x,s_y));
  visited[make_pair(s_x,s_y)]=true;
  distance[make_pair(s_x,s_y)]=0;
  int flag=0;
  while(!q.empty()){
    pair<int,int> a=q.front();
    q.pop();
    if(a.first==d_x&&a.second==d_y){
    	flag=1;
      break;
    }
    for(int i=0;i<4;i++){
      int x=a.first+arr[i];
      int y=a.second+arr[i+1];
      if((x<=n-1&&x>=0)&&(y<=n-1&&y>=0)){
      if(!visited[make_pair(x,y)]){
      	if(!enemy[make_pair(x,y)]){
        visited[make_pair(x,y)]=true;
        q.push(make_pair(x,y));
        parent[make_pair(x,y)]=make_pair(a.first,a.second);
        distance[make_pair(x,y)]=1+distance[make_pair(a.first,a.second)];
             }
      }
    }
    }
  }
  if(flag){
  cout<<"Shortest distance is : ";
  cout<<distance[make_pair(d_x,d_y)]<<" unit"<<endl;
   ///////////////////// getting path in stack (S) by iterating through parent list ///////////////////////
  stack<pair<int,int> >s;
  pair<int,int>destination;
  destination.first=d_x;
  destination.second=d_y;
  s.push(make_pair(d_x,d_y));
  while(destination.first!=s_x||destination.second!=s_y){
pair<int,int> p=parent[make_pair(destination.first,destination.second)];
destination.first=p.first;
destination.second=p.second;
s.push(make_pair(p.first,p.second));
  }
 ///////////////// Animating the shortest Path wiht line segment ///////////////////////////////////////// 
  pair<int,int >it;
  it.first=s.top().first;
  it.second=s.top().second;
  s.pop();
  setcolor(2);
    while(!s.empty()){
    pair<int,int>p=s.top();
    s.pop();
    line((base_x+gap*it.first),(base_y+gap*it.second),(base_x+gap*p.first),(base_y+gap*p.second));
    it.first=p.first;
    it.second=p.second;
    delay(500);
  }
}
else cout<<" Sorry! No Path Exist between given points.";
   getch();
   closegraph();
   return 0;
}
