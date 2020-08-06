/*
Syed Ali
COSC514 Project 2 
LRU (Least Recently Used (LRU) Page Replacement algorithm)
Assignment Due August 2nd, 2020
*/

#include<stdio.h>

int main()
{
  int seq[1000], mem[100];                                                           // Allocation of memory for frames and pages
  int n, frame, flag, i, j, k,l,temp, pf, c;
  printf("Enter the number of frames: ");                                            // Allowing the user to enter the number of pages, frames, and the reference string
  scanf("%d", &frame);
  printf("Enter the number of pages: ");
  scanf("%d",&n);
  printf("Enter the reference string: ");

  for(i = 0; i < n; i++)                                                             // for the size of the pages provided scan through the list
    {
      scanf("%d", &seq[i]);
    }
  printf("\n");

  pf = 0;                                                                           // initialzing variables hits and page faults
  c = 0;

  for(i = 0; i < n; i++)                                                            // for the size of the pages 
    {
      flag = 0;                                                                     // set the flag to 0
      for(j = 0; j < c; j++)                                                        // if j is less than the count
	{
	  if (mem[j] == seq[i])                                                         // then set the mem of j to the seq
	    {
	      flag = 1;                                                                 // set the flag to 1
	      break;
	    }
	}
      if(flag == 1)                                                                 // if the flag is 1
	{
	  if(j < c - 1)                                                                 // and if j is less than count - 1
	    {
	      for(k = j; k < c - 1; k++)                                                // for k equal j where k is less than count - 1 
		mem[k] = mem[k + 1];                                                        // then set mem to k and increment k
	    }
	}
      else
	{
	  pf++;                                                                         // else find the page faults
	  if ( c < frame)                                                               // if count is less than the frame then increment count
	    c++;
	  else
	    {
	      for(k = 0; k < c - 1; k++)                                                // else for k which is set count - 1
		mem[k] = mem[k + 1];                                                        // then set mem to k and increment k
	    }
	}
      mem[c - 1] = seq[i];                                                         // set the mem count - 1 to seq of i
    }

  printf("Total Page Faults = %d\n", pf);                                         // print the number of page faults 
  printf("Total Page Hits = %d\n", (n-pf));                                       // print the number of hits
printf("\n");
  return 0;
}
  
