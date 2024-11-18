import java.util.Random;

class Obraz {

	private int size_n;
	private int size_m;
	private char[][] tab;
	private char[] tab_symb;
	private int[] histogram;
	private int[] hist_parallel;

	public Obraz(int n, int m) {
		this.size_n = n;
		this.size_m = m;
		tab = new char[n][m];
		tab_symb = new char[94];
		histogram = new int[94];
		hist_parallel = new int[94];

		final Random random = new Random();

		for(int k = 0; k < 94; k++) {
			tab_symb[k] = (char)(k + 33);
		}

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				tab[i][j] = tab_symb[random.nextInt(94)];
				System.out.print(tab[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();

		clear_histogram();
	}

	public void clear_histogram() {
		for(int i = 0; i < 94; i++) {
			histogram[i] = 0;
			hist_parallel[i] = 0;
		}
	}

	public void calculate_histogram() {
		for(int i = 0; i < size_n; i++) {
			for(int j = 0; j < size_m; j++) {
				for(int k = 0; k < 94; k++) {
					if(tab[i][j] == tab_symb[k]) histogram[k]++;
				}
			}
		}
	}

	public void calculate_histogram_parallel(char symbol) {
		for(int i = 0; i < size_n; i++) {
			for(int j = 0; j < size_m; j++) {
				if(tab[i][j] == symbol) {
					hist_parallel[symbol - 33]++;
				}
			}
		}
	}

	public void compare_histograms() {
		for(int i = 0; i < 94; i++) {
			if(histogram[i] != hist_parallel[i]) {
				System.out.println("Niepoprawność dla symbolu: " + tab_symb[i]);
				return;
			}
		}
		System.out.println("Histogramy są zgodne.");
	}

	public void print_histogram() {
		for(int i = 0; i < 94; i++) {
			System.out.println(tab_symb[i] + " " + histogram[i]);
		}
	}

	//dukowanie równoległego
	public synchronized void print_histogram_parallel(char symbol) {
		int count = hist_parallel[symbol - 33];
		System.out.print("Wątek " + symbol + ": " + symbol + " ");
		for(int i = 0; i < count; i++) {
			System.out.print("=");
		}
		System.out.println();
	}
}
