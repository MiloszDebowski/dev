import java.util.Scanner;

class Histogram_test {

	public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);

		System.out.println("Podaj rozmiar obrazu: n (wiersze), m (kolumny)");
		int n = scanner.nextInt();
		int m = scanner.nextInt();

		Obraz obraz_1 = new Obraz(n, m);
		obraz_1.calculate_histogram();
		obraz_1.print_histogram();

		System.out.println("Uruchamianie wersji równoległej");

		WatekSymbol[] watekArray = new WatekSymbol[94];
		for(int i = 0; i < 94; i++) {
			watekArray[i] = new WatekSymbol(obraz_1, (char)(i + 33));
			watekArray[i].start();
		}

		for (WatekSymbol watek : watekArray) {
			try {
				watek.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		obraz_1.compare_histograms();
	}
}
