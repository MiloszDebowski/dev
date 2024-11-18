import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Simple_executor_test {

    private static final int NTHREADS = 10;
        
    public static void main(String[] args) {

	Counter counter = new Counter();
	ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

	for (int i = 0; i < 50; i++) {
	    Runnable worker = new CounterPlus(counter);
	    executor.execute(worker);
	}

	// This will make the executor accept no new threads
	// and finish all existing threads in the queue
	executor.shutdown();

	// Wait until all threads finish
	while (!executor.isTerminated()) {}

	System.out.println("Finished all threads");
	System.out.format("\nCounter_1: %d, Counter_2 %d\n\n", 
			  counter.get_c1(), counter.get_c2());
    }
} 
