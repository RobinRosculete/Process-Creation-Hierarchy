#include <stdio.h>
#include <stdlib.h>
enum menuOptions { DEFAULT, ENTER_PARAMATERS, CREATE_CHILD, DESTROY_DESCENDENTS, QUIT }; // Used for optionMenu

typedef struct node1
{
  int process;
  struct node1 *link;

} LinkedList;

typedef struct node2
{
  int parent;
  LinkedList *children;
} PCB;

void printOptionMenu (int *optionNum);
void numOfProcesses (PCB ** PCB_ARRAY, int *length, int*countProcceses);    // Procedure for option #1
void createNewChild (PCB ** PCB_ARRAY, int length, int *countProcceses);    //Procedure for option #2
void listAppend(LinkedList ** head, int index_Q);
void printHierarchy (PCB PCB_ARRAY[], int length);    // Procedure to Print Hierarchy of Processes
void destroyDesendants(PCB ** PCB_ARRAY ,int length, int *countProcceses); //Procedure option #3
void destroyChildrenProcesses(PCB * PCB_ARRAY, LinkedList * head, int *countProcceses );//Helper function fot option #3
void freeAndQuit(PCB ** PCB_ARRAY, int* countProcesses); // Procedure for option #4

// ****MAIN****
int main (void)
{
  int optionNum = 0;
  PCB *PCB_ARRAY = NULL;
  int length = 0;
  int countProcceses = 1; //Used to keep track of number of PCB's

  do
    {
      printOptionMenu (&optionNum);

 switch (optionNum)
    {
    case ENTER_PARAMATERS:
      printf ("Enter selection: %d\n", ENTER_PARAMATERS);
      numOfProcesses (&PCB_ARRAY, &length, &countProcceses);
      break;

    case CREATE_CHILD:
      printf ("Enter selection: %d\n", CREATE_CHILD);
      createNewChild (&PCB_ARRAY, length, &countProcceses);
      break;

    case DESTROY_DESCENDENTS:
      printf ("Enter selection: %d\n", DESTROY_DESCENDENTS);
      destroyDesendants(&PCB_ARRAY, length, &countProcceses);
      break;

    case QUIT:
      printf ("Enter selection: %d\n", QUIT);
      freeAndQuit(&PCB_ARRAY, &countProcceses);
      printf ("Quitting program...\n");
      break;
            
    default:
      break;
    }

    } while (optionNum != QUIT);

  return 1;
}                // *****MAIN******


//Function purpose to print optionMenu and return the optionNumber given by the user
void printOptionMenu (int *optionNum)
{

  int numRead = 0;        //Used for error checking user input;


  printf
    ("\nProcess creation and destruction\n--------------------------------\n");

  printf
    (" %d)Enter parameters\n %d)Create a new child process\n %d)Destroy all descendants of a process\n %d)Quit program and free memory \n",
     ENTER_PARAMATERS, CREATE_CHILD, DESTROY_DESCENDENTS, QUIT);

  numRead = scanf ("%d", &*optionNum);

  while (numRead != 1 || *optionNum <= 0 || *optionNum > QUIT)
    {
      printf ("Invalid input, please enter an option bellow\n");

      printf
    (" %d)Enter parameters\n %d)Create a new child process\n %d)Destroy all descendants of a process\n %d)Quit program and free memory \n",
     ENTER_PARAMATERS, CREATE_CHILD, DESTROY_DESCENDENTS, QUIT);

      scanf ("%*[^\n]");

      numRead = scanf ("%d", &*optionNum);
    }


}//end printOptionMenu(char * optionNum)

//Function purpose: To allocate an Array of PCB's of szie length and return it
void numOfProcesses (PCB ** PCB_ARRAY, int *length, int*countProcceses)
{
  int numRead = 0;        //Used for error checking user input;
  *countProcceses = 1;
    
  printf ("Enter maximum number of processes: ");
  numRead = scanf ("%d", &*length);

  while (numRead != 1 || *length <= 0)
    {
      printf ("Invalid input, please enter a positive integer: \n");
      scanf ("%*[^\n]");
      numRead = scanf ("%d", &*length);
    }

  *PCB_ARRAY = (PCB *) malloc (*length * sizeof (PCB));

  if (*PCB_ARRAY == NULL)
    {
      printf ("Warning memory for PCB[] not allocated!\n");
      exit (1);
    }

  (*PCB_ARRAY)[0].parent = 0;
  (*PCB_ARRAY)[0].children = NULL;

  for (int i = 1; i < *length; ++i)
    {
      (*PCB_ARRAY)[i].parent = -1;
      (*PCB_ARRAY)[i].children = NULL;
    }

}//End numOfProcesses()

//Function purpose: Print the hierarchy of processes
void printHierarchy (PCB PCB_ARRAY[], int length)
{
    LinkedList *next = NULL;
    
if(PCB_ARRAY != NULL){
  for (int i = 0; i < length; ++i)
    {
      if ((PCB_ARRAY[i].parent != -1) && (PCB_ARRAY[i].children != NULL))
      {
            printf ("PCB[%d] is the parent of: ", i);
            next = PCB_ARRAY[i].children;
            while (next != NULL)
              {
                printf ("PCB[%d] ", next->process);
                next = next->link;
              }
             
            printf ("\n");
       }
   }
        
  }//End if(PCB_ARRAY != NULL)
    
}//end Function printHierarchy(...)

//Function purpose: To create a new Child process given a parent process index
void createNewChild (PCB ** PCB_ARRAY, int length, int *countProcceses)
{
      // define local vars
      int numRead = 0;        //Used for input error checking
      int index_Q = 0;
      int index_P = 0;        //Used to hold the value of the parent Index
      LinkedList * newLink = NULL;
      LinkedList * next = NULL;
      
  if (*countProcceses >= length)
    {
      printf("Maximum # of processes has been reached, unable to create new child\n\nCurrent processes are:\n");
    }
  else
    {
      
      //prompting for parent process index p
      printf ("Enter the parent process index: ");
      numRead = scanf ("%d", &index_P);

      //input Error checking
while (index_P < 0 || numRead != 1 || index_P >= length|| index_P >= *countProcceses)
    {
      printf("Invalid input, please enter a positive integer less than %d: \n", *countProcceses);
      scanf ("%*[^\n]");
      numRead = scanf ("%d", &index_P);
    }
    
      //searching for first available index q without a parent in a while loop
      while ((*PCB_ARRAY)[index_Q].parent != -1 && index_Q < (length - 1))
    {
      ++index_Q;
    }

      //allocateing memory for new child process, initilize fields
      (*PCB_ARRAY)[index_Q].children = (LinkedList *) malloc (sizeof(LinkedList));
      (*PCB_ARRAY)[index_Q].children = NULL;
      (*PCB_ARRAY)[index_Q].parent = -1;
        
      (*PCB_ARRAY)[index_Q].parent = index_P;
      (*PCB_ARRAY)[index_Q].children = NULL;
        
      newLink =(LinkedList *) malloc (sizeof(LinkedList));
      newLink->process = index_Q;
      newLink-> link = NULL;

      next= (*PCB_ARRAY)[index_P].children;
     
    if((*PCB_ARRAY)[index_P].children == NULL)
    {
        (*PCB_ARRAY)[index_P].children = newLink;
    }
     else{
         while(next->link!=NULL){
             next = next->link;
             
         }
           next->link= newLink;
     }
        (*countProcceses)++;
}//End else
    
  
  //printing current hierachy of processes
  printHierarchy (*PCB_ARRAY, length);
    
}//End function createNewChild()


//Function purpose: To destroy all desendents given
void destroyDesendants(PCB ** PCB_ARRAY ,int length, int *countProcceses)
{
int numRead = 0;
int index_P = 0;

      printf ("Enter the parent process index: ");
      numRead = scanf ("%d", &index_P);

      //input Error checking
      while (index_P < 0 || numRead != 1 || index_P >= *countProcceses)
    {
      printf
        ("Invalid input, please enter a positive integer less than %d: \n",
         *countProcceses);
      scanf ("%*[^\n]");
      numRead = scanf ("%d", &index_P);
    }

    destroyChildrenProcesses(*PCB_ARRAY, (*PCB_ARRAY)[index_P].children, countProcceses);
    (*PCB_ARRAY)[index_P].children = NULL;
 
    printf("Current Hierarchy: \n");
    printHierarchy (*PCB_ARRAY, length);
    
}//End Function destroyDesendants(...)


//Function purpose: To recursivelly destroy all descendents
void destroyChildrenProcesses(PCB * PCB_ARRAY, LinkedList * head, int *countProcceses )
{
 int index_Q = 0;
    
 if(head ==NULL)
 {
     return;
 }
 else{
     destroyChildrenProcesses(PCB_ARRAY, head->link, countProcceses);
     index_Q= head->process;
     destroyChildrenProcesses(PCB_ARRAY, PCB_ARRAY[index_Q].children, countProcceses);
     free(head);
     (*countProcceses)--;
     PCB_ARRAY[index_Q].parent =-1;
     head= NULL;
    }
    
}//End fucntion destroyChildrenProcesses(...)


//Function purpose:Free all allocated memory before program terminates
void freeAndQuit(PCB ** PCB_ARRAY, int* countProcesses)
{
    if((*PCB_ARRAY) != NULL)
    {
        if((*PCB_ARRAY)[0].children !=NULL){
            destroyChildrenProcesses(*PCB_ARRAY, (*PCB_ARRAY)[0].children, countProcesses);
        }
        free(*PCB_ARRAY);
        *PCB_ARRAY = NULL;
      }
    
}//end function freeAndQuit(...)
