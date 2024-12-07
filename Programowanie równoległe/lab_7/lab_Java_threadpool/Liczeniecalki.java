import java.util.concurrent.*;
import java.util.List;
import java.util.ArrayList;

public class Liczeniecalki {

    private static final int NTHREADS = 10; 
    public static void main(String[] args) {
    	ExecutorService executor = Executors.newFixedThreadPool(NTHREADS); //tworzenie wykonawcy o zadanej puli wątków
    	List<Future<Double>> listaWynikow = new ArrayList<Future<Double>>(); // lista w ktorej zapisujemy obiekty future

	//Przedział
	double start = 0;
	double end = Math.PI;

	double task = 10; //ilość zadań
	double dx = 0.000001; //dokładność

	double przedzialPerZadanie = (end - start) / task; //przedział dla każdego pojedynczego zadania

	double kX = przedzialPerZadanie; //zmienna pomocnicza

	for (double pX = start; pX < end; pX += przedzialPerZadanie){

		if(kX > end){kX = end;}  // w przypadku bledu zaokraglen ten if to wychwyci

		Callable<Double> calkacallable = new Calka_callable(pX, kX, dx);
		Future<Double> future = executor.submit(calkacallable);
		listaWynikow.add(future);
		kX += przedzialPerZadanie; //przejscie na inny przedział dla kolejnego wątku z puli
	}

	double wynik = 0;

	for (Future<Double> future : listaWynikow){
		try {
		wynik += future.get(); // uzyskanie wyników metody call
		}
		catch (InterruptedException | ExecutionException e){
			e.printStackTrace();
		}
		
	}
		executor.shutdown(); //zakończenie pracy wykonwacy, przestaje przyjmować wątki

	// Wait until all threads finish
	while (!executor.isTerminated()) {} //oczekiwanie na zakończenie pracy wątków
	System.out.println("Finished all threads");
	System.out.println("Wynik calkowania rownolegle: " + wynik);
	
    }
   }
