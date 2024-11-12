// AnimalShelter.java (zmodyfikowano do dodania obsługi błędów)

import java.util.*;
import java.util.stream.Collectors;

public class AnimalShelter {
    private String shelterName;
    private List<Animal> animalList;
    private int maxCapacity;

    public AnimalShelter(String shelterName, int maxCapacity) {
        this.shelterName = shelterName;
        this.maxCapacity = maxCapacity;
        this.animalList = new ArrayList<>();
    }

    public void addAnimal(Animal animal) throws Exception {
        if (animalList.contains(animal)) {
            throw new Exception("Zwierzę już istnieje.");
        }
        if (animalList.size() >= maxCapacity) {
            throw new Exception("Przekroczono limit schroniska.");
        }
        animalList.add(animal);
    }

    public void removeAnimal(Animal animal) {
        animalList.remove(animal);
    }

    public void adoptAnimal(Animal animal) throws Exception {
        if (animalList.contains(animal)) {
            animal.setCondition(AnimalCondition.W_TRAKCIE_ADOPCJI);
            removeAnimal(animal);
            System.out.println("Zwierzę " + animal.getName() + " zostało zaadoptowane.");
        } else {
            throw new Exception("Zwierzę nie istnieje w schronisku.");
        }
    }

    public List<Animal> getAnimals() {
        return animalList;
    }

    public String getShelterName() {
        return shelterName;
    }

    public int getCapacity() {return maxCapacity;}

}
