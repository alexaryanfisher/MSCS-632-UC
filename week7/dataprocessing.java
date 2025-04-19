// Data Sharing System, Java.
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Level;
import java.util.logging.Logger;

// Task Class structure.
class Task {
    private final int id;
    private final String data;

    public Task(int id, String data){
        this.id = id;
        this.data = data;
    }

    public int getId() {
        return id;
    }

    public String getData() {
        return data;
    }

    // Processing time.
    public String process(){
        try {
            //Simulate processing time
            Thread.sleep(100);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        return data + " = Processed data for task " + id + ".";
    }
}

// Result Class structure.
class Result {
    private final int taskId;
    private final String resultData;

    public Result(int taskId, String resultData){
        this.taskId = taskId;
        this.resultData = resultData;
    }
    @Override
    public String toString() {
        return "{ TaskID: " + taskId +
                ", ResultData: " + resultData +
                " }";
    }
}

// Worker class with task processing.
class Worker implements Runnable{
    private static final Logger logger = Logger.getLogger(Worker.class.getName());
    private final BlockingQueue<Task> tasks;
    private final List<Result> results;
    private final Lock resultsLock;

    public Worker(BlockingQueue<Task> tasks, List<Result> results, Lock resultsLock){
        this.tasks = tasks;
        this.results = results;
        this.resultsLock = resultsLock;
    }
    @Override
    public void run() {
        String threadName = Thread.currentThread().getName();
        String workerID = "";
        String [] parts = threadName.split("-");
        if (parts.length > 3 && parts[2].equals("thread")) {
            // Extracting worker ID from thread name.
            workerID = parts[3];
        } else {
            workerID = threadName;
        }
        logger.log(Level.INFO, "Worker {0} started processing tasks.", workerID);
        // Process tasks until interrupted or exit signal is received.
        try {
            while (true) {
                // Poll with timeout to allow for exiting.
                Task task = tasks.poll(1, TimeUnit.SECONDS);
                if (task == null) {
                    logger.log(Level.INFO, "Worker {0} finished.", workerID);
                    break; // Exit if no task is available.
                }
                try {
                    String processingResult = task.process();
                    Result result = new Result(task.getId(), processingResult);
                    // Locking to ensure thread-safe access to results.
                    resultsLock.lock();
                    try {
                        results.add(result);
                        logger.log(Level.INFO, "{0} processed task {1}.", new Object[]{workerID, task.getId()});
                    } finally {
                        resultsLock.unlock();
                    }
                // Exception handling for task processing.
                } catch (Exception e) {
                    logger.log(Level.SEVERE, "{0} encountered an error processing task " + task.getId() + "from " + workerID, e);               
                }
            }
        } catch (InterruptedException e) {
            logger.log(Level.WARNING, "{0} was interrupted.", workerID);
            Thread.currentThread().interrupt();
        }
    }
}

// Main class for data sharing system.
public class dataprocessing {
    private static final Logger logger = Logger.getLogger(dataprocessing.class.getName());
    private static final int numWorkers = 10;
    private static final int numTasks = 20;
    private static final String outputFile = "results_java.txt";

    public static void main (String[] args) {
        BlockingQueue<Task> tasks = new LinkedBlockingQueue<>();
        List<Result> results = new ArrayList<>();
        Lock resultsLock = new ReentrantLock();

        // Create and start worker threads.
        ExecutorService executor = Executors.newFixedThreadPool(numWorkers);
        for (int i = 0; i < numWorkers; i++) {
            executor.execute(new Worker(tasks, results, resultsLock));
        }

        // Generate and add tasks to the queue.
        for (int i = 0; i < numTasks; i++) {
            Task task = new Task(i, "Data " + i);
            tasks.offer(task);
            logger.log(Level.INFO, "Task {0} added to the tasks list.", task.getId());
        }

        // Shutdown executor service.
        executor.shutdown();
        try {
            if (!executor.awaitTermination(10, TimeUnit.SECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            logger.log(Level.SEVERE, "Executor service interrupted during shutdown.", e);
            Thread.currentThread().interrupt();
        }

        // Writing and saving results to file.
        try (FileWriter writer = new FileWriter(outputFile)) {
            resultsLock.lock();
            try{
                for (Result result : results) {
                writer.write(result.toString() + "\n");
                }
            } finally {
                resultsLock.unlock();
            }
            //Confirming results written to file.
            logger.log(Level.INFO, "Results have been written to {0}.", outputFile);
        } catch (IOException e) {
            logger.log(Level.SEVERE, "Error writing results to file.", e);
        }
        // Confirming tasks completed and results saved.
        logger.log(Level.INFO, "All tasks processed and results written to file.");
    }
}
