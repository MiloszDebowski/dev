import java.util.concurrent.Callable;
import java.text.DecimalFormat;

public class Calka_callable implements Callable<Double>{  
//public class Calka_callable{
    
    private double dx;
    private double xp;
    private double xk;
    private int N;
    
    public Calka_callable(double xp, double xk, double dx) {
	this.xp = xp;
	this.xk = xk;
	this.N = (int) Math.ceil((xk-xp)/dx);
	this.dx = (xk-xp)/N;

	DecimalFormat df = new DecimalFormat("#.################");
	System.out.println("Creating an instance of Calka_callable");
	System.out.println("xp = " + xp + ", xk = " + xk + ", N = " + N);
	System.out.println("dx requested = " + df.format(dx) + ", dx final = " + df.format(this.dx));
	
    }
    
    private double getFunction(double x) {
	return Math.sin(x);
    }
    
    public double compute_integral() {
	double calka = 0;
	int i;
	for(i=0; i<N; i++){
	    double x1 = xp+i*dx;
	    double x2 = x1+dx;
	    calka += ((getFunction(x1) + getFunction(x2))/2.)*dx;
	}

	//System.out.println("Calka czastkowa: " + calka);
	return calka;
    }
    public Double call() throws Exception {  
    	return compute_integral();
    }    
}
