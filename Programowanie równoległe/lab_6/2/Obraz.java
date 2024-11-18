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

		final Random random = new Random();

		for (int k = 0; k < 94; k++) {
			tab_symb[k] = (char) (k + 33); 
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tab[i][j] = tab_symb[random.nextInt(94)];
				System.out.print(tab[i][j] + " ");
			}
			System.out.print("\n");
		}
		System.out.print("\n\n");

		histogram = new int[94];
		hist_parallel = new int[94];
		clear_histogram();
	}

	public void clear_histogram() {
		for (int i = 0; i < 94; i++) histogram[i] = 0;
		for (int i = 0; i < 94; i++) hist_parallel[i] = 0; 
	}

	public void calculate_histogram() {
		for (int i = 0; i < size_n; i++) {
			for (int j = 0; j < size_m; j++) {
				for (int k = 0; k < 94; k++) {
					if (tab[i][j] == tab_symb[k]) histogram[k]++;
				}
			}
		}
	}

	// Metoda do równoległego obliczania histogramu dla bloku symboli
	public void calculate_histogram_parallel_block(int startSymbol, int endSymbol) {
		for (int i = 0; i < size_n; i++) {
			for (int j = 0; j < size_m; j++) {
				for (int k = startSymbol; k < endSymbol; k++) {
					if (tab[i][j] == tab_symb[k]) {
						hist_parallel[k]++;
					}
				}
			}
		}
	}

	// Metoda wypisująca histogram sekwencyjny za pomocą znaków `=`
	public void print_histogram() {
		for (int i = 0; i < 94; i++) {
			System.out.print(tab_symb[i] + " ");
			for (int j = 0; j < histogram[i]; j++) {
				System.out.print("=");
			}
			System.out.print("\n");
		}
	}

	// Metoda wypisująca równoległy histogram za pomocą znaków `=`
	public void print_histogram_parallel() {
		for (int i = 0; i < 94; i++) {
			System.out.print(tab_symb[i] + " ");
			for (int j = 0; j < hist_parallel[i]; j++) {
				System.out.print("=");
			}
			System.out.print("\n");
		}
	}

	public boolean compare_histograms() {
		for (int i = 0; i < 94; i++) {
			if (histogram[i] != hist_parallel[i]) {
				System.out.println("Histograms do not match!");
				return false;
			}
		}
		System.out.println("Histograms match!");
		return true;
	}
}
