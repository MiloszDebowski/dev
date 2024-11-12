public class Main {
    public static void main(String[] args) {
        ShelterManager shelterManager = new ShelterManager();
        MainGUI mainGUI = new MainGUI(shelterManager);
        mainGUI.displayLogin();
    }
}
