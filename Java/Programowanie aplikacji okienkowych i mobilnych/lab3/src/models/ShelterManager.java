package models;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ShelterManager {
    private Map<String, AnimalShelter> shelters = new HashMap<>();

    public void addShelter(String name, int capacity) {
        shelters.put(name, new AnimalShelter(name, capacity));
    }

    public List<AnimalShelter> getShelters() {
        return new ArrayList<>(shelters.values());
    }
}
