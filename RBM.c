#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct appointment
{
	//eg. Mee YYYY - MM - DD 09:00 2.0 tenant_A A
    char service[3]; /* "Mee" for meeting, "Pre" for presentation, "Con" for conference, "Dev" for device */
    char date[10]; /* YYYY-MM-DD*/
    char time[5]; /* hh:mm*/
    double duration; /* Duration of the appointment in hours, e.g. 2.0*/
	char caller[8]; /* three tenants: "tenant_A", "tenant_B" and "tenant_C"*/
    char room[1]; /* "A" or "B", represent room A, room B, can be empty*/
	char fac1[20]; /* specific facility, can be "webcam_720p" or "webcam_1080p" or "projector_fhd" or "projector_xga"*/
	char fac2[20]; /* specific facility, can be "monitor_50" or "monitor_75" or "screen_100" or "screen_150".*/
	int priority;/*smaller number, higher priority*/
	int exist;
	
};

struct appointment input(char array []){
	/* not yet finished*/
	struct appointment ap;
	int i=0, j=0, k=0;
	char temp[] = "MPCD";
	char *p;
	
	if (array[3] == temp[0] || array[3] == temp[2] || array[3] == temp[2]){
		p = strtok (array, " ");
		while (p != NULL){
			if(i == 0){
				strcpy(ap.service, p);//error
			}
			if(i == 1){
				strcpy(ap.room, p);
			}
			if(i == 2){
				strcpy(ap.date, p);
			}
			if(i == 3){
				strcpy(ap.time, p);
			}
			if(i == 4){
				ap.duration = atof(p);
			}
			if(i == 5){
				strcpy(ap.caller, p);
			}
			if(i == 6){
				strcpy(ap.fac1, p);
			}
			if(i == 6){
				strcpy(ap.fac2, p);
			}
			i++;
			p = strtok (NULL, " ");
		}
	}
	
	return ap;


}

void interface(){
	int job=0;
	char in[200];
	char firstchar[3] = "ape", methodchar[3] = "fpo";
	struct appointment ap[100];/*Array of struct, The max number of appoinment is 100*/
	
	printf("~~ WELCOME TO PolySME ~~\n");
	while(1){
		
		printf("Please enter booking: \n");
		fgets ( in, sizeof (in), stdin);
		
		if (in[0] == firstchar[1]/*p*/ ){
			if(in[11] == methodchar[0]/*f*/ ){
				/* Use the fcfs*/
			}
			if(in[11] == methodchar[1]/*p*/ ){
				/* Use the prio*/
			}
			if(in[11] == methodchar[2]/*o*/ ){
				/* Use the opti*/
			}
		}
		
		if (in[0] == firstchar[2]/*e*/ ) break;
		
		if (in[0] == firstchar[0]/*a*/ ){
			/* recevice the appointment and put into the appointment array*/
			ap[job] = input(in);
			printf("Input is %s", ap[job].caller);
			job++;
		}
	}
}

/*child function that checks and update the availibility*/
int childfunction(char booked_time_date[4],int duration, int priority,int timeslot[10][9][2],int c){
	/*transfer date time duration to timeslot*/
	int start_time = 0;
	int date=0;
	int highest_priority=99;
	char booked_time[2];
	switch (booked_time_date[2]){
	case 'M': date = 0; 
		break;
	case 'T': date = 1;
		break;
	case 'W': date = 2;
		break;
	case 'R': date = 3;
		break;
	case 'F': date = 4;
		break;
	}
	if (booked_time_date[3] == '2'){
		date = date + 5;
	}
	strncpy(booked_time, booked_time_date, 2);
	if (strcmp(booked_time, "09") == 0)
	{
		start_time = 0;
	}
	else if (strcmp(booked_time, "10") == 0)
	{
		start_time = 1;
	}
	else if (strcmp(booked_time, "11") == 0)
	{
		start_time = 2;
	}
	else if (strcmp(booked_time, "12") == 0)
	{
		start_time = 3;
	}
	else if (strcmp(booked_time, "13") == 0)
	{
		start_time = 4;
	}
	else if (strcmp(booked_time, "14") == 0)
	{
		start_time = 5;
	}
	else if (strcmp(booked_time, "15") == 0)
	{
		start_time = 6;
	}
	else if (strcmp(booked_time, "16") == 0)
	{
		start_time = 7;
	}
	else if(strcmp(booked_time, "17") == 0)
	{
		start_time = 8;
	}
	/*check availibility*/
	int i = 0;
	int flag = 0;	
	//int bufc;
	/*Check whether it is booked, if yes, compare the priority */
	for (i = start_time; i < (start_time + duration); i++){
		if ((timeslot[date][i][0] != 0)&&(timeslot[date][i][1]<=priority)){
			flag = 1;
			break;
		}
	}


	/*Update the booking if not booked yet*/
	if (flag == 0){
	//	strcpy(bufc,"")
		for (i = start_time; i < (start_time + duration); i++){
			timeslot[date][i][0] = 1;
			timeslot[date][i][1] = priority;
			}
		return 99;//book successfully
	}
	else{
		//do nothing
	}
	/*Figure out the highest priority in the booked timeslot*/
	if (flag == 1) {
		for (i = start_time; i < (start_time + duration); i++) {
			if ((timeslot[date][i][1] != 0) && (timeslot[date][i][i] < highest_priority)) {
				highest_priority = timeslot[date][i][1];
			}
		}
		return highest_priority;//booking rejected
	}
}
int main(){
	int job = 0;
	char in[200];
	char firstchar[3] = "ape", methodchar[3] = "fpo";
	struct appointment ap[100];/*Array of struct, The max number of appoinment is 100*/

	printf("~~ WELCOME TO PolySME ~~\n");
	while (1){

		printf("Please enter booking: \n");
		fgets(in, sizeof(in), stdin);

		if (in[0] == firstchar[1]/*p*/){
			if (in[11] == methodchar[0]/*f*/){
				/* Use the fcfs*/
			}
			if (in[11] == methodchar[1]/*p*/){
				/* Use the prio*/
			}
			if (in[11] == methodchar[2]/*o*/){
				/* Use the opti*/
			}
		}

		if (in[0] == firstchar[2]/*e*/) break;

		if (in[0] == firstchar[0]/*a*/){
			/* recevice the appointment and put into the appointment array*/
			ap[job] = input(in);
			printf("Input is %s", ap[job].caller);
			job++;
		}
		break;
	}

	int pNo = 13;//No. of child process
	int i = 0;
	int j = 0;
	int pid,cid,n;
	int pcp[13][2];              //pipe from parent to children
	int cpp[13][2];             //pipe from children to parent
	char Represent[20];
	char buf[80];
	//create pipe

	for (i = 0; i < pNo; i++)
	{
		if (pipe(pcp[i]) < 0)
		{
			printf("pipe pcp error\n");
		}
		if (pipe(cpp[i]) < 0)
		{
			printf("pipe cpp error\n");
		}
	}
	int index=0;
	for (i = 0; i < pNo; i++) {
		index = i;
		pid = fork();
		if (pid < 0) {/*fork error*/
			printf("Fork Failed\n");
			exit(1);
		}
		if (pid == 0)
		{
			break;
		}
	}

		if (pid == 0) {/*child process: check availablity*/
			close(pcp[index][1]); /* close child out */
			close(cpp[index][0]); /* close child in */
			switch (index) {
			case 0: strcpy(Represent, "tenanat_A");
				break;
			case 1: strcpy(Represent, "tenanat_B");
				break;
			case 2: strcpy(Represent, "tenanat_C");
				break;
			case 3: strcpy(Represent, "room_A");
				break;
			case 4: strcpy(Represent, "room_B");
				break;
			case 5: strcpy(Represent, "webcam_720p");
				break;
			case 6: strcpy(Represent, "webcam_1080p");
				break;
			case 7: strcpy(Represent, "monitor_50");
				break;
			case 8: strcpy(Represent, "monitor_75");
				break;
			case 9: strcpy(Represent, "projector_fhd");
				break;
			case 10: strcpy(Represent, "projector_xga");
				break;
			case 11: strcpy(Represent, "screen_100");
				break;
			case 12: strcpy(Represent, "screen_150");
				break;
			}
			/*Totally 90 time slot to be filled in for each room*/
			int timeslot[10][9][2];
			int k = 0;
			int l = 0;
			/*Initialize all unused timeslot to be denoted by 0*/
			for (k; k < 10; k++) {
				for (l; l < 9; l++) {
					timeslot[k][l][0] = 0;
					timeslot[k][l][1] = 99;//indicating not booked status
				}
			}
			printf("Child: %s\n", Represent);
			/* read from pipe */
			if ((n = read(pcp[i][0], buf, 7)) > 0) {
				buf[n] = 0;
				printf("<child> message [%s] of size %d bytes received\n", buf, n);
				char start[4];
				int duration;
				int prio;//returned priority from child function
				char pri[2];
				strncpy(start, buf, 2);//store the start time
				start[2] = buf[5];//week day
				start[3] = buf[6];//which week
				duration = buf[2] - '0';
				/*Call the child function to check the availibility*/
				prio=childfunction(start, duration, 1, timeslot, i);//priority set to be 1
				switch (prio)
				{
				case 1: strcpy(pri, "01");
					break;
				case 2: strcpy(pri, "02");
					break;
				case 3: strcpy(pri, "03");
					break;
				case 4: strcpy(pri, "04");
					break;
				default:
					strcpy(pri, "99");
					break;
				}
				write(cpp[i][1], pri, 2);
				printf("%d\n", timeslot[0][1][0]);
			}
			else
			{
				printf("skip\n");
			}

			wait(NULL);
			//exit(0);
		//	close(pcp[i][0]); /* close child in */
		//	close(cpp[i][1]); /* close child out */
		}

		if (pid > 0)/*parent process*/
		{
			printf("Parent\n");
			int success = 1;
			close(pcp[i][0]); /* close parent out */
			close(cpp[i][1]); /* close parent in */
			/*Send part of the request to child*/
			strncpy(buf, ap[job].time, 2);
			strcat(buf, "2.0");//for duration............to be continued
			strcat(buf, "M2");//for date.....not finished
			if (!strcmp(ap[job].room, "A")) {
				write(pcp[3][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[3][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
					break;
				}
			}
			if (!strcmp(ap[job].room, "B")) {
				write(pcp[4][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[4][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac1, "webcam_720p")) {
				write(pcp[5][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[5][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac1, "webcam_1080p")) {
				write(pcp[6][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[6][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac1, "projector_fhd")) {
				write(pcp[7][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[7][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac1, "projector_xga")) {
				write(pcp[8][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[8][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac2, "monitor_50")) {
				write(pcp[9][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[9][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac2, "monitor_75")) {
				write(pcp[10][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[10][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac2, "screen_100")) {
				write(pcp[11][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[11][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (!strcmp(ap[job].fac2, "screen_150")) {
				write(pcp[12][1], buf, 7); /* write to pipe */
				while ((n = read(cpp[12][0], buf, 2)) > 0) { /* read from pipe */
					buf[n] = 0;
					if (!strcmp(buf, "99")) {
						//do nothing...
					}
					else {
						success = 0;
					}
					printf("<parent> message [%s] of size %d bytes received\n", buf, n);
					break;
				}
			}
			if (success == 1){
				printf("Booking accepted\n");
			}
			else
				printf("Rejected\n");
			cid = wait(NULL);
		//	exit(0);
		}
	
	return 0;
}

