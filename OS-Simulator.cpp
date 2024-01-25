#include <iostream>
#include <queue>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

//cpu sheduling
class process {
private:
	int pid;
	int arrival;
	int burst;
	bool running;
	bool waiting;
	bool finished;

	int wait;

	int priority;

	int done;
public:
	int getpid() {
		return pid;
	}
	int getarrival() {
		return arrival;
	}
	int getburst() {
		return burst;
	}
	bool isrunning() {
		return running;
	}
	bool iswaiting() {
		return waiting;
	}
	bool isfinish() {
		return finished;
	}
	int getwait() {
		return wait;
	}
	int getpriority() {
		return priority;
	}
	int getdone() {
		return done;
	}

	void set(process obj) {
		pid = obj.getpid();
		arrival = obj.getarrival();
		burst = obj.getburst();
		wait = obj.getwait();
		priority = obj.getpriority();
		done = obj.getdone();
	}
	void setprocess(int p, int a, int b) {
		pid = p;
		arrival = a;
		burst = b;
		running = false;
		waiting = true;
		finished = false;
		wait = 0;
		priority = 0;
		done = 0;
	}
	void setprocess(int p, int a, int b, int pr) {
		pid = p;
		arrival = a;
		burst = b;
		running = false;
		waiting = true;
		finished = false;
		wait = 0;
		priority = pr;
		done = 0;
	}
	void setrunning(bool r) {
		running = r;
	}
	void setwaiting(bool w) {
		waiting = w;
	}
	void setfinish(bool f) {
		finished = f;
	}

	void setwait(int w) {
		wait = w;
	}
	float getfeed() {
		float a = wait;
		float b = burst;
		float c = a + b;
		c = c / b;
		return c;
	}

	void setpriority(int p) {
		priority = p;
	}

	void setdone(int d) {
		done = d;
	}

	void printprocess() {
		cout << "PID: " << pid << "\tArrival: " << arrival << "\tBurst: " << burst << endl;
	}
	void printprocess1() {
		cout << "PID: " << pid << "\tArrival: " << arrival << "\tBurst: " << burst << "\tWait: " << wait << "\tFeed: " << getfeed() << endl;
	}
	void printprocess2() {
		cout << "PID: " << pid << "\tArrival: " << arrival << "\tBurst: " << burst << "\tDone: " << done << endl;
	}
};
void LJF() {
	int np;//total number of processes
	cout << "Enter number of processes: ";
	cin >> np;
	process* p = new process[np];
	int iburst, iarrival;
	for (int a = 0; a < np; a++) {
		cout << "Enter arrival time for process " << a + 1 << ": ";
		cin >> iarrival;
		cout << "Enter burst time for process " << a + 1 << ": ";
		cin >> iburst;
		p[a].setprocess(a + 1, iarrival, iburst);
	}
	int starttime = p[0].getarrival();
	int endtime = 0;
	//getting the minimum start time and maximum end time
	for (int a = 0; a < np; a++) {
		if (starttime > p[a].getarrival()) {
			starttime = p[a].getarrival();
		}
		endtime = endtime + p[a].getburst();// total time for all processes
	}
	endtime = endtime + starttime;// add minimum start time to get final end time
	cout << starttime << endl;
	cout << endtime << endl;
	cout << endl;
	for (int a = 0; a < np; a++) {
		p[a].printprocess();
	}
	//sort processes with arrival time
	int tempid, temparr, tempbur;
	for (int a = 0; a < np; a++) {
		for (int b = 0; b < np - 1; b++) {
			if (p[b].getarrival() > p[b + 1].getarrival()) {
				tempid = p[b].getpid();
				temparr = p[b].getarrival();
				tempbur = p[b].getburst();
				p[b].setprocess(p[b + 1].getpid(), p[b + 1].getarrival(), p[b + 1].getburst());
				p[b + 1].setprocess(tempid, temparr, tempbur);
			}
		}
	}
	cout << endl;
	for (int a = 0; a < np; a++) {
		p[a].printprocess();
	}
	//made 2 arrays for processes to reside in
	process* ready;
	ready = new process[np];
	int rptr = 0;
	process* done;
	done = new process[np];
	int dptr = 0;
	//manual clock, 1 time unit for 1 iteration
	int busy = 0;
	for (int a = starttime; a <= endtime; a++) {
		//check for any new processes and enter into ready queue
		for (int b = 0; b < np; b++) {
			if (p[b].getarrival() == a) {
				ready[rptr].set(p[b]);
				ready[rptr].setwaiting(true);
				rptr++;
			}
		}
		//pick a process from ready queue only if processor is free and atleast 1 process exists
		//get the index of longest job and add it to done
		if (busy == 0 && rptr != 0) {
			int id = -1;
			int maxburst = 0;
			for (int b = 0; b < rptr; b++) {
				if (ready[b].getburst() > maxburst && ready[b].iswaiting() == true) {
					maxburst = ready[b].getburst();
					id = b;
				}
			}
			if (id != -1) {
				done[dptr].set(ready[id]);
				dptr++;
				busy = ready[id].getburst();
				ready[id].setwaiting(false);
			}
		}
		if (busy > 0) {
			busy--;
		}
		cout << "\nState of done queue at time = " << a << "\n";
		for (int c = 0; c < dptr; c++) {
			done[c].printprocess();
		}
	}
	return;
}
void LFRN() {
	int np;//total number of processes
	cout << "Enter number of processes: ";
	cin >> np;
	process* p = new process[np];
	int iburst, iarrival;
	for (int a = 0; a < np; a++) {
		cout << "Enter arrival time for process " << a + 1 << ": ";
		cin >> iarrival;
		cout << "Enter burst time for process " << a + 1 << ": ";
		cin >> iburst;
		p[a].setprocess(a + 1, iarrival, iburst);
	}
	int starttime = p[0].getarrival();
	int endtime = 0;
	//getting the minimum start time and maximum end time
	for (int a = 0; a < np; a++) {
		if (starttime > p[a].getarrival()) {
			starttime = p[a].getarrival();
		}
		endtime = endtime + p[a].getburst();// total time for all processes
	}
	endtime = endtime + starttime;// add minimum start time to get final end time
	cout << starttime << endl;
	cout << endtime << endl;
	cout << endl;
	for (int a = 0; a < np; a++) {
		p[a].printprocess();
	}
	//sort processes with arrival time
	int tempid, temparr, tempbur;
	for (int a = 0; a < np; a++) {
		for (int b = 0; b < np - 1; b++) {
			if (p[b].getarrival() > p[b + 1].getarrival()) {
				tempid = p[b].getpid();
				temparr = p[b].getarrival();
				tempbur = p[b].getburst();
				p[b].setprocess(p[b + 1].getpid(), p[b + 1].getarrival(), p[b + 1].getburst());
				p[b + 1].setprocess(tempid, temparr, tempbur);
			}

		}
	}
	cout << endl;
	for (int a = 0; a < np; a++) {
		p[a].printprocess();
	}
	//made 2 arrays for processes to reside in
	process* ready;
	ready = new process[np];
	int rptr = 0;
	process* done;
	done = new process[np];
	int dptr = 0;
	//manual clock, 1 time unit for 1 iteration
	int busy = 0;
	for (int a = starttime; a <= endtime; a++) {
		//check for any new processes and enter into ready queue
		for (int b = 0; b < np; b++) {
			if (p[b].getarrival() == a) {
				ready[rptr].set(p[b]);
				ready[rptr].setwaiting(true);
				rptr++;
			}
		}
		//pick a process from ready queue only if processor is free and atleast 1 process exists
		//get the index of lowest feedback ratio and add it to done
		if (busy == 0 && rptr != 0) {
			int id = -1;
			float lowfeed = INT_MAX;
			for (int b = 0; b < rptr; b++) {
				if (ready[b].getfeed() < lowfeed && ready[b].iswaiting() == true) {
					lowfeed = ready[b].getfeed();
					id = b;
				}
			}
			if (id != -1) {
				done[dptr].set(ready[id]);
				dptr++;
				busy = ready[id].getburst();
				ready[id].setwaiting(false);
			}
		}
		if (busy > 0) {
			busy--;
		}

		cout << "\nState of done queue at time = " << a << "\n";
		for (int c = 0; c < dptr; c++) {
			done[c].printprocess1();
		}

		for (int b = 0; b < rptr; b++) {

			if (ready[b].iswaiting() == true) {
				ready[b].setwait(ready[b].getwait() + 1);
			}
		}
	}
	return;
}
void MLQ() {
	//STF for queue 1 as priority
	//priority starts from 0 being the highest and 2 being the lowest for the 3 queues

	//total number of processes
	int np;
	cout << "Enter number of processes: ";
	cin >> np;
	//quantum or round robin;
	cout << "Input time quantum for RR: ";
	int quan;
	cin >> quan;
	process* p = new process[np];
	int iburst, iarrival, iprio;
	for (int a = 0; a < np; a++) {
		cout << "Enter arrival time for process " << a + 1 << ": ";
		cin >> iarrival;
		cout << "Enter burst time for process " << a + 1 << ": ";
		cin >> iburst;
		cout << "Enter priority for process " << a + 1 << ": ";
		cin >> iprio;
		p[a].setprocess(a + 1, iarrival, iburst, iprio);
	}
	int starttime = p[0].getarrival();
	int endtime = 0;
	//getting the minimum start time and maximum end time
	for (int a = 0; a < np; a++) {
		if (starttime > p[a].getarrival()) {
			starttime = p[a].getarrival();
		}
		endtime = endtime + p[a].getburst();// total time for all processes
	}
	endtime = endtime + starttime;// add minimum start time to get final end time
	cout << starttime << endl;
	cout << endtime << endl;
	cout << endl;
	for (int a = 0; a < np; a++) {
		p[a].printprocess();
	}
	//sort processes with arrival time
	int tempid, temparr, tempbur, tempprio;
	for (int a = 0; a < np; a++) {
		for (int b = 0; b < np - 1; b++) {
			if (p[b].getarrival() > p[b + 1].getarrival()) {
				tempid = p[b].getpid();
				temparr = p[b].getarrival();
				tempbur = p[b].getburst();
				tempprio = p[b].getpriority();
				p[b].setprocess(p[b + 1].getpid(), p[b + 1].getarrival(), p[b + 1].getburst(), p[b + 1].getpriority());
				p[b + 1].setprocess(tempid, temparr, tempbur, tempprio);
			}

		}
	}
	//done queue for final completed processes
	process* done;
	done = new process[np];
	int dptr = 0;
	//3 queues to store processes in each for execution
	queue<process> q1;
	queue<process> q2;
	queue<process> q3;

	int busy = 0;
	process cur;
	int prq = -1;//which queue is being used
	for (int a = starttime; a <= endtime; a++) {
		//check for any new processes and enter into respective queue
		for (int b = 0; b < np; b++) {
			if (p[b].getarrival() == a) {

				if (p[b].getpriority() % 3 == 0) {
					q1.push(p[b]);
				}
				else if (p[b].getpriority() % 3 == 1) {
					q2.push(p[b]);
				}
				else if (p[b].getpriority() % 3 == 2) {
					q3.push(p[b]);
				}

			}
		}
		//for round robin if current process isnt finished add it back to the queue
		if (busy == 0 && prq == 2) {
			q2.push(cur);
		}


		cout << "before State of Q3 at time = " << a << endl;
		for (int b = 0; b < q3.size(); b++) {
			q3.front().printprocess2();
			q3.push(q3.front());
			q3.pop();
		}


		if (busy == 0) {
			prq = -1;
			//taking process from queue 1
			if (q1.size() != 0) {
				prq = 1;
				//find process with shortest burst time;
				int shorttime = INT_MAX;
				process temp;
				int id = -1;
				for (int b = 0; b < q1.size(); b++) {
					temp = q1.front();
					q1.pop();
					q1.push(temp);

					if (temp.getburst() < shorttime && temp.iswaiting() == true) {
						shorttime = temp.getburst();
						id = temp.getpid();
					}
				}
				//remove this job from the queue
				if (id != -1) {
					for (int b = 0; b < q1.size() + 1; b++) {
						if (q1.front().getpid() != id) {
							q1.push(q1.front());
						}
						else {
							temp = q1.front();
							break;
						}
						q1.pop();
					}
					//add it to done queue
					temp.setwaiting(false);
					done[dptr].set(temp);
					dptr++;
					busy = temp.getburst();
				}
			}
			//taking process from queue 2
			else if (q2.size() != 0) {
				prq = 2;
				cur = q2.front();
				q2.pop();

				//the processor is busy with the current process now;
				if (cur.getburst() - cur.getdone() <= quan) {
					//the process leaves the queue
					busy = cur.getburst() - cur.getdone();
				}
				else {
					//the process stays in queue
					busy = quan;
				}
			}
			//taking process from queue 3
			else if (q3.size() != 0) {

				prq = 3;
				//find process with shortest remaining time;
				int shorttime = INT_MAX;
				process temp;
				int id = -1;
				for (int b = 0; b < q3.size(); b++) {
					temp = q3.front();
					q3.pop();
					q3.push(temp);

					if (temp.getburst() - temp.getdone() < shorttime && temp.iswaiting() == true) {
						shorttime = temp.getburst() - temp.getdone();
						id = temp.getpid();
					}
				}
				//update this job in the queue
				if (id != -1) {

					process cur2;
					for (int b = 0; b < q3.size(); b++) {
						//find the job
						cur2 = q3.front();
						if (cur2.getpid() == id) {
							//increase its time by 1
							cur2.setdone(cur2.getdone() + 1);
							//the processor is busy for 1 second now
							busy = 1;
							//if its complete add it to done and remove it from queue
							if (cur2.getdone() == cur2.getburst()) {
								cur2.setwaiting(false);
								done[dptr].set(cur2);
								dptr++;
								q3.pop();
								break;
							}
						}
						q3.push(cur2);
						q3.pop();
					}
				}
			}
		}


		//for round robin update the time of current process being executed
		if (prq == 2) {
			if (busy != 0) {
				cur.setdone(cur.getdone() + 1);
				if (cur.getdone() == cur.getburst()) {
					done[dptr].set(cur);
					dptr++;
				}
			}
			cout << "Currently processing:\n";
			cur.printprocess2();
			cout << "After State of Q2 at time = " << a << endl;
			for (int b = 0; b < q2.size(); b++) {
				q2.front().printprocess2();
				q2.push(q2.front());
				q2.pop();
			}
		}



		if (busy != 0) {
			busy--;
		}

		cout << "After State of Q3 at time = " << a << endl;
		for (int b = 0; b < q3.size(); b++) {
			q3.front().printprocess2();
			q3.push(q3.front());
			q3.pop();
		}


		cout << "\nState of done queue at time = " << a << "\n";
		for (int c = 0; c < dptr; c++) {
			done[c].printprocess2();
		}
	}






}
void MLFQ() {
	//total number of processes
	int np;
	cout << "Enter number of processes: ";
	cin >> np;
	//quantum or round robin;
	cout << "Input time quantum for q1 FCFS: ";
	int qn1;
	cin >> qn1;
	cout << "Input time quantum for q2 SJF: ";
	int qn2;
	cin >> qn2;
	cout << "Input time quantum for q3 FCFS: ";
	int qn3;
	cin >> qn3;

	process* p = new process[np];
	int iburst, iarrival, iprio;
	for (int a = 0; a < np; a++) {
		cout << "Enter arrival time for process " << a + 1 << ": ";
		cin >> iarrival;
		cout << "Enter burst time for process " << a + 1 << ": ";
		cin >> iburst;
		cout << "Enter priority for process " << a + 1 << ": ";
		cin >> iprio;
		p[a].setprocess(a + 1, iarrival, iburst, iprio);
	}
	int starttime = p[0].getarrival();
	int endtime = 0;
	//getting the minimum start time and maximum end time
	for (int a = 0; a < np; a++) {
		if (starttime > p[a].getarrival()) {
			starttime = p[a].getarrival();
		}
		endtime = endtime + p[a].getburst();// total time for all processes
	}
	endtime = endtime + starttime;// add minimum start time to get final end time
	cout << starttime << endl;
	cout << endtime << endl;
	cout << endl;
	for (int a = 0; a < np; a++) {
		p[a].printprocess();
	}
	//sort processes with arrival time
	int tempid, temparr, tempbur, tempprio;
	for (int a = 0; a < np; a++) {
		for (int b = 0; b < np - 1; b++) {
			if (p[b].getarrival() > p[b + 1].getarrival()) {
				tempid = p[b].getpid();
				temparr = p[b].getarrival();
				tempbur = p[b].getburst();
				tempprio = p[b].getpriority();
				p[b].setprocess(p[b + 1].getpid(), p[b + 1].getarrival(), p[b + 1].getburst(), p[b + 1].getpriority());
				p[b + 1].setprocess(tempid, temparr, tempbur, tempprio);
			}
		}
	}
	//done queue for final completed processes
	process* done;
	done = new process[np];
	int dptr = 0;
	//3 queues to store processes in each for execution
	queue<process> q1;
	queue<process> q2;
	queue<process> q3;
	int prq = -1;//which queue is being used
	process cur;//current process under execution
	int busy = 0;
	for (int a = starttime; a <= endtime; a++) {
		//check for any new processes and enter into respective queue
		for (int b = 0; b < np; b++) {
			if (p[b].getarrival() == a) {

				if (p[b].getpriority() % 3 == 0) {
					q1.push(p[b]);
				}
				else if (p[b].getpriority() % 3 == 1) {
					q2.push(p[b]);
				}
				else if (p[b].getpriority() % 3 == 2) {
					q3.push(p[b]);
				}

			}
		}


		//check if process done from q1
		if (prq == 1 && busy == 0) {
			//process complete
			if (cur.getdone() == cur.getburst()) {
				done[dptr].set(cur);
				dptr++;
			}
			//process not complete
			else {
				cur.setpriority(1);
				q2.push(cur);
			}
		}
		//check if process done from q2
		if (prq == 2 && busy == 0) {
			//process complete
			if (cur.getdone() == cur.getburst()) {
				done[dptr].set(cur);
				dptr++;
			}
			//process not complete
			else {
				cur.setpriority(2);
				q3.push(cur);
			}
		}
		//check if process done from q3
		if (prq == 3 && busy == 0) {
			if (cur.getdone() == cur.getburst()) {
				done[dptr].set(cur);
				dptr++;
			}
			else {
				q3.push(cur);
			}
		}


		if (busy == 0) {
			prq = -1;
			//fcfs
			if (q1.size() != 0) {
				prq = 1;
				//since processes arrive in queue according to start time, they are already in fcfs sequence
				cur = q1.front();
				q1.pop();

				if (cur.getburst() - cur.getdone() < qn1) {
					busy = cur.getburst() - cur.getdone();
				}
				else {
					busy = qn1;
				}
			}
			//sjf
			else if (q2.size() != 0) {
				prq = 2;
				//picking the shortest job
				int min = INT_MAX;
				for (int c = 0; c < q2.size(); c++) {
					if (min < q2.front().getburst() - q2.front().getdone()) {
						min = q2.front().getburst() - q2.front().getdone();
						cur = q2.front();
					}
					q2.push(q2.front());
					q2.pop();
				}
				//remove this process from the queue
				for (int c = 0; c < q2.size(); c++) {
					if (cur.getpid() == q2.front().getpid()) {
						q2.pop();
						break;
					}
					q2.push(q2.front());
					q2.pop();
				}
				//set the busy for processor
				if (cur.getburst() - cur.getdone() < qn2) {
					busy = cur.getburst() - cur.getdone();
				}
				else {
					busy = qn2;
				}

			}
			//rr srjf
			else if (q3.size() != 0) {
				prq = 3;
				for (int c = 0; c < q3.size(); c++) {
					if (cur.getpid() == q3.front().getpid()) {
						q3.pop();
						break;
					}
					q3.push(q3.front());
					q3.pop();
				}
				//set the busy for processor
				busy = 1;
			}
		}
		if (busy != 0) {
			cur.setdone(cur.getdone() + 1);
			busy--;
		}
	}
}

//semaphore
/*
#define philosophers 5
sem_t semaphore1[philosophers];
void* fun(void* arg) {
	int* f = (int*) arg;
	int left = *f;
	int right = (*f + 1) % philosophers;

   while (1) {
		printf("Philosopher %d is thinking to eat\n", *f);
		sem_wait(&semaphore1[left]);
		printf("Philosopher %d picked up the left fork\n", *f);
		sem_wait(&semaphore1[right]);
		printf("Philosopher %d picked up the right fork and started eating\n", *f);

		sleep(1);

		sem_post(&semaphore1[right]);
		printf("Philosopher %d released the right fork\n", *f);

		sem_post(&semaphore1[left]);
		printf("Philosopher %d released the left fork and finished eating\n", *f);

		sleep(1);
	}

	pthread_exit(NULL);
}
*/

//banker and request
void safetyalgo(int r, int p, int need[][100], int available[], int allocation[][100]) {
	int totalresources[100];
	int safe[100];
	int c = 0;
	for (int i = 0; i < r; i++)
	{
		totalresources[i] = available[i];
	}
	bool finished[100];
	for (int i = 0; i < p; i++)
	{
		finished[i] = false;
	}
	for (int k = 0; k < p; k++) {

		for (int i = 0; i < p; i++)
		{
			if (finished[i] == false) {
				bool done = true;
				for (int j = 0; j < r; j++)
				{


					if (need[i][j] > totalresources[j])
					{
						done = false;
						break;
					}


				}

				if (done)
				{
					for (int j = 0; j < r; j++)
					{
						totalresources[j] += allocation[i][j];
					}
					safe[c] = i;
					c++;

					finished[i] = true;

				}
			}


		}
	}
	bool flag = true;
	cout << "Safe sequence: ";
	for (int i = 0; i < p; i++)
	{
		if (safe[i] < 0)
		{

			flag = false;
			break;
		}
		else {

			cout << "P" << safe[i] << " ";
			flag = true;
		}


	}
	if (!flag)
	{
		cout << "Deadlock!!Request not granted immediately" << endl;
	}

}
void requestalgo(int r, int p, int need[][100], int available[], int allocation[][100])
{
	int n;
	cout << "Enter process no: ";
	cin >> n;
	cout << "Enter the request: ";
	int request[100];
	for (int i = 0; i < r; i++)
	{
		cin >> request[i];
	}
	bool done = true;
	for (int i = 0; i < r; i++)
	{
		if (request[i] > need[n][i])
		{
			cout << "Error.Cant grant the request ";
			done = false;
			break;
		}
	}

	if (done)
	{
		for (int i = 0; i < r; i++)
		{
			if (request[i] <= available[i])
			{
				need[n][i] = need[n][i] - request[i];
				allocation[n][i] += request[i];
				available[i] -= request[i];

			}

		}
		safetyalgo(r, p, need, available, allocation);
	}



}

//memory management
class pagetable {
	int* page;
	int* frame;
	int maxsize;
public:
	pagetable() {
		maxsize = 14;
		page = new int[14];
		frame = new int[14];
		page[0] = 1;
		page[1] = 2;
		page[2] = 10;
		page[3] = 4;
		page[4] = 122;
		page[5] = 44;
		page[6] = 3;
		page[7] = 5;
		page[8] = 6;
		page[9] = 13;
		page[10] = 21;
		page[11] = 22;
		page[12] = 42;
		page[13] = 24;
		page[14] = 54;





		frame[0] = 4;
		frame[1] = 1;
		frame[2] = 3;
		frame[3] = 8;
		frame[4] = 2;
		frame[5] = 9;
		frame[6] = 5;
		frame[7] = 6;
		frame[8] = 12;
		frame[9] = 10;
		frame[10] = 19;
		frame[11] = 62;
		frame[12] = 31;
		frame[13] = 29;
		frame[14] = 45;


	}
	bool seachpage(int page1)
	{
		bool fk = false;
		for (int i = 0; i < maxsize; i++)
		{
			if (page1 == page[i])
			{
				fk = true;
				break;
			}
		}
		return fk;
	}
	void display() {
		cout << "-------------Page Table------------" << endl;
		cout << "Page number" << "         " << "Frame number " << endl;
		cout << endl << "----------------------------" << endl;
		for (int i = 0; i < maxsize; i++)
		{
			cout << "| " << page[i] << "     " << frame[i] << "                | " << endl;
		}

		cout << endl << "----------------------------" << endl;
	}
	int returnframe(int page1) {
		int ind;
		for (int i = 0; i < maxsize; i++)
		{
			if (page1 == page[i]) {
				ind = i;
			}
		}
		return frame[ind];
	}
};
class tlb {
	int size;
	vector<int>arrtlb;
	vector<int>frameno;
	unordered_map<int, int>fre;
	int ele;
	int frame;
public:
	tlb(int s) {
		size = s;

		ele = 0;

	}
	void removetheleast(vector<int>& arr, unordered_map<int, int>& fre) {
		int a = arr[0];
		int fr = fre[a];
		int index = 0;
		for (int i = 0; i < arr.size(); i++)
		{
			int n = arr[i];
			if (fre[n] < fr)
			{
				a = arr[n];
				fr = fre[n];
				index = i;

			}
		}
		fre[a]--;
		///removing that element
		/*auto i = find(arr.begin(), arr.end(), a);
		if (i != arr.end())

		{
			arr.erase(i);

		}*/
		arr.erase(arr.begin() + index);
		frameno.erase(frameno.begin() + index);

	}
	void addtlb(int p, int f)
	{



		arrtlb.push_back(p);
		frameno.push_back(f);
		fre[p]++;
		if (arrtlb.size() > size)
		{
			removetheleast(arrtlb, fre);
		}


	}
	bool searchtlb(int p)
	{
		bool flag = false;
		//int ind;
		for (int i = 0; i < arrtlb.size(); i++)
		{
			if (arrtlb[i] == p)
			{
				flag = true;
				fre[p]++;
				this->frame = frameno[i];
			}
		}
		if (flag)
		{
			cout << endl;
			cout << "Tlb Hit!! Frame number : " << frame << endl;
			return true;
		}
		else {
			cout << endl;
			cout << "Not found in Tlb" << endl;
			return false;
		}
	}
	int getframeno() {
		return frame;
	}
	void print()
	{
		cout << "-----------TLB----------" << endl;
		/*for (int i = 0; i < ele; i++)
		{
			cout << "Page number: " << arrtlb[i] << " " << "Frame number: " << frameno[i] << endl;
		}*/

		for (int num : arrtlb) {
			cout << "Page number:" << num << "  ";
		}
		cout << endl; cout << endl;
		for (int num : frameno) {
			cout << "Frame number:" << num << " ";
		}
		cout << endl;


	}
	void printfre() {
		cout << "Frequencies: ";
		for (const auto& p : fre)
		{
			cout << p.first << " " << p.second << endl;
		}
	}

};
class HashNode
{
public:
	int page;
	int frame;
	HashNode* next;
	HashNode(int key, int value)
	{
		this->page = key;
		this->frame = value;
		this->next = NULL;
	}
};
class hashtable {
	int hsize;
	vector< HashNode*>arr;
	int ss;
	int f;

public:
	hashtable(int s)
	{
		hsize = s;
		arr.resize(s);
		for (int i = 0; i < hsize; i++)
		{
			arr[i] = nullptr;
		}
	}
	int HashFunc(int key)
	{
		return key % hsize;
	}
	void Insert(int key, int value)
	{
		int hashval = HashFunc(key);
		HashNode* newnode = new HashNode(key, value);
		if (arr[hashval] == nullptr)
		{
			arr[hashval] = newnode;
		}
		else {

			HashNode* first = arr[hashval];
			while (first->next != nullptr)
			{
				first = first->next;
			}
			first->next = newnode;
		}
		//cout <<"Index: "<<hashval<<" "<< "Page number: " << arr[hashval]->page << " " << "Frame number: " << arr[hashval]->frame << endl;
		ss++;
	}
	void display() {
		cout << endl;
		cout << "---------------Hash Table---------------" << endl;
		for (int i = 0; i < hsize; i++) {
			cout << "Index: " << i << " ";
			HashNode* entry = arr[i];
			while (entry != NULL)
			{
				cout << "Page number: " << entry->page << " ";
				cout << "Frame number: " << entry->frame << endl;
				entry = entry->next;
			}
			cout << endl;
		}
	}
	bool Search(int key)
	{
		bool flag = false;
		int hash_val = HashFunc(key);
		HashNode* first = arr[hash_val];
		while (first != nullptr)
		{
			if (first->page == key)
			{
				cout << first->frame << " ";
				//t.addtlb(entry->page);
				flag = true;
				f = first->frame;
				return flag;
			}
			first = first->next;
		}
		if (!flag)
		{
			cout << endl;
			cout << "Not in hash table" << endl;
			return false;
		}
	}
	int getframe() {
		return f;
	}
};
class twolevel {
	int pagesize;
	int oisize;
	int* outerpage;
	int** innerpage;
	void start() {
		outerpage = new int[oisize];
		innerpage = new int* [oisize];
		for (int i = 0; i < oisize; i++)
		{
			outerpage[i] = -1;
		}

		for (int i = 0; i < oisize; i++)
		{
			innerpage[i] = new int[oisize];
			for (int j = 0; j < oisize; j++)
			{
				innerpage[i][j] = -1;
			}
		}
	}
public:
	twolevel(int m, int b)
	{
		pagesize = m;
		oisize = b;

		start();
	}
	void fillvalues() {

		outerpage[0] = 0;
		outerpage[1] = 7;
		outerpage[2] = 5;
		outerpage[3] = 23;
		outerpage[5] = 6;

		innerpage[0][3] = 8;
		innerpage[0][8] = 9;
		innerpage[1][3] = 1;
		innerpage[2][8] = 2;
		innerpage[2][7] = 5;
		innerpage[3][4] = 6;
		innerpage[3][6] = 7;
		innerpage[5][0] = 12;
		innerpage[5][1] = 10;

	}
	void print() {
		for (int i = 0; i < oisize; i++)
		{
			cout << outerpage[i];
		}
	}
	void addresstranslation(int l)
	{
		int pagenumber = l / pagesize;
		int offset = l % pagesize;

		///pages get divided when page table size is larger than the pagesize(framesize)
		///calculation indeces

		int outerindex = pagenumber / oisize;
		int innerindex = pagenumber % oisize;

		///checking conditions



		cout << "Pagenumber: " << pagenumber << endl;
		cout << "Offset: " << offset << endl;
		cout << "Outer page index: " << outerindex << endl;
		cout << "Inner page index: " << innerindex << endl;

		cout << "Value in outer page: " << outerpage[outerindex] << endl;
		cout << "Value in inner page: " << innerpage[outerindex][innerindex] << endl;
		bool flag = false;
		if (outerpage[outerindex] != -1 && innerpage[outerindex][innerindex] != -1)////dekhnay ke liye ke page memory me hai 
		{
			flag = true;
		}

		if (flag) {
			int physicalframe = innerpage[outerindex][innerindex];
			int physicaladd = (physicalframe * pagesize) + offset;
			cout << "Physical Address: " << physicaladd << endl;
		}
		else {
			cout << "Physical address not generated!Page not mapped" << endl;
		}
	}
};
void hashedpage() {

	int pagesize = 1024;
	int pagefaults = 0;
	pagetable f;
	f.display();
	tlb t(5);
	t.addtlb(1, 4);
	t.addtlb(10, 3);
	t.addtlb(4, 8);
	t.addtlb(122, 2);
	t.addtlb(44, 9);
	t.print();
	cout << endl;
	//t.printfre();

	cout << endl;
	hashtable h(10);

	h.Insert(3, 5);
	h.Insert(5, 6);
	h.Insert(6, 12);
	h.Insert(13, 0);
	h.display();

	cout << endl;
	//int page;

	int lol;

	cout << "Enter Logical address to search page: ";

	while (cin >> lol && lol != -1) {
		int page = lol / pagesize;
		int offset = lol % pagesize;
		cout << "Page: " << page;
		bool flag = f.seachpage(page);

		if (flag) {
			if (t.searchtlb(page))
			{
				int physical = (t.getframeno() * pagesize) + offset;
				cout << endl;
				cout << "Physical Address: " << physical << endl;
			}
			else {
				if (h.Search(page))//returning the frame no, that page and frame are added to tlb
				{
					cout << endl;
					cout << "Frame no returned by hash: " << h.getframe() << endl;
					int physcial = (h.getframe() * pagesize) + offset;
					cout << endl;
					cout << "Physical Address: " << physcial << endl;
					t.addtlb(page, h.getframe());
				}
				else {
					cout << endl;
					cout << "!!Inserting into Hash function!!: " << endl;
					int g = f.returnframe(page);
					h.Insert(page, g);
				}
			}
			cout << endl;
			t.print(); cout << endl;
			h.display();
			//t.printfre();
			cout << "Enter Logical address to search page: ";

		}
		else
		{
			cout << "Page fault! As the page is not in Page table " << endl;
			pagefaults++;
			cout << "Enter page to search: ";
		}
	}
	cout << endl << endl;

	cout << "Total page faults: " << pagefaults << endl;
}
void twolevelpage() {
	twolevel t(1024, 256);
	t.fillvalues();
	//t.print();
	cout << "Enter logical address in bytes: ";
	int n;
	cin >> n;
	t.addresstranslation(n);
}

//page placement
class node {
public:
	int pagenumber;
	int referencebit;
	node* next;
	node() {
		pagenumber = -1;
		next = nullptr;
	}
};
class secondchance {
	node* head;
	int frameno;
	int faults;
public:

	secondchance(int f, node* hea) {
		head = hea;
		frameno = f;
		faults = 0;
	}
	void check(int page)
	{

		bool done = false; ///ye deknay keliey ke page same aya ke nahi

		// condition to check is same page comes
		node* current = head;
		do {
			if (current->pagenumber == page) {
				done = true;
				cout << "No page fault" << endl;
				break;
			}
			current = current->next;
		} while (current != head);

		// page frame me nahi, search
		if (done == false) {
			while (true) {

				if (head->referencebit == 0) {////jiski bit 0 ho usko replace kro or naya pagenumber load
					cout << "Page Fault " << endl;
					head->pagenumber = page;
					head->referencebit = 1;  // Set the use bit to 1

					faults++;
					head = head->next;  // iskay sath apna head agay move karo takay next time wo replace ho
					break;
				}
				else {
					head->referencebit = 0;  ///second chance do
					head = head->next;  // head agay move
				}
			}
		}
		else {

			current->referencebit = 1;
		}


		node* curr = head;
		for (int i = 0; i < frameno; ++i) {
			cout << curr->pagenumber << "--" << "'" << curr->referencebit << "'" << "          ";
			curr = curr->next;
		}
		cout << endl;
		// cout << head->pagenumber << endl;
	}
	int getfaults() {
		return faults;
	}


};
void second() {
	int frameno;
	cout << "Enter the number of frames: ";
	cin >> frameno;

	node* frames = new node[frameno];
	for (int i = 0; i < frameno; ++i) {
		frames[i].next = &frames[(i + 1) % frameno];  // Connect frames in circular manner
	}

	int page;
	int number;

	cout << "Enter no of pages: ";
	cin >> number;

	cout << "Enter the page reference string : ";

	node* head = &frames[0];



	secondchance s(frameno, head);

	for (int i = 0; i < number; i++)
	{
		cin >> page;
		s.check(page);

	}


	cout << "Total Page Faults: " << s.getfaults() << endl;
	float m = float(s.getfaults()) / float(number);
	cout << "Page Fault probability: " << m << endl;
	cout << "Page Fault Percentage: " << m * 100 << endl;
	delete[] frames;
}


int main() {
	int choice = -1;
	while (choice != 0) {
		system("CLS");
		cout << "0-Exit\n";
		cout << "1-CPU Sheduling\n";
		cout << "2-Semaphores\n";
		cout << "3-Deadlock\n";
		cout << "4-Memory Management\n";
		cout << "5-Page Placement\n";
		cin >> choice;
		//cpu sheduling
		if (choice == 1) {
			cout << "1-LJF\n";
			cout << "2-LFRN\n";
			cout << "3-MLQ\n";
			cout << "4-MLFQ\n";
			cin >> choice;
			if (choice == 1) {
				LJF();
			}
			else if (choice == 2) {
				LFRN();
			}
			else if (choice == 3) {
				MLQ();
			}
			else if (choice == 4) {
				MLFQ();
			}
			else {
				cout << "Invalid Choice\n";
			}
		}
		//semaphores
		else if (choice == 2) {
			/*
			for (int i = 0; i < philosophers; i++) {
				sem_init(&semaphore1[i], 0, 1);
			}

			pthread_t t[philosophers];

			for (int i = 0; i < philosophers; i++) {
				int* arg = malloc(sizeof(*arg));
				*arg = i;
				pthread_create(&t[i], NULL, fun, arg);
			}

			for (int i = 0; i < philosophers; i++) {
				pthread_join(t[i], NULL);
			}

			for (int i = 0; i < philosophers; i++) {
				sem_destroy(&semaphore1[i]);
			}
			*/
		}
		//banker and request
		else if (choice == 3) {
			cout << "1-Safety Algorithm\n";
			cout << "2-Request Algorithm\n";
			cout << "Input Choice:";
			cin >> choice;

			int need[100][100];
			int maxx[100][100];
			int allocation[100][100];
			int available[100];
			int resource, noofprocess;
			cout << "Enter the number of processes: ";
			cin >> noofprocess;
			cout << endl;
			cout << "Enter the number of resources: ";
			cin >> resource;
			cout << endl;
			cout << "Enter Available resouces: " << endl;
			for (int i = 0; i < resource; i++)
			{
				cout << "Resource " << i << " ";
				cin >> available[i];
				cout << endl;
			}
			cout << endl;
			cout << "Enter allocated resources for each process " << endl;
			for (int i = 0; i < noofprocess; i++)
			{
				cout << "Process " << i << endl;
				for (int j = 0; j < resource; j++)
				{
					cout << "Resource " << j << " ";
					cin >> allocation[i][j];
				}
				cout << endl;

			}
			cout << endl;
			cout << "Enter max need for each process " << endl;
			for (int i = 0; i < noofprocess; i++)
			{
				cout << "Process " << i << endl;
				for (int j = 0; j < resource; j++)
				{
					cout << "Resource " << j << " ";
					cin >> maxx[i][j];
					if (maxx[i][j] < allocation[i][j]) {
						cout << "Max need should be greater than allocated resources. Enter again: ";
						cin >> maxx[i][j];
					}
					else continue;
				}
				cout << endl;
			}

			for (int i = 0; i < noofprocess; i++)
			{
				for (int j = 0; j < resource; j++)
				{
					need[i][j] = maxx[i][j] - allocation[i][j];
				}
			}
			for (int i = 0; i < noofprocess; i++)
			{
				cout << "Process " << i << endl;
				for (int j = 0; j < resource; j++)
				{
					cout << "Resource: " << j << " " << "Need " << need[i][j] << endl;


				}
				cout << endl;
			}

			if (choice == 1) {
				safetyalgo(resource, noofprocess, need, available, allocation);
			}
			else if (choice == 2) {
				requestalgo(resource, noofprocess, need, available, allocation);
			}
			else {
				cout << "Invalid Choice\n";
			}
		}
		//memory
		else if (choice == 4) {
			cout << "1-Two Level Page Table\n";
			cout << "2-Hashed Page Table with TLB\n";
			cout << "Input Choice:";
			cin >> choice;
			if (choice == 1) {
				twolevelpage();
			}
			else if (choice == 2) {
				hashedpage();
			}
			else {
				cout << "Invalid Choice\n";
			}
		}
		//paging
		else if (choice == 5) {
			second();
		}
		//invalid
		else {
			cout << "Invalid Choice\n";
		}
		system("pause");
	}
	cout << "Terminating OS\n";
	system("pause");
	return 0;
}