import java.util.*;
import java.util.stream.Collectors;

enum AnimalCondition {
    HEALTHY,
    SICK,
    IN_ADOPTION,
    QUARANTINE
}

class Animal implements Comparable<Animal> {
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

    public String getName() {
        return name;
    }

    public String getSpecies() {
        return species;
    }

    public AnimalCondition getCondition() {
        return condition;
    }

    public int getAge() {
        return age;
    }

    public double getPrice() {
        return price;
    }

    public void setCondition(AnimalCondition condition) {
        this.condition = condition;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return String.format("Animal{name='%s', species='%s', condition=%s, age=%d, price=%.2f}",
                name, species, condition, age, price);
    }

    @Override
    public int compareTo(Animal other) {
        return this.name.compareTo(other.name);
    }
}

class AnimalShelter {
    private String shelterName;
    private List<Animal> animalList;
    private int maxCapacity;

    public AnimalShelter(String shelterName, int maxCapacity) {
        this.shelterName = shelterName;
        this.maxCapacity = maxCapacity;
        this.animalList = new ArrayList<>();
    }

    public void addAnimal(Animal animal) {
        if (animalList.size() >= maxCapacity) {
            System.err.println("Shelter capacity exceeded.");
            return;
        }
        if (animalList.contains(animal)) {
            System.out.println("Animal already exists in the shelter.");
            return;
        }
        animalList.add(animal);
    }

    public boolean removeAnimal(Animal animal) {
        return animalList.remove(animal); // Usuwa zwierzę, jeśli istnieje
    }

    public void adoptAnimal(Animal animal) {
        // Sprawdza, czy zwierzę jest na liście i adoptuje je, usuwając z listy schroniska
        if (animalList.contains(animal)) {
            animal.setCondition(AnimalCondition.IN_ADOPTION);
            removeAnimal(animal); // Usuwamy z listy
            System.out.println(animal.getName() + " has been adopted.");
        }
    }

    public void changeCondition(Animal animal, AnimalCondition condition) {
        if (animalList.contains(animal)) {
            animal.setCondition(condition);
        }
    }

    public void changeAge(Animal animal, int newAge) {
        if (animalList.contains(animal)) {
            animal.setAge(newAge);
        }
    }

    public long countByCondition(AnimalCondition condition) {
        return animalList.stream().filter(a -> a.getCondition() == condition).count();
    }

    public List<Animal> sortByName() {
        return animalList.stream().sorted().collect(Collectors.toList());
    }

    public List<Animal> sortByPrice() {
        return animalList.stream().sorted(Comparator.comparingDouble(Animal::getPrice)).collect(Collectors.toList());
    }

    public List<Animal> search(String name) {
        return animalList.stream()
                .filter(a -> a.getName().equals(name))
                .collect(Collectors.toList());
    }

    public List<Animal> searchPartial(String query) {
        return animalList.stream()
                .filter(a -> a.getName().contains(query) || a.getSpecies().contains(query))
                .collect(Collectors.toList());
    }

    public void summary() {
        animalList.forEach(System.out::println);
    }

    public Animal maxPrice() {
        return Collections.max(animalList, Comparator.comparingDouble(Animal::getPrice));
    }

    public boolean isEmpty() {
        return animalList.isEmpty();
    }

    public int getAnimalCount() {
        return animalList.size();
    }

    public int getMaxCapacity() {
        return maxCapacity;
    }

    public String getShelterName() {
        return shelterName;
    }

    public List<Animal> getAnimals() {
        return new ArrayList<>(animalList); // Zwraca nową listę, aby uniknąć modyfikacji oryginalnej
    }
}


class ShelterManager {
    private Map<String, AnimalShelter> shelters;

    public ShelterManager() {
        shelters = new HashMap<>();
    }

    public void addShelter(String name, int capacity) {
        shelters.put(name, new AnimalShelter(name, capacity));
    }

    public void removeShelter(String name) {
        shelters.remove(name);
    }

    public List<AnimalShelter> findEmpty() {
        return shelters.values().stream().filter(AnimalShelter::isEmpty).collect(Collectors.toList());
    }

    public void summary() {
        shelters.forEach((shelterName, shelter) -> {
            double percentageFilled = (double) shelter.getAnimalCount() / shelter.getMaxCapacity() * 100;
            System.out.printf("Shelter: %s, Capacity Filled: %.2f%%\n", shelterName, percentageFilled);
        });
    }

    //sortowanie schronisk
    public List<AnimalShelter> getSortedShelters() {
        return shelters.values().stream()
                .sorted(Comparator.comparingInt(AnimalShelter::getMaxCapacity).reversed())
                .collect(Collectors.toList());
    }

    public Map<String, AnimalShelter> getShelters() {
        return shelters;
    }
}