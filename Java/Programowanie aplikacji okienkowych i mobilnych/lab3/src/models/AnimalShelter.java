package models;
import java.util.*;
import java.util.List;


public class AnimalShelter {
    private String shelterName;
    private int capacity;
    private List<Animal> animals;

    public AnimalShelter(String shelterName, int capacity) {
        this.shelterName = shelterName;
        this.capacity = capacity;
        this.animals = new ArrayList<>();
    }

    public void addAnimal(Animal animal) {
        if (animals.size() < capacity) animals.add(animal);
        else System.out.println("Brak miejsca w schronisku.");
    }

    public void removeAnimal(Animal animal) {
        animals.remove(animal);
    }

    public String getShelterName() { return shelterName; }
    public List<Animal> getAnimals() { return animals; }

    public int  getCapacity() {return capacity;
    }
}
