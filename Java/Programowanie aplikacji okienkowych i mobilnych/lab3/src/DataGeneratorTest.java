
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class DataGeneratorTest {

    @Test
    public void testSingleton() {
        DataGenerator instance1 = DataGenerator.getInstance();
        DataGenerator instance2 = DataGenerator.getInstance();

        assertSame(instance1, instance2);
    }

    @Test
    public void testAddAnimal() {
        AnimalShelter shelter = new AnimalShelter("Test Shelter", 10);

        Animal animal = new Animal("Test Animal", "Dog", AnimalCondition.HEALTHY, 3, 100);

        shelter.addAnimal(animal);

        assertTrue(shelter.getAnimals().contains(animal), "Shelter should contain the animal");
    }


    @Test
    public void testDataGeneration() {
        DataGenerator dataGenerator = DataGenerator.getInstance();

        List<AnimalShelter> shelters = dataGenerator.getShelters();

        assertFalse(shelters.isEmpty(), "List of shelters should not be empty");

        for (AnimalShelter shelter : shelters) {
            assertFalse(shelter.getAnimals().isEmpty(), "Shelter should contain animals");
        }
    }
}
