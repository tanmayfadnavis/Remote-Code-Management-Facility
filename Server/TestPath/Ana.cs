using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Anagram2
{
    class Ana
    {
        
        //Function to find whether two strings are an anagram.

      void removeDup(char[] array)
        {

            int numDups = 0, prevIndex = 0;

            for (int i = 0; i < array.Length; i++)
            {
                bool foundDup = false;
                for (int j = 0; j < i; j++)
                {
                    if (array[i] == array[j])
                    {
                        foundDup = true;
                        numDups++; // Increment means Count for Duplicate found in array.
                        break;
                    }
                }

                if (foundDup == false)
                {
                    array[prevIndex] = array[i];
                    prevIndex++;
                }
            }

            // Just Duplicate records replce by zero.
            for (int k = 1; k <= numDups; k++)
            {
                array[array.Length - k] = '\0';
            }

            foreach (var x in array)
                Console.WriteLine(x);

        }


        //Function to reverse words in a string.

        string reverseWords(string input)
      {
          char[] inp = input.ToCharArray();
          int temp = 0;
          int s = 0;

            for(;temp<=inp.Length;temp++)
            {
                
                if(temp==inp.Length)
                {
                    reverse(inp, s, temp-1);
                }
                else if(inp[temp]==' ')
                {
                    reverse(inp, s, temp);
                    s = temp + 1;
                }

            }

            reverse(inp, 0, temp - 2);

            string output = new string(inp);
            return output;
      }

 

        void reverse(char[] s,int beg,int end)
        {
            //char[] arr = s.ToCharArray();
            for (int i = beg, j = end; i < j; i++, j--)
            {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }

        }


        //Function to find whether two strings are anagrams of each other.
        bool findAnagram(string s1,string s2)
        {

            char[] arra1 = s1.ToCharArray();
            char[] arra2 = s2.ToCharArray();

            Dictionary<char, int> temp = new Dictionary<char, int>();

            for(int i=0;i<arra1.Length;i++)
            {
                if (temp.ContainsKey(arra1[i]))
                    temp[arra1[i]] += 1;
                else
                    temp[arra1[i]] = 1;

            }

            for(int i=0;i<arra2.Length;i++)
            {
                if (!(temp.ContainsKey(arra2[i])))
                    return false;
                else
                    temp[arra2[i]] -= 1;
            }

            foreach (var i in temp)
            {
                if (i.Value != 0)
                    return false;
            }

            return true;


        }


        static void Main(string[] args)
        {
            Ana a=new Ana();
            string s1 = "abc234";
            string s2 = "23bcx4";

            if (a.findAnagram(s1, s2))
                Console.WriteLine("is anagram");
            else
                Console.WriteLine("not");

            char[] test = { 'a', 'b', 'c', 'b', 'e', 'a' };

            

            a.removeDup(test);

            foreach (var x in test)
                Console.WriteLine(x);

            String s = "hello tanmay hopefully works";

            string o = a.reverseWords(s);

            Console.WriteLine("Reverse is {0}", o);
            

            Console.Read();
        }

    }
}
