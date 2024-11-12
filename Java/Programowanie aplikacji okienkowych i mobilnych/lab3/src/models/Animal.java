package models;

public class Animal {
    private String name;
    private String species;
    private AnimalCondition condition;
    private int age;
    private double price;

    public Animal(String name, String species, AnimalCondition condition, int age, double price) {
        this.name = name;
        this.species = species;
        this.condition = condition;
        this.age = age;
        this.price = price;
    }

    // Getters and setters
    public String getName() { return name; }
    public String getSpecies() { return species; }
    public AnimalCondition getCondition() { return condition; }
    public void setCondition(AnimalCondition condition) { this.condition = condition; }
    public int getAge() { return age; }
    public void setAge(int age) { this.age = age; }
    public double getPrice() { return price; }
}

