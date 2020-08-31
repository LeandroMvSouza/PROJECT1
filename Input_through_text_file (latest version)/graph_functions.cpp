#include "header.h"

void Graph::addEdge(casa node1, casa node2)
{
	string key = node1.pos;
	vector<casa> to_add = adjList[key];
	to_add.push_back(node2);
	adjList[key] = to_add;
}

void Graph::bfs(casa src,casa desired)
{	
	
	int added;
	int current = 0;
	int next = 0;
		
    queue<casa> q;
    map<string, bool> visited;
    q.push(src);
    visited[src.pos] = true;
    
	vector<casa> temporary;
	temporary.push_back(src);
    Graph::layers_set.push_back(temporary);
    
    temporary.clear();
    
    while(!q.empty())
    {
    	if(current==0)
		{
			added = 0;
        	casa node = q.front();
        	q.pop();
        	for(auto i = Graph::adjList[node.pos].begin(); i != Graph::adjList[node.pos].end(); i++)
        	{
        		string aux = (*i).pos;
        		if(!visited[aux])
				{
					visited[aux]=true;
					q.push(*i);
					temporary.push_back(*i);
					added+=1;
					if((*i).pos == desired.pos)
					{
						Graph::can_win = true;
					}
				}
			}
			next += added;
			current = next - 1;
			next = 0;
			
			Graph::layers_set.push_back(temporary);
			
			if(Graph::can_win){
				Graph::turns_it_takes_to_win = Graph::layers_set.size() - 1;
    			break;
			}
			temporary.clear();
		}
		else if(current>0)
		{
			added = 0;
        	casa node = q.front();
        	q.pop();
        	for(auto i = Graph::adjList[node.pos].begin(); i != Graph::adjList[node.pos].end(); i++)
        	{
        		string aux = (*i).pos;
        		if(!visited[aux])
				{
					visited[aux]=true;
					q.push(*i);
					temporary.push_back(*i);
					added+=1;
					if((*i).pos == desired.pos)
					{
						Graph::can_win = true;
					}
				}
			}
			next+=added;
			current-=1;
		}
    }
}
