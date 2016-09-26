using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LinkedList
{
    class Node
    {
       public int data;
       public Node next;
    }
    
    class LinkedList
    {
        public Node head;
        public void add(int data)
        {
            Node n = new Node();
            n.data = data;
            if(head==null)
            {
                head = n;
            }
            else
            {
                n.next = head;
                head = n;
            }
            

        }

        public void display()
        {
            Node cur = head;
            while (cur != null)
            {
                Console.WriteLine(cur.data);
                cur = cur.next;
            }
                
        }

        public void detectLoop(Node n)
        {
            Node slow = n;
            Node fast = n;

            while(slow!=null && fast.next !=null)
            {
                slow = slow.next;
                fast = fast.next.next;

            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            LinkedList ll = new LinkedList();
            ll.add(3);
            ll.add(34);
            ll.add(32);
            ll.display();
            Console.ReadKey();
        }
    }
}
