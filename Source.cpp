#include <iomanip>
#include <iostream>
#include <fstream>
#include<vector>
#include<string>
#include<queue>
using namespace std;
int hashFunction(int nodeID)
{
	return nodeID % 10000;
}
struct Node {
	int id;
	string url;
	Node(vector<string>& data) {
		id = stoi(data[1]);
		url = data[2];
	}
	Node()
	{
		id = -1;
		url = "Empty";
	}
};
Node bfs(vector<vector<Node*>>* adjList, string url) // arbitrary thing
{
	vector<vector<int>> visited(10000);
	visited.at(hashFunction(adjList->at(0).at(0)->id)).push_back(adjList->at(0).at(0)->id);
	queue<Node> q;
	q.push(*adjList->at(0).at(0));
	string currURL;
	
	int count = 0;
	while (!q.empty())
	{
		Node currNode = q.front(); // 63002-base // 63002	92769
		q.pop();
		currURL = currNode.url; // www.awn.com
		count++;
		//evaluation of current Node
		//if not equal
		if (currURL.compare(url) != 0)
		{
			bool isVisited = false;
			for (int i = 0; i < adjList->at(currNode.id).size(); i++)
			{
				Node* temp = adjList->at(currNode.id).at(i); // 92769
				for (int j = 0; j < visited.at(hashFunction(temp->id)).size(); j++)
				{
					if (temp->id == visited.at(hashFunction(temp->id)).at(j))
					{
						isVisited = true;
						break;
					}
				}
				//add to queue considering it has NOT been visited
				if (!isVisited)
				{
					visited.at(hashFunction(temp->id)).push_back(temp->id);
					q.push(*temp);
				}
			}
		}
		else if ((currURL.compare(url) == 0))
		{
			Node temp = currNode;
			return temp;
		}
	}
	Node temp;
	return temp;
}

//function prototype
void splitString(char delimiter, string  str, vector<string>& values);
vector<vector<Node*>>* createAdjList();

int main()
{
	vector<vector<Node*>>* adjList = createAdjList();
	Node foundNode = bfs(adjList, "http://animegirlky.tripod.com/animegirlky/");
	cout << "Node Id: " << foundNode.id << " Node url: " << foundNode.url << endl;
	return 0;
}


vector<vector<Node*>>* createAdjList()
{
	ifstream file("URL.csv");

	vector<vector<Node*>>* adjList = new vector<vector<Node*>>(100000);
	string input = "";
	vector<string> data;
	//switch based on option, read in file information
	if (file.is_open())
	{
		//while (getline(file1, input) && debug) //while there are still lines in the file to read... store the line in input string and proceed...
		while (getline(file, input))
		{
			splitString(',', input, data);
			if (stoi(data[0]) != stoi(data[1])) {
				Node* temp = new Node(data);
				adjList->at(stoi(data[0]) % 100000).push_back(temp);
			}
			data.clear();
		}
	}
	return adjList;
}//end of function

void splitString(char delimiter, string  str, vector<string>& values)
{
	string token;
	long unsigned int start = 0;
	long unsigned int end = 0;
	long unsigned int length = 0;

	while (end <= str.length())
	{
		end = str.find(delimiter, start);
		length = end - start;
		token = str.substr(start, length);
		start = end + 1;

		values.push_back(token);

		//debug
		//cout << token << endl;
	}

}//end of function