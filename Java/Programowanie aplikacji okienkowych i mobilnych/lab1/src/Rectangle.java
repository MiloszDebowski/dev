public class Rectangle extends Figure {
    private final double a;
    private final double b;

    public double getA() {
        return a;
    }

    public double getB() {
        return b;
    }

    public Rectangle(double a, double b) {
        if(a<=0 || b<=0) {
            throw new IllegalArgumentException("LENGTHS MUST BE GREATER THAN 0");
        }

        this.a = a;
        this.b = b;
    }

    @Override
    public double calculatePerimeter() {
        return 2*(a+b);
    }

    @Override
    public double calculateArea() {
        return a*b;
    }

    @Override
    public void print(){
        System.out.println("RECTANGLE'S LENGTHS:");
        System.out.println("a = " + a);
        System.out.println("b = " + b);
        System.out.println("RECTANGLE'S PERIMETER = " + calculatePerimeter());
        System.out.println("RECTANGLE'S AREA = " + calculateArea());
    }
}
