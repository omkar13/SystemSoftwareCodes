#include <stdio.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>
// beautiful example of using forking.
// the data space of each process is different and hence only 3 variables are sufficient to store the traversal id,left_child_pid and right_chil// d_pid for all the processes

int main(){

	int l=0,h=2, traversal_id_parent=1,left_child_pid,right_child_pid ;

	printf("[1] pid %d , ppid %d\n", getpid(),getppid());

	while(l<h){

		if((left_child_pid = fork())==0){ 				//left child

			int j;

			for(j=1;j<=l+1;j++){
				printf(" ");
			}
			
			printf("[%d] pid %d , ppid %d\n",traversal_id_parent*2 , getpid(),getppid());
			l++;
			traversal_id_parent = traversal_id_parent *2;
			continue;					//now this child will become parent
		}

		else{
			int j;
			for(j=1;j<=l;j++){
				printf(" ");
			}
			printf("[%d] pid %d created left child with pid %d\n",traversal_id_parent, getpid(), left_child_pid);

			if((right_child_pid = fork())==0){ 					//create right child
					
				int j;
				for(j=1;j<=l+1;j++){
					printf(" ");
				}
				printf("[%d] pid %d , ppid %d\n",traversal_id_parent*2 + 1 , getpid(),getppid());

				l++;
				traversal_id_parent = traversal_id_parent *2 + 1 ;
				continue;      					//now this child will become parent 

			}
			else{//right child has been created. print it
				int j;

				for(j=1;j<=l;j++){
					printf(" ");
				}	
				printf("[%d] pid %d created right child with pid %d\n",traversal_id_parent, getpid(),right_child_pid);

				int left_status,right_status;
				//I HAVE HAD ENOUGH CHILDREN ...NOW LETS WAIT FOR THEM TO DIE . SO SAYS THE PARENT

				waitpid(right_child_pid ,&right_status,0);
				if(WIFEXITED(right_status))
				{int j;
					for(j=1;j<=l;j++){
						printf(" ");
					}

					printf("[%d] right child %d of %d exited with status %d\n" , traversal_id_parent,right_child_pid,getpid(),WEXITSTATUS(right_status));
				}

				waitpid(left_child_pid ,&left_status,0);
				if(WIFEXITED(left_status))
				{int j;
					for(j=1;j<=l;j++){
						printf(" ");
					}

					printf("[%d] left child %d of %d exited with status %d\n" , traversal_id_parent,left_child_pid,getpid(),WEXITSTATUS(left_status));}
				

			exit(traversal_id_parent);			//all non leaf nodes exit here

				break; //breaks out of the while loop
			}


		}

		l++;
	}

	//now dont create any children we have reached the end.just give exit status
	exit(traversal_id_parent);		//all leaf nodes exit from here

}
