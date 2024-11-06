#include<iostream>
#include<string>
#include<climits>
#include<vector>
using namespace std;

void SJF_pre(int n, int BT[], string p[], int AT[]) {
    int RT[10], WT[10], TA[10], FT[10];
    bool complete[10] = {false};
    vector<string> gantt_chart;  // To store the Gantt chart execution sequence

    for (int i = 0; i < n; i++) RT[i] = BT[i];  // Remaining times are initialized to burst times
    
    int time = 0, completed = 0, min_time, shortest = -1;
    while (completed < n) {
        min_time = INT_MAX;

        // Select the shortest process available at the current time
        for (int i = 0; i < n; i++) {
            if (AT[i] <= time && !complete[i] && RT[i] < min_time) {
                shortest = i;
                min_time = RT[i];
            }
        }

        if (shortest == -1) { // No process is available, CPU is idle
            gantt_chart.push_back("Idle");
            time++;
            continue;
        }

        // Process the selected shortest job
        gantt_chart.push_back(p[shortest]);
        RT[shortest]--;
        time++;

        // If the process is completed
        if (RT[shortest] == 0) {
            completed++;
            complete[shortest] = true;
            FT[shortest] = time;
            TA[shortest] = FT[shortest] - AT[shortest];
            WT[shortest] = TA[shortest] - BT[shortest];
        }
    }

    // Output Gantt Chart
    cout << "\nPreemptive SJF\n";
    cout << "GANTT-CHART\n\n";
    for (const auto& process : gantt_chart) {
        cout << "  " << process << "  ";
    }
    cout << endl;

    for (int i = 0; i <= gantt_chart.size(); i++) {
        cout << i << "   ";
    }
    cout << "\n\n";

    // Output Turnaround and Waiting Times
    float total_TA = 0, total_WT = 0;
    cout << "TURN-AROUND TIME\n";
    for (int i = 0; i < n; i++) {
        cout << "Turn-around time of " << p[i] << " = " << TA[i] << " msec" << endl;
        total_TA += TA[i];
    }
    cout << "Average Turn-around time = " << total_TA / n << " msec\n\n";

    cout << "WAITING TIME\n";
    for (int i = 0; i < n; i++) {
        cout << "Waiting time of " << p[i] << " = " << WT[i] << " msec" << endl;
        total_WT += WT[i];
    }
    cout << "Average Waiting time = " << total_WT / n << " msec\n";
}

int main() {
    int s, BT[10], AT[10];
    string p[10];
    cout << "Enter the number of processes: ";
    cin >> s;

    for (int i = 0; i < s; i++) {
        cout << "Enter the process name: ";
        cin >> p[i];
        cout << "Enter the Burst time: ";
        cin >> BT[i];
        cout << "Enter the Arrival time: ";
        cin >> AT[i];
    }

    SJF_pre(s, BT, p, AT);
    return 0;
}


// Enter the number of processes: 3
// Enter the process name: P1
// Enter the Burst time: 6
// Enter the Arrival time: 0
// Enter the process name: P2
// Enter the Burst time: 4
// Enter the Arrival time: 1
// Enter the process name: P3
// Enter the Burst time: 2
// Enter the Arrival time: 2

// Preemptive SJF
// GANTT-CHART

//   P1   P2   P2   P3   P3   P2   P1   P1   P1   P1   P1  
// 0   1   2   3   4   5   6   7   8   9  10  11  

// TURN-AROUND TIME
// Turn-around time of P1 = 11 msec
// Turn-around time of P2 = 6 msec
// Turn-around time of P3 = 3 msec
// Average Turn-around time = 6.66667 msec

// WAITING TIME
// Waiting time of P1 = 5 msec
// Waiting time of P2 = 2 msec
// Waiting time of P3 = 1 msec
// Average Waiting time = 2.66667 msec

