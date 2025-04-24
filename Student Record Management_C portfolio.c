#include<stdio.h>    //this is a standard I/O function that is a must in all C programmin language as this allows printf and scanf to work

struct Student{ //creating a structure call student that will be used throughouT the program
	
	int id;   //declaring an integer for ID which will be unique and will be use later for searching and deleting data in the files.
	char name[50];   //declaring a string of 50 charaters for the user to enter their name
	float marks, GPA;  //decalring a floating point value so that the user can enter their marks and GPA
	
};

//creating a function to enter the required student data into the file that we will create
void StudentData(){
	
	struct Student s;
	
	FILE *fp = fopen("students.txt", "a");  //creating and opening a file name students and using the append mode which is one of three modes in file handling 
	if(fp == NULL){                         //this if statement is to display only if there is an error opening the file in which case there will return
		
		printf("There was an error opening the file! Try again.");
		return;
	}
	
	printf("Enter ID: ");                            //get the user to enter an number and store it into the structure
	scanf("%d", &s.id);
	
	printf("Enter name(only first name is needed):  ");   //get the user to enter their first name and store it into the structure
	scanf("%s", &s.name);
	
	printf("Enter marks(in two decimal point): ");         //get the user to enter their marks in two decimal point and store it into the structure
	scanf("%f", &s.marks);
	
	printf("Enter GPA(in two decimal point): ");           // get the user to enter thei GPA in two decimal points and store it into the structure
	scanf("%f", &s.GPA);
	
	//now we will want to write to the file without quotes ""
	fprintf(fp, "%d %s %.2f %.2f\n", s.id, s.name, s.marks, s.GPA);
	
	fclose(fp);                       // always close the file once being used to not cause buffer in the file
	printf("Data has been recorded succesfully!\n");         //display to the user that the data has been recorded into the file
	
}

	//function to view and search student based on ID
	void AddStudent(int searchid){
		
		struct Student s;
		
		FILE *fp = fopen("students.txt", "r");  // open the file like above but this time in read mode
		if(fp == NULL){
			
			printf("There was an error opening the file! Try again.");
			return ;
		}
		
		int found = 0;
		
		printf("\n%-10s %-30s %-10s %-10s\n", "ID", "name", "marks", "GPA");             /* what this two printf statement does is that it print out the data from the file */
		printf("-------------------------------------------------------------------\n");
		
		//this while loop that has a nested if statement inside is to read and display out the data from the file if there is a same
		while(fscanf(fp, "%d %s %f %f", &s.id, s.name, &s.marks, &s.GPA)==4)
		{
			if(searchid == -1|| s.id==searchid){
				
				printf("%-10d %-30s %-10.2f %-10.2f\n", s.id, s.name, s.marks, s.GPA );
				found =1;
			}
		}
		
		fclose(fp);    //as the above function, close the file one use is complete
		
		if(searchid != -1  && !found){
			
			printf("Student with ID %d could not be found.\n", searchid);
		}
		
	}
	
	//this function is to delete the data in the file using ID
	void deleteStudent(){

int DelID, found = 0;                //declare two integer varible to delete the data and set the found counter to 0 so it does not cause any error
		
		struct Student s;
		
		FILE *fp = fopen("students.txt", "r"); //this two lines are to open the original file in read mode but we will also be opening a new file
		FILE *temp = fopen("temp.txt", "w");  
		
		//this if statement is the same as before to tell the user that there is a problem opning the file but this time we are including the new file we have created just for this function
		if(fp == NULL || temp == NULL){
			
			printf("There was an error opening the file! Try again.");
			return ;
		}
		
		//ask the user which ID they would like to delete
		printf("Enter an ID to delete: ");
		scanf("%d", &DelID);
		
		while(fscanf(fp, "%d %s %f %f", &s.id, s.name, &s.marks, &s.GPA)==4){
			
			if(s.id == DelID){
				
				found = 1;
			}else{
				
				fprintf(temp, "%d %s %.2f %.2f\n",s.id, s.name, s.marks, s.GPA );
			}
		}
		
		fclose(fp);
		fclose(temp);
		
	     remove("students.txt");
	     rename("temp.txt", "students.txt");
		
		if(found){
			
			printf("Data has been deleted succecfully deleted.\n");
		}else{
			
			printf("The student ID could not be found.\n");
		}
	}		

	
	
	
	
	
	


//main function the most essential and important  function in the C Language 
int main(){

int choice; //Declaring an integer variable to capture the user's choice

//when the program runs, below is what the user will see first
do{
	
	printf("----Student Management Record System----\n");
	printf("1. Add Student\n");
	printf("2. Search/View student\n");
	printf("3. Delete Student\n");
	printf("4. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	
	switch(choice){
		
		case 1: StudentData(); break;
		
		case 2: {
			
		   	int IDChoice;
		   	printf("Enter an ID to search a student(or -1 to view all): ");
		   	scanf("%d", &IDChoice);
		   	AddStudent(IDChoice);
			break;
	}
				
		case 3: deleteStudent(); break;
		
		case 4: printf("Exiting...\n"); break;
		
		default: printf("Invalid Choice! Try again..\n");
	}
}while(choice !=4);


return 0;


}
