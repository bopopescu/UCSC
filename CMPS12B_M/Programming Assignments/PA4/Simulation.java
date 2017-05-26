/*Seongwoo Choi
 *This program is a simulation that find the time it takes to  
 *complete m number of Jobs 
 * 
 */ 
import java.io.*;
import java.util.Scanner;

public class Simulation {

    public static Job getJob(Scanner in) {
        String[] s = in.nextLine().split(" ");
        int a = Integer.parseInt(s[0]);
        int d = Integer.parseInt(s[1]);
        return new Job(a, d);
    }

    public static void main(String[] args) throws IOException {

        //    1.  check command line arguments
        if (args.length < 1) {
            System.out.println("Usage: Simulation input_file ");
            System.exit(1);
        }

        //    2.  open files for reading and writing
        PrintWriter report = new PrintWriter(new FileWriter(args[0] + ".rpt"));
        PrintWriter trace = new PrintWriter(new FileWriter(args[0] + ".trc"));

        //    3.  read in numJobs jobs from input file
        Scanner in = new Scanner(new File(args[0]));
        String fileName = args[0];
        int numJobs = in.nextInt();
        in.nextLine();

        Queue backup = new Queue(); //backup to reload initial state of jobs
        Queue storage = new Queue(); //used for storage manipulation
        for ( int i = 0; i < numJobs; i++) {
            Job J = getJob(in);
            backup.enqueue(J);
            storage.enqueue(J);
        }

        //    4.  run simulation with n processors for n=1 to n=numJobs-1  {
        // Output to report file:
        report.println("Report file: " + args[0] + ".rpt");
        report.println(numJobs + " Jobs:");
        report.println(storage);
        report.println();
        report.println("***********************************************************");

        // Output to trace file:
        trace.println("Trace file: " + args[0] + ".trc");
        trace.println(numJobs + " Jobs:");
        trace.println(storage);
        trace.println();

        for (int n = 1; n < numJobs; n++) {
            trace.println("*****************************");
            if (n == 1) {
                trace.println("1 processor:");
                trace.println("*****************************");
            } else {
                trace.println(n + " processors:");
                trace.println("*****************************");
            }

            int time = 0; //keep track of the time it takes to process
            int[] wait = new int[numJobs]; //keeps track of jobs to calculate times in the end
            int waitCount = 0; //keeps count for the wait counting array
            boolean emptyProcessor = true; //initialize the processor as true
            boolean jobCheck = false; //keeps track of the jobs being computed

            //
            //    5.      declare and initialize an array of n processor Queues and any
            //            necessary storage Queues
            Queue[] processors = new Queue[n]; //length of the processors
            for (int i = 0; i < n; i++) {
                processors[i] = new Queue();
            }
            Queue transferQ = new Queue(); //move the queue when job is computed
            trace.println("time=" + time);
            trace.println("0: " + storage);
            for (int i = 0; i < n; i++) {
                trace.println((i + 1) + ": " + processors[i]);
            }
            trace.println();

            //    6.      while unprocessed jobs remain  {
            while (storage.isEmpty() == false || emptyProcessor == false) {

                //    7.          determine the time of the next arrival or finish event and
                //                update time
                for ( int i = 0; i < n; i++) {
                    if (processors[i].isEmpty() == false && ((Job)(processors[i].peek())).getFinish() == -1) {
                        ((Job)(processors[i].peek())).computeFinishTime(time); //manipulation to figure wait time
                    }
                }
                if (jobCheck == true) {
                    trace.println("time=" + time);
                    trace.println("0: " + storage + transferQ);
                    for (int i = 0; i < n; i++) {
                        trace.println((i + 1) + ": " + processors[i]);
                    }
                    trace.println();
                    jobCheck = false;
                }

                time++; //keep incrementing the time to check when the job will come into play

                //    8.  complete all processes finishing now
                for (int i = 0; i < n; i++) {
                    if (processors[i].isEmpty() == false) {
                        if (((Job)(processors[i].peek())).getFinish() == time) {
                            wait[waitCount++] = ((Job)(processors[i].peek())).getWaitTime();
                            transferQ.enqueue(((Job)(processors[i].dequeue())));
                            jobCheck = true;
                        }
                    }
                }
                //    9. if there are any jobs arriving now, assign them to i processor
                //       Queue of minimum length and with lowest index in the queue array.
                while ((storage.isEmpty()) == false && ((Job)(storage.peek())).getArrival() == time) {
                    int lowest = 9999;  //arbitrary int for min length of queue
                    int lowestIndex = 0; //lowest index in the queue array
                    for (int i = 0; i < n; i++) {
                        if (processors[i].length() < lowest) {
                            lowest = processors[i].length();
                            lowestIndex = i;
                        }
                    }
                    processors[lowestIndex].enqueue(storage.dequeue());
                    jobCheck = true;
                }
                emptyProcessor = true;
                for (int i = 0; i < n; i++) {
                    if (processors[i].isEmpty() == false) {
                        emptyProcessor = false;
                        break;
                    }
                }

                //    10.     } end loop
            }

            trace.println("time=" + time);
            trace.println("0: " + storage + transferQ);
            for (int i = 0; i < n; i++) trace.println((i + 1) + ": " + processors[i]);

            //    11.     compute the totalWait wait, maximum wait, and avgWait wait for
            //            all Jobs, then reset finish times

            double maxWait = 0; //initialize to doubles in order to calculate the avg
            double totalWait = 0;
            double avgWait = 0;
            for (int index = 0; index < wait.length; index++) {
                totalWait += wait[index];
            }
            for (int i = 0; i < wait.length; i++) {
                if (wait[i] > maxWait) {
                    maxWait = wait[i];
                }
            }

            avgWait = totalWait / wait.length;
            if (n == 1) {
                report.printf("1 processor: totalWait=%.0f, maxWait=%.0f, averageWait=%.2f\n",
                              totalWait, maxWait, avgWait);
            } else {
                report.printf("%d processors: totalWait=%.0f, maxWait=%.0f, averageWait=%.2f\n",
                              n, totalWait, maxWait, avgWait);
            }
            
            for ( int i = 0; i < backup.length() ; i++) {
                backup.enqueue(((Job)(backup.peek())));
                ((Job)(backup.peek())).resetFinishTime();
                storage.enqueue(((Job)(backup.dequeue())));
            }
            transferQ.dequeueAll();

            //    12. } end loop
        }
        //    13. close input and output files
        in.close();
        trace.close();
        report.close();
    }
}