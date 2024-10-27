import java.util.*;
import java.util.stream.Collectors;

public class ShelterManager {
    private Map<String, AnimalShelter> shelters;

    public ShelterManager() {
        this.shelters = new HashMap<>();
    }

    public void addShelter(String name, int capacity) {
        shelters.put(name, new AnimalShelter(name, capacity));
    }


    public void removeShelter(String name) {
        shelters.remove(name);
    }

    public List<AnimalShelter> findEmpty() {
        return shelters.values().stream()
                .filter(AnimalShelter::isEmpty)
                .collect(Collectors.toList());
    }

    public void summary() {
        shelters.values().forEach(shelter -> {
            double occupancyRate = (double) shelter.getAnimalCount() / shelter.getMaxCapacity() * 100;
            System.out.printf("Shelter: %s, Occupancy: %.2f%%\n", shelter.getShelterName(), occupancyRate);
        });
    }

    public Optional<AnimalShelter> getShelter(String name) {
        return Optional.ofNullable(shelters.get(name));
    }
}
