import java.util.Scanner;
public class UserInterface {

    public void createTriangle(Scanner scanner){
        System.out.println("ENTER TRIANGLE SIDE LENGTHS");
        double lengthA = scanner.nextDouble();
        double lengthB = scanner.nextDouble();
        double lengthC = scanner.nextDouble();

        try{
            Triangle triangle = new Triangle(lengthA, lengthB, lengthC);
            triangle.print();
        } catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }

    public void createCircle(Scanner scanner){
        System.out.print("ENTER CIRCLE RADIUS:");
        double radius = scanner.nextDouble();

        try {
            Circle circle = new Circle(radius);
            circle.print();
        } catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }

    public void createRectangle(Scanner scanner){
        System.out.println("ENTER RECTANGLE SIDE LENGTHS");
        double lengthA = scanner.nextDouble();
        double lengthB = scanner.nextDouble();

        try {
            Rectangle rectangle = new Rectangle(lengthA, lengthB);
            rectangle.print();
        } catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }

    public void createPyramid(Scanner scanner){
        System.out.println("CHOOSE PYRAMID BASE");
        System.out.println("1. TRIANGLE");
        System.out.println("2. RECTANGLE");
        System.out.println("3. CIRCLE");

        int choice = scanner.nextInt();
        Figure base = null;
        switch(choice){
            case 1:
                System.out.println("ENTER TRIANGLE SIDE LENGTHS");
                double lengthA = scanner.nextDouble();
                double lengthB = scanner.nextDouble();
                double lengthC = scanner.nextDouble();

                try{
                    base = new Triangle(lengthA, lengthB, lengthC);
                } catch (IllegalArgumentException e){
                    System.out.println(e.getMessage());
                }
                break;
            case 2:
                System.out.println("ENTER RECTANGLE SIDE LENGTHS");
                double width = scanner.nextDouble();
                double height = scanner.nextDouble();

                try {
                    base = new Rectangle(width, height);
                } catch (IllegalArgumentException e){
                    System.out.println(e.getMessage());
                }
                break;
            case 3:
                System.out.print("ENTER CIRCLE RADIUS:");
                double radius = scanner.nextDouble();

                try {
                    base = new Circle(radius);
                } catch (IllegalArgumentException e){
                    System.out.println(e.getMessage());
                }
                break;
            default:
                System.out.println("WRONG CHOICE");
                break;
        }

        System.out.println("ENTER PYRAMID HEIGHT");
        double height = scanner.nextDouble();

        try{
            Pyramid pyramid = new Pyramid(base,height);
            pyramid.print();
        }catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }

    public void start()
    {
        while(true) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("\nCHOOSE FIGURE TO CALCULATE ITS PARAMETERS");
            System.out.println("1. TRIANGLE");
            System.out.println("2. RECTANGLE");
            System.out.println("3. CIRCLE");
            System.out.println("4. PYRAMID");
            System.out.println("5. EXIT");

            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    System.out.println("YOU CHOSE TRIANGLE");
                    createTriangle(scanner);
                    break;
                case 2:
                    System.out.println("YOU CHOSE RECTANGLE");
                    createRectangle(scanner);
                    break;
                case 3:
                    System.out.println("YOU CHOSE CIRCLE");
                    createCircle(scanner);
                    break;
                case 4:
                    System.out.println("YOU CHOSE PYRAMID");
                    createPyramid(scanner);
                    break;
                case 5:
                    System.out.println("EXITING...");
                    return;
                default:
                    System.out.println("INVALID CHOICE");
                    break;
            }
        }
    }
}
