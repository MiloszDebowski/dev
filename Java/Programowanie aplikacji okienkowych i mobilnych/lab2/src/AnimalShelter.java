// AnimalShelter.java
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

    public void addAnimal(Animal animal) {
        if (animalList.contains(animal)) {
            System.out.println("Animal already exists in the shelter.");
            return;
        }
        if (animalList.size() >= maxCapacity) {
            System.err.println("Shelter capacity exceeded.");
            return;
        }
        animalList.add(animal);
    }

    public void removeAnimal(Animal animal) {
        animalList.remove(animal);
    }

    public void adoptAnimal(Animal animal) {
        if (animalList.contains(animal)) {
            animal.setCondition(AnimalCondition.W_TRAKCIE_ADOPCJI);
            removeAnimal(animal);
            System.out.println("Zwierzę " + animal.getName() + " zostało zaadoptowane.");
        } else {
            System.out.println("Zwierzę nie znajduje się w schronisku.");
        }
    }

    public void changeCondition(Animal animal, AnimalCondition condition) {
        if (animalList.contains(animal)) {
            animal.setCondition(condition);
        }
    }

    public void changeAge(Animal animal, int age) {
        if (animalList.contains(animal)) {
            animal.setAge(age);
        }
    }

    public int countByCondition(AnimalCondition condition) {
        return (int) animalList.stream()
                .filter(animal -> animal.getCondition() == condition)
                .count();
    }

    public List<Animal> sortByName() {
        return animalList.stream()
                .sorted(Comparator.comparing(Animal::getName))
                .collect(Collectors.toList());
    }

    public List<Animal> sortByPrice() {
        return animalList.stream()
                .sorted(Comparator.comparingDouble(Animal::getPrice))
                .collect(Collectors.toList());
    }

    public Optional<Animal> search(String name) {
        return animalList.stream()
                .filter(animal -> animal.getName().equalsIgnoreCase(name))
                .findFirst();
    }

    public List<Animal> searchPartial(String searchTerm) {
        return animalList.stream()
                .filter(animal -> animal.getName().contains(searchTerm) || animal.getSpecies().contains(searchTerm))
                .collect(Collectors.toList());
    }

    public void summary() {
        animalList.forEach(Animal::print);
    }

    public Optional<Animal> max() {
        return animalList.stream().max(Comparator.comparing(Animal::getPrice));
    }

    public boolean isEmpty() {
        return animalList.isEmpty();
    }

    public String getShelterName() {
        return shelterName;
    }

    public int getAnimalCount() {
        return animalList.size();
    }

    public int getMaxCapacity() {
        return maxCapacity;
    }
}
