public class CounterPlus implements Runnable {
    
  private Counter counter;

  public CounterPlus(Counter counter) {
    this.counter = counter;
  }

  public void run() {

    for (int i = 0; i < 10; i++) {

	counter.inc1();
	counter.inc2();
	counter.inc1();
	counter.inc2();

    }
  }
}
