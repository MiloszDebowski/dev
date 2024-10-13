public  class Triangle extends Figure {
    private double a;
    private double b;
    private double c;

    public Triangle(double a, double b, double c){
        if(a <= 0 || b <= 0 || c <= 0 || a + b <= c || b + c <= a || c + a <= b) {
            throw new IllegalArgumentException("WRONG TRIANGLE SIDE LENGTHS INPUT");
        }
            this.a = a;
            this.b = b;
            this.c = c;
    }

    @Override
    public double calculatePerimeter() {
        return a+b+c;
    }

    @Override
    public double calculateArea(){
        double halfPerimeter = (a+b+c)/2;
        return Math.sqrt(halfPerimeter*(halfPerimeter-a)*(halfPerimeter-b)*(halfPerimeter-c));
    }

    @Override
    public void print(){
        System.out.println("TRIANGLE LENGTHS:");
        System.out.println("a = "+a);
        System.out.println("b = "+b);
        System.out.println("c = "+c);
        System.out.println("TRIANGLE PERIMETER = "+calculatePerimeter());
        System.out.println("TRIANGLE AREAArea = "+calculateArea());
    }
}
