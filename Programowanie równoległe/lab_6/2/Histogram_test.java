import java.util.Scanner;

class Histogram_test {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		System.out.println("Set image size: n (#rows), m(#columns)");
		int n = scanner.nextInt();
		int m = scanner.nextInt();
		Obraz obraz_1 = new Obraz(n, m);

		obraz_1.calculate_histogram();
		obraz_1.print_histogram();

		System.out.println("\nSet number of threads");
		int num_threads = scanner.nextInt();
		Thread[] threads = new Thread[num_threads];

		int symbolsPerThread = 94 / num_threads;
		for (int i = 0; i < num_threads; i++) {
			int startSymbol = i * symbolsPerThread;
			int endSymbol = (i == num_threads - 1) ? 94 : startSymbol + symbolsPerThread;
			threads[i] = new Thread(new HistogramWorker(obraz_1, startSymbol, endSymbol));
			threads[i].start();
		}

		for (int i = 0; i < num_threads; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		System.out.println("\nParallel Histogram:");
		obraz_1.print_histogram_parallel();
		obraz_1.compare_histograms();
	}
}
