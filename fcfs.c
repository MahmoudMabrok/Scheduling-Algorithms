
#include <stdio.h>

const int NUMBER_OF_PROCESSES = 3;

int processes_ids[NUMBER_OF_PROCESSES] = { 1, 2, 3 };

int arrival_time[NUMBER_OF_PROCESSES] = { 0 , 0, 0 };
int completion_time[NUMBER_OF_PROCESSES];
int burst_time[NUMBER_OF_PROCESSES] = { 10, 5, 8 };
int turnaround_time[NUMBER_OF_PROCESSES];
int waiting_time[NUMBER_OF_PROCESSES];

double average_turnaround_time = 0;
double average_waiting_time = 0;

int find_process_with_least_arrival_time(int _arrival_time[], int n);
void calculate_completion_time();
void calculate_turnaround_time();
void calculate_waiting_time();
void calculate_average_turnaround_time();
void calculate_average_waiting_time();
void calculate_and_print();

int main(void) {

	calculate_and_print();
	return 0;
}

int find_process_with_least_arrival_time(int _arrival_time[], int n) {
	int i, position = 0, least = _arrival_time[0];
	for (i = 1; i < n; i++) {
		if (_arrival_time[i] < least) {
			least = _arrival_time[i];
			position = i;
		}
	}
	return position;
}

void calculate_completion_time() {
	int _arrival_time[NUMBER_OF_PROCESSES];

	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		_arrival_time[i] = arrival_time[i];
	}

	int least_position = 0;        //position of least arrival time process
	int last_completion_time = 0;     //time of completion for last executed process
	int start_execution_time;       //time for current process to start execution
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		least_position = find_process_with_least_arrival_time(_arrival_time, NUMBER_OF_PROCESSES);

		if (last_completion_time > arrival_time[least_position]) {
			completion_time[least_position] = last_completion_time + burst_time[least_position];
		}
		else {
			completion_time[least_position] = arrival_time[least_position] + burst_time[least_position];
		}

		last_completion_time = completion_time[least_position];
		_arrival_time[least_position] = 2147483647;       //Use a big number to prevent choosing this process again as least arrival time
	}
}

void calculate_turnaround_time() {
	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		turnaround_time[i] = completion_time[i] - arrival_time[i];
	}
}

void calculate_waiting_time() {
	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		waiting_time[i] = turnaround_time[i] - burst_time[i];
	}
}

void calculate_average_turnaround_time() {
	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		average_turnaround_time += turnaround_time[i];
	}
	average_turnaround_time /= NUMBER_OF_PROCESSES;
}

void calculate_average_waiting_time() {
	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		average_waiting_time += waiting_time[i];
	}
	average_waiting_time /= NUMBER_OF_PROCESSES;
}

void calculate_and_print() {
	calculate_completion_time();
	calculate_turnaround_time();
	calculate_waiting_time();
	calculate_average_turnaround_time();
	calculate_average_waiting_time();

	printf("%-20s", "Processes");
	printf("%-20s", "Arrival time");
	printf("%-20s", "Burst time");
	printf("%-20s", "Waiting time");
	printf("%-20s\n", "Turn around time");

	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		printf("%-20d", processes_ids[i]);
		printf("%-20d", arrival_time[i]);
		printf("%-20d", burst_time[i]);
		printf("%-20d", waiting_time[i]);
		printf("%-20d\n", turnaround_time[i]);
	}

	printf("Average waiting time = %f\n", average_waiting_time);
	printf("Average turn around time = %f\n", average_turnaround_time);
}