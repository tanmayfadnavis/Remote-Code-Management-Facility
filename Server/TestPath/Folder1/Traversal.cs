using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Graphs
{
   public class Node
    {
       public int data;
       public bool visited;
       public List<Node> adj=new List<Node>();
    }

    
   public class Graph
    {
       Node makeVertex(int data)
       {
           Node v = new Node();
           v.visited = false;
           v.data = data;
           return v;
       }

       //For undirected graphs.
       void addEdge(Node v,Node w)
       {
           v.adj.Add(w);
           w.adj.Add(v);
       }
        void DFS(Node v)
        {
            v.visited = true;
            Console.WriteLine("The node visited is {0}", v.data);
            IEnumerable<Node> ienum = v.adj;
            foreach(Node w in ienum)
            {
                if (!w.visited)
                    DFS(w);
            }
        }

       //Function to do a BFS search.

       void BFS(Node v)
        {
            v.visited = true;
            Queue q = new Queue();
            q.Enqueue(v);
            while(!(q.Count==0))
            {
                Node temp =(Node) q.Dequeue();
                Console.WriteLine("The node visited is {0}", temp.data);
                foreach(Node x in temp.adj)
                {
                    if(x.visited==false)
                    {
                        x.visited = true;
                        q.Enqueue(x);
                    }
                }
            }

        }

        static void Main(string[] args)
        {
            //Make a graph of 6 nodes.

            Graph g = new Graph();
            Node one=g.makeVertex(1);
            Node two= g.makeVertex(2);
            Node three=g.makeVertex(3);
            Node four=g.makeVertex(4);
            Node five=g.makeVertex(5);
            Node six=g.makeVertex(6);

            g.addEdge(one, two);
            g.addEdge(one, three);
            g.addEdge(three, six);
            g.addEdge(two, four);
            g.addEdge(four, five);


            Graph t = new Graph();
            t.BFS(two);

            Console.Read();
        }
    }
}
