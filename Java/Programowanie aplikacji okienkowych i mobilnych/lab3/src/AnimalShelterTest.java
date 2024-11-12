import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class AnimalShelterTest {

    @Test
    public void testAddAnimal() {

        AnimalShelter shelter = new AnimalShelter("Test Shelter", 10);

        Animal animal = new Animal("Test Animal", "Dog", AnimalCondition.HEALTHY, 3, 100);

        shelter.addAnimal(animal);

        assertTrue(shelter.getAnimals().contains(animal), "Shelter should contain the animal");
    }

    @Test
    public void testRemoveAnimal() {
        AnimalShelter shelter = new AnimalShelter("Test Shelter", 10);

        Animal animal = new Animal("Test Animal", "Dog", AnimalCondition.HEALTHY, 3, 100);
        shelter.addAnimal(animal);

        shelter.removeAnimal(animal);

        assertFalse(shelter.getAnimals().contains(animal), "Shelter should not contain the animal after removal");
    }
}
