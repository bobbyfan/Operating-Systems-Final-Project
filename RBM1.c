#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct appointment
{
	//eg. Mee YYYY - MM - DD 09:00 2.0 tenant_A A
	char service[10]; /* "Mee" for meeting, "Pre" for presentation, "Con" for conference, "Dev" for device */
	char room[5]; /* "A" or "B", represent room A, room B, can be empty*/
	char date[20]; /* YYYY-MM-DD*/
	char time[10]; /* hh:mm*/
	char duration[5]; /* Duration of the appointment in hours, e.g. 2.0*/
	char caller[10]; /* three tenants: "tenant_A", "tenant_B" and "tenant_C"*/
	char fac1[20]; /* specific facility, can be "webcam_720p" or "webcam_1080p" or "projector_fhd" or "projector_xga"*/
	char fac2[20]; /* specific facility, can be "monitor_50" or "monitor_75" or "screen_100" or "screen_150".*/
	char priority[2];/*smaller number, higher priority*/
	int accepted;
	int start;     // the start time(hour) of the appointment eg: 08, 18
	int end;		//the end time of the appointment

};

struct appointment input(char array []){
	/* not yet finished*/
	struct appointment ap;
	int i=0, j=0, k=0;
	char temp[] = "MPCD;";
	char *p;
	
	if (array[3] == temp[0] || array[3] == temp[1] || array[3] == temp[2]){
		p = strtok (array, " ");
		while (p != NULL){
			if(i == 0){
				for ( j = 0; j < 3; j++){
					ap.service[j] = p[j+3];
				}
				ap.service[j] = 0;
			}
			if(i == 1){
				for ( j = 0; j < sizeof(ap.room); j++){
					if(p[j+6] == 'A'){
						 ap.room[0] = 'A';
						break;}
					if(p[j+6] == 'B'){
						 ap.room[0] = 'B';
						break;}
				}
				ap.room[1] = 0;
			}
			if(i == 2){
				for ( j = 0; j <= sizeof(ap.date); j++){
					ap.date[j] = p[j];
				}
				ap.date[j] = 0;
			}
			if(i == 3){
				for ( j = 0; j <= sizeof(ap.time); j++){
					ap.time[j] = p[j];
				}
				ap.time[j] = 0;
			}
			if(i == 4){
				for ( j = 0; j <= sizeof(ap.duration); j++){
					ap.duration[j] = p[j];
				}
				ap.duration[j] = 0;
			}
			if(i == 5){
				for ( j = 0; j <= sizeof(ap.caller); j++){
					if (p[j] == temp[4]) break;
					ap.caller[j] = p[j];
				}
				ap.caller[j] = 0;
			}
			if(array[3] == temp[0] && i == 5){
				ap.fac1[0] = 0;
				ap.fac2[0] = 0;
				break;
			}
			if(i == 6){
				for ( j = 0; j <= sizeof(ap.fac1); j++){
					ap.fac1[j] = p[j];
				}
				ap.fac1[j] = 0;
			}
			if(i == 7){
				for ( j = 0; j < sizeof(ap.fac2); j++){
					if (p[j] == temp[4]) break;
					ap.fac2[j] = p[j];
				}
				ap.fac2[j] = 0;
			}
			i++;
			p = strtok (NULL, " ");
		}

	}
	
	if (array[3] == temp[3]){
		p = strtok (array, " ");
		while (p != NULL){
			if(i == 0){
				for ( j = 0; j < 3; j++){
					ap.service[j] = p[j+3];
				}
				ap.service[j] = 0;
			}
			if(i == 1){
				for ( j = 0; j < sizeof(ap.fac1); j++){
					ap.fac1[j] = p[j+1];
				}
				ap.fac1[j] = 0;
			}
			if(i == 2){
				for ( j = 0; j <= sizeof(ap.date); j++){
					ap.date[j] = p[j];
				}
				ap.date[j] = 0;
			}
			if(i == 3){
				for ( j = 0; j <= sizeof(ap.time); j++){
					ap.time[j] = p[j];
				}
				ap.time[j] = 0;
			}
			if(i == 4){
				for ( j = 0; j <= sizeof(ap.duration); j++){
					ap.duration[j] = p[j];
				}
				ap.duration[j] = 0;
			
			}
			if(i == 5){
				for ( j = 0; j <= sizeof(ap.caller); j++){
					if (p[j] == temp[4]) break;
					ap.caller[j] = p[j];
				}
				ap.caller[j] = 0;
			}
			i++;
			p = strtok (NULL, " ");
		}
		ap.room[0] = 0;
	}
	

	return ap;

}



void interface(){
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
	}
}

/*child function that checks and update the availibility*/
int childfunction(char booked_time_date[4], int duration, int priority, int timeslot[10][9][2], int c){
	/*transfer date time duration to timeslot*/
	int start_time = 0;
	int date = 0;
	int highest_priority = 100;
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
	else if (strcmp(booked_time, "17") == 0)
	{
		start_time = 8;
	}
	/*check availibility*/
	int i = 0;
	int flag = 0;
	//int bufc;
	/*Check whether it is booked, if yes, compare the priority */
	//
	for (i = start_time; i < (start_time + duration); i++){
		if ((timeslot[date][i][0] != 0)){
			flag = 1;
			break;
		}
	}

	/*Update the booking if not booked yet*/
	if (flag == 0){
		for (i = start_time; i < (start_time + duration); i++){
			timeslot[date][i][0] = 1;
			timeslot[date][i][1] = priority;
		}
		return 100;//book successfully
	}
	else{
		//do nothing
	}
	/*Figure out the highest priority in the booked timeslot*/
	if (flag == 1) {
		
		for (i = start_time; i < (start_time + duration); i++) {
			if ((timeslot[date][i][0] != 0) && (timeslot[date][i][1] < highest_priority)) {
				highest_priority = timeslot[date][i][1];
			}
		}
		if (priority < highest_priority){
			for (i = start_time; i < (start_time + duration); i++) {
				timeslot[date][i][1] = priority;
			}
			return 101;//book successfully
		}
		else
			return highest_priority;//booking rejected
	}

}

void OutTable(struct appointment ap[],int job)
{
	int n ;
	int acA=0, reA=0;
	int acB = 0, reB= 0;
	for (n = 0; n < job; n++)
	{
		if(!strcmp(ap[n].room, "A"))
		{
			(ap[n].accepted == 1) ? acA++ : reA++;
		}
		if (!strcmp(ap[n].room, "B"))
		{
			(ap[n].accepted == 1) ? acB++ : reB++;
		}
	}
	printf("%d", job);
	//*********************Accepted Part***********************//
	printf("***Room Booking – ACCEPTED***\n");
	printf("Room A has the following bookings:\n");
	printf("Date\t\t Start\t End\t Type\t\t Requester\t Device\n");
	printf("==========================================================\n");
	for (n = 0; n <= job; n++)
	{
		if (!strcmp(ap[n].room, "A"))
		{
			if (ap[n].accepted == 1)
			{
				printf("%s\t %s\t %s\t %s\t\t %s\t %s\n", ap[n].date, ap[n].time, ap[n].duration,ap[n].service, ap[n].caller, ap[n].fac1);
				if (ap[n].fac2[0] =!'\0')
				{
					printf("\t \t \t \t\t \t %s\n", ap[n].fac2);
				}
			}
		}
	}

	printf("```````````````````````````````````````````````````````````````````````\n");

	printf("Room B has the following bookings:\n");
	printf("Date\t\t Start\t End\t Type\t\t Requester\t Device\n");
	for (n = 0; n <= job; n++)
	{
		if (!strcmp(ap[n].room, "B"))
		{
			if (ap[n].accepted == 1)
			{
				printf("%s\t %s\t %s\t %s\t\t %s\t %s\n", ap[n].date, ap[n].time, ap[n].duration,ap[n].service, ap[n].caller, ap[n].fac1);
				if (ap[n].fac2[0] =!'\0')
				{
					printf("\t \t \t \t\t \t %s\n", ap[n].fac2);
				}
			}
		}
	}
	printf("==========================================================\n");

	printf("End\n");

	//*********************Rejected Part***********************//
	printf("***Room Booking – REJECTED***\n");
	printf("Room_A, there are %d bookings rejected.\n",reA);
	printf("Date\t\t Start\t End\t Type\t\t Requester\t Device\n");
	printf("==========================================================\n");
	for (n = 0; n <= job; n++)
	{
		if (!strcmp(ap[n].room, "A"))
		{
			if (ap[n].accepted == 0)
			{
				printf("%s\t %s\t %s\t %s\t\t %s\t %s\n", ap[n].date, ap[n].time, ap[n].duration,ap[n].service, ap[n].caller, ap[n].fac1);
				if (ap[n].fac2[0] =!'\0')
				{
					printf("\t \t \t \t\t \t %s\n", ap[n].fac2);
				}
			}
		}
	}
	printf("Room_B, there are %d bookings rejected.\n",reB);
	printf("Date\t\t Start\t End\t Type\t\t Requester\t Device\n");
	for (n = 0; n <= job; n++)
	{
		if (!strcmp(ap[n].room, "B"))
		{
			if (ap[n].accepted == 0)
			{
				printf("%s\t %s\t %s\t %s\t\t %s\t %s\n", ap[n].date, ap[n].time, ap[n].duration,ap[n].service, ap[n].caller, ap[n].fac1);
				if (ap[n].fac2[0] =!'\0')
				{
					printf("\t \t \t \t\t \t %s\n", ap[n].fac2);
				}
			}
		}
	}
	printf("==========================================================\n");

	printf("End\n");

}

int main(){
	printf("~~ WELCOME TO PolySME ~~\n");
	
	/*Create child process and pipes*/
	int pNo = 13;//No. of child process
	int flag = 0;
	int i = 0;
	int j = 0;
	int pid, cid, n;
	int pcp[13][2];              //pipe from parent to children
	int cpp[13][2];             //pipe from children to parent
	char Represent[20];
	char buf[80];
	int job_tmp = 0;
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
	int index = 0;
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

	while (1){
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

			//	printf("Child: %s\n", Represent);
			while (1){
				/* read from pipe */
				if ((n = read(pcp[i][0], buf, 12)) > 0) {

					if (!strcmp(buf, "Claear"))
					{
						continue;
					}
					buf[n] = 0;
					//printf("<child>%s message [%s] of size %d bytes received\n",Represent, buf, n);
					char start[4];
					int duration;
					int prio;//returned priority from child function
					int priority; //Received from parent
					char pri[2];
					strncpy(start, buf, 2);//store the start time
					start[2] = buf[8];//week day
					start[3] = buf[9];//which week
					duration = buf[5] - '0';
					pri[0] = buf[10];
					pri[1] = buf[11];
					switch (pri[1])
					{
					case '1': 
						priority = 1;
						break;
					case '2':
						priority = 2;
						break;
					case '3':
						priority = 3;
						break;
					case '4':
						priority = 4;
						break;
					default:
						priority = 99;
						break;
					}
					//printf("priority:%c\n", pri[1]);
					/*Call the child function to check the availibility*/
					prio = childfunction(start, duration, priority, timeslot, i);
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
					case 101:strcpy(pri, "-1"); // replace and success
						break;
					case 100:strcpy(pri, "00"); // success
						break;
					}
					write(cpp[i][1], pri, 2);
					//		printf("%d\n", timeslot[0][1][0]);
				}

			}
			wait(NULL);
			//exit(0);
			//	close(pcp[i][0]); /* close child in */
			//	close(cpp[i][1]); /* close child out */
		}
		else
			break;
		}
		if (pid > 0)/*parent process*/
		{
			int job = 0;
			int rejectNo = 0;
			char in[200];
			char firstchar[4] = "apeA", methodchar[3] = "fpo", temp[] ="B;";
			struct appointment ap[100];/*Array of struct, The max number of appoinment is 100*/
			//printf("Parent\n");
			char file[20];
			char *buf;
			FILE *fp;
			close(pcp[i][0]); /* close parent out */
			close(cpp[i][1]); /* close parent in */
			while (1){
				printf("Please enter booking: \n");
				fgets(in, sizeof(in), stdin);
				if (in[0] == firstchar[1]/*p*/){
					if (in[17] == methodchar[0]/*f*/){
						/* Use the fcfs*/
						for (job_tmp = 0; job_tmp < job; job_tmp++)
						{
							strcpy(ap[job_tmp].priority, "99");
						}
					}
					if (in[17] == methodchar[1]/*p*/){
						/* Use the prio*/
						for (job_tmp = 0; job_tmp < job; job_tmp++)
						{
							switch (ap[job_tmp].service[0])
							{
							case 'M':	strcpy(ap[job_tmp].priority,"03"); break;
							case 'P':	strcpy(ap[job_tmp].priority, "02"); break;
							case 'C':	strcpy(ap[job_tmp].priority, "01"); break;
							case 'D':	strcpy(ap[job_tmp].priority, "04"); break;
							}
							ap[job_tmp].start = atoi(ap[job_tmp].time);
							ap[job_tmp].end = atoi(ap[job_tmp].time) + atoi(ap[job_tmp].duration);
							//printf("%s %s\n", ap[job_tmp].service, ap[job_tmp].priority);
						}

					}
					if (in[17] == methodchar[2]/*o*/){
						/* Use the opti*/
					}
					printf("-> [Done!]\n");
					//printf("Jobs: %d", job);
					int success = 1;
					//job_tmp = 0;
					for (job_tmp=0; job_tmp < job; job_tmp++){
						printf("job_tmp :%d\n", job_tmp);
						/*Send part of the request to child*/
					printf("%s %s %s %s %s %s fac1: %s %s\n", ap[job_tmp].service, ap[job_tmp].date, ap[job_tmp].time, ap[job_tmp].duration, ap[job_tmp].room, ap[job_tmp].caller, ap[job_tmp].fac1, ap[job_tmp].fac2);
						strcpy(buf, ap[job_tmp].time);
						strcat(buf, ap[job_tmp].duration);
						strcat(buf, "M1");//for date.....not finished
						strcat(buf, ap[job_tmp].priority);
						//
						if ((strcmp(ap[job_tmp].room, "A") == 0)) {
							write(pcp[3][1], buf, 12); /* write to pipe */
								while ((n = read(cpp[3][0], buf, 2)) > 0) { /* read from pipe */
									buf[n] = 0;
									if (!strcmp(buf, "-1")) {
										rejectNo++;
										ap[job_tmp].accepted = 1;

									}
									else if (!strcmp(buf, "00"))
									{
										ap[job_tmp].accepted = 1;
									}
									else {
										success = 0;
										ap[job_tmp].accepted = 0;
									}
									//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
									n++;
									break;
								}
						}
						if (!strcmp(ap[job_tmp].room, "B")) {
							write(pcp[4][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[4][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (!strcmp(ap[job_tmp].fac1, "webcam_720p")) {
							write(pcp[5][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[5][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (!strcmp(ap[job_tmp].fac1, "webcam_1080p")) {
							write(pcp[6][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[6][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (strcmp(ap[job_tmp].fac1, "project_fhd")==0) {
							write(pcp[7][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[7][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (!strcmp(ap[job_tmp].fac1, "project_xga")) {
							write(pcp[8][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[8][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						printf("%s", ap[job_tmp].fac2);
						if (!strcmp(ap[job_tmp].fac2, "monitor_50")) {
							write(pcp[9][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[9][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (!strcmp(ap[job_tmp].fac2, "monitor_75")) {
							write(pcp[10][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[10][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (!strcmp(ap[job_tmp].fac2, "screen_100")) {
							write(pcp[11][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[11][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (!strcmp(ap[job_tmp].fac2, "screen_150")) {
							write(pcp[12][1], buf, 12); /* write to pipe */
							while ((n = read(cpp[12][0], buf, 2)) > 0) { /* read from pipe */
								buf[n] = 0;
								if (!strcmp(buf, "-1")) {
									rejectNo++;
									ap[job_tmp].accepted = 1;

								}
								else if (!strcmp(buf, "00"))
								{
									ap[job_tmp].accepted = 1;
								}
								else {
									success = 0;
									ap[job_tmp].accepted = 0;
								}
								//	printf("<parent> message [%s] of size %d bytes received\n", buf, n);//99=>success
								n++;
								break;
							}
						}
						if (success == 1){
							printf("Booking accepted\n");
						}
						else{
							printf("Rejected\n");
							rejectNo++;
							success = 1;
						}
						printf("Rejected: %d\n", rejectNo);
						//break;
						//

					}
					
					if (in[17] == methodchar[1]/*p*/) {
						/* Use the prio*/ //the previous accepted appointment is rejected due to the later one with higher priority
						for (job_tmp = 0; job_tmp <= job; job_tmp++)
						{
							int n;
							for (n = job_tmp+1; n <= job; n++)
							{
								if (!strcmp(ap[job_tmp].date, ap[n].date) && !strcmp(ap[job_tmp].room,ap[n].room))
								{
									if (ap[job_tmp].end > ap[n].start && ap[job_tmp].start < ap[n].end)
									{
										ap[job_tmp].accepted = 0;
									}
								}
							}
						}
					}
					OutTable(ap, job);   //ap-> the job pointer   job->number of total jobs (accepted + rejeacted)
					for (i = 0; i < 13; i++)     //clear the information in child processes 
					{
						write(pcp[i][1], "Clear", 5); /* write to pipe */
					}
					rejectNo = 0;
					continue; cid = wait(NULL);
				}
				if (in[0] == firstchar[2]/*e*/) {
					printf("-> Bye!\n");
					
					break;
				}

				if (in[0] == firstchar[0]/*a*/ ){
					if (in[3] == 'B'){
						size_t len = 0;
						ssize_t read;
						for ( i = 0; i <= sizeof(in); i++){
							if (in[i+12] == temp[1]) break;
							file[i] = in[i+12];
						}
						file[i] = 0;
			
						fp = fopen( file , "r");
						
						if (!fp) printf("%s", file);
		
						while ((read = getline(&buf, &len, fp)) != -1) {
							if (read > 10){
								ap[job] = input(buf);
								//printf("%s %s %s %s %s %s %s %s\n", ap[job].service, ap[job].date, ap[job].time, ap[job].duration, ap[job].room, ap[job].caller, ap[job].fac1, ap[job].fac2);
								strcpy(ap[job].priority, "99");
								job++;
							}
						}
						printf("-> [Pending]\n");
					}
					else{
					/* recevice the appointment and put into the appointment array*/
						ap[job] = input(in);
						//printf("%s %s %s %s %s %s %s %s\n", ap[job].service, ap[job].date, ap[job].time, ap[job].duration, ap[job].room, ap[job].caller, ap[job].fac1, ap[job].fac2);
						strcpy(ap[job].priority, "99");
						job++;
			
						printf("-> [Pending]\n");
					}
			
			
				}

			}
		}
			//	exit(0);

	//	}
		
	return 0;
}