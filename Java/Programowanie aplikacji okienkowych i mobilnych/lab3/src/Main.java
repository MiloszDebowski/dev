import models.ShelterManager;
import ui.LoginModule;
public class Main {
    public static void main(String[] args) {
        ShelterManager shelterManager = new ShelterManager();
        LoginModule loginPanel = new LoginModule(shelterManager);
        loginPanel.showLoginPanel();  // Wyświetlenie panelu logowania
    }
}
