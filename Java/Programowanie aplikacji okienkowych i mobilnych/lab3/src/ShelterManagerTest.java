import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class ShelterManagerTest {

    @Test
    void testAddAndSortShelters() {
        ShelterManager shelterManager = new ShelterManager();

        //schroniska do testow
        shelterManager.addShelter("Shelter A", 50);
        shelterManager.addShelter("Shelter B", 100);
        shelterManager.addShelter("Shelter C", 30);


        List<AnimalShelter> sortedShelters = shelterManager.getSortedShelters();


        assertEquals("Shelter B", sortedShelters.get(0).getShelterName());
        assertEquals("Shelter A", sortedShelters.get(1).getShelterName());
        assertEquals("Shelter C", sortedShelters.get(2).getShelterName());
    }
}