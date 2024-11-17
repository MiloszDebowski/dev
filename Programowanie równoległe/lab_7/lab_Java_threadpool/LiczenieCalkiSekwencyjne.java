
public class LiczenieCalkiSekwencyjne {
	public static void main(String[] args) {
   		double start = 0;
		double end= Math.PI;
		double dx = 0.000001;
		Calka_callable calka = new Calka_callable(start, end, dx);
		System.out.println("Wynik calki sekwencyjnie: " + calka.compute_integral());
   	}
}
