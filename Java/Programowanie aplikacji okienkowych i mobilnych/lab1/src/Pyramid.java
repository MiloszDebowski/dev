public class Pyramid implements Printable{
    private final Figure base;
    private final double height;

    public Pyramid(Figure base, double height) {
        if(height <= 0) {
        throw new IllegalArgumentException("HEIGHT MUST BE GREATER THAN 0");
        }

        this.base = base;
        this.height = height;
    }

    public double surfaceArea(){
        if(base instanceof Circle) {
            double radius = ((Circle) base).getRadius();
            double sideHeight = Math.sqrt(((radius)*(radius)+(height*height)));
            return Math.PI * radius * (radius + sideHeight);
        } else if (base instanceof Rectangle) {
            double sideHeightA = Math.sqrt((((Rectangle) base).getB()/2)*(((Rectangle) base).getB()/2)+(height*height));
            double sideHeightB = Math.sqrt((((Rectangle) base).getA()/2)*(((Rectangle) base).getA()/2)+(height*height));
            return base.calculateArea()+ ((Rectangle) base).getA()*sideHeightA+ ((Rectangle) base).getB()*sideHeightB;
        }else{
            return 0;//Nie wiem jak
        }
    }

    public double calculateVolume(){
        return (1.0/3)* base.calculateArea() *height;
    }


    @Override
    public void print() {
        System.out.println("\nFIGURE PARAMETERS:");
        base.print();
        System.out.println("HEIGHT = " + height);
        System.out.println("VOLUME = " + calculateVolume());
        System.out.println("SURFACE AREA = " + surfaceArea());
    }
}
