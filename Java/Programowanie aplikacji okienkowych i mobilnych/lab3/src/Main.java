import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        ShelterManager shelterManager = new ShelterManager();
        SwingUtilities.invokeLater(() -> {
            LoginView loginView = new LoginView(shelterManager);
            loginView.setVisible(true);
        });
    }
}

