public class Circle extends Figure {
    private final double radius;

    public double getRadius() {
        return radius;
    }

    public Circle(double radius) {
        if(radius <= 0) {
            throw new IllegalArgumentException("RADIUS MUST BE GREATER THAN 0");
        }

        this.radius = radius;
    }

    @Override
    public double calculatePerimeter() {
        return 2 * Math.PI * radius;
    }

    @Override
    public double calculateArea() {
        return Math.PI * radius * radius;
    }

    @Override
    public void print()
    {
        System.out.println("CIRCLE'S RADIUS = " + radius);
        System.out.println("CIRCLE'S PERIMETER = " + calculatePerimeter());
        System.out.println("CIRCLE'S AREA= " + calculateArea());
    }
}
