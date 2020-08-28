#include "header.h"

void Graph::addEdge(casa node1, casa node2)
{
	string key = node1.pos;
	vector<casa> to_add = adjList[key];
	to_add.push_back(node2);
	adjList[key] = to_add;
    //adjList[key].push_back(node2);
    //adjList[node2].push_back(node1);

}

void Graph::bfs(casa src,casa desired)
{	
	int count_while=0;
	int count_for=0;
	//int count_iterator=0;
	
    queue<casa> q;
    map<string, bool> visited;
    q.push(src);
    visited[src.pos] = true;
    //Graph::Layer[count_iterator].push_back(src);
    
    while(!q.empty())
    {
    	count_while+=1;
    	cout<<"---------------------------------------------------------------------------------"<<endl;
    	cout<<"While loop : "<<count_while<<endl;
        casa node = q.front();
        cout <<"Node = "<< node.pos <<endl;
        cout<<"Estamos na lista de adjacencia de "<<node.pos<<endl;
        q.pop();
        for(auto i = adjList[node.pos].begin(); i != adjList[node.pos].end(); i++)
        {
        	count_for+=1;
        	cout<<"Item "<<count_for<<" da lista = "<<*i.pos<<endl;
        	if(!visited[*i.pos])
			{
				cout<<*i.pos<<" nao foi visitado! Marcando-o como visitado e colocando-o na queue."<<endl;
				visited[**i.pos]=true;
				q.push(*i);
			}
		}
		count_for=0;
    }
    
}

