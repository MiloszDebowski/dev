// ShelterManager.java (dodano getShelters i editShelter)

import java.util.*;

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

    public List<AnimalShelter> getShelters() {
        return new ArrayList<>(shelters.values());
    }

    public AnimalShelter editShelter(String name) {
        return shelters.get(name);
    }
}
