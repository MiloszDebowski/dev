import java.util.Optional;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ShelterManager shelterManager = new ShelterManager();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nMenu główne:");
            System.out.println("1. Dodaj schronisko");
            System.out.println("2. Usuń schronisko");
            System.out.println("3. Wyświetl schroniska");
            System.out.println("4. Znajdź puste schroniska");
            System.out.println("5. Zarządzaj schroniskiem");
            System.out.println("6. Wyjście");
            System.out.print("Wybierz opcję: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    System.out.print("Podaj nazwę schroniska: ");
                    String shelterName = scanner.nextLine();
                    System.out.print("Podaj maksymalną pojemność: ");
                    int capacity = scanner.nextInt();
                    shelterManager.addShelter(shelterName, capacity);
                    break;
                case 2:
                    System.out.print("Podaj nazwę schroniska do usunięcia: ");
                    String nameToRemove = scanner.nextLine();
                    shelterManager.removeShelter(nameToRemove);
                    break;
                case 3:
                    shelterManager.summary();
                    break;
                case 4:
                    System.out.println("Puste schroniska:");
                    shelterManager.findEmpty().forEach(s -> System.out.println(s.getShelterName()));
                    break;
                case 5:
                    System.out.print("Podaj nazwę schroniska do zarządzania: ");
                    String shelterToManage = scanner.nextLine();
                    Optional<AnimalShelter> shelterOpt = shelterManager.getShelter(shelterToManage);

                    if (shelterOpt.isPresent()) {
                        manageShelter(shelterOpt.get(), scanner);
                    } else {
                        System.out.println("Schronisko o nazwie " + shelterToManage + " nie istnieje.");
                    }
                    break;
                case 6:
                    System.out.println("Zamykam program.");
                    return;
                default:
                    System.out.println("Niepoprawna opcja.");
            }
        }
    }

    private static void manageShelter(AnimalShelter shelter, Scanner scanner) {
        while (true) {
            System.out.println("\nZarządzanie schroniskiem: " + shelter.getShelterName());
            System.out.println("1. Dodaj zwierzę");
            System.out.println("2. Usuń zwierzę");
            System.out.println("3. Zaadoptuj zwierzę");
            System.out.println("4. Zmień stan zwierzęcia");
            System.out.println("5. Zmień wiek zwierzęcia");
            System.out.println("6. Liczba zwierząt w określonym stanie");
            System.out.println("7. Sortuj zwierzęta po nazwie");
            System.out.println("8. Sortuj zwierzęta po cenie");
            System.out.println("9. Wyszukaj zwierzę po nazwie");
            System.out.println("10. Wyszukaj zwierzę po części nazwy/gatunku");
            System.out.println("11. Wyświetl podsumowanie");
            System.out.println("12. Wyświetl najdroższe zwierzę");
            System.out.println("13. Powrót do menu głównego");
            System.out.print("Wybierz opcję: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    System.out.print("Podaj imię zwierzęcia: ");
                    String name = scanner.nextLine();
                    System.out.print("Podaj gatunek zwierzęcia: ");
                    String species = scanner.nextLine();
                    System.out.print("Podaj stan zwierzęcia (ZDROWE, CHORE, W_TRAKCIE_ADOPCJI, KWARANTANNA): ");
                    AnimalCondition condition = AnimalCondition.valueOf(scanner.nextLine().toUpperCase());
                    System.out.print("Podaj wiek zwierzęcia: ");
                    int age = scanner.nextInt();
                    System.out.print("Podaj cenę zwierzęcia: ");
                    double price = scanner.nextDouble();
                    scanner.nextLine();
                    shelter.addAnimal(new Animal(name, species, condition, age, price));
                    break;
                case 2:
                    System.out.print("Podaj imię zwierzęcia do usunięcia: ");
                    String removeName = scanner.nextLine();
                    Optional<Animal> animalToRemove = shelter.search(removeName);
                    animalToRemove.ifPresent(shelter::removeAnimal);
                    if (animalToRemove.isEmpty()) {
                        System.out.println("Zwierzę o podanej nazwie nie istnieje.");
                    }
                    break;
                case 3:
                    System.out.print("Podaj imię zwierzęcia do adopcji: ");
                    String adoptName = scanner.nextLine();
                    Optional<Animal> animalToAdopt = shelter.search(adoptName);
                    animalToAdopt.ifPresentOrElse(
                            shelter::adoptAnimal,
                            () -> System.out.println("Zwierzę o podanej nazwie nie istnieje.")
                    );
                    break;
                case 4:
                    System.out.print("Podaj imię zwierzęcia do zmiany stanu: ");
                    String animalName = scanner.nextLine();
                    Optional<Animal> animalToChangeCondition = shelter.search(animalName);
                    if (animalToChangeCondition.isPresent()) {
                        System.out.print("Podaj nowy stan (ZDROWE, CHORE, W_TRAKCIE_ADOPCJI, KWARANTANNA): ");
                        AnimalCondition newCondition = AnimalCondition.valueOf(scanner.nextLine().toUpperCase());
                        shelter.changeCondition(animalToChangeCondition.get(), newCondition);
                    } else {
                        System.out.println("Zwierzę o podanej nazwie nie istnieje.");
                    }
                    break;
                case 5:
                    System.out.print("Podaj imię zwierzęcia do zmiany wieku: ");
                    String animalNameAge = scanner.nextLine();
                    Optional<Animal> animalToChangeAge = shelter.search(animalNameAge);
                    if (animalToChangeAge.isPresent()) {
                        System.out.print("Podaj nowy wiek: ");
                        int newAge = scanner.nextInt();
                        scanner.nextLine();
                        shelter.changeAge(animalToChangeAge.get(), newAge);
                    } else {
                        System.out.println("Zwierzę o podanej nazwie nie istnieje.");
                    }
                    break;
                case 6:
                    System.out.print("Podaj stan zwierząt do zliczenia (ZDROWE, CHORE, W_TRAKCIE_ADOPCJI, KWARANTANNA): ");
                    AnimalCondition countCondition = AnimalCondition.valueOf(scanner.nextLine().toUpperCase());
                    int count = shelter.countByCondition(countCondition);
                    System.out.println("Liczba zwierząt w stanie " + countCondition + ": " + count);
                    break;
                case 7:
                    System.out.println("Zwierzęta posortowane po nazwie:");
                    shelter.sortByName().forEach(Animal::print);
                    break;
                case 8:
                    System.out.println("Zwierzęta posortowane po cenie:");
                    shelter.sortByPrice().forEach(Animal::print);
                    break;
                case 9:
                    System.out.print("Podaj imię zwierzęcia do wyszukania: ");
                    String searchName = scanner.nextLine();
                    shelter.search(searchName).ifPresentOrElse(
                            Animal::print,
                            () -> System.out.println("Zwierzę o podanej nazwie nie istnieje.")
                    );
                    break;
                case 10:
                    System.out.print("Podaj fragment imienia lub gatunku zwierzęcia do wyszukania: ");
                    String partial = scanner.nextLine();
                    System.out.println("Wyniki wyszukiwania:");
                    shelter.searchPartial(partial).forEach(Animal::print);
                    break;
                case 11:
                    System.out.println("Podsumowanie wszystkich zwierząt:");
                    shelter.summary();
                    break;
                case 12:
                    System.out.println("Najdroższe zwierzę:");
                    shelter.max().ifPresentOrElse(
                            Animal::print,
                            () -> System.out.println("Brak zwierząt w schronisku.")
                    );
                    break;
                case 13:
                    return;
                default:
                    System.out.println("Niepoprawna opcja.");
            }
        }
    }
}
