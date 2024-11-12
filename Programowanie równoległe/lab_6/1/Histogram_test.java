import java.util.Scanner;

class Histogram_test {

	public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);

		System.out.println("Podaj rozmiar obrazu: n (wiersze), m (kolumny)");
		int n = scanner.nextInt();
		int m = scanner.nextInt();

		// Tworzenie obrazu i obliczanie histogramu sekwencyjnie
		Obraz obraz_1 = new Obraz(n, m);
		obraz_1.calculate_histogram();
		obraz_1.print_histogram();

		// Ustal liczbe wątków odpowiadających symbolom
		System.out.println("Uruchamianie wersji równoległej");

		// Tworzenie i uruchamianie wątków dla każdego znaku ASCII
		WatekSymbol[] watekArray = new WatekSymbol[94];
		for(int i = 0; i < 94; i++) {
			watekArray[i] = new WatekSymbol(obraz_1, (char)(i + 33));
			watekArray[i].start();
		}

		// Oczekiwanie na zakończenie wątków
		for (WatekSymbol watek : watekArray) {
			try {
				watek.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		// Porównanie wyników sekwencyjnych i równoległych
		obraz_1.compare_histograms();
	}
}
