#include <cstdlib>
#include <cstdio>
#include <climits>
#include <string>
#include <vector>

using namespace std;

class Solution {
    class Node
    {
    public:
        int distToEnd = INT32_MAX;
        vector<Node*> neighbors;
    };
    inline void computeDistToEnd(Node* node, Node* start)
    {
        if (node->distToEnd + 1 >= start->distToEnd)
            return;
        for (int i = 0; i < node->neighbors.size(); i++)
            if (node->neighbors[i]->distToEnd > node->distToEnd + 1)
            {
                node->neighbors[i]->distToEnd = node->distToEnd + 1;
                if (node->neighbors[i] == start)
                    return;
                computeDistToEnd(node->neighbors[i], start);
            }   
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        /* 首先，如果endWord 不在Wordlist中，那么可以直接返回0 */
        int endIdx; // 顺便记录endword所在的位置
        bool isEndWordExist = false;
        for (endIdx = 0; endIdx < wordList.size(); endIdx++)
            if (!endWord.compare(wordList[endIdx]))
            {
                endIdx++;
                isEndWordExist = true;
                break;
            }
        if (!isEndWordExist)
            return 0;
        /* 构造图 */
        /* 以单词作为图中的节点，相邻的节点连上长度为1的边。以beginWord作为起点，endWord作为终点，算最短路径的长度就行 */
        const int graphLEN = wordList.size() + 1;
        Node graph[graphLEN];
        /* 初始化distToEnd, graph[0]为起点 */
        /* 构造neighbors */
        for (int i = 0; i < graphLEN; i++)
        {
            for (int j = i + 1; j < graphLEN; j++)
            {
                int distance = 0;
                if (i == 0)
                {
                    for (int k = 0; k < beginWord.size(); k++)
                    {
                        distance += beginWord[k] != wordList[j - 1][k];
                        if (distance > 1)
                            break;
                    }
                }
                else
                    for (int k = 0; k < wordList[i - 1].size(); k++)
                    {
                        distance += wordList[i - 1][k] != wordList[j - 1][k];
                        if (distance > 1)
                            break;
                    }
                if (distance == 1)
                {
                    graph[i].neighbors.push_back(&graph[j]); // 连接一条边
                    graph[j].neighbors.push_back(&graph[i]); // 双向连接
                }
            }
        }
        /* 初始化distToEnd */
        graph[endIdx].distToEnd = 0;
        computeDistToEnd(&graph[endIdx], &graph[0]);
        /**/
        /*
        for (int i = 0; i < graphLEN; i++)
        {
            printf("graph[%d].distToEnd=%d\r\n", i, graph[i].distToEnd);
            for (int j = 0; j < graph[i].neighbors.size(); j++)
                printf("\tgraph[%d].neighbor[%d].distToEnd=%d\r\n", i, j, graph[i].neighbors[j]->distToEnd);
        }
        */
        /* 找图 */
        int res = graph[0].distToEnd;
        if (res <= graphLEN)
            return res + 1;
        else
            return  0;
    }
};

class Solution2 {
    bool isNeighbor(const string& str1, const string& str2)
    {
        int count = 0;
        for (int i = 0; i < str1.size(); i++)
        {
            count += str1[i] != str2[i];
            if (count > 1)
                return false;
        }
        if (count == 1)
            return true;
        else
            return false;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int res = 1;
        vector<string> stack = {beginWord};
        while (!stack.empty())
        {
            for (int i = stack.size(); i > 0; --i)
            {
                string word = stack.back();
                stack.pop_back();
                vector<string>::iterator its;
                for (its = wordList.begin(); its < wordList.end(); its++)
                    if (isNeighbor(*its, word))
                        if (!(*its).compare(endWord))
                            return res + 1;
                        else
                        {
                            stack.push_back(*its);
                            wordList.erase(its);
                        }
            }
            ++res;
        }
        return 0;
    }
};

class Solution3 {
    bool isNeighbor(const string& str1, const string& str2)
    {
        int count = 0;
        for (int i = 0; i < str1.size(); i++)
        {
            count += str1[i] != str2[i];
            if (count > 1)
                return false;
        }
        if (count == 1)
            return true;
        else
            return false;
    }
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		/* 首先，如果endWord 不在Wordlist中，那么可以直接返回0 */
        int endIdx; // 顺便记录endword所在的位置
        bool isEndWordExist = false;
        for (endIdx = 0; endIdx < wordList.size(); endIdx++)
            if (!endWord.compare(wordList[endIdx]))
            {
                endIdx++;
                isEndWordExist = true;
                break;
            }
        if (!isEndWordExist)
            return 0;
		vector<string> stack = {beginWord};
		int res = 0;
		while (!stack.empty()) {
			for (int k = 0; k < stack.size(); k++) 
            {
				string word = stack.back();
				stack.pop_back();
                printf("%s\r\n", word.c_str());
				if (word == endWord)
					return res + 1;
                for (vector<string>::iterator its = wordList.begin(); its < wordList.end(); its++)
                    if (isNeighbor(*its, word))
                    {
                        stack.push_back(*its);
                        wordList.erase(its);
                    }
			}
			++res;
		}
		return 0;
	}
};