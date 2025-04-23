#include<stdio.h> //this is a standard I/O library for function like printf, scanf and among others to work. It is a must for every C language to have this at the first line.

//creating a structure to store the student data such as name, ID & Marks.
struct Student{
	
	int id;          // a unique student ID where one student has one unique ID where  other sudents cant have the same.
	char name[50];  // the student name will be stored into here which has a space for 50 characters
	float marks;   // when student enter their marks, it will be stored into here. 
	
	
};

//creating a function to add whatever that is stored into the structure above to be added into a file
void addStudent(){

	struct Student s; // creating a  Student structure instance	
	
	FILE *fp = fopen("student.txt", "a"); // opening the file in append mode(threr are three which are read(r) whee it only exist for reading, write(w)where if the file exist, the content will be discarded and the file is treated as new, append(a)where if the file exist new data is written to the end of the file)
	
	if(fp == NULL){                       // this simple if statement is to chck if the file can be open, if cant, the printf statement will be display out to the user
		
		printf("Error Opening the file!\n");
		return;
		
	}
	
	//now we will get the student data and store it into the structure we have created
	printf("Enter student ID: ");                    //get the student to give an ID in INTEGER form and we store it into the structure
	scanf("%d", &s.id);
	
    printf("Enter Student Name: ");                 //get the student name
    scanf("%s", &s.name);
    
    printf("Enter Marks: ");
    scanf("%f", &s.marks);                          //get the student marks
    
    //write the given data to the file created
    fprintf(fp, "%d \"%s\" %.2f\n", s.id, s.name, s.marks);

    
    //once append the file we must always close it
    fclose(fp);
    printf("All data has been recorded successfully!\n");  //let the user know the data has been recorded into the file without any errors
    
	
}

//creating a function to display whatever that is stored into the file
void viewStudents(){
	
	struct Student s;                            // creating a temporary structure to read the data
	
	FILE *fp = fopen("student.txt", "r");        // as mentioned above there are three primarily mode to open the file and now we are gonna open it in reading mode where we can only read the data but we cannot change any data or add any data.
	
	if(fp == NULL){
		
		printf("There is no record inside the file\n");     //similar like in the addStudent function we create an IF statement but this time if there is no record found inside the file, the user will see the printf statement
		return;
		
	}
	
	// print headers
	printf("\n%-10s %-30s %-10s\n", "ID", "Name", "Marks");
	printf("---------------------------------------------------\n");
	
	//now we will ask the program to read each student from the file and print it out using a while loop

     char line[100];
	while(fgets(line, sizeof(line), fp)) {
    	if (sscanf(line, "%d \"%[^\"]\" %f", &s.id, s.name, &s.marks) == 3) {
        	printf("%-10d %-30s %-10.2f\n", s.id, s.name, s.marks);
    }
}

	   
	   fclose(fp);                  //as mentioned above close the file after using
	   
}

//this function will help to search for a student using ID
void searchStudent(){
	
	int searchID;  //declare a variable that we will use to search for the student later
    
	struct Student s;
	int found = 0;   //	this is to check if there was a record that was found
	
	FILE *fp = fopen("student.txt", "r");  //similar to the above function we will be opening the file and in read mode
    
    if(fp == NULL)
    {
    	
    	printf("There is an error trying to open the file\n");
    	return;
    	
	}
	
	 printf("Enter student ID to search: ");        //the program will now ask the user to enter the ID of the student that want to be searched
    scanf("%d", &searchID);
    
    //here we will find for the same match and display for ID the user is looking for using a while loop with two nested if statement. At the end the break statement will tell the program to stop after finding a match.
    
  char line[100]; 
		while(fgets(line, sizeof(line), fp)) {
    		if (sscanf(line, "%d \"%[^\"]\" %f", &s.id, s.name, &s.marks) == 3) {
        		if (s.id == searchID) {
            		printf("Student found:\n");
            		printf("%-10s %-30s %-10s\n", "ID", "Name", "Marks");
            		printf("%-10d %-30s %-10.2f\n", s.id, s.name, s.marks);
            		found = 1;
            		break; // stop after finding
        }
    }
}


	
	//this is statement will display if the ID that the user has entered does not match with any of the ID in the file
	if(!found){
		
		
		printf("Student with ID %d not found.\n", searchID);
		
	}
	
	fclose(fp);   //As we have done with the previous funtion, close the file once we are done
}

	
	
	//this last function is to delete a student record by ID
	
	void deleteStudent(){
		
		int DelID, found = 0;   /*declare a variable that we will use to delete for the student later
		                          check if there was a record that was found*/
		
		struct Student s;
		
		//open the file to do two things which are to read records and create a temporary file to copy non-deleted records 
		FILE *fp = fopen("student.txt", "r");
		FILE *temp = fopen("temp.txt", "w");
		
		if(fp == NULL || temp == NULL ){
			
			printf("There is an error trying to open the file!\n");
			return;
			
		}
		
		//now we will read the ID that wants to be deleted by the user
		printf("Enter student ID to delete: ");
		scanf("%d", &DelID);
		
		/* this while loop has a nested if and also an if-else loop is to copy only the non-matching student records into the temp file we have created  */
	char line[100]; 
	while(fgets(line, sizeof(line), fp)) {
    	if (sscanf(line, "%d \"%[^\"]\" %f", &s.id, s.name, &s.marks) == 3) {
        	if (s.id == DelID) {
            	found = 1; // mark as found, and don't write this to temp
        	} else {
            		fprintf(temp, "%d \"%s\" %.2f\n", s.id, s.name, s.marks);
        }
    }
}


		
		fclose(fp);            // as usual close the file
		fclose(temp);          // close the temporary file
		
		remove("student.txt");   //delete the original file
		rename("temp.txt", "student.txt");  //rename the temporary file to the original file
		
		if(found){
			
			printf("Student record deleted successfully. \n");
		}else{
			printf("The student ID is not found.\n");
		}
		
	}
	
	//main function is a must in all C programming language
int main(){
	
	int choice;   //This variable is created to store user's  menu choice
	
	//we will now do a do-while loop that has a nested switch case inside to print out the menu options and execute the function based on the user's choice
   do{
   	
   	printf("\n--- Student Record Management System ---\n");
   	printf("1. Add Student\n");
   	printf("2. View Students\n");
   	printf("3. Search Student\n");
   	printf("4. Delete Student\n");
   	printf("5. Exit\n");
   	printf("Enter your choice: ");
   	scanf("%d", &choice);
   	
   	switch(choice){
   		
   		case 1: addStudent(); break;
   		case 2: viewStudents(); break;
   		case 3: searchStudent(); break;
   		case 4: deleteStudent(); break;
   		case 5: printf("Exiting...\n"); break;
   		default: printf("Invalid choice! Try again. \n"); break;
   		
	   }
   	
   } while( choice != 5);    //this is to tell the program to end the loop if the user exits
	return 0; //end of program is a must in C programming language
}
