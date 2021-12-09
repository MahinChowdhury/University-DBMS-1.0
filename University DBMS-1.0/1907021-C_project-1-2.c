//Mahin
//1907021

#include<stdio.h>
#include<string.h>

int i,j;
int select=-1;

struct a_info{
	char name[100],pass[100];
};
struct t_info{
	char name[100],pass[100];
	int course_cnt;
	char courses[10][100]; // This 2D char array will hold all courses together in a single array
};
struct s_info{
	char name[100];
	int mark[10]; // This array will hold marks for all those courses at the same index
	int course_cnt;
	char courses[10][100]; // This 2D char array will hold all courses together in a single array
}st;

//Checking section
int admin_check(struct a_info a){
	
	FILE *fp;
	fp = fopen("admin.txt","r");
	
	struct a_info x;
	//searching in my database
	while(fread(&x,sizeof(x),1,fp)){
	
		if(strcmp(x.name,a.name) == 0 && strcmp(x.pass,a.pass)==0){
			fclose(fp);
			return 1;
		}
	}
	
	fclose(fp);
	return 0;
	
}

int teacher_check(struct t_info a){
	
	FILE *fp;
	fp = fopen("teacher.txt","r");
	
	struct t_info x;
	//searching in my database
	while(fread(&x,sizeof(x),1,fp)>0){
	
		if(strcmp(x.name,a.name) == 0 && strcmp(x.pass,a.pass)==0 ){
			fclose(fp);
			return 1;
		}
	}
	
	fclose(fp);
	return 0;
	
}

int student_check(struct s_info a){
	
	FILE *fp;
	fp = fopen("student.txt","r");
	
	struct s_info x;
	//searching in my database
	while(fread(&x,sizeof(x),1,fp)>0){
	
		if(strcmp(x.name,a.name) == 0){
			fclose(fp);
			return 1;
		}
	}
	
	fclose(fp);
	return 0;
	
}
//End of checking section
//Login section
void admin_login(){

		FILE *fp = fopen("admin.txt","w");
		struct a_info a = {
			"Mahin",
			"1907021"
			};
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		
		fflush(stdin);
		printf("Enter your username : ");
		gets(a.name);
		printf("Enter your password : ");
		gets(a.pass);
		
		int flag = admin_check(a);
		
		while(flag != 1){
			
			printf("Oops,User not found!! Please,try again!\n");
			
			fflush(stdin);
			printf("Enter your username : ");
			gets(a.name);
			printf("Enter your password : ");
			gets(a.pass);
			
			flag = admin_check(a);
		}
		
		
}

void teacher_login(){
	
	struct t_info a;
		
		fflush(stdin);
		printf("Enter your username : ");
		gets(a.name);
		printf("Enter your password : ");
		gets(a.pass);
		
		int flag = teacher_check(a);
		
		while(flag != 1){

			printf("Oops,User not found!! Please,try again!\n");
			
			fflush(stdin);
			printf("Enter your username : ");
			gets(a.name);
			printf("Enter your password : ");
			gets(a.pass);
			
			flag = teacher_check(a);
		}
	
}

void student_login(){
		
		fflush(stdin);
		printf("Enter your name : ");
		gets(st.name);
		
		int flag = student_check(st);
		
		while(flag != 1){

			printf("Oops,User not found!! Please,try again!\n");
			
			fflush(stdin);
			printf("Enter your name : ");
			gets(st.name);
			
			flag = student_check(st);
		}
		
	
}
//End of login section
//adding section
void add_teacher(){
	
	FILE *fp;
	fp = fopen("teacher.txt","a");
	
	struct t_info t;
	
	fflush(stdin);
	printf("Enter Teacher's name : ");
	gets(t.name);
	printf("Enter Teacher's password : ");
	gets(t.pass);
	printf("Enter how many courses you want to assign : ");
	scanf("%d",&t.course_cnt);
	
	for(i=0 ; i<t.course_cnt ; i++){
		printf("Enter %d'th course name : ",i+1);
		fflush(stdin);
		gets(t.courses[i]);
	}
	
	fwrite(&t,sizeof(t),1,fp);
	fclose(fp);

	printf("\nTeacher's profile created successfully.\n");
	
}

void add_student(){
	
	FILE *fp;
	fp = fopen("student.txt","a");
	
	struct s_info s;

	for(i=0 ; i<10 ; i++){
		s.mark[i] = -1;
	}
	
	fflush(stdin);
	printf("Enter Student's name : ");
	gets(s.name);
	printf("Enter how many courses you want to assign : ");
	scanf("%d",&s.course_cnt);
	
	for(i=0 ; i<s.course_cnt ; i++){
		printf("Enter %d'th course name : ",i+1);
		fflush(stdin);
		gets(s.courses[i]);
	}
	
	fwrite(&s,sizeof(s),1,fp);
	fclose(fp);

	printf("\nStudent's profile created successfully.\n");
	
}
//end of adding section
//update section

void up_teacher(){

	struct t_info x,y,tmp;
	fflush(stdin);
	printf("Enter the teacher's name you want to update : ");
	gets(y.name);
	printf("Enter teacher's password : ");
	gets(y.pass);
	
	
	FILE *tf,*tm;
	tf = fopen("teacher.txt","r");
	tm = fopen("temp.txt","a");
	
	int flag = 0;

	//Checking if that teacher's profile exist.
	while(fread(&x,sizeof(x),1,tf)){
		
		if(strcmp(x.name,y.name)==0 && strcmp(x.pass,y.pass)==0){
			flag = 1;

			tmp = x;
			printf("\nTeacher's profile found!!\n\n");
			for(i=0 ; i<x.course_cnt ; i++){
				printf("'%s' ",x.courses[i]);
			}
			printf("Courses are assigned to this teacher.\n");
			
			//If found, putting that course on that particular index position
			int pos=-1;
			while(pos==-1){

				printf("which course do you want to update: ");
				char str[100];
				fflush(stdin);
				gets(str);

				for(i=0 ; i<x.course_cnt ; i++){
					if(strcmp(x.courses[i],str)==0){
						pos = i;
						break;
					}
				}
				if(pos!=-1){
					printf("Enter new course you want to update %s with : ",x.courses[pos]);
					fflush(stdin);
					gets(tmp.courses[pos]);
					break;
				}
				else{
					printf("Course not found! Please try again.\n");
					up_teacher();
					return;
				}
			}
			
			fwrite(&tmp,sizeof(tmp),1,tm);
		}
		else fwrite(&x,sizeof(x),1,tm);
	}
	
	fclose(tf);
	fclose(tm);
	
	if(flag==0){
		printf("Teacher not found.Try again\n");
		up_teacher();
		return;
		
	}
	else{
		
		printf("\nTeacher's information updated successfully.");

		//overwriting the file using a temporary file.
		tf = fopen("teacher.txt","w");
		tm = fopen("temp.txt","r");

		while(fread(&x,sizeof(x),1,tm)){
			y = x;
			fwrite(&y,sizeof(y),1,tf);
		}
		
		fclose(tf);
		fclose(tm);
		tm = fopen("temp.txt","w");
		fclose(tm);
		
	}

}

void up_student(){
	
	struct s_info x,y,tm;
	fflush(stdin);
	printf("Enter the student's name you want to update : ");
	gets(y.name);
	
	
	FILE *sf,*sm;
	sf = fopen("student.txt","r");
	sm = fopen("temp.txt","a");
	
	int flag = 0;
	//Checking if that student's profile exist.
	while(fread(&x,sizeof(x),1,sf)){
		
		if(strcmp(x.name,y.name)==0){
			flag = 1;

			tm = x;
			printf("\nStudnt's profile found!!\n\n");
			for(i=0 ; i<x.course_cnt ; i++){
				printf("'%s' ",x.courses[i]);
			}
			printf("Courses are assigned to this student.\n");
			//If found, putting that course on that particular index position
			int pos=-1;
			while(pos==-1){

				printf("which course do you want to update: ");
				char str[100];
				fflush(stdin);
				gets(str);

				for(i=0 ; i<x.course_cnt ; i++){
					if(strcmp(x.courses[i],str)==0){
						pos = i;
						break;
					}
				}
				if(pos!=-1){
					printf("Enter new course you want to update %s with : ",x.courses[pos]);
					fflush(stdin);
					gets(tm.courses[pos]);
					break;
				}
				else{
					printf("Course not found! Please try again.\n");
					up_student();
					return;
				}
			}
			
			fwrite(&tm,sizeof(tm),1,sm);
		}
		else fwrite(&x,sizeof(x),1,sm);
	}
	
	fclose(sf);
	fclose(sm);
	
	if(flag==0){
		printf("Student not found.Try again\n");
		up_student();
		return;
		
	}
	else{
		
		printf("\nStudent's information updated successfully.");

		//overwriting the file using a temporary file.
		sf = fopen("student.txt","w");
		sm = fopen("temp.txt","r");
			
		while(fread(&x,sizeof(x),1,sm)){
			y = x;
			fwrite(&y,sizeof(y),1,sf);
		}
		
		fclose(sf);
		fclose(sm);
		sm = fopen("temp.txt","w");
		fclose(sm);
		
	}
}
//end of update section
//Course assign section

void add_t_course(){

	struct t_info x,y,tmp;
	fflush(stdin);
	printf("Enter the teacher's name you want to assign courses : ");
	gets(y.name);
	printf("Enter teacher's password : ");
	gets(y.pass);
	
	
	FILE *tf,*tm;
	tf = fopen("teacher.txt","r");
	tm = fopen("temp.txt","a");
	
	int flag = 0;
	//Checking if that teacher's profile exist.
	while(fread(&x,sizeof(x),1,tf)){
		
		if(strcmp(x.name,y.name)==0 && strcmp(x.pass,y.pass)==0){
			flag = 1;
			//Assigning course after the last course index position
			tmp = x;
			printf("\nTeacher's profile found!!\n\n");
			printf("There are already %d courses assigned.\nHow many more course you want to assign now : ",x.course_cnt);
			int c;
			scanf("%d",&c);
			
			for(i=x.course_cnt ; i<x.course_cnt+c ; i++){
				printf("Enter %d'th course name : ",i+1);
				fflush(stdin);
				gets(tmp.courses[i]);
			}

			tmp.course_cnt += c;
			
			fwrite(&tmp,sizeof(tmp),1,tm);
		}
		else fwrite(&x,sizeof(x),1,tm);
	}
	
	fclose(tf);
	fclose(tm);
	
	if(flag==0){
		printf("Teacher not found.Try again\n");
		add_t_course();
		return;
		
	}
	else{
		
		printf("\nTeacher's information updated successfully.");

		//overwriting the file using a temporary file.
		tf = fopen("teacher.txt","w");
		tm = fopen("temp.txt","r");
			
		while(fread(&x,sizeof(x),1,tm)){
			y = x;
			fwrite(&y,sizeof(y),1,tf);
		}
		
		fclose(tf);
		fclose(tm);
		tm = fopen("temp.txt","w");
		fclose(tm);
		
	}

}

void add_s_course(){

	struct s_info x,y,tmp;
	fflush(stdin);
	printf("Enter the Student's name you want to assign courses : ");
	gets(y.name);
	
	FILE *sf,*sm;
	sf = fopen("student.txt","r");
	sm = fopen("temp.txt","a");
	
	int flag = 0;
	//Checking if that student's profile exist.
	while(fread(&x,sizeof(x),1,sf)){
		
		if(strcmp(x.name,y.name)==0){
			flag = 1;
			//Assigning course after the last course index position
			tmp = x;
			printf("\nStudent's profile found!!\n\n");
			printf("There are already %d courses assigned.\nHow many more courses you want to assing now : ",x.course_cnt);
			int c;
			scanf("%d",&c);
			
			for(i=x.course_cnt ; i<x.course_cnt+c ; i++){
				printf("Enter %d'th course name : ",i+1);
				fflush(stdin);
				gets(tmp.courses[i]);
			}

			tmp.course_cnt += c;
			
			fwrite(&tmp,sizeof(tmp),1,sm);
		}
		else fwrite(&x,sizeof(x),1,sm);
	}
	
	fclose(sf);
	fclose(sm);
	
	if(flag==0){
		printf("Student not found.Try again\n");
		add_s_course();
		return;
		
	}
	else{
		
		printf("\nStudent's information updated successfully.");

		//overwriting the file using a temporary file.
		sf = fopen("student.txt","w");
		sm = fopen("temp.txt","r");
			
		while(fread(&x,sizeof(x),1,sm)){
			y = x;
			fwrite(&y,sizeof(y),1,sf);
		}
		
		fclose(sf);
		fclose(sm);
		sm = fopen("temp.txt","w");
		fclose(sm);
		
	}

}

//end of course assign section
//student marking section

void provide_marks(){

	struct s_info x,y,tmp;
	fflush(stdin);
	printf("Enter the Student's name : ");
	gets(y.name);
	
	FILE *sf,*sm;
	sf = fopen("student.txt","r");
	sm = fopen("temp.txt","a");
	
	int flag = 0;
	while(fread(&x,sizeof(x),1,sf)){
		
		if(strcmp(x.name,y.name)==0){
			flag = 1;

			tmp = x;
			printf("\nStudent's profile found!!\n\n");
			for(i=0 ; i<x.course_cnt ; i++){
				printf("'%s' ",x.courses[i]);
			}
			printf("Courses are assigned to this student.\n");
			printf("How many course marks you want to provide : ");
			int lp;
			scanf("%d",&lp);
			for(i=0 ; i<lp ; i++){
				char src[100];
				printf("Which course do you want to provide marks : ");
				fflush(stdin);
				gets(src);

				for(i=0 ; i<x.course_cnt ; i++){
					if(strcmp(x.courses[i],src)==0){
						printf("Enter obtained marks on %s : ",src);
						scanf("%d",&tmp.mark[i]);
						break;
					}
				}
			}
			
			fwrite(&tmp,sizeof(tmp),1,sm);
		}
		else fwrite(&x,sizeof(x),1,sm);
	}
	
	fclose(sf);
	fclose(sm);
	
	if(flag==0){
		printf("Student not found.Try again\n");
		add_s_course();
		return;
		
	}
	else{
		
		printf("\nStudent's information updated successfully.");
		
		sf = fopen("student.txt","w");
		sm = fopen("temp.txt","r");
			
		while(fread(&x,sizeof(x),1,sm)){
			y = x;
			fwrite(&y,sizeof(y),1,sf);
		}
		
		fclose(sf);
		fclose(sm);
		sm = fopen("temp.txt","w");
		fclose(sm);
		
	}

}

void get_stud_marks(){
	
	FILE *fp;
	fp = fopen("student.txt","r");
	
	struct s_info b;
	
	int flag = 0;
	while(fread(&b,sizeof(b),1,fp)>0){
	
		if(strcmp(b.name,st.name) == 0){

			flag = 1;
			printf("Congratulation %s,You have obtained :\n\n",b.name);
			for(i=0 ; i<b.course_cnt ; i++){
				if(b.mark[i]==-1) printf("\t%s = Not given.\n",b.courses[i]);
				else printf("\t%s = %d\n",b.courses[i],b.mark[i]);
			}
		}
	}
	
	if(!flag){
		get_stud_marks();
		return;
	}

	fclose(fp);
}

int count_student(){
	FILE *fp;
	fp = fopen("student.txt","r");
	struct s_info x;

	int cnt = 0;
	while(fread(&x,sizeof(x),1,fp)){
		cnt++;
	}

	fclose(fp);
	return cnt;
}
//End of student marking section

void MDBMS(){
	
	//for teacher debugging
	/*FILE *tf;
	tf = fopen("teacher.txt","r");
	struct t_info x;
	while(fread(&x,sizeof(x),1,tf)>0){
		printf("%s %s\n",x.name,x.pass);
		for(i=0 ; i<x.course_cnt ; i++){
			printf("%s ",x.courses[i]);
		}
		printf("\n");
	}*/

	//for student debuggin
	/*FILE *sf;
	sf = fopen("student.txt","r");
	struct s_info y;
	while(fread(&y,sizeof(y),1,sf)>0){
		printf("%s\n",y.name);
		for(i=0 ; i<y.course_cnt ; i++){
			printf("%s ",y.courses[i]);
		}
		printf("\n");
	}*/
	
	
	printf("\t\t\t***Welcome to Mahin's University database management system***\n");
	
	printf("Enter:\n\t'0' to exit\n\t'1' for Admin panel\n\t'2' for Teacher panel\n\t'3' for Student panel\n" );

	printf("\nWhich panel you want to login : ");
	scanf("%d",&select); //  Getting selected panel from user.

	if(select==0) return;
	
	//Admin Panel
	if(select == 1){
		printf("\n\t\t--- Welcome to \"Admin Panel\" boss ---\n\n");
		admin_login();

		while(1){
			int mode_select;
			printf("\nHello sir,Enter:\n\n\t'0' to exit from Admin panel\n\t'1' to create section\n\t'2' to update section\n\t'3' to assign courses\n" );
			scanf("%d",&mode_select);

			if(mode_select==0) break;

			if(mode_select == 1){

				int create_selector;
				while(1){
					printf("\nEnter:\n\n\t'0' to exit from create section\n\t'1' to create Teacher account\n\t'2' to create Student account\n");
					scanf("%d",&create_selector);

					if(create_selector==0) break;
		
					if(create_selector == 1){
						add_teacher();
					}
					else{
						add_student();
					}
				}
			}
			else if(mode_select==2){
				int up_selector;

				while(1){
					printf("\nEnter:\n\n\t'0' to exit from update section\n\t'1' to update Teacher account\n\t'2' to update Student account\n");
					
					scanf("%d",&up_selector);
					if(up_selector==0) break;
		
					if(up_selector == 1){
						up_teacher();
					}
					else{
						up_student();
					}
				}
			}
			else{
				int cr_select;
				while(1){
					printf("\nEnter :\n\n\t to exit from course assign section\n\t'1' to add courese to teacher\n\t'2' to add course to student\n");

					scanf("%d",&cr_select);

					if(cr_select==0) break;

					if(cr_select==1){
						add_t_course();
					}
					else{
						add_s_course();
					}

				}
			}
		} 
		
	}// end of admin Panel
	else if(select == 2){
		
		// teacher panel
		printf("\n\t\t--- Welcome to \"Teacher Panel\" honourable teacher ---\n\n");
		
		teacher_login();
		
		int mode_select;
		while(1){

			printf("\nHello, sir! Enter:\n\n\t'0' to exit from teacher panel\n\t'1' for Providing class test marks\n\t'2' for Find the student\n\t'3' for Count of Students\n");
			scanf("%d",&mode_select);
			if(mode_select==0) break;

			if(mode_select==1){
				provide_marks();
			}
			else if(mode_select==2){
				printf("Enter the student's name you want to check : ");
				fflush(stdin);
				gets(st.name);
			
				if(student_check(st)){
					get_stud_marks();
				}
				else printf("Student not found.\n");
			}
			else{
				int count = count_student();
				printf("\nCount of student is : %d\n",count);
			}

		}
		
		// end of teacher panel
	}
	else{
		//students panel
		printf("\n\t\t--- Welcome to \"Student Panel\" dear student ---\n\n");
		
		student_login();

		get_stud_marks();
		
	}// end of students panel
}

int main(){
	
	while(1){
		MDBMS();
		if(select==0) break;
	}
		
	
	printf("\n\n``Thanks for using this DBMS, don't forget to visit again.``");
	
	
	return 0;
}
