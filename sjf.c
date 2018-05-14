
#include <stdio.h>

const int NUMBER_OF_PROCESSES = 4;

int processes_ids[NUMBER_OF_PROCESSES] = { 1, 2, 3, 4 };
int processes_execution_order[NUMBER_OF_PROCESSES];

int arrival_time[NUMBER_OF_PROCESSES] = { 0 , 0, 0, 0 };
int completion_time[NUMBER_OF_PROCESSES];
int burst_time[NUMBER_OF_PROCESSES] = { 6, 8, 7, 3 };
int turnaround_time[NUMBER_OF_PROCESSES];
int waiting_time[NUMBER_OF_PROCESSES];

double average_turnaround_time = 0;
double average_waiting_time = 0;

int find_shortest_job_process(int _burst_time[], int n, int last_completion_time);
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

int find_shortest_job_process(int _burst_time[], int n, int last_completion_time) {
	int i, position = 0, shortest = _burst_time[0];
	for (i = 1; i < n; i++) {
		if (arrival_time[i] <= last_completion_time && _burst_time[i] < shortest) {
			shortest = _burst_time[i];
			position = i;
		}
	}

	return position;
}

void calculate_completion_time() {
	int _burst_time[NUMBER_OF_PROCESSES];

	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		_burst_time[i] = burst_time[i];
	}

	int shortest_position = 0;        //position of shortest job process
	int last_completion_time = 0;     //time of completion for last executed process
	int start_execution_time = 0;       //time for current process to start execution
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		shortest_position = find_shortest_job_process(_burst_time, NUMBER_OF_PROCESSES, last_completion_time);
		processes_execution_order[i] = shortest_position + 1;

		if (last_completion_time > arrival_time[shortest_position]) {
			start_execution_time = last_completion_time;
		}
		else {
			start_execution_time = arrival_time[shortest_position];
		}

		last_completion_time = completion_time[shortest_position] = start_execution_time + burst_time[shortest_position];
		_burst_time[shortest_position] = 2147483647;       //Use a big number to prevent choosing this process again as least arrival time
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

	printf("Order in which process gets executed\n");
	int i;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		printf("%d ", processes_execution_order[i]);
	}

	printf("\n%-20s", "Processes");
	printf("%-20s", "Arrival time");
	printf("%-20s", "Burst time");
	printf("%-20s", "Waiting time");
	printf("%-20s\n", "Turn around time");

	int process_order;
	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		process_order = processes_execution_order[i] - 1;
		printf("%-20d", processes_ids[process_order]);
		printf("%-20d", arrival_time[process_order]);
		printf("%-20d", burst_time[process_order]);
		printf("%-20d", waiting_time[process_order]);
		printf("%-20d\n", turnaround_time[process_order]);
	}

	printf("Average waiting time = %f\n", average_waiting_time);
	printf("Average turn around time = %f\n", average_turnaround_time);
}